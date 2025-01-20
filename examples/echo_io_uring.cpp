#include <unistd.h>

import std;
import retina;

enum class connection_type : std::int8_t {
	server,
	client
};

struct connection {
	std::int32_t fd;
	connection_type type;
	std::array<char, 1024> buffer;
};

auto main() -> int {
	auto server_socket = retina::socket::socket(retina::socket::type::stream);
	server_socket.bind("localhost", "10001");
	server_socket.listen();
	server_socket.set_reuseaddr(true);
	std::println("listening to {}:{}", server_socket.ip(), server_socket.port());

	auto ring = retina::io_uring::ring();
	ring.queue_init();

	auto sqe = *ring.get_sqe();
	sqe.prepare_accept(server_socket.fd(), nullptr, nullptr, 0);
	sqe.set_data(new connection{.fd = server_socket.fd(), .type = connection_type::server});
	ring.submit();

	while (true) {
		auto cqe = *ring.wait();
		auto res = *cqe.result();
		auto* conn = static_cast<connection*>(cqe.data());

		if (conn != nullptr) {
			switch (conn->type) {
				using enum connection_type;
				case server: {
					std::println("client connected");
					auto* client_conn = new connection{.fd = res, .type = connection_type::client};
					sqe = *ring.get_sqe();
					sqe.prepare_recv(client_conn->fd, client_conn->buffer.data(), client_conn->buffer.size(), 0);
					sqe.set_data(client_conn);

					sqe = *ring.get_sqe();
					sqe.prepare_accept(server_socket.fd(), nullptr, nullptr, 0);
					sqe.set_data(conn);
					break;
				}
				case client: {
					if (res == 0) {
						close(conn->fd);
						delete conn;
						break;
					}
					sqe = *ring.get_sqe();
					sqe.prepare_send(conn->fd, conn->buffer.data(), res, 0);
					sqe = *ring.get_sqe();
					sqe.prepare_recv(conn->fd, conn->buffer.data(), conn->buffer.size(), 0);
					sqe.set_data(conn);
					break;
				}
			}
			ring.submit();
		}
		cqe.seen();
	}
}
