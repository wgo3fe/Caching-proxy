#include <boost/program_options.hpp>
#include <iostream>
#include <string>

#include "CacheHandler.h"
#include "RequestHandler.h"

#define LOG(x) std::cout << x << "\n"

namespace po = boost::program_options;

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
            LOG(desc);
            return EXIT_SUCCESS;
        }

        // Notify to enforce required options
        po::notify(vm);

        // Retrieve the values
        port = static_cast<uint16_t>(std::stoi(vm["port"].as<std::string>()));
        origin = vm["origin"].as<std::string>();

        LOG("Starting caching proxy server...");
        LOG("Listening on port: " << port);
        LOG("Forwarding requests to origin: " << origin);
    }
    catch (const po::error &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    CacheHandler cacheHandler{};

    // Check if the content is already in the cache
    std::string cachedPage = cacheHandler.get(origin, port);
    if(!cachedPage.empty())
    {
        LOG("Cache hit! Content found in cache.");
        LOG("Cached content: " << cachedPage);
        return EXIT_SUCCESS;
    }
    LOG("Cache miss! Content not found in cache.");

    
    // If the content is not in the cache, make a request to the origin server
    RequestHandler requestHandler{};
    requestHandler.initialize(origin, port);
    std::string content = requestHandler.forwardRequest(target, "GET");
    if (content.empty())
    {
        LOG("Failed to retrieve content from origin server.");
        return EXIT_FAILURE;
    }
    LOG("Content retrieved from origin server: " << content);
    
    // and add it to the cache
    cacheHandler.add(origin, port, content);
    LOG("Content added to cache.");

    return EXIT_SUCCESS;
}