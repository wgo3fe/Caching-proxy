# Caching Proxy Server

The **Caching Proxy Server** is a lightweight and efficient tool that intercepts HTTP requests, caches responses, and forwards requests to an origin server when necessary. This improves performance and reduces redundant network traffic.

## Features

- **Caching**: Stores responses locally to reduce redundant requests to the origin server.
- **Performance**: Improves response times for frequently accessed resources.
- **Customizable**: Easily configure the port and origin server via command-line arguments.

## Getting Started

To start the caching proxy server, use the following command:

```bash
caching-proxy --port <number> --origin <url>
```

### Command-Line Options:
- `--port`: Specifies the port on which the caching proxy server will listen for incoming requests.
- `--origin`: Defines the URL of the origin server to which uncached requests will be forwarded.

### Example Usage:
To run the proxy server on port `3000` and forward requests to `http://dummyjson.com`, use the following command:

```bash
caching-proxy --port 3000 --origin http://dummyjson.com
```

Once started, the proxy server will:
1. Check if the requested content is available in the cache.
2. Serve cached content if available.
3. Forward the request to the origin server if the content is not cached.
4. Cache the response for future requests.

## Requirements

- A Linux environment with a C++ compiler.
- Required libraries:
  - **Boost**: For command-line argument parsing.
  - **ASIO**: For networking (if applicable).

## Testing the Proxy

You can test the proxy server using tools like `curl` or a web browser.

### Example with `curl`:
```bash
curl -x http://localhost:3000 http://dummyjson.com/products
```

This command sends a request through the proxy server running on `localhost:3000` and fetches data from the origin server `http://dummyjson.com`.

## Notes

- Ensure the specified port is not already in use.
- The proxy currently supports HTTP traffic. HTTPS support requires additional configuration.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
