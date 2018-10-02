
package obj;
import java.io.IOException;
import java.util.*;

public class Obj {

    public static void main(String[] args) {
        Scanner scan=new Scanner(System.in); 
        //fibonaxi n=new fibonaxi();
        //n.setNum(scan.nextInt());
        //System.out.print(n.getFibonaxi());
        
        phanso num=new phanso(scan.nextInt(),scan.nextInt());
        phanso num2=new phanso(scan.nextInt(),scan.nextInt());
        if(num.equals(num2)) System.out.print("true");
        else System.out.print("false");
        
        
    }
    
}
