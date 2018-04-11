#include <iomanip>
#include <iostream>
#include <vector>
#include <random>
#include <conio.h>
#include <windows.h>
#include "console.h"
using namespace std;
struct them{
    int content;
    int color;
    int x;
    int y;
};
struct block{
    int rank_b=4;
    int blocktype;
    int block[4][4];
    int color;
    int x;
    int y;
};

struct screen{
    int field[25][14];
    int y=25, x=14;
};

vector<vector<vector<int>>> block_list ={
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

void manu(int &speed);
void display(screen &scr, block& b,them &score);
void makeBlocks(block &b,screen &scr, bool &gameover);
void initGame(screen & scr,block &b);
void moveBlock(block &b,screen & scr,int x2, int y2);
bool isCollide(block &b,screen & scr,int x2, int y2);
void userInput(block &b,screen & scr);
bool rotateBolck(block &b,screen &scr);
bool test_score(int y,screen &scr);
void sun_score(block &b,them &score,screen &scr);

int main(){
    while(true){
    int speed;
        cout<<"TETRIS"<<endl;
        cout<< "muc do (1, 2, 3) : ";
        cin>> speed;
        cout<<endl<<"start game";
        Sleep(1000);
        system("cls");
        manu(speed);
    }


}

void manu(int &speed){
    bool gameover = false;
    int GAMESPEED = speed*5;
    size_t time = 0;
    struct block b;

    struct them score;
    score.content=0;
    score.x =15;
    score.y =2;
    struct screen scr;
    scr.x=14;
    scr.y=25;

    initGame(scr, b);
    display(scr,b,score);
    makeBlocks(b,scr,gameover);
    while (!gameover){
        userInput(b,scr);
        if (time < GAMESPEED) time++;
        else{

            if (!isCollide( b, scr, b.x , b.y + 1) ){
                moveBlock( b, scr, b.x , b.y + 1);
            }
            else{
                for (int y = 0; y < b.rank_b; y++){
                    for (int x = 0; x < b.rank_b; x++){
                        if (b.y+y>=0) scr.field[b.y + y][b.x + x] +=b.block[y][x];
                    }
                }
                sun_score(b,score,scr);
                if(score.content> 50)  GAMESPEED--;
                makeBlocks(b, scr, gameover);
            }
            time = 0;
       }
    }
    system("cls");
    cout<<"game over"<<endl;
    cout<< "your score : "<<score.content<<endl;
}


void display(screen &scr, block & b, them & score){
    for(int y=0; y<scr.y; y++){
        if(y==0 || y==scr.y-1) {
            for(int x=scr.x; x<scr.x+10; x++){
                gotoxy(x,y);
                setcolor(0);
                putchar(177);
            }
        }
        gotoxy(23,y);
        putchar(177);
    }
    system("color 70");
    gotoxy(0,0);
    for (int y = 0; y < scr.y; y++){
        for (int x = 0; x < scr.x; x++){
            if(scr.field[y][x]==9|| y==0) {
                setcolor(0);
                putchar(177);
            }
            else if(scr.field[y][x]==0) {
                putchar(32);
            }
            else if(scr.field[y][x]==1) {
                setcolor(1);
                putchar(219);
            }
            else if(scr.field[y][x]==2) {
                setcolor(2);
                putchar(219);
            }
            else if(scr.field[y][x]==3) {
                setcolor(3);
                putchar(219);
            }
            else if(scr.field[y][x]==4) {
                setcolor(4);
                putchar(219);
            }
            else if(scr.field[y][x]==5) {
                setcolor(5);
                putchar(219);
            }
            else if(scr.field[y][x]==6) {
                setcolor(6);
                putchar(219);
            }
            if(scr.field[y][x]==7) {
                setcolor(0);
                putchar(219);
            }
        }
        cout<<endl;
    }
    gotoxy(score.x,score.y);
    cout<<"score :";
    gotoxy(score.x,score.y+1);
    cout<<score.content;
}

void initGame(screen &scr, block &b){
    for (int y = 0; y <scr.y; y++){
        for (int x = 0; x <scr.x; x++){
            if ((x == 0) || (x == scr.x-1) || (y ==scr.y-1))  scr.field[y][x]= 9;
            else   scr.field[y][x] = 0;
        }
    }
    srand(time(NULL));                                                                  //can sua
    b.blocktype= 0;
    b.color=b.blocktype;
}

void makeBlocks(block &b,screen & scr, bool &gameover){
    b.color=b.blocktype;
    b.x = 5;
    b.y = -3;
    for (int y = 0; y < b.rank_b; y++){
        for (int x = 0; x < b.rank_b; x++){
            b.block[y][x] = block_list[b.blocktype][y][x];
        }
    }
    srand(time(NULL));                                                                  //can sua
    b.blocktype = rand()%7;
    struct block b_next;
    b_next.y=6;
    b_next.x=16;
    for (int y = 0; y < b.rank_b; y++){
        for (int x = 0; x < b.rank_b; x++){
            gotoxy(b_next.x+x, b_next.y+y);
            putchar(32);
            if(block_list[b.blocktype][y][x] != 0) {
                setcolor(b.blocktype);
                gotoxy(b_next.x + x, b_next.y + y);
                putchar(219);
            }
        }
    }

    for (int x = 1; x < scr.x-1; x++)
        if(scr.field[0][x] !=0 ) gameover=true;
}

void moveBlock(block &b,screen & scr,int x2, int y2){             // di chuyển khối
    for (int y = 0; y < b.rank_b; y++){
        for (int x = 0; x < b.rank_b; x++){
            if(b.y+y>0 && b.block[y][x] !=0) {
                setcolor(b.color);
                gotoxy(b.x+x, b.y+y);
                putchar(32);
            }
        }
    }
    b.y= y2;
    b.x= x2;
    for(int y = 0; y < b.rank_b ;y ++){
        for(int x = 0;x< b.rank_b ;x++){
            if(b.y+y>0 && b.block[y][x] !=0){
                setcolor(b.color);
                gotoxy(b.x+x,b.y+y);
                putchar(219);
            }
        }
    }
}
//
//
bool isCollide(block &b,screen &scr,int x2, int y2){             //kiểm tra di chuyen
    for (int y = 0; y < b.rank_b; y++){
        for (int x = 0; x < b.rank_b; x++){
            if(x2+x<1|| x2+x>=scr.x-1)
                if(b.block[y][x]!=0)return true;
            if (y2+y>=0
                &&b.block[y][x]!=0
                && scr.field[y2 + y][x2 + x]!=0 ) return true;
        }
    }
    return false;
}
//
void userInput(block &b,screen &scr){
    Sleep(20);
    if(GetAsyncKeyState(VK_RIGHT))
        if (!isCollide(b, scr, b.x +1, b.y )){
            Sleep(30);
            moveBlock(b, scr, b.x +1, b.y);
        }
    if(GetAsyncKeyState(VK_LEFT))
        if (!isCollide(b, scr, b.x -1, b.y)){
                Sleep(30);
            moveBlock(b, scr, b.x -1, b.y);
        }
    if(GetAsyncKeyState(VK_DOWN))
        if (!isCollide(b, scr, b.x , b.y+1)){
                Sleep(10);
            moveBlock(b, scr, b.x , b.y+1);
        }
    if(GetAsyncKeyState(VK_UP)){
        rotateBolck(b,scr);
        Sleep(50);
    }
}
//
bool rotateBolck(block &b,screen &scr){                          //xoay khối
    struct block b2;
    b2=b;

    for (int y = 0; y < b.rank_b; y++){ //xoay khối
        for (int  x =0; x < b.rank_b; x++){
            b.block[y][x] = b2.block[3 - x][y];
        }
    }

    if (isCollide(b,scr,b.x,b.y)){ // dừng nếu khối không thể xoay
        for (int  i = 0; i < b.rank_b; i++){
            for (int  j = 0; j < b.rank_b; j++){
                b.block[i][j] = b2.block[i][j];
            }
        }
        return true;
    }
    for (int y = 0; y < b2.rank_b; y++){
        for (int  x = 0; x < b2.rank_b; x++){
            if(b2.y+y>0 && b2.block[y][x] !=0) {
                setcolor(b.color);
                gotoxy(b2.x+x, b2.y+y);
                putchar(32);
            }
        }
    }
     moveBlock(b, scr, b.x , b.y);
    return false;
}
//
bool test_score(int y, screen &scr){
    for(int x=1;x<scr.x-1;x++){
        if(scr.field[y][x]==0||scr.field[y][x]==9) return false;
    }
    return true;
}
//
void sun_score(block &b,them &score, screen &scr){
    int temp=0;
    for(int y=0;y<b.rank_b;y++){
        if(test_score(b.y + y ,scr)) {
            temp++;
            for(int row=b.y + y ; row>0 ; row--){
                for(int column =1; column<scr.x -2;column++){
                    if(row != 0)
                        scr.field[row][column]=scr.field[row-1][column];
                    else scr.field[row][column]=0;
                }
            }
        }
    }
    Sleep(10);
    score.content+= temp*temp;
    if(temp>0)display(scr,b, score);
    else setcolor(b.color);
}
//
//
