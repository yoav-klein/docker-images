public class MemoryConsumer {
    
    public static void main(String[] args) {
        String sizeStr = System.getenv("SIZE");
        if(null == sizeStr) {
            System.out.println("Define the SIZE environment variable");
            System.exit(1);
        }

        try {
            int memoryInMB = Integer.parseInt(sizeStr);
            if (memoryInMB <= 0) {
                System.out.println("Memory must be a positive integer.");
                System.exit(1);
            }

            System.out.println("Consuming " + memoryInMB + " MB of heap memory...");
            byte[] mem = consumeMemory(memoryInMB);


            try {
                while(true) {
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

    private static byte[] consumeMemory(int memoryInMB) {
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

