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
public class FIFOCache implements Cache{
    static ArrayList<Subscription> cacheMemory;
    static int maxSize;

    /**
     *
     * @param maxSize
     */
    public FIFOCache(int maxSize) {
        cacheMemory = new ArrayList<>();
        FIFOCache.maxSize = maxSize;
    }
    
    /**
     *
     * @param item
     */
    @Override
    public void add(Subscription item) {
        if (cacheMemory.size() < maxSize) {
            cacheMemory.add(item);
        } else {
            remove();
            cacheMemory.add(item);
        }
    }
    
    /**
     *
     * @param item
     */
    @Override
    public void remove(Subscription item) {
        cacheMemory.remove(item);
    }
    
    /**
     *
     */
    public void remove() {
        cacheMemory.remove(0);
    }
    
    /**
     *
     * @param index
     */
    @Override
    public void remove(int index) {
        cacheMemory.remove(index);
    }
    
    /**
     *
     * @param name
     * @return
     */
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
    
    /**
     *
     * @return
     */
    public boolean empty() {
        return cacheMemory.isEmpty();
    }

    /**
     *
     * @param index
     * @return
     */
    @Override
    public Subscription getMemory(int index) {
        return cacheMemory.get(index);
    }

    /**
     *
     * @return
     */
    @Override
    public int minim() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
}
