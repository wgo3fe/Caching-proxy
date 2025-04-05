#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
namespace po = boost::program_options;
using tcp = asio::ip::tcp;

int main(int argc, char** argv) {
    try {
        // Define the command-line options
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "Show help message")
            ("port,p", po::value<std::string>()->required(), "Port number for the proxy server")
            ("origin,o", po::value<std::string>()->required(), "Origin server URL");

        // Parse the command-line arguments
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);

        // Display help message if needed
        if (vm.count("help")) {
            std::cout << desc << "\n";
            return EXIT_SUCCESS;
        }

        // Notify to enforce required options
        po::notify(vm);

        // Retrieve the values
        std::string port = vm["port"].as<std::string>();
        std::string origin = vm["origin"].as<std::string>();

        std::cout << "Starting caching proxy server...\n";
        std::cout << "Listening on port: " << port << "\n";
        std::cout << "Forwarding requests to origin: " << origin << "\n";

        // TODO: Implement the caching proxy server logic here

    } catch (const po::error& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}