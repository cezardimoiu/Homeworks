/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Cezar
 */
public class Entity {
    private String name;
    private int RF;
    private int nrAttributes;
    private String[] attr;
    
    Entity(String name, String primary_key) {
        this.name = name;
        this.attr = new String[1];
        this.attr[0] = primary_key;
    }

    Entity(String name, String[] attr) {
        this.name = name;
        this.attr = new String[attr.length];
        for (int i = 0; i < attr.length; i++) {
            this.attr[i] = attr[i];
        }
    }
    
    Entity(String name, int RF, int n, String[] attr) {
        this.name = name;
        this.RF = RF;
        this.nrAttributes = n;
        this.attr = new String[n];
        for (int i = 0; i < n; i++) {
            this.attr[i] = attr[i];
        }
    }
    
    String getName() {
        return this.name;
    }

    int getRF() {
        return this.RF;
    }
    
    String getAttr(int index) {
        return this.attr[index - 1];
    }
    
    int nrAttr() {
        return this.nrAttributes;
    }
}
