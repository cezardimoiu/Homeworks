/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.util.*;
/**
 *
 * @author Cezar
 */
public class Tema2 {

    /**
     *
     * @param args
     * @throws FileNotFoundException
     */
    public static void main(String[] args) throws FileNotFoundException {
        // TODO code application logic here
        //File file = new File(args[0]);
        File file = new File(args[0]);
        PrintWriter writer = new PrintWriter(args[0] + "_out");
        Scanner scanner = new Scanner(file);
        
        int maxCapacity;
        int aux;
        String[] parts1 = scanner.nextLine().split(" ");
        Database database = new Database();
        database.maxCapacity = toInt(parts1[3]);
        ArrayList<Entity> entityList = new ArrayList<>();
        
        //citesc din fisier si parsez
        parse(writer, parts1, database, entityList);
        while (scanner.hasNextLine()) {
            String[] parts = (scanner.nextLine()).split(" ");
            parse(writer, parts, database, entityList);
        }
        writer.close();
    }
    
    static void parse(PrintWriter writer, String[] parts, Database database, ArrayList<Entity> entityList) {
        
        if (parts[0].equals("CREATE")) {
            createEntity(parts, entityList); 
            
        } else if (parts[0].equals("INSERT")) {
            Entity ent = objectEntity(parts);
            insertEntity(database.getDatabase(), ent, entityList, database.getCapacity());

        } else if (parts[0].equals("DELETE")) {
            Entity ent = new Entity(parts[1], parts[2]);
            deleteEntity(database.databaseList, ent, writer);

        } else if (parts[0].equals("UPDATE")) {
            // TODO
        } else if (parts[0].equals("GET")) {
            Entity ent = new Entity(parts[1], parts[2]);
            getEntity(database.databaseList, ent, writer, entityList);
        } else if (parts[0].equals("SNAPSHOTDB")) {
            if (database.size() == 0) writer.println("EMPTY DB");
            int i = 1;
            for (Nodes node : database.getDatabase()) {
                if (node.size() > 0) {
                    writer.println("Nod" + i++);
                }
                print(writer, node.nodeList, entityList);
            }
        }
        
    }
    
    static Database createDatabase(String[] parts) {
        Database database = new Database();
        return database;
    }
    
    static void createEntity(String[] parts, ArrayList<Entity> entityList) {
        int n = toInt(parts[3]);
        String[] attr = new String[n];
        for (int i = 0; i < attr.length; i++) {
            attr[i] = parts[4 + 2*i];
        }
        Entity ent = new Entity(parts[1], toInt(parts[2]), toInt(parts[3]), attr);

        entityList.add(ent);
    }
    
    static Entity objectEntity(String[] parts) {
        String[] attr = new String[parts.length - 1];
        for (int i = 0; i < attr.length; i++) {
            attr[i] = parts[i+1];
        }
        Entity ent = new Entity(parts[1], attr);
        return ent;
    }
    
    static void insertEntity(ArrayList<Nodes> database, Entity ent, ArrayList<Entity> entityList, int capacity) {
        
        int RF = 0;
        for (Entity elem : entityList) {
            if (elem.getName().equals(ent.getName())) {
                RF = elem.getRF();
                break;
            }
        }
        int max = 0;
        //verific maximul RF
        for (Entity elem: entityList) {
            if (elem.getRF() > max) max = elem.getRF();
        }
        
        //verificare baza de date goala
        if (database.isEmpty()) {
            for (int i = 0; i < max; i++) {
                Nodes node = new Nodes();
                database.add(node);
            }
        } 
        
        for (int i = 0; i < database.size(); i++) {
            if (RF > 0) {
                Nodes node = database.get(i);
                if (node.size() < capacity) {
                    node.addEntity(ent);
                    RF--;
                } else { //daca n-am loc, mai creez un nod
                    Nodes aux_node = new Nodes();
                    database.add(aux_node);
                }
            }
        }
    }
    
    static void deleteEntity(ArrayList<Nodes> database, Entity ent, PrintWriter writer) {
        Nodes aux_node;
        Entity aux_entity;
        Entity deleteEntity = null;
        int ok = 1;
        for (int i = 0; i < database.size(); i++) {
            aux_node = database.get(i);
            for (int j = 0; j < aux_node.size(); j++) {
                aux_entity = aux_node.get(j);
                //verificare dupa nume si cheie primara
                if (ent.getName().equals(aux_entity.getName()) &&
                   (ent.getAttr(1).equals(aux_entity.getAttr(2)))) {
                    
                    deleteEntity = database.get(i).get(j);
                    database.get(i).remove(j);
                    ok = 1;
                    break;
                }
            }
        }
        if (deleteEntity == null) writer.println("NO INSTANCE TO DELETE");
    }
    
    static Entity getEntity(ArrayList<Entity> list, String nume) {
        for (Entity e : list) {
            if (e.getName().equals(nume)) return e;
        }
        return null;
    }
    
    static void getEntity(ArrayList<Nodes> database, Entity ent, 
                          PrintWriter writer, ArrayList<Entity> list) {

        int nrAtributes = 0;
        int nrNode = 0;
        Entity aux_entity = null;
        for (Nodes node : database) {
            nrNode++;
            for (Entity e : node.nodeList) {
                if (ent.getName().equals(e.getName()) && 
                   (ent.getAttr(1).equals(e.getAttr(2)))) {
                   //verificare dupa atribut si cheie primara
                    aux_entity = e;
                    writer.print("Nod" + nrNode + " ");
                    break;
                }
            } 
        }
        
        if (aux_entity == null) {
            writer.println("NO INSTANCE FOUND");
        } else {
            Entity aux = null;
            for (int i = 0; i < list.size(); i++) {
                if (list.get(i).getName().equals(aux_entity.getName()) ) {
                    aux = getEntity(list, ent.getName());

                    nrAtributes = aux.nrAttr();
                }
            } 
            writer.print(ent.getName());
            // numele atributului il iau din aux
            // valoarea atributului o iau din aux_entity
            for (int j = 1; j <= nrAtributes; j++) {
                    writer.print(" " + dec(aux.getAttr(j)) + ":" + dec(aux_entity.getAttr(j + 1)));
            }
            writer.print("\n");
        }
    }
    
    static int toInt(String str) {
        return Integer.parseInt(str);
    }
    
    static String dec(String str) {
        Locale locale = new Locale("en", "UK");
        String pattern = "#.##";
        DecimalFormatSymbols symbols = new DecimalFormatSymbols(locale);
        DecimalFormat decimalFormat = new DecimalFormat(pattern, symbols);
        
        //verificare daca e numar 
        String[] split = str.split("[0-9]");
        if (split.length > 1) { 
            String number = decimalFormat.format(Double.parseDouble(str));
            return number;
        } else return str;
    }
    
    static void print(PrintWriter writer, ArrayList<Entity> nodes, ArrayList<Entity> list) {
        int i;
        int k = 1;
        for (Entity ent : nodes) {
            Entity aux = getEntity(list, ent.getName());
            i = aux.nrAttr();
            writer.print(ent.getName());
            
            // numele atributului il iau din aux
            // valoarea atributului o iau din ent
            for (int j = 1; j <= i; j++) {
                writer.print(" " + dec(aux.getAttr(j)) + ":" + dec(ent.getAttr(j + 1)));
            }
            writer.print("\n");
            k++;
            if (k == list.size()) k--;
        }
    }
    
    static void update(ArrayList<Nodes> database, ArrayList<Entity> list, Entity ent) {
        
    }  
}
