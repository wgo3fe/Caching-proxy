#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

int main(int argc, char** argv) {
    // Parse command-line argumenfts
    if (argc != 5) {
        std::cerr << "Usage: caching-proxy --port <number> --origin <url>\n"
                  << "Example:\n"
                  << "    caching-proxy --port 3000 --origin http://dummyjson.com\n";
        return EXIT_FAILURE;
    }

    std::string port;
    std::string origin;

    for (int i = 1; i < argc; i += 2) {
        std::string arg = argv[i];
        if (arg == "--port") {
            port = argv[i + 1];
        } else if (arg == "--origin") {
            origin = argv[i + 1];
        } else {
            std::cerr << "Unknown argument: " << arg << "\n";
            return EXIT_FAILURE;
        }
    }

    if (port.empty() || origin.empty()) {
        std::cerr << "Both --port and --origin must be specified.\n";
        return EXIT_FAILURE;
    }

    std::cout << "Starting caching proxy server...\n";
    std::cout << "Listening on port: " << port << "\n";
    std::cout << "Forwarding requests to origin: " << origin << "\n";

    // TODO: Implement the caching proxy server logic here
    // This will involve setting up an Asio acceptor to listen on the specified port
    // and forwarding requests to the specified origin using Boost.Beast.

    return EXIT_SUCCESS;
}