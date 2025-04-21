import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpExchange;
import java.net.URI;

import java.net.InetSocketAddress;
import java.io.IOException;
import java.io.OutputStream;

public class Controller extends Thread {
    private MemoryConsumer consumer;
    private HttpServer server;
    
    public Controller(MemoryConsumer consumer) throws IOException {
        this.consumer = consumer;
        this.server = HttpServer.create(new InetSocketAddress(8090), 0);
    }

    @Override
    public void run() {
        server.createContext("/update", new Handler(consumer));
        System.out.println("STarting server");
        server.start();
    }

    private static class Handler implements HttpHandler {
        MemoryConsumer consumer;

        public Handler(MemoryConsumer consumer) {
            this.consumer = consumer;
        }

        @Override
        public void handle(HttpExchange exchange) throws IOException {
            try {
                String method = exchange.getRequestMethod();
                URI uri = exchange.getRequestURI();
                System.out.println("Query: " + uri.getQuery());
                String[] requestParams = uri.getQuery().split("&");

                int newVal;
            
                String response = "Hello from server";
                for(String param : requestParams) {
                    String[] parts = param.split("=");
                    if(parts[0].equals("size")) {
                        newVal = Integer.parseInt(parts[1]);
                        consumer.update(newVal);
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
}