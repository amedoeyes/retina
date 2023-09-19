#ifndef RETINA_SERVER_H
#define RETINA_SERVER_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <istream>
#include <map>
#include <utility>

namespace retina {

using Status = boost::beast::http::status;
using Method = boost::beast::http::verb;
using Field = boost::beast::http::field;

using Request = boost::beast::http::request<boost::beast::http::string_body>;
using Response = boost::beast::http::response<boost::beast::http::string_body>;

using RouteHandler = std::function<void(const Request &, Response &)>;
using Router = std::map<std::pair<std::string, Method>, RouteHandler>;

class Server {
	public:
	Server(const short &port);

	auto start() -> void;
	auto stop() -> void;

	auto route(
		const std::string &path, const Method &method,
		const RouteHandler &handler
	) -> void;

	private:
	boost::asio::io_context ioc;
	boost::asio::ip::tcp::acceptor acceptor;
	Router router;

	auto accept() -> void;
};

class Client {
	public:
	Client(const std::string &host, const std::string &port);

	auto send(Method method, std::string path, std::string payload = "")
		-> Response;

	private:
	std::string host;
	std::string port;
	boost::asio::io_context ioc;
	boost::asio::ip::tcp::resolver resolver;
	boost::beast::tcp_stream stream;
	boost::beast::flat_buffer buffer;
};

}  // namespace retina

#endif
