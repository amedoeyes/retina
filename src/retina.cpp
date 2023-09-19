#include "retina.hpp"

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <map>
#include <memory>
#include <utility>

namespace retina {

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
	public:
	Session(tcp::socket socket, Router &router)
		: socket{std::move(socket)}, router{router} {}

	auto start() -> void {
		readRequest();
	}

	private:
	tcp::socket socket;
	beast::flat_buffer buffer;
	Request request;
	Response response;
	Router &router;

	auto readRequest() -> void {
		auto self{shared_from_this()};

		http::async_read(
			socket, buffer, request,
			[self](beast::error_code ec, std::size_t) {
				if (!ec) self->processRequest();
			}
		);
	}

	auto processRequest() -> void {
		response.version(request.version());
		response.keep_alive(request.keep_alive());
		response.set(Field::server, BOOST_BEAST_VERSION_STRING);

		auto key{std::make_pair(request.target(), request.method())};
		auto it{router.find(key)};

		if (it != router.end()) it->second(request, response);
		else response.result(Status::not_found);

		writeResponse(response);
	}

	auto writeResponse(const Response &response) -> void {
		auto self{shared_from_this()};

		http::async_write(
			socket, response,
			[self](beast::error_code ec, std::size_t) {
				self->socket.shutdown(tcp::socket::shutdown_send, ec);
			}
		);
	}
};

Server::Server(const short &port)
	: acceptor{ioc, tcp::endpoint(tcp::v4(), port)} {}

auto Server::start() -> void {
	accept();
	ioc.run();
}

auto Server::stop() -> void {
	ioc.stop();
}

auto Server::route(
	const std::string &path, const Method &method, const RouteHandler &handler
) -> void {
	router[std::make_pair(path, method)] = handler;
}

auto Server::accept() -> void {
	acceptor.async_accept([this](beast::error_code ec, tcp::socket socket) {
		if (!ec) std::make_shared<Session>(std::move(socket), router)->start();

		accept();
	});
}

Client::Client(const std::string &host, const std::string &port)
	: host{host}, port{port}, resolver{ioc}, stream{ioc} {
	stream.connect(resolver.resolve(host, port));
}

auto Client::send(Method method, std::string path, std::string payload)
	-> Response {
	Request req{method, path, 11};
	Response res;

	req.set(http::field::host, host);
	req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

	req.body() = payload;

	req.prepare_payload();

	http::write(stream, req);
	http::read(stream, buffer, res);

	stream.socket().shutdown(tcp::socket::shutdown_both);

	return res;
}

}  // namespace retina
