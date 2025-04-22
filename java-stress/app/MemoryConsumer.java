
public class MemoryConsumer extends Thread {

    private MemorySizeHolder sizeHolder;

    public MemoryConsumer(MemorySizeHolder sizeHolder) {
        this.sizeHolder = sizeHolder;
    }
    
    @Override
    public void run() {
        while(true) {
            int memoryInMB = sizeHolder.getSize();
            if(memoryInMB == 0) break;
            consume(memoryInMB);
        }
    }

    public void consume(int memoryInMB) {
        System.out.println("Consuming " + memoryInMB + " MB of heap memory...");
        byte[] mem = consumeMemory(memoryInMB);
        sizeHolder.waitForNewValue();
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

