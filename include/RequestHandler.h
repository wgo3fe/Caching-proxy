#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class RequestHandler {
public:
    RequestHandler() = default;
    ~RequestHandler() = default;

    // Forward a request to the origin server and return the response
    std::string forwardRequest(const std::string& target, const std::string& method = "GET");
    void initialize(const std::string& origin, uint16_t port);

private:
    std::string _origin;
    uint16_t _port;
    net::io_context _ioc;
};