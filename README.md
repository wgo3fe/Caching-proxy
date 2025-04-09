User should be able to start the caching proxy server by running a command like following:

caching-proxy --port <number> --origin <url>
--port is the port on which the caching proxy server will run.
--origin is the URL of the server to which the requests will be forwarded.
For example, if the user runs the following command:

caching-proxy --port 3000 --origin http://dummyjson.com
