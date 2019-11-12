/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author Cezar
 */
public class Basic extends Free{
    private int basicCounter = 0;
    
    Basic(String name, int basicCounter) {
        super(name);
        this.basicCounter = basicCounter;
    }
    
    /**
     *
     * @return
     */
    @Override
    public String getType() {
        if (basicCounter > 0) {
            basicCounter--;
            return "Basic";
        } else return super.getType();
    }
    
    /**
     *
     * @return 
     */
    @Override
    public String getName() {
        return super.getName();
    }
}
