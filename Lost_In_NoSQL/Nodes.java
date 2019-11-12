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
public class Nodes {
    ArrayList<Entity> nodeList;
    
    public Nodes() {
        nodeList = new ArrayList<>();
    }
    
    public void addEntity(Entity e) {
        nodeList.add(0, e);
    }
    
    public int size() {
        return nodeList.size();
    }
    
    public void remove(int index) {
        nodeList.remove(index);
    }
    public Entity get(int index) {
        return nodeList.get(index);
    }
    
}
