/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author Cezar
 */
public class Premium extends Basic{
    private int premiumCounter = 0;
    
    Premium(String name, int basicCounter, int premiumCounter) {
        super(name, basicCounter);
        this.premiumCounter = premiumCounter;
    }
    
    /**
     *
     * @return
     */
    @Override
    public String getType() {
        if (premiumCounter > 0) {
            premiumCounter--;
            return "Premium";
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
