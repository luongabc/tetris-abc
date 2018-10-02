
package obj;


public class phanso {
    private int tu,mau;
    public phanso(int tu,int mau){
        this.tu=tu;
        this.mau=mau;
    }
    public void setTu(int n){
        tu=n;
    }
    public void setMau(int n){
        mau=n;
    }
    public int getTu(){
        return tu;
    }
    public int getMau(){
        return mau;
    }
    public int timUSCLN(int a, int b) {
        while (a != b) {
            if (a > b) {
                a -= b;
            } else {
                b -= a;
            }
        }
        return a;
    }
    public void toiGianPhanSo() {
        int i = timUSCLN(this.getTu(), this.getMau());
        this.setTu(this.getTu() / i);
        this.setMau(this.getMau() / i);
    }
     
    public phanso congPhanSo(phanso ps) {
        int ts = this.getTu() * ps.getMau() + ps.getTu() * this.getMau();
        int ms = this.getMau() * ps.getMau();
        phanso phanSoTong = new phanso(ts, ms);
        phanSoTong.toiGianPhanSo();
        return phanSoTong;
    }
      
    public phanso truPhanSo(phanso ps) {
        int ts = this.getTu() * ps.getMau() - ps.getTu() * this.getMau();
        int ms = this.getMau() * ps.getMau();
        phanso phanSoHieu = new phanso(ts, ms);
        phanSoHieu.toiGianPhanSo();
        return phanSoHieu;
    }
     
    public phanso nhanPhanSo(phanso ps) {
        int ts = this.getTu() * ps.getTu();
        int ms = this.getMau() * ps.getMau();
        phanso phanSoTich = new phanso(ts, ms);
        phanSoTich.toiGianPhanSo();
        return phanSoTich;
    }
     
    public phanso chiaPhanSo(phanso ps) {
        int ts = this.getTu() * ps.getMau();
        int ms = this.getMau() * ps.getTu();
        phanso phanSoThuong = new phanso(ts, ms);
        phanSoThuong.toiGianPhanSo();
        return phanSoThuong;
    }
    public boolean equals(phanso obj){
        obj.toiGianPhanSo();
        this.toiGianPhanSo();
        if(obj.getTu()!=this.tu) return false;
        else if(obj.getMau()!=this.mau) return false;
        return true;
    }
}
