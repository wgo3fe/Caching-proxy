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

/**
 * @class RequestHandler
 * @brief Handles HTTP requests and responses, forwarding them to the origin server.
 */
class RequestHandler {
public:
    /**
     * @brief Default constructor.
     */
    RequestHandler() = default;

    /**
     * @brief Default destructor.
     */
    ~RequestHandler() = default;

    /**
     * @brief Forwards an HTTP request to the origin server and retrieves the response.
     * @param target The target path for the HTTP request (e.g., "/api/resource").
     * @param method The HTTP method to use (e.g., "GET", "POST"). Defaults to "GET".
     * @return The response body as a string.
     */
    std::string forwardRequest(const std::string& target, const std::string& method = "GET");

    /**
     * @brief Initializes the request handler with the origin server's details.
     * @param origin The hostname or IP address of the origin server.
     * @param port The port number of the origin server.
     */
    void initialize(const std::string& origin, uint16_t port);

private:
    std::string _origin; ///< The hostname or IP address of the origin server.
    uint16_t _port; ///< The port number of the origin server.
    net::io_context _ioc; ///< The Boost.Asio I/O context used for network operations.
};