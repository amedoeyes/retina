#include "retina.hpp"

#include <catch2/catch_test_macros.hpp>
#include <thread>

TEST_CASE("retina", "[retina]") {
	retina::Server server{8080};

	int i{0};

	std::thread t{[&]() {
		server.route(
			"/", retina::Method::get,
			[](const retina::Request &, retina::Response &res) {
				res.body() = "test";
			}
		);

		server.route(
			"/", retina::Method::post,
			[&i](const retina::Request &req, retina::Response &res) {
				i = std::stoi(req.body());

				res.body() = std::to_string(i);
			}
		);

		server.start();
	}};

	retina::Client client{"localhost", "8080"};

	SECTION("GET") {
		auto res{client.send(retina::Method::get, "/")};

		REQUIRE(res.body() == "test");
	}

	SECTION("POST") {
		auto res{client.send(retina::Method::post, "/", "100")};

		REQUIRE(res.body() == "100");
		REQUIRE(i == 100);
	}

	server.stop();
	t.join();
}
