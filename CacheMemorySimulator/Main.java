

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.Scanner;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Cezar
 */
public class Main {

    /**
     * @param args the command line arguments
     * @throws java.io.FileNotFoundException
     * @throws java.io.UnsupportedEncodingException
     */
    public static void main(String[] args) throws FileNotFoundException, UnsupportedEncodingException {
        // TODO code application logic here
        File input = new File(args[0]);
        Scanner scanner = new Scanner(input);
        PrintWriter writer = new PrintWriter(args[1], "UTF-8"); 
        Memory memory = new Memory();
        String typeCache = scanner.nextLine();
        int sizeCache = scanner.nextInt();
        Cache cache;
        
        if (typeCache.equals("LRU")) {
            cache = new LRUCache(sizeCache);
        } else {
            cache = new FIFOCache(sizeCache);
        } 
        
        String trash = scanner.nextLine();
        int it = scanner.nextInt();
        trash = scanner.nextLine();
        
        for (int i = 0; i < it; i++) {
            String buffer = scanner.nextLine();
            String[] parts = buffer.split(" ");
            //GET 
            if (parts.length == 2) {
                int index = memory.searchInMemory(parts[1]);
                int index2 = cache.searchInCache(parts[1]);
                if (memory.searchInMemory(parts[1]) != -1) {
                    String typeObject = memory.getMemory(index).getType();
                    if (cache.searchInCache(parts[1]) != -1) {
                        writer.println("0 " + typeObject);
                        if ("LRU".equals(typeCache)) {
                            Subscription ob = cache.getMemory(index2);
                            cache.remove(index2);
                            cache.add(ob);
                        } /*else if ("LFU".equals(typeCache)){
                            Subscription ob = cache.getMemory(cache.minim());
                            cache.remove(cache.minim());
                            cache.add(ob);
                            cache.remove(LFUCache.cacheMemory.size() - 1);
                        }*/
                    } else {
                        writer.println("1 " + typeObject);
                        cache.add(memory.getMemory(index));
                    }
                } else {
                    writer.println("2");
                }
            } else if (parts.length == 3) { //ADD BASIC
                if (memory.empty()) {
                    Subscription s1 = new Basic(parts[1], getInt(parts[2]));
                    memory.add(s1);
                } else {
                    int index1 = memory.searchInMemory(parts[1]);
                    int index2 = cache.searchInCache(parts[1]);
                    if (memory.searchInMemory(parts[1]) != -1) {
                        if (cache.searchInCache(parts[1]) != -1) {
                            cache.remove(cache.getMemory(index2));
                        } 
                        Subscription ob = new Basic(parts[1], getInt(parts[2]));
                        memory.set(ob, index1);
                    } else {
                        memory.add(new Basic(parts[1], getInt(parts[2])));
                    }
                }
            } else {
                int index1 = memory.searchInMemory(parts[1]);
                int index2 = cache.searchInCache(parts[1]);
                if (memory.searchInMemory(parts[1]) != -1) {
                    if (cache.searchInCache(parts[1]) != -1) {
                        cache.remove(cache.getMemory(index2));
                    } 
                    Subscription ob = new Premium(parts[1], getInt(parts[2]), getInt(parts[3]));
                    memory.set(ob, index1);
                } else {
                    memory.add(new Premium(parts[1], getInt(parts[2]), getInt(parts[3])));
                }
            }
        }
        
        writer.close();
    }   
    
    static int getInt(String whatever) {
        return Integer.parseInt(whatever);
    }
}



