#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace po = boost::program_options;
using tcp = net::ip::tcp;

int main(int argc, char **argv)
{
    std::string port{};
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
        port = vm["port"].as<std::string>();
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

    // TODO: Implement the caching proxy server logic here

    try
    {
        // The io_context is required for all I/O
        net::io_context ioc;

        // These objects perform our I/O
        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);

        // Look up the domain name
        auto const results = resolver.resolve(origin, port);

        // Make the connection on the IP address we get from a lookup
        stream.connect(results);

        // Set up an HTTP GET request message
        http::request<http::string_body> req{http::verb::get, target, version};
        req.set(http::field::host, origin);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // Send the HTTP request to the remote origin
        http::write(stream, req);

        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;

        // Declare a container to hold the response
        http::response<http::dynamic_body> res;

        // Receive the HTTP response
        http::read(stream, buffer, res);

        // Write the message to standard out
        std::cout << res << std::endl;

        // Gracefully close the socket
        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        // not_connected happens sometimes
        // so don't bother reporting it.
        //
        if (ec && ec != beast::errc::not_connected)
            throw beast::system_error{ec};

        // If we get here then the connection is closed gracefully
    }
    catch (std::exception const &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}