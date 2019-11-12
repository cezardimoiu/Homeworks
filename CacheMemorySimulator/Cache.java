/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author Cezar
 */
public interface Cache {

    /**
     *
     * @param item
     */
    public void add(Subscription item);

    /**
     *
     * @param item
     */
    public void remove(Subscription item);

    /**
     *
     * @param name
     * @return
     */
    public int searchInCache(String name);

    /**
     *
     * @param index
     */
    public void remove(int index);

    /**
     *
     * @return
     */
    public boolean empty();

    /**
     *
     * @param index2
     * @return
     */
    public Subscription getMemory(int index2);

    /**
     *
     * @return
     */
    public int minim();
}
