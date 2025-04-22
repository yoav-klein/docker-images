


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

        MemorySizeHolder sizeHolder = new MemorySizeHolder(memoryInMB);
        MemoryConsumer consumer = new MemoryConsumer(sizeHolder);
        consumer.start();

        Controller controller = new Controller(sizeHolder);
        controller.start();

        try {
            controller.join();
            consumer.join();
        } catch(InterruptedException e) {}

        System.out.println("Program ends...");

    }
}