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
public class ucln {
    private int a,b;
    public void setNum(int num1,int num2){
        this.a=num1;
        this.b=num2;
    }
    public int ucln(){
        int x=this.a;
        int y=this.b;
        while(x!=y){
            if(x>y) x=x-y;
            else if(y>x) y=y-x;
        }
        return x;
    }
    
    
    
    
}
