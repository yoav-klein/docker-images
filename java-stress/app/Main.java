


import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {


        String sizeStr = System.getenv("SIZE");
        if(null == sizeStr) {
            System.out.println("Define the SIZE environment variable");
            System.exit(1);
        }

        int memoryInMB = Integer.parseInt(sizeStr);

        if (memoryInMB <= 0) {
            System.out.println("Memory must be a positive integer.");
            System.exit(1);
        }

        MemoryConsumer consumer = new MemoryConsumer(memoryInMB);
        consumer.start();

        Controller controller = new Controller(consumer);
        controller.start();

        while(true) {
            try {
                Thread.sleep(3000);
            } catch(InterruptedException e) {}
        }

    }
}