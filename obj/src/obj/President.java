/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package obj;

/**
 *
 * @author devil
 */
public class President extends peoples{
    protected int year;
    protected String country;
    public void setYear(int n){
        this.year=n;
    }
    public int getYear(){
        return this.year;
    }
    public void setCountry(String n){
        this.country=n;
    }
    public String getCountry(){
        return this.country;
    }
}
