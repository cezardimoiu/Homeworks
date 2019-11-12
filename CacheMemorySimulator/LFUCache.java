/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.util.ArrayList;
/**
 *
 * @author Cezar
 */
public class LFUCache implements Cache{
    static ArrayList<Subscription> cacheMemory;
    static int maxSize;

    public LFUCache(int maxSize) {
        cacheMemory = new ArrayList<>();
        LFUCache.maxSize = maxSize;
    }
    
    @Override
    public void add(Subscription item) {
        if (cacheMemory.size() < maxSize) {
            cacheMemory.add(item);
        } else {
            remove(0);
            cacheMemory.add(item);
        }
    }
    
    @Override
    public void remove(Subscription item) {
        cacheMemory.remove(item);
    }

    @Override
    public void remove(int index) {
        cacheMemory.remove(index);
    }
    
    public void increase(Subscription item) {
        item.nrAccesari++;
    }
    @Override
    public int searchInCache(String name) {
        /* 
         * if item in memory - index
         * else -1
        */
        for (Subscription item : cacheMemory) { 
            if (item.getName().equals(name)) {
                return cacheMemory.indexOf(item);
            }
        }
        return -1; 
    }
    
    @Override
    public boolean empty() {
        return cacheMemory.isEmpty();
    }

    @Override
    public Subscription getMemory(int index) {
        return cacheMemory.get(index);
    }
    
    @Override

    public int minim() {
        int max = 0;
        for (Subscription item : cacheMemory) {
            if (item.nrAccesari > max) 
                max = item.nrAccesari;
        }
        int index = 0;
        
        for (Subscription item : cacheMemory) {
            index++;
            if (item.nrAccesari == max) {
                return index;
            }
        }
        return 0;
    }
}
