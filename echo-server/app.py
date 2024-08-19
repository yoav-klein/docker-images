from http.server import BaseHTTPRequestHandler, HTTPServer
import socket

class SimpleHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Get the client IP address
        client_ip = self.client_address[0]

        # Get the server IP address
        server_ip = socket.gethostbyname(socket.gethostname())
        
        # Construct the response message
        message = f"Hello {client_ip}, this is {server_ip}"

        # Send HTTP status code 200 (OK)
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()

        # Send the message
        self.wfile.write(message.encode())

def run(server_class=HTTPServer, handler_class=SimpleHandler, port=5000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f"Starting HTTP server on port {port}")
    httpd.serve_forever()

if __name__ == '__main__':
    run()

