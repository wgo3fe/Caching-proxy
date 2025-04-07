#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <string>

#include <CacheHandler.h>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace po = boost::program_options;
using tcp = net::ip::tcp;

int main(int argc, char **argv)
{
    uint16_t port{};
    std::string origin{};
    const std::string target{"/"}; // The target path for the HTTP request, const for now
    const int version{11};         // HTTP version (1.1)

    try
    {
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
        if (vm.count("help"))
        {
            std::cout << desc << "\n";
            return EXIT_SUCCESS;
        }

        // Notify to enforce required options
        po::notify(vm);

        // Retrieve the values
        port = vm["port"].as<uint16_t>();
        origin = vm["origin"].as<std::string>();

        std::cout << "Starting caching proxy server...\n";
        std::cout << "Listening on port: " << port << "\n";
        std::cout << "Forwarding requests to origin: " << origin << "\n";
    }
    catch (const po::error &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    CacheHandler cacheHandler{};

    // Check if the content is already in the cache
    cacheHandler.get(origin, port);

    // If the content is not in the cache, make a request to the origin server
    // and add it to the cache
    //cacheHandler.add(origin, port, content);

    return EXIT_SUCCESS;
}