/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author Cezar
 */
public class Free extends Subscription{
    private final String name;
    
    Free(String name) {
        this.name = name;
    }
    
    @Override
    String getType() {
        return "Free";
    }

    @Override
    String getName() {
        return name;
    }
    
}
