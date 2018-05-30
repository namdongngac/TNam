#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "Console.h"

using namespace std;

#define ConsoleW 25
#define ConsoleH 25

class Pos2D
{
	public:
		char s[20];
		char a[20];
		int x; int y;
		int hp;	
};

class Object
{
	public:
		Pos2D multi[25];
};

Pos2D Plane;
Object Bullet;
Object Bullet2;
Object Fly;
Pos2D Boss;
Object BulletBoss;
Object Item_life;
Object Item_bullet;
Object Fly2;
bool endgame, sumBoss;
int score, life, newBosshp, levelBullet ;
int iBullet, iFly, iBulletBoss;
int bulPlane, bulBoss;
int tempFly, tempFly2, tempBoss;
int countfly, countfly2, countlife, countbullet, countplane;

//ham khoi tao vat the
void create(Pos2D & Object,int x,int y)
{
	Object.x = x;
	Object.y = y;
}

//ham khoi tao mot so gia tri ban dau
void Init()
{	
	create(Boss,rand()%ConsoleH-10,0);
	create(Plane,ConsoleW/2,ConsoleH-1);
	Boss.hp=20;
	newBosshp=Boss.hp;
	tempFly=15; tempFly2=40; tempBoss=15;
	endgame = false; sumBoss = false;
	score = 0; life = 3; levelBullet = 1;  
	countfly=0; countfly2=0; countlife=0; countbullet=0; countplane=0;
	iBullet=0; iFly=0; iBulletBoss=0;
	bulPlane=0; bulBoss=0;
	strcpy(Plane.s,">}^{<"); 
	strcpy(Boss.s,"=|[<>]|=");
	strcpy(Boss.a,"        ");
	for(int i=0;i<25;i++)
	{
		strcpy(Bullet.multi[i].s,"^");
		strcpy(Bullet.multi[i].a," ");
		strcpy(Bullet2.multi[i].s,"^ ^");
		strcpy(Bullet2.multi[i].a,"   ");
		strcpy(Fly.multi[i].s,">0<");
		strcpy(Fly.multi[i].a,"   ");
		strcpy(BulletBoss.multi[i].s,"||");
		strcpy(BulletBoss.multi[i].a,"  ");
		strcpy(Item_life.multi[i].s,"O");
		strcpy(Item_life.multi[i].a," ");
		strcpy(Item_bullet.multi[i].s,"$");
		strcpy(Item_bullet.multi[i].a," ");
		strcpy(Fly2.multi[i].s,"=)U(=");
		strcpy(Fly2.multi[i].a,"     ");
	}
	for(int i=0;i<25;i++)
	{
		Fly2.multi[i].hp = 5;
	}
	for(int i=0;i<25;i++)
	{
		Fly.multi[i].hp = 1;
	}
}

//ham xu li Boss
void sum(Pos2D & Boss, Object & BulletBoss,int & count,int tempBoss)
{
	gotoxy(Boss.x,Boss.y);
	cout<<Boss.a;
	Boss.y++;
	int ran=rand()%2+1;
	if(ran%2==0)
	{
		gotoxy(Boss.x,Boss.y);
		cout<<" ";
		Boss.x++;
		if(Boss.x>=ConsoleW-4)Boss.x--;
	}
	if(ran%2==1)
	{
		gotoxy(Boss.x+7,Boss.y);
		cout<<" ";
		Boss.x--;
		if(Boss.x<=0)Boss.x++;
	}
	if(Boss.y==3)Boss.y--;
	count++;
	if(bulBoss>0)
	{
		BulletBoss.multi[iBulletBoss].x=Boss.x+3;
		BulletBoss.multi[iBulletBoss].y=Boss.y+1;
		iBulletBoss++;
		bulBoss=0;
	}
	if(count%tempBoss==0)bulBoss=1;	
	if(iBulletBoss==24)iBulletBoss=0;
		
	for(int i=0;i<25;i++)
	{
		if(BulletBoss.multi[i].y>=0&&BulletBoss.multi[i].y<=ConsoleH&&BulletBoss.multi[i].x<=ConsoleW)
		{
			gotoxy(BulletBoss.multi[i].x, BulletBoss.multi[i].y);
			cout<<BulletBoss.multi[i].a;
			BulletBoss.multi[i].y++;
		}
		
			
	}
}

//ham xu li mang vat the
void createMul(Object & Object,int x, int y,int speed, int temp, int &count,int &iFly)
{
	int ran=rand()%temp;
	if(ran==10&&!sumBoss)
	{
		Object.multi[iFly].x=x;
		Object.multi[iFly].y=y;
		iFly++;	
	}
	if(iFly==24)iFly=0;	
	count++;
	for(int i=0;i<25;i++)
	{
		if(count%speed==0)
		{
			if(Object.multi[i].y>=0&&Object.multi[i].y<=ConsoleH&&Object.multi[i].x<=ConsoleW)
			{
				gotoxy(Object.multi[i].x,Object.multi[i].y);
				cout<<Object.multi[i].a;
				Object.multi[i].y++;
			}
		}		
	}
}

//ham ve vat the
void draw(Pos2D & Object,int color)
{	
	SetColor(color);	
	gotoxy(Object.x, Object.y);
	cout<<Object.s;
}

//ham ve mang vat the
void drawMul(Object & Object,int color)
{	
	for(int i=0;i<25;i++)
	{
		
		if(Object.multi[i].y>=0&&Object.multi[i].y<=ConsoleH&&Object.multi[i].x<=ConsoleW+2)
		{
			SetColor(color);
			gotoxy(Object.multi[i].x,Object.multi[i].y);
			cout<<Object.multi[i].s;
			
		}
	}
	
}

//ham xu li va cham loai 1 (mang vat the voi vat the)
void impact_1(Object & Object1, Pos2D & Object2, int left, int right, int mid,int live,int hp,int point,int tt)
{
	for(int i=0;i<25;i++){
			if((((Object2.x-Object1.multi[i].x)<=left&&(Object2.x-Object1.multi[i].x)>=mid)||((Object1.multi[i].x-Object2.x)<=right&&(Object1.multi[i].x-Object2.x)>=mid))&& Object2.y == Object1.multi[i].y)
			{
				gotoxy(Object1.multi[i].x,Object1.multi[i].y);
				cout<<Object1.multi[i].a;
				Object1.multi[i].x = 40; 
    			Object1.multi[i].y = 0;
    			if(life>=4)life--;
				life+=live;
				score+=point;
				levelBullet+=tt;
				Object2.hp-=hp;
				if(Object2.hp<=0)
				{
					gotoxy(Object2.x,Object2.y);
					cout<<Object2.a;
				}
				if(life<=0)endgame=true;
			}
	}
}

//ham xu li va cham loai 2 (mang vat the voi mang vat the)
void impact_2(Object & Object1, Object & Object2,int left, int right,int mid,int point,int hp)
{
	for(int i=0;i<25;i++){
		for(int j=0;j<25;j++){
			if((((Object2.multi[j].x-Object1.multi[i].x)<=left&&(Object2.multi[j].x-Object1.multi[i].x)>=mid)||((Object1.multi[i].x-Object2.multi[j].x)<=right&&(Object1.multi[i].x-Object2.multi[j].x)>=mid))&& Object2.multi[j].y == Object1.multi[i].y)
			{
				Object1.multi[i].x = 40;
				Object1.multi[i].y = 0;
				Object2.multi[j].hp-=hp;
				if(Object2.multi[j].hp<=0)
				{
					score+=point;
					gotoxy(Object2.multi[j].x,Object2.multi[j].y);
					cout<<Object2.multi[j].a;
					Object2.multi[j].x = 50; 
    				Object2.multi[j].y = 0;
				}		
			}
		}
	}
}

//ham xu li va cham loai 3 (vat the voi vat the)
void impact_3(Pos2D & Object1, Pos2D & Object2, int left, int right, int mid, int tt, int hp, int point)
{
	if((((Object2.x-Object1.x)<=left&&(Object2.x-Object1.x)>=mid)||((Object1.x-Object2.x)<=right&&(Object1.x-Object2.x)>=mid))&& Object2.y == Object1.y)
			{
				Object1.x = 40; 
    			Object1.y = 0;
    			if(life>=4)life--;
				life+=tt;
				score+=point;
				Object2.hp-=hp;
				if(life<=0)endgame=true;
			}
}

//ham dieu khien may bay
void movePlane(Pos2D & Plane)
{
	if (checkKey(KEY_LEFT))
	{
		gotoxy(Plane.x+4,Plane.y);
	    cout<<" ";
		Plane.x--;
		if(Plane.x < 0) Plane.x++;
	}
    else if (checkKey(KEY_RIGHT))
	{
		gotoxy(Plane.x,Plane.y);
	    cout<<" ";
		Plane.x++;
		if(Plane.x >= ConsoleW) Plane.x--;
	}
    else if (checkKey(KEY_UP))
	{
		gotoxy(Plane.x,Plane.y);
	    cout<<"     ";
		Plane.y--;
		if(Plane.y < 0) Plane.y++;
	}
    else if (checkKey(KEY_DOWN))
	{
		gotoxy(Plane.x,Plane.y);
	    cout<<"     ";
		Plane.y++;
		if(Plane.y >= ConsoleH) Plane.y--;
	}
	else if(checkKey(KEY_ESC))
		endgame=true;
}

//ham ban dan
void shoot(Pos2D & Plane, Object & Bullet, Object & Bullet2, int & iBullet, int &bulPlane,int & countplane)
{
	if (checkKey(KEY_A))
	{
		if(bulPlane>0&&levelBullet<2)
		{
			Bullet.multi[iBullet].x=Plane.x+2;
			Bullet.multi[iBullet].y=Plane.y-1;
			iBullet++;
			bulPlane=0;
		}
		if(bulPlane>0&&levelBullet>=2)
		{
			Bullet2.multi[iBullet].x=Plane.x+1;
			Bullet2.multi[iBullet].y=Plane.y-1;
			iBullet++;
			bulPlane=0;
		}
	}
	if(iBullet==20)iBullet=0;
	
	countplane++;
	if(countplane%5==0)bulPlane=1;	
	
	for(int i=0;i<20;i++)
	{
		gotoxy(Bullet.multi[i].x,Bullet.multi[i].y);
		cout<<Bullet.multi[i].a;
		Bullet.multi[i].y--;
		gotoxy(Bullet2.multi[i].x,Bullet2.multi[i].y);
		cout<<Bullet2.multi[i].a;
		Bullet2.multi[i].y--;
	}
}

//xu li game
void cregame()
{
	//xu li mang vat the
	createMul(Fly,rand()%ConsoleW+1,0,5,tempFly,countfly,iFly);
	createMul(Fly2,rand()%(ConsoleW-1)+1,0,4,tempFly2,countfly2,iFly);	
	createMul(Item_life,rand()%ConsoleW+1,0,2,500,countlife,iFly);
	createMul(Item_bullet,rand()%ConsoleW+1,0,2,500,countbullet,iFly);
	//xu li dan
	shoot(Plane,Bullet,Bullet2,iBullet,bulPlane,countplane);	
	//xu li va cham
	impact_1(Item_life,Plane,0,4,0,1,0,0,0);
	impact_1(Item_bullet,Plane,0,4,0,1,0,0,1);
	impact_1(Fly,Plane,2,4,0,-1,0,1,-1);
	impact_1(Fly2,Plane,4,4,0,-1,0,0,-1);
	impact_1(Bullet,Boss,0,7,0,0,1,0,0);
	impact_1(Bullet2,Boss,2,7,0,0,2,0,0);
	impact_1(BulletBoss,Plane,1,4,0,-1,0,0,-1);
	impact_2(Bullet,Fly,0,2,0,1,1);
	impact_2(Bullet2,Fly,2,2,0,1,1);
	impact_2(Bullet,Fly2,0,4,0,2,1);
	impact_2(Bullet2,Fly2,2,4,0,2,2);
	impact_3(Plane,Boss,4,7,0,-4,0,0);
	//dieu khien may bay
	movePlane(Plane);
	//xu li cac bien thuc hien chay Boss
	if(score!=0&&score%50==0) sumBoss=true;
	if(sumBoss&&Boss.hp>0)
	{
		
		sum(Boss,BulletBoss,countfly,tempBoss);
	} 
	if(Boss.hp<=0)
	{
		for(int i=0;i<25;i++)
		{
			
			gotoxy(BulletBoss.multi[i].x, BulletBoss.multi[i].y);
			cout<<BulletBoss.multi[i].a;
			BulletBoss.multi[i].x=41;
			BulletBoss.multi[i].y=0;
			BulletBoss.multi[i].y++;
		}
		
		gotoxy(Boss.x,Boss.y);
		cout<<Boss.a;
		score+=10;
		sumBoss=false;
		Boss.hp=newBosshp+10;
		newBosshp=Boss.hp;
		if(tempFly>11) tempFly--;
		if(tempFly2>15) tempFly2--;
		if(tempBoss>5) tempBoss-=2;
	} 
	
}

//ve man hinh game
void drawgame()
{
	SetColor(15);
	
	for(int i=0;i<=ConsoleH;i++)
	{
		gotoxy(ConsoleW+4,i);
		cout<<(char)179;
	}
	gotoxy(0,ConsoleH);
	for(int i=0;i<ConsoleW+4;i++)
	{
		cout<<"_";
	}
    if(score>0&&score%50==0)sumBoss=true;
    SetColor(6);
    gotoxy(ConsoleW+10, ConsoleH/2);
    cout<<"Score: "<<score*100;
    gotoxy(ConsoleW+10,ConsoleH/2+1);
    cout<<"Life: ";
    SetColor(12);
    for(int i=0; i<life; i++) cout<<(char)3<<" ";
    cout<<"     ";
    draw(Plane,18);
 	drawMul(Bullet,14);	
	drawMul(Bullet2,14);
    drawMul(Fly,10);
    drawMul(Item_life,12);
    drawMul(Item_bullet,13);
	if(sumBoss)
	{
		draw(Boss,15);
		drawMul(BulletBoss,13);	
	}	
   	drawMul(Fly2,11);		
}

int main()
{
	resetgame:;
	ShowCur(false);
	srand(time(NULL));
	Init();
	while(!endgame)
	{	
		cregame();
		drawgame();
		Sleep(25);
	}
	while(1)
	{
		SetColor(12);
		gotoxy(ConsoleW/2-10,ConsoleH/2+2);
		cout<<"Do you want play again ?";
		gotoxy(ConsoleW/2-10,ConsoleH/2+3);
		cout<<"Press Y: YES  Press N: NO";
		if(checkKey(KEY_Y))
		{
			clrscr();
			goto resetgame;
		}
		if(checkKey(KEY_N))break;
	}
	return 0;
}
