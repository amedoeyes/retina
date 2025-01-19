import std;
import retina;

auto main() -> int {
	auto server_socket = retina::socket::socket(retina::socket::type::stream);
	server_socket.bind("localhost", "10001");
	server_socket.listen();
	std::println("listening");

		// auto ipstr = std::string();
		// ipstr.resize(INET6_ADDRSTRLEN);
		// if (client_addr.ss_family == AF_INET) {
		// 	auto* ipv4 = std::bit_cast<sockaddr_in*>(&client_addr);
		// 	inet_ntop(AF_INET, &(ipv4->sin_addr), ipstr.data(), ipstr.size());
		// } else if (client_addr.ss_family == AF_INET6) {
		// 	auto* ipv6 = std::bit_cast<sockaddr_in6*>(&client_addr);
		// 	inet_ntop(AF_INET6, &(ipv6->sin6_addr), ipstr.data(), ipstr.size());
		// } else {
		// 	std::println(std::cerr, "Unknown address family");
		// 	close(client_fd);
		// 	return 1;
		// }
		// std::println("connection from: {}", ipstr);

	while (true) {
		auto client_socket = server_socket.accept();
		while (true) {
			const auto data = client_socket.receive(1024);
			if (!data.has_value()) break;
			(void)client_socket.send(*data);
		}
	}
}
