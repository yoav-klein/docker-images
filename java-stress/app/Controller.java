import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpExchange;
import java.net.URI;

import java.net.InetSocketAddress;
import java.io.IOException;
import java.io.OutputStream;

public class Controller extends Thread {
    private MemorySizeHolder sizeHolder;
    private HttpServer server;
    
    public Controller(MemorySizeHolder holder) throws IOException {
        this.sizeHolder = holder;
        this.server = HttpServer.create(new InetSocketAddress(8090), 0);
    }

    @Override
    public void run() {
        server.createContext("/update", new UpdateHandler(this.sizeHolder));
        server.createContext("/stop", new StopHandler(this.sizeHolder, server));

        server.start();
    }

    private static class UpdateHandler implements HttpHandler {
        MemorySizeHolder sizeHolder;

        public UpdateHandler(MemorySizeHolder sizeHolder) {
            this.sizeHolder = sizeHolder;
        }

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            try {
                URI uri = exchange.getRequestURI();
                String[] requestParams = uri.getQuery().split("&");

                int newVal;
                String response = "No size parameter received";
                for(String param : requestParams) {
                    String[] parts = param.split("=");
                    if(parts[0].equals("size")) {
                        newVal = Integer.parseInt(parts[1]);
                        sizeHolder.update(newVal);
                        response = "Value updated!";
                    }
                }
                exchange.sendResponseHeaders(200, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
            } finally {}

        }

    }

    private static class StopHandler implements HttpHandler {
        MemorySizeHolder sizeHolder;
        HttpServer server;

        public StopHandler(MemorySizeHolder sizeHolder, HttpServer server) {
            this.server = server;
            this.sizeHolder = sizeHolder;
        }

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            try {
                String response = "Stopping...";
                sizeHolder.update(0);
                exchange.sendResponseHeaders(200, response.length());
                OutputStream os = exchange.getResponseBody();
                os.write(response.getBytes());
                os.close();
                this.server.stop(0);
            } finally {}

        }

    }
}