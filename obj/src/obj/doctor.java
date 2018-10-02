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
public class doctor extends peoples{
    protected String hospital;
    public void setHospital(String n){
        this.hospital=n;
    }
    public String getHospital(){
        return this.hospital;
    }
}
