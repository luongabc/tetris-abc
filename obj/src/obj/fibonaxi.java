
package obj;


public class fibonaxi {
    private int num;
    private int fibonaxi;
    public void setNum(int n){
        this.num=n;
        this.fibonaxi();
    }
    public int getNum(){
        return this.num;
    }
    public int getFibonaxi(){
        return this.fibonaxi;
    }
    public void fibonaxi(){
        if(num==0) this.fibonaxi=0;
        else if(num==1) this.fibonaxi=1;
        else {
            int a=0;
            int b=1;
            for(int i=0;i<num-1;i++){
                int c=b+a;
                a=b;
                b=c;
            }
            this.fibonaxi=b;
        }
    }
}
