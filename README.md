# Retina

Simple HTTP server and client.

## Installation

To install using CMake FetchContent:

```cmake
include(FetchContent)
fetchcontent_declare(
    retina
    GIT_REPOSITORY https://github.com/amedoeyes/retina
    GIT_TAG master
)
fetchcontent_makeavailable(retina)
```

## Usage

Server

```cpp
#include <retina.hpp>

int main() {
    retina::Server server{8080};

    server.route(
	"/", retina::Method::get,
	[](const retina::Request &, retina::Response &res) {
	    res.body() = "Hello World!\n";
	}
    );

    int i{0};

    server.route(
        "/", retina::Method::post,
        [&i](const retina::Request &req, retina::Response &res) {
            i = std::stoi(req.body());
            res.body() = std::to_string(i);
        }
    );

    server.start();

    return 0;
}
```

Client

```cpp
#include <retina.hpp>

int main() {
    retina::Client client{"localhost", "8080"};

    retina::Response resGet{client.send(retina::Method::get, "/")};
    std::cout << resGet.body() << "\n";

    retina::Response resPost{client.send(retina::Method::post, "/", "100")};
    std::cout << resPost.body() << "\n";

    return 0;
}
```
