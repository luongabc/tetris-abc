#include <iomanip>
#include <vector>
#include <random>
#include <windows.h>
#include "console.h"
using namespace std;


struct khac
{
    int du_lieu;
    int mau;
    int x;
    int y;
};

struct hinh
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
    int khoi_lon[29][14];
    int y=25, x=14;
    int muc_cham;
};

vector<vector<vector<int>>> ds_khoi ={
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
    },
	{
		{ 0, 0, 0, 0 },
		{ 0, 8, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	}
};

enum dieukhien{ RIGHT , LEFT , UP , DOWN , ENTER, NO };
const int tuong=9;
const int trong=0;

void phim_vao(dieukhien & phim);                            // nhận phím vào và xủ lý
int phim_vao_menu(int & so_lua_chon);
int cai_dat_menu(int &cap_do, int &phan_choi);                    // cài dat game
void chay_game(int &cap_do, int &phan_choi);                 // chạy game
void cai_du_lieu(man_hinh & scr, hinh &b);                    // tạo khối ban đầu va cài man hinh
void in_man_hinh(man_hinh &scr, hinh& b,khac &diem, khac & muc_do);         // in lại màn hình
void tao_khoi(hinh &b,man_hinh &scr, bool &gameover);				// tạo ra khoi moi
bool kt_toa_do_moi(hinh &b, man_hinh & scr, int x2, int y2);	   // kiểm tra khoi o toa do moi
void di_chuyen(hinh &b,man_hinh& scr,int x2, int y2);        // di chuyên khoi
bool xoay_khoi(hinh &b,man_hinh &scr);                       // xoay khoi
bool kt_an_diem(int y,man_hinh &scr);                        //kiểm tra ăn điểm
void tong_diem(hinh &b,khac &score,khac &muc_do, man_hinh &scr);           // tính điểm
void xoay_cot(man_hinh &scr);                                // di chuyen man hình --phầm chơi nhanh
void gan_khoi(hinh &b,man_hinh &scr);                       //gán khoi vào man hình

void an_con_tro(bool hien);

int main()
{
    system("color f0");
	an_con_tro(false);
    while(true)
    {
        system("cls");
        int cap_do=3;
        int phan_choi=1;
        cai_dat_menu(cap_do, phan_choi);
        Sleep(1000);
        system("cls");
        chay_game(cap_do,phan_choi);
    }
}
//
int phim_vao_menu(int &so_lua_chon)
{
	dieukhien  phim;
	int lua_chon = 1;
	int x = 6;
	int y = lua_chon + 1;
	gotoxy(x, y);
	putchar(175);
	do {
		phim = NO;
		phim_vao(phim);
		switch (phim)
		{
		case DOWN:
		{
			if (y  < so_lua_chon+1 ) {
				gotoxy(x, y);
				putchar(32);
				y++;
				gotoxy(x, y);
				putchar(175);
			}
			break;
		}
		case UP:
		{
			if (y > lua_chon+1) {
				gotoxy(x, y);
				putchar(32);
				y--;
				gotoxy(x, y);
				putchar(175);
			}
			break;
		}
		}
		Sleep(100);
	} while (phim != ENTER);
	return y-1;
}
//
void chay_game(int &cap_do,int &phan_choi)
{
    bool gameover = false;
    int thoi_gian = 0;
	int gioi_han = 50;
	int choi_thuong = 1;
	int choi_nhanh = 2;						// phan choi nhanh
	int luot = 0;

	struct hinh b;

    struct khac diem;
    diem.du_lieu=0;
    diem.x =15;
    diem.y =2;

	struct khac muc_do;
	muc_do.du_lieu = 1;
	muc_do.x = 15;
	muc_do.y = 17;

    struct man_hinh scr;
    scr.muc_cham = cap_do*3;
    scr.x=14;
    scr.y=24;

    cai_du_lieu(scr, b);
    in_man_hinh(scr,b,diem, muc_do);
    tao_khoi(b,scr,gameover);
    while (!gameover)
    {
        // dieu khien
        dieukhien  phim;
        phim_vao(phim);
		switch (phim)
		{
		case RIGHT:
		{
			if (kt_toa_do_moi(b, scr, b.x + 1, b.y)) di_chuyen(b, scr, b.x + 1, b.y);
			break;
		}
		case LEFT:
		{
			if (kt_toa_do_moi(b, scr, b.x - 1, b.y)) di_chuyen(b, scr, b.x - 1, b.y);
			break;
		}
		case DOWN:
		{
			if (kt_toa_do_moi(b, scr, b.x, b.y + 1))  di_chuyen(b, scr, b.x, b.y + 1);
			break;
		}
		case UP:
		{
			xoay_khoi(b, scr);
			Sleep(50);
			break;
		}
		}
		phim = NO;

        if (thoi_gian < scr.muc_cham) thoi_gian++;			//thời gian rơi khối
        else
        {
            if (kt_toa_do_moi( b, scr, b.x , b.y + 1) )		//kiểm tra rơi khối
                di_chuyen( b, scr, b.x , b.y + 1);			//rơi khối

			// khối không xuống dc nữa
            else
            {
                luot ++;
                if(luot==gioi_han							// tăng tốc độ xuống
                   && scr.muc_cham!=0){
						scr.muc_cham--;
						muc_do.du_lieu++;
						gotoxy(muc_do.x, muc_do.y);
						cout << "cap :" << muc_do.du_lieu;
						luot = 0;
                }
                gan_khoi(b, scr);
                tong_diem(b,diem,muc_do,scr);
                if(phan_choi == choi_nhanh) xoay_cot(scr);			//phan choi nhanh
                in_man_hinh(scr,b,diem, muc_do);
                tao_khoi(b, scr, gameover);
            }
            thoi_gian = 0;
        }
		Sleep(50);
    }
    system("cls");
    cout<<"\n \n \t game over \n";
    cout<<"\t your score : "<<diem.du_lieu<<endl;
    Sleep(2000);
}
//
int cai_dat_menu(int &cap_do, int &phan_choi)
{
	int so_lua_chon=4;
	int lua_chon;
	int huong_dan = 3;
	int thoat = 4;
	int de = 3;
	int vua = 2;
	int kho = 1;
	while(true)
	{
		system("cls");

		cout << "\tGAME XEP HINH \n \n\t CHOI THUONG \n\t CHOI NHANH \n\t HUONG DAN \n\t THOAT";
		lua_chon = phim_vao_menu(so_lua_chon);
		if (lua_chon == thoat) exit(EXIT_SUCCESS);
		else if (lua_chon == huong_dan) {
			system("cls");
			cout << "Phim phai di chuyen khoi sang phai.\nPhim trai di chuyen khoi sang trai.\nPhim len xoay khoi.\nPhim xuong lam khoi xuong nhanh hon.\nPhim enter de lua chon.";
			Sleep(10000);
		}
		else {
			phan_choi = lua_chon;
			system("cls");
			cout << "\tGAME XEP HINH \n \n\t KHO \n\t VUA \n\t DE \n\t THOAT";
			cap_do = phim_vao_menu(so_lua_chon);
			if(cap_do != thoat) return 0;
		}
	}
}
//
void in_man_hinh(man_hinh &scr, hinh & b, khac & diem, khac &muc_do )
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
            if(scr.khoi_lon[y][x]==tuong|| y==0)
            {
                setcolor(0);
                putchar(177);
            }
            else if(scr.khoi_lon[y][x]==trong)
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
	gotoxy(muc_do.x, muc_do.y);
	cout << "cap :"<<muc_do.du_lieu;
}
//
void cai_du_lieu(man_hinh &scr, hinh &b)
{
    for (int y = 0; y <scr.y; y++)
    {
        for (int x = 0; x <scr.x; x++)
        {
            if((x == 0)
                || (x == scr.x-1)
                || (y ==scr.y-1)
               )
                    scr.khoi_lon[y][x]= tuong;
            else   scr.khoi_lon[y][x] = trong;
        }
    }
    srand(time(NULL));                                                                  //can sua
    b.khoi_moi= (rand()*9)%7;
    b.khoi_cu=b.khoi_moi;
}
//
void tao_khoi(hinh &b,man_hinh &scr, bool &gameover)
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
    b.khoi_moi = rand()%8;

	struct hinh b_tiep;
    b_tiep.y=6;
    b_tiep.x=16;
    for (int y = 0; y < b.bac; y++)
    {
        for (int x = 0; x < b.bac; x++)
        {
            gotoxy(b_tiep.x+x, b_tiep.y+y);
            putchar(32);
            if(ds_khoi[b.khoi_moi][y][x] != trong)
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

void di_chuyen(hinh &b,man_hinh &scr,int x2, int y2)
{
	setcolor(b.khoi_cu);
    for (int y = 0; y < b.bac; y++)
    {
        for (int x = 0; x < b.bac; x++)
        {
            if(b.y+y>0 && b.khoi[y][x] !=trong)
            {
                gotoxy(b.x+x, b.y+y);
                putchar(32);
            }
        }
    }
    b.y= y2;
    b.x= x2;
    for(int y = 0; y < b.bac;y ++)
    {
        for(int x = 0;x< b.bac ;x++)
        {
            if(b.y+y>0 && b.khoi[y][x] !=trong)
            {

                gotoxy(b.x+x,b.y+y);
                putchar(219);
            }
        }
    }
}
//
bool kt_toa_do_moi(hinh &b,man_hinh &scr,int x2, int y2)
{
    for (int y = 0; y < b.bac; y++)
    {
        for (int x = 0; x < b.bac; x++)
        {
			if (y2 + y >= 0
                &&b.khoi[y][x]!=trong
                && scr.khoi_lon[y2 + y][x2 + x]!=trong ) return false;
			if (x2 + x<1 || x2 + x >= scr.x - 1)
				if (b.khoi[y][x] != trong)return false;
        }
    }
    return true;
}
//
void phim_vao(dieukhien &phim)
{
    if(GetAsyncKeyState(VK_RIGHT))      phim=RIGHT;
    else if(GetAsyncKeyState(VK_LEFT))  phim=LEFT;
    else if(GetAsyncKeyState(VK_DOWN))  phim=DOWN;
    else if(GetAsyncKeyState(VK_UP))    phim=UP;
	else if(GetAsyncKeyState(VK_RETURN))phim=ENTER;
}
//
bool xoay_khoi(hinh &b,man_hinh &scr)
{
    struct hinh b2;
    b2=b;

    for (int y = 0; y < b.bac; y++){ //xoay khối
        for (int  x =0; x < b.bac; x++)
        {
            b.khoi[y][x] = b2.khoi[3 - x][y];
        }
    }

    if (!kt_toa_do_moi(b,scr,b.x,b.y)){ // dừng nếu khối không thể xoay
		b = b2;
        return true;
    }
    for (int y = 0; y < b2.bac; y++)
    {
        for (int  x = 0; x < b2.bac; x++)
        {
            if(b2.y+y>0 && b2.khoi[y][x] !=trong)
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
        if(scr.khoi_lon[y][x]==trong
			||scr.khoi_lon[y][x] == tuong)
                return false;
    }
    return true;
}
//
void tong_diem(hinh &b,khac &diem,khac & muc_do, man_hinh &scr)
{
    int temp=0;
    for(int y=0;y<b.bac;y++)
    {
		if (b.y + y < scr.y
			&&b.y + y > 0
			&&kt_an_diem(b.y + y ,scr))
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
    if(temp>0) in_man_hinh(scr,b, diem, muc_do);
    else setcolor(b.khoi_cu);
}
//
void xoay_cot(man_hinh &scr)
{
    vector<int> temp(scr.y,0);
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

void gan_khoi(hinh &b, man_hinh &scr)
{
    int item = 7;
    int khoang_xoa=3;

    for (int y = 0; y < b.bac; y++)
    {
        for (int x = 0; x < b.bac; x++)
        {
			if(b.khoi_cu == item					// khối "chấm" để xóa viền xung quang
				&& x<khoang_xoa
				&& y<khoang_xoa
				&& scr.khoi_lon[b.y + y][b.x + x]!=tuong)
					scr.khoi_lon[b.y + y][b.x + x]=trong;
            else if (b.y+y>=0 ) scr.khoi_lon[b.y + y][b.x + x] +=b.khoi[y][x];
        }
    }
}
//
void an_con_tro(bool hien) {
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO cursor = { 1, hien };
		SetConsoleCursorInfo(handle, &cursor);
}
//
//
