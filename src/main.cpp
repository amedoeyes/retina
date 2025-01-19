import std;
import retina;

auto main() -> int {
	auto server_socket = retina::socket::socket(retina::socket::type::stream);
	server_socket.bind("localhost", "10001");
	server_socket.listen();
	std::println("listening to {}:{}", server_socket.ip(), server_socket.port());
	while (true) {
		auto client_socket = server_socket.accept();
		std::println("connection from {}:{}", client_socket.ip(), client_socket.port());
		while (true) {
			const auto data = client_socket.receive(1024);
			if (!data.has_value()) break;
			std::println("received: {}", std::string(std::bit_cast<const char*>(data->data())));
			(void)client_socket.send(*data);
		}
	}
}
