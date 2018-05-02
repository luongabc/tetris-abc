#include <iomanip>
#include <iostream>
#include <vector>
#include <random>
#include <windows.h>
#include <fstream>
#include "console.h"
using namespace std;
struct khac
{
    int du_lieu;
    int mau;
    int x;
    int y;
};

struct khoi
{
    int bac=4;
    int khoi_moi;
    int khoi[4][4];
    int khoi_cu;
    int x;
    int y;
};

struct man_hinh
{
    int khoi_lon[25][14];
    int y=25, x=14;
    int toc_do;
};

vector<vector<vector<int>>> ds_khoi =
{
    {
        { 0, 7, 0, 0 },
        { 0, 7, 0, 0 },
        { 0, 7, 0, 0 },
        { 0, 7, 0, 0 }
    },
    {
        { 0, 0, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 }
    },
    {
        { 0, 0, 2, 0 },
        { 0, 2, 2, 0 },
        { 0, 2, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 3, 0, 0 },
        { 0, 3, 3, 0 },
        { 0, 0, 3, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 0, 0, 0 },
        { 0, 4, 0, 0 },
        { 4, 4, 4, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 0, 0, 0 },
        { 0, 5, 5, 0 },
        { 0, 5, 5, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 0, 0, 0 },
        { 0, 6, 6, 0 },
        { 0, 0, 6, 0 },
        { 0, 0, 6, 0 }
    }
};

void chay_game(int &cap_do, int &phan_choi);                 // chạy game
void in_man_hinh(man_hinh &scr, khoi& b,khac &diem);         // in lại màn hình
void tao_khoi(khoi &b,man_hinh &scr, bool &gameover);        // tạo ra khoi moi
void cai_du_lieu(man_hinh & scr,khoi &b);                    // tạo khối ban đầu va cài man hinh
void di_chuyen(khoi &b,man_hinh& scr,int x2, int y2);        // di chuyên khoi
bool kt_toa_do_moi(khoi &b,man_hinh & scr,int x2, int y2);   // kiểm tra khoi o toa do moi
void phim_vao(int &phim);                                    // nhận phím vào và xủ lý
bool xoay_khoi(khoi &b,man_hinh &scr);                       // xoay khoi
bool kt_an_diem(int y,man_hinh &scr);                        //kiểm tra ăn điểm
void tong_diem(khoi &b,khac &score,man_hinh &scr);           // tính điểm
void xoay_cot(man_hinh &scr);                                // di chuyen man hình
void gan_khoi(khoi &b,man_hinh &scr);                        //gán khoi vào man hình
void cai_dat(int &cap_do,int &phan_choi);                    // cài dat game

int main()
{
    system("color f0");                // mau nen
    while(true)
    {
        system("cls");
        int cap_do;
        int phan_choi;
        cai_dat(cap_do, phan_choi);
        Sleep(1000);
        system("cls");
        chay_game(cap_do,phan_choi);
    }


}
//
void chay_game(int &cap_do,int &phan_choi)
{
    bool gameover = false;
    int thoi_gian = 0;
    int gioi_han=50;
    struct khoi b;

    struct khac diem;
    diem.du_lieu=0;
    diem.x =15;
    diem.y =2;

    struct man_hinh scr;
    scr.toc_do = cap_do*5;
    scr.x=14;
    scr.y=24;

    cai_du_lieu(scr, b);
    in_man_hinh(scr,b,diem);
    tao_khoi(b,scr,gameover);

    while (!gameover)
    {
        int luot =0;
        Sleep(20*cap_do);

        // dieu khien
        int phim;
        phim_vao(phim);
        if(phim==1)
            if (!kt_toa_do_moi(b, scr, b.x +1, b.y ))
            {
                Sleep(30);
            di_chuyen(b, scr, b.x +1, b.y);
            }
        if(phim==2)
            if (!kt_toa_do_moi(b, scr, b.x -1, b.y))
            {
                Sleep(30);
                di_chuyen(b, scr, b.x -1, b.y);
            }
        if(phim==3)
            if (!kt_toa_do_moi(b, scr, b.x , b.y+1))
            {
                di_chuyen(b, scr, b.x , b.y+1);
            }
        if(phim==4)
        {
            xoay_khoi(b,scr);
            Sleep(50);
        }
        phim=0;

        if (thoi_gian < scr.toc_do) thoi_gian++;
        else
        {
            if (!kt_toa_do_moi( b, scr, b.x , b.y + 1) )
            {
                di_chuyen( b, scr, b.x , b.y + 1);
            }
            else
            {
                luot ++;
                if(luot==gioi_han
                   && scr.toc_do!=0)
                {
                        scr.toc_do--;
                        luot =0;
                }
                gan_khoi(b, scr);
                tong_diem(b,diem,scr);
                if(phan_choi ==2) xoay_cot(scr);
                in_man_hinh(scr,b,diem);
                tao_khoi(b, scr, gameover);
            }
            thoi_gian = 0;
       }
    }
    system("cls");
    cout<<endl<<endl<<"\t"<<"game over"<<endl;
    cout<<"\t"<< "your score : "<<diem.du_lieu<<endl;
    Sleep(2000);
}
//
void cai_dat(int &cap_do,int &phan_choi)
{
    string data;
    fstream datafile;
    datafile.open("hienthi.txt",ios::in);
    cout<<endl<<endl;
    for(int i=0;i<5;i++)
    {
        getline(datafile,data,',');
        cout<<"\t"<<data;
        if(i!=4)cout<<endl;

    }
    while(phan_choi <1|| phan_choi>2){
        gotoxy(20,6);
        cin>>phan_choi;
    }
    gotoxy(20,3);
    if(phan_choi==1) cout<<"thuong";
    else cout<<"toc do";
    gotoxy(5,4);
    for(int i=0;i<5;i++)
    {
        getline(datafile,data,',');
        cout<<"\t"<<data;
        if(i!=4)cout<<endl;
    }
    while(cap_do <1|| cap_do>3){
        gotoxy(20,8);
        cin>>cap_do;
    }
     gotoxy(20,4);
    if(cap_do==1) cout<<"kho";
    else if(cap_do==2)cout<<"vua";
    else cout<<"de";
    cout<<endl<<"\t"<<"game start     ";
    for(int i=0;i<5;i++)
    {
        cout<<"                             ";
        if(i!=4)cout<<endl;
    }
    datafile.close();
    Sleep(500);
}
//
void in_man_hinh(man_hinh &scr, khoi & b, khac & diem)
{
    for(int y=0; y<scr.y; y++)
    {
        if(y==0 || y==scr.y-1)
        {
            for(int x=scr.x; x<scr.x+10; x++)
            {
                gotoxy(x,y);
                setcolor(0);
                putchar(177);
            }
        }
        gotoxy(23,y);
        putchar(177);
    }
    gotoxy(0,0);
    for (int y = 0; y < scr.y; y++)
    {
        for (int x = 0; x < scr.x; x++)
        {
            if(scr.khoi_lon[y][x]==9|| y==0)
            {
                setcolor(0);
                putchar(177);
            }
            else if(scr.khoi_lon[y][x]==0)
            {
                putchar(32);
            }
            else if(scr.khoi_lon[y][x]==7)
            {
                setcolor(0);
                putchar(219);
            }
            else
            {
                setcolor(scr.khoi_lon[y][x]);
                putchar(219);
            }
        }
        cout<<endl;
    }
    gotoxy(diem.x,diem.y);
    cout<<"score :";
    gotoxy(diem.x,diem.y+1);
    cout<<diem.du_lieu;
}
//
void cai_du_lieu(man_hinh &scr, khoi &b)
{
    for (int y = 0; y <scr.y; y++)
    {
        for (int x = 0; x <scr.x; x++)
        {
            if((x == 0)
                || (x == scr.x-1)
                || (y ==scr.y-1)
               )
                    scr.khoi_lon[y][x]= 9;
            else   scr.khoi_lon[y][x] = 0;
        }
    }
    srand(time(NULL));                                                                  //can sua
    b.khoi_moi= (rand()*9)%7;
    b.khoi_cu=b.khoi_moi;
}
//
void tao_khoi(khoi &b,man_hinh &scr, bool &gameover)
{
    b.khoi_cu=b.khoi_moi;
    b.x = 5;
    b.y = -3;
    for (int y = 0; y < b.bac; y++)
    {
        for (int x = 0; x < b.bac; x++)
        {
            b.khoi[y][x] = ds_khoi[b.khoi_moi][y][x];
        }
    }
    srand(time(NULL));                                                                  //can sua
    b.khoi_moi = rand()%7;
    struct khoi b_tiep;
    b_tiep.y=6;
    b_tiep.x=16;
    for (int y = 0; y < b.bac; y++)
    {
        for (int x = 0; x < b.bac; x++)
        {
            gotoxy(b_tiep.x+x, b_tiep.y+y);
            putchar(32);
            if(ds_khoi[b.khoi_moi][y][x] != 0)
            {
                setcolor(b.khoi_moi);
                gotoxy(b_tiep.x + x, b_tiep.y + y);
                putchar(219);
            }
        }
    }

    for (int x = 1; x < scr.x-1; x++)
        if(scr.khoi_lon[0][x] !=0 ) gameover=true;
}

void di_chuyen(khoi &b,man_hinh & scr,int x2, int y2)
{
    for (int y = 0; y < b.bac; y++)
    {
        for (int x = 0; x < b.bac; x++)
        {
            if(b.y+y>0 && b.khoi[y][x] !=0)
            {
                setcolor(b.khoi_cu);
                gotoxy(b.x+x, b.y+y);
                putchar(32);
            }
        }
    }
    b.y= y2;
    b.x= x2;
    setcolor(b.khoi_cu);
    for(int y = 0; y < b.bac;y ++)
    {
        for(int x = 0;x< b.bac ;x++)
        {
            if(b.y+y>0 && b.khoi[y][x] !=0)
            {

                gotoxy(b.x+x,b.y+y);
                putchar(219);
            }
        }
    }
}
//
bool kt_toa_do_moi(khoi &b,man_hinh &scr,int x2, int y2)
{
    for (int y = 0; y < b.bac; y++)
    {
        for (int x = 0; x < b.bac; x++)
        {
            if(x2+x<1|| x2+x>=scr.x-1)
                if(b.khoi[y][x]!=0)return true;
            if (y2+y>=0
                &&b.khoi[y][x]!=0
                && scr.khoi_lon[y2 + y][x2 + x]!=0 ) return true;
        }
    }
    return false;
}
//
void phim_vao(int &phim)
{
    if(GetAsyncKeyState(VK_RIGHT))      phim=1;
    else if(GetAsyncKeyState(VK_LEFT))  phim=2;
    else if(GetAsyncKeyState(VK_DOWN))  phim=3;
    else if(GetAsyncKeyState(VK_UP))    phim=4;
}
//
bool xoay_khoi(khoi &b,man_hinh &scr)
{
    struct khoi b2;
    b2=b;

    for (int y = 0; y < b.bac; y++)
    { //xoay khối
        for (int  x =0; x < b.bac; x++)
        {
            b.khoi[y][x] = b2.khoi[3 - x][y];
        }
    }

    if (kt_toa_do_moi(b,scr,b.x,b.y))
    { // dừng nếu khối không thể xoay
        for (int  i = 0; i < b.bac; i++)
        {
            for (int  j = 0; j < b.bac; j++)
            {
                b.khoi[i][j] = b2.khoi[i][j];
            }
        }
        return true;
    }
    for (int y = 0; y < b2.bac; y++)
    {
        for (int  x = 0; x < b2.bac; x++)
        {
            if(b2.y+y>0 && b2.khoi[y][x] !=0)
            {
                setcolor(b.khoi_cu);
                gotoxy(b2.x+x, b2.y+y);
                putchar(32);
            }
        }
    }
    di_chuyen(b, scr, b.x , b.y);
    return false;
}
//
bool kt_an_diem(int y, man_hinh &scr)
{
    for(int x=1;x<scr.x-1;x++)
    {
        if(scr.khoi_lon[y][x]==0
           ||scr.khoi_lon[y][x]==9)
                return false;
    }
    return true;
}
//
void tong_diem(khoi &b,khac &diem, man_hinh &scr)
{
    int temp=0;
    for(int y=0;y<b.bac;y++)
    {
        if(kt_an_diem(b.y + y ,scr))
        {
            temp++;
            for(int row=b.y + y ; row>0 ; row--)
            {
                for(int column =1; column<scr.x -1;column++)
                {
                    if(row != 0)
                        scr.khoi_lon[row][column]=scr.khoi_lon[row-1][column];
                    else scr.khoi_lon[row][column]=0;
                }
            }
        }
    }
    diem.du_lieu+= temp*temp;
    if(temp>0) in_man_hinh(scr,b, diem);
    else setcolor(b.khoi_cu);
}
//
void xoay_cot(man_hinh &scr)
{
    int temp[scr.y];
    for(int y=0;y<scr.y-1;y++)
    {
        temp[y]= scr.khoi_lon[y][1];
    }
    for(int x=1;x<=scr.x-2 ;x++)
    {
        for(int y=0;y<scr.y-1;y++)
        {
            if(x==scr.x-2) scr.khoi_lon[y][x] =temp[y];
            else scr.khoi_lon[y][x]=scr.khoi_lon[y][x+1];
        }
    }
}

void gan_khoi(khoi &b, man_hinh &scr)
{
    for (int y = 0; y < b.bac; y++)
    {
        for (int x = 0; x < b.bac; x++)
        {
            if (b.y+y>=0) scr.khoi_lon[b.y + y][b.x + x] +=b.khoi[y][x];
        }
    }
}



