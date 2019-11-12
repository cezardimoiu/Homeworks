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
public class Memory {
    ArrayList<Subscription> memory;
    
    Memory() {
        memory = new ArrayList<>();
    }
    
    public Subscription getMemory(int index) {
        return memory.get(index);
    }
    
    public void add(Subscription item) {
        memory.add(item);
    }
    
    public void set(Subscription item, int index) {
        memory.set(index, item);
    }
    
    public void remove(Subscription item) {
        memory.remove(item);
    }
    
    public int searchInMemory(String name) {
        /* 
         * if item in memory - index
         * else -1
        */
        for (Subscription item : memory) { 
            if (item.getName().equals(name)) {
                return memory.indexOf(item);
            }
        }
        return -1; 
    }
    
    public boolean empty() {
        return memory.isEmpty();
    }
}
