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
public class students extends peoples{
    protected String group,school;
    public void setGroup(String n){
        this.group=n;
    }
    public String getGroup(){
        return this.group;
    }
    public void setSchool(String n){
        this.school=n;
    }
    public String getSchool(){
        return this.school;
    }
}
