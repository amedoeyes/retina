module;

#include <arpa/inet.h>
#include <cassert>
#include <fcntl.h>
#include <liburing.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

export module retina.io_uring;

import std;

export namespace retina::io_uring {

class ring;

enum class sqe_flags : std::int8_t {
	fixed_file = IOSQE_FIXED_FILE_BIT,
	io_drain = IOSQE_IO_DRAIN_BIT,
	io_link = IOSQE_IO_LINK_BIT,
	io_hardlink = IOSQE_IO_HARDLINK_BIT,
	async = IOSQE_ASYNC_BIT,
	buffer_select = IOSQE_BUFFER_SELECT_BIT,
	cqe_skip_success = IOSQE_CQE_SKIP_SUCCESS_BIT,
};

class sqe {
	friend ring;

public:
	sqe() = delete;

	[[nodiscard]] auto raw() -> io_uring_sqe* { return raw_; }

	auto set_data(void* data) -> void { io_uring_sqe_set_data(raw_, data); }
	auto set_data64(std::int64_t data) -> void { io_uring_sqe_set_data64(raw_, data); }
	auto set_flags(std::uint32_t flags) -> void { io_uring_sqe_set_flags(raw_, flags); }

	auto prepare_accept(std::int32_t fd, sockaddr* addr, socklen_t* addrlen, std::int32_t flags) -> void {
		io_uring_prep_accept(raw_, fd, addr, addrlen, flags);
	}

	auto prepare_accept_direct() -> void { assert(false && "TODO"); }
	auto prepare_bind() -> void { assert(false && "TODO"); }
	auto prepare_cancel() -> void { assert(false && "TODO"); }
	auto prepare_cancel64() -> void { assert(false && "TODO"); }
	auto prepare_cancel_fd() -> void { assert(false && "TODO"); }
	auto prepare_close() -> void { assert(false && "TODO"); }
	auto prepare_close_direct() -> void { assert(false && "TODO"); }
	auto prepare_cmd_discard() -> void { assert(false && "TODO"); }
	auto prepare_cmd_sock() -> void { assert(false && "TODO"); }
	auto prepare_connect() -> void { assert(false && "TODO"); }
	auto prepare_epoll_ctl() -> void { assert(false && "TODO"); }
	auto prepare_fadvise() -> void { assert(false && "TODO"); }
	auto prepare_fadvise64() -> void { assert(false && "TODO"); }
	auto prepare_fallocate() -> void { assert(false && "TODO"); }
	auto prepare_fgetxattr() -> void { assert(false && "TODO"); }
	auto prepare_files_update() -> void { assert(false && "TODO"); }
	auto prepare_fixed_fd_install() -> void { assert(false && "TODO"); }
	auto prepare_fsetxattr() -> void { assert(false && "TODO"); }
	auto prepare_fsync() -> void { assert(false && "TODO"); }
	auto prepare_ftruncate() -> void { assert(false && "TODO"); }
	auto prepare_futex_wait() -> void { assert(false && "TODO"); }
	auto prepare_futex_waitv() -> void { assert(false && "TODO"); }
	auto prepare_futex_wake() -> void { assert(false && "TODO"); }
	auto prepare_getxattr() -> void { assert(false && "TODO"); }
	auto prepare_link() -> void { assert(false && "TODO"); }
	auto prepare_link_timeout() -> void { assert(false && "TODO"); }
	auto prepare_linkat() -> void { assert(false && "TODO"); }
	auto prepare_listen() -> void { assert(false && "TODO"); }
	auto prepare_madvise() -> void { assert(false && "TODO"); }
	auto prepare_madvise64() -> void { assert(false && "TODO"); }
	auto prepare_mkdir() -> void { assert(false && "TODO"); }
	auto prepare_mkdirat() -> void { assert(false && "TODO"); }
	auto prepare_msg_ring() -> void { assert(false && "TODO"); }
	auto prepare_msg_ring_cqe_flags() -> void { assert(false && "TODO"); }
	auto prepare_msg_ring_fd() -> void { assert(false && "TODO"); }
	auto prepare_msg_ring_fd_alloc() -> void { assert(false && "TODO"); }
	auto prepare_multishot_accept() -> void { assert(false && "TODO"); }
	auto prepare_multishot_accept_direct() -> void { assert(false && "TODO"); }

	auto prepare_nop() -> void { io_uring_prep_nop(raw_); }

	auto prepare_open() -> void { assert(false && "TODO"); }
	auto prepare_open_direct() -> void { assert(false && "TODO"); }
	auto prepare_openat() -> void { assert(false && "TODO"); }
	auto prepare_openat2() -> void { assert(false && "TODO"); }
	auto prepare_openat2_direct() -> void { assert(false && "TODO"); }
	auto prepare_openat_direct() -> void { assert(false && "TODO"); }
	auto prepare_poll_add() -> void { assert(false && "TODO"); }
	auto prepare_poll_multishot() -> void { assert(false && "TODO"); }
	auto prepare_poll_remove() -> void { assert(false && "TODO"); }
	auto prepare_poll_update() -> void { assert(false && "TODO"); }
	auto prepare_provide_buffers() -> void { assert(false && "TODO"); }

	auto prepare_read(std::int32_t fd, void* buffer, std::uint32_t nbytes, std::uint64_t offset) -> void {
		io_uring_prep_read(raw_, fd, buffer, nbytes, offset);
	}

	auto prepare_read_fixed() -> void { assert(false && "TODO"); }
	auto prepare_read_multishot() -> void { assert(false && "TODO"); }
	auto prepare_readv() -> void { assert(false && "TODO"); }
	auto prepare_readv2() -> void { assert(false && "TODO"); }

	auto prepare_recv(std::int32_t sockfd, void* buffer, std::uint64_t len, std::int32_t flags) -> void {
		io_uring_prep_recv(raw_, sockfd, buffer, len, flags);
	}

	auto prepare_recv_multishot() -> void { assert(false && "TODO"); }
	auto prepare_recvmsg() -> void { assert(false && "TODO"); }
	auto prepare_recvmsg_multishot() -> void { assert(false && "TODO"); }
	auto prepare_remove_buffers() -> void { assert(false && "TODO"); }
	auto prepare_rename() -> void { assert(false && "TODO"); }
	auto prepare_renameat() -> void { assert(false && "TODO"); }
	auto prepare_rw() -> void { assert(false && "TODO"); }

	auto prepare_send(std::int32_t sockfd, const void* buffer, std::uint64_t len, std::int32_t flags) -> void {
		io_uring_prep_send(raw_, sockfd, buffer, len, flags);
	}

	auto prepare_send_bundle() -> void { assert(false && "TODO"); }
	auto prepare_send_set_addr() -> void { assert(false && "TODO"); }
	auto prepare_send_zc() -> void { assert(false && "TODO"); }
	auto prepare_send_zc_fixed() -> void { assert(false && "TODO"); }
	auto prepare_sendmsg() -> void { assert(false && "TODO"); }
	auto prepare_sendmsg_zc() -> void { assert(false && "TODO"); }
	auto prepare_sendto() -> void { assert(false && "TODO"); }
	auto prepare_setxattr() -> void { assert(false && "TODO"); }
	auto prepare_shutdown() -> void { assert(false && "TODO"); }
	auto prepare_socket() -> void { assert(false && "TODO"); }
	auto prepare_socket_direct() -> void { assert(false && "TODO"); }
	auto prepare_socket_direct_alloc() -> void { assert(false && "TODO"); }
	auto prepare_splice() -> void { assert(false && "TODO"); }
	auto prepare_statx() -> void { assert(false && "TODO"); }
	auto prepare_symlink() -> void { assert(false && "TODO"); }
	auto prepare_symlinkat() -> void { assert(false && "TODO"); }
	auto prepare_sync_file_range() -> void { assert(false && "TODO"); }
	auto prepare_tee() -> void { assert(false && "TODO"); }
	auto prepare_timeout() -> void { assert(false && "TODO"); }
	auto prepare_timeout_remove() -> void { assert(false && "TODO"); }
	auto prepare_timeout_update() -> void { assert(false && "TODO"); }
	auto prepare_unlink() -> void { assert(false && "TODO"); }
	auto prepare_unlinkat() -> void { assert(false && "TODO"); }
	auto prepare_waitid() -> void { assert(false && "TODO"); }

	auto prepare_write(std::int32_t fd, const void* buffer, std::uint32_t nbytes, std::uint64_t offset) -> void {
		io_uring_prep_write(raw_, fd, buffer, nbytes, offset);
	}

	auto prepare_write_fixed() -> void { assert(false && "TODO"); }
	auto prepare_writev() -> void { assert(false && "TODO"); }
	auto prepare_writev2() -> void { assert(false && "TODO"); }

private:
	io_uring_sqe* raw_;

	explicit sqe(io_uring_sqe* ptr) : raw_(ptr) {}
};

class cqe {
	friend ring;

public:
	cqe() = delete;

	[[nodiscard]] auto raw() -> io_uring_cqe* { return raw_cqe_; }
	[[nodiscard]] auto data() -> void* { return io_uring_cqe_get_data(raw_cqe_); };
	[[nodiscard]] auto data64() -> std::uint64_t { return io_uring_cqe_get_data64(raw_cqe_); };
	[[nodiscard]] auto result() -> std::expected<std::int32_t, std::int32_t> {
		const auto res = raw_cqe_->res;
		if (res < 0) return std::unexpected(-res);
		return res;
	}
	[[nodiscard]] auto flags() -> std::uint32_t { return raw_cqe_->flags; }

	auto seen() -> void { io_uring_cqe_seen(raw_ring_, raw_cqe_); }

private:
	io_uring_cqe* raw_cqe_;
	::io_uring* raw_ring_;

	explicit cqe(io_uring_cqe* raw_cqe, ::io_uring* raw_ring) : raw_cqe_(raw_cqe), raw_ring_(raw_ring) {}
};

class ring {
public:
	ring(const ring&) = delete;
	ring(ring&&) = delete;
	auto operator=(const ring&) -> ring& = delete;
	auto operator=(ring&&) -> ring& = delete;
	ring() = default;
	~ring() { queue_exit(); }

	[[nodiscard]] auto raw() -> ::io_uring* { return &raw_; }

	auto queue_init(std::uint32_t queue_size = 256) -> std::expected<void, std::int32_t> {
		const auto res = io_uring_queue_init(queue_size, &raw_, 0);
		if (res < 0) return std::unexpected(-res);
		return {};
	}

	auto queue_exit() -> void { io_uring_queue_exit(&raw_); }

	[[nodiscard]] auto get_sqe() -> std::expected<sqe, std::monostate> {
		auto* raw_sqe = io_uring_get_sqe(&raw_);
		if (raw_sqe == nullptr) return std::unexpected(std::monostate{});
		return sqe(raw_sqe);
	}

	auto submit() -> std::expected<void, std::int32_t> {
		const auto res = io_uring_submit(&raw_);
		if (res < 0) return std::unexpected(-res);
		return {};
	}

	[[nodiscard]] auto wait() -> std::expected<cqe, std::int32_t> {
		auto* raw_cqe = static_cast<io_uring_cqe*>(nullptr);
		const auto res = io_uring_wait_cqe(&raw_, &raw_cqe);
		if (res < 0) return std::unexpected(-res);
		return cqe(raw_cqe, &raw_);
	}

	[[nodiscard]] auto wait_nr(std::uint32_t nr) -> std::expected<std::vector<cqe>, std::int32_t> {
		auto raw_cqes = std::vector<io_uring_cqe*>(nr);
		const auto res = io_uring_wait_cqe_nr(&raw_, raw_cqes.data(), nr);
		if (res < 0) return std::unexpected(-res);
		auto wrapped_cqes = std::vector<cqe>();
		wrapped_cqes.reserve(nr);
		for (auto i = 0; i < nr; ++i) wrapped_cqes.push_back(cqe(raw_cqes[i], &raw_));
		return wrapped_cqes;
	}

	[[nodiscard]] auto peek() -> std::expected<cqe, std::int32_t> {
		auto* cqe_ptr = static_cast<io_uring_cqe*>(nullptr);
		const auto res = io_uring_peek_cqe(&raw_, &cqe_ptr);
		if (res < 0) return std::unexpected(-res);
		return cqe(cqe_ptr, &raw_);
	}

	[[nodiscard]] auto peek_batch(std::uint32_t count) -> std::expected<std::vector<cqe>, std::int32_t> {
		auto raw_cqes = std::vector<io_uring_cqe*>(count);
		const auto res = io_uring_peek_batch_cqe(&raw_, raw_cqes.data(), count);
		if (res < 0) return std::unexpected(-res);
		auto wrapped_cqes = std::vector<cqe>();
		wrapped_cqes.reserve(count);
		for (auto i = 0; i < count; ++i) wrapped_cqes.push_back(cqe(raw_cqes[i], &raw_));
		return wrapped_cqes;
	}

private:
	::io_uring raw_;
};

} // namespace retina::io_uring
