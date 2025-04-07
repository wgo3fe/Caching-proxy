#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include "RequestHandler.h"

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>

void RequestHandler::initialize(const std::string& origin, uint16_t port)
{
    _origin = origin;
    _port = port;
}

std::string RequestHandler::forwardRequest(const std::string& target, const std::string& method)
{
    // Set up an I/O context
    net::io_context ioc;

    // Create a resolver and a socket
    tcp::resolver resolver(ioc);
    beast::tcp_stream stream(ioc);

    // Resolve the origin server address
    auto const results = resolver.resolve(_origin, std::to_string(_port));

    // Connect to the origin server
    beast::get_lowest_layer(stream).connect(results);

    // Set up an HTTP request
    http::request<http::string_body> req{http::verb::get, target, 11};
    req.set(http::field::host, _origin);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    // Send the HTTP request to the origin server
    http::write(stream, req);

    // Receive the HTTP response from the origin server
    beast::flat_buffer buffer;
    http::response<http::string_body> res;
    http::read(stream, buffer, res);

    // Gracefully close the socket
    beast::error_code ec;
    stream.socket().shutdown(tcp::socket::shutdown_both, ec);

    // Return the response body as a string
    return res.body();
}