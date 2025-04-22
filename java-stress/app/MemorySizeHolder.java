
public class MemorySizeHolder {
    private int memoryInMB;
    private boolean changed = false;

    MemorySizeHolder(int initialSize) {
        this.memoryInMB = initialSize;
    }

    public synchronized void update(int newVal) {
        memoryInMB = newVal;
        changed = true;
        notifyAll();
    }

    public synchronized void waitForNewValue() {
        while(!changed) {
            try {
                wait();
            } catch(InterruptedException e) {}
        }
        changed = false;
    }

    public int getSize() { return this.memoryInMB; }
}