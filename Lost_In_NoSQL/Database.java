/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.util.*;
/**
 *
 * @author Cezar
 */
public class Database {
    ArrayList<Nodes> databaseList;
    int maxCapacity;
    int nrNodes;

    public Database() {
        databaseList = new ArrayList<Nodes>();
    }
    
    public void setCapacity(int n) {
        this.maxCapacity = n;
    }
    
    public ArrayList<Nodes> getDatabase() {
        return databaseList;
    }
    
    public int size() {
        return databaseList.size();
    }
    
    public int getCapacity() {
        return this.maxCapacity;
    }

}
