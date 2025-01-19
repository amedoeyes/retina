module;

#include <arpa/inet.h>
#include <cerrno>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

export module retina.socket;

import std;

export namespace retina::socket {

enum class type : std::uint8_t {
	stream = SOCK_STREAM,
	dgram = SOCK_DGRAM
};

class socket {
public:
	socket(const socket&) = delete;
	socket(socket&&) = default;
	auto operator=(const socket&) -> socket& = delete;
	auto operator=(socket&&) -> socket& = default;
	explicit socket(type type) : type_(type) {}
	~socket() { close(); }

	void bind(std::string_view ip, std::string_view port) {
		const auto hints = addrinfo{
			.ai_flags = AI_PASSIVE,
			.ai_family = AF_UNSPEC,
			.ai_socktype = std::to_underlying(type_),
		};

		auto* info = static_cast<addrinfo*>(nullptr);
		const auto res = getaddrinfo(ip.data(), port.data(), &hints, &info);
		if (res != 0) throw std::runtime_error(std::format("getaddrinfo: {}", gai_strerror(res)));
		for (auto* curr = info; curr != nullptr; curr = curr->ai_next) {
			fd_ = ::socket(curr->ai_family, curr->ai_socktype, curr->ai_protocol);
			if (fd_ == -1) continue;
			const auto res = ::bind(fd_, curr->ai_addr, curr->ai_addrlen);
			if (res == -1) {
				close();
				continue;
			}
			std::memcpy(&addr_, curr->ai_addr, curr->ai_addrlen);
			break;
		}
		freeaddrinfo(info);
		if (fd_ == -1) throw std::runtime_error(std::format("failed to bind socket: {}", std::strerror(errno)));
	}

	void connect(std::string_view ip, std::string_view port) {
		const auto hints = addrinfo{
			.ai_flags = AI_PASSIVE,
			.ai_family = AF_UNSPEC,
			.ai_socktype = std::to_underlying(type_),
		};
		auto* info = static_cast<addrinfo*>(nullptr);
		const auto res = getaddrinfo(ip.data(), port.data(), &hints, &info);
		if (res != 0) throw std::runtime_error(std::format("getaddrinfo: {}", gai_strerror(res)));
		for (auto* curr = info; curr != nullptr; curr = curr->ai_next) {
			fd_ = ::socket(curr->ai_family, curr->ai_socktype, curr->ai_protocol);
			if (fd_ == -1) continue;
			const auto res = ::bind(fd_, curr->ai_addr, curr->ai_addrlen);
			if (res == -1) {
				close();
				continue;
			}
			std::memcpy(&addr_, curr->ai_addr, curr->ai_addrlen);
			break;
		}
		freeaddrinfo(info);
		if (fd_ == -1) throw std::runtime_error(std::format("failed to connect socket: {}", std::strerror(errno)));
	}

	auto listen(std::int32_t backlog = 20) const -> void {
		const auto res = ::listen(fd_, backlog);
		if (res == -1) throw std::runtime_error(std::format("failed to listen on socket: {}", std::strerror(errno)));
	}

	auto accept() -> socket {
		auto client_addr = sockaddr_storage{};
		auto client_addr_len = socklen_t(sizeof(client_addr));
		auto fd = ::accept(fd_, std::bit_cast<sockaddr*>(&client_addr), &client_addr_len);
		if (fd == -1) throw std::runtime_error(std::format("failed to accept client connection: {}", std::strerror(errno)));
		auto client_socket = socket(type_);
		client_socket.fd_ = fd;
		std::memcpy(&client_socket.addr_, &client_addr, client_addr_len);
		return client_socket;
	}

	[[nodiscard]] auto send(std::span<const std::byte> data) const -> std::uint32_t {
		const auto res = ::send(fd_, data.data(), data.size(), 0);
		if (res == -1) throw std::runtime_error(std::format("failed to send data: {}", std::strerror(errno)));
		return res;
	}

	[[nodiscard]] auto receive(std::uint64_t max_size) const -> std::optional<std::vector<std::byte>> {
		std::vector<std::byte> buffer(max_size);
		ssize_t bytes_received = ::recv(fd_, buffer.data(), buffer.size(), 0);
		if (bytes_received == 0) return std::nullopt;
		if (bytes_received == -1) throw std::runtime_error(std::format("failed to receive data: {}", std::strerror(errno)));
		buffer.resize(bytes_received);
		return buffer;
	}

	auto close() -> void {
		::close(fd_);
		fd_ = -1;
	}

	[[nodiscard]] auto fd() const -> std::int32_t { return fd_; }

	[[nodiscard]] auto ip() const -> std::string {
		auto ipstr = std::string();
		const void* addr_ptr = nullptr;
		switch (addr_.ss_family) {
			case AF_INET:
				ipstr.resize(INET_ADDRSTRLEN);
				addr_ptr = &std::bit_cast<const sockaddr_in*>(&addr_)->sin_addr;
				break;
			case AF_INET6:
				ipstr.resize(INET6_ADDRSTRLEN);
				addr_ptr = &std::bit_cast<const sockaddr_in6*>(&addr_)->sin6_addr;
				break;
			default: throw std::runtime_error("unknown address family");
		}
		inet_ntop(addr_.ss_family, addr_ptr, ipstr.data(), ipstr.size());
		return ipstr;
	}

	[[nodiscard]] auto port() const -> std::uint16_t {
		switch (addr_.ss_family) {
			case AF_INET: return ntohs(std::bit_cast<const sockaddr_in*>(&addr_)->sin_port);
			case AF_INET6: return ntohs(std::bit_cast<const sockaddr_in6*>(&addr_)->sin6_port);
			default: throw std::runtime_error("unknown address family");
		}
	}

private:
	type type_;
	std::int32_t fd_ = -1;
	sockaddr_storage addr_{};
};

} // namespace retina::socket
