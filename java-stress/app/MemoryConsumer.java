
public class MemoryConsumer extends Thread {

    private boolean changed = false;
    private int memoryInMB;

    public MemoryConsumer(int memoryInMB) {
        this.memoryInMB = memoryInMB;
    }

    public void update(int newVal) {
        this.memoryInMB = newVal;
        this.changed = true;
    }
    
    @Override
    public void run() {
        while(true) {
            changed = false;
            consume();
        }
    }

    public void consume() {

        try {
            System.out.println("Consuming " + this.memoryInMB + " MB of heap memory...");
            byte[] mem = consumeMemory(memoryInMB);

            try {
                while(!this.changed) {
                    Thread.sleep(3000);
                }
            } catch(Exception e) {
                System.out.println("Done sleeping");
            }

        } catch (NumberFormatException e) {
            System.out.println("Invalid memory value. Please enter a valid integer.");
            System.exit(1);
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }

    }

    private byte[] consumeMemory(int memoryInMB) {
        // Calculate the number of bytes to allocate
        long bytesToAllocate = memoryInMB * 1024L * 1024L;
        // Create a large array to consume the memory
        byte[] memoryHog = new byte[(int) bytesToAllocate];
        
        for(int i = 0; i < bytesToAllocate; ++i) {
            memoryHog[i] = 1;
        }
        return memoryHog;
    }
}

