#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<map>
#include<deque>
#include<list>
#include<queue>
#include<stack>
#include<set>
#define aa 10010
#define re(i,a,b) for(int i=a;i<b;i++)
typedef long long ll;
#define debug(x) cout<<endl<<#x<<": "<<x<<endl;
#define Range(a) a.begin(),a.end()
#include "time.h"
#include<easyx.h>
#include<graphics.h>
#include"标头.h"

#include<windows.h>
#include<Mmsystem.h>

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <thread>


static int timee[11]={0};
#define kuan 360
#define chang 510
bool timer(int ms,int id) {
	int q = clock();
	if (q - timee[id] >= ms)
	{
		timee[id] = q;
		return 1;
	}
	return 0;
}
struct snake {
	POINT a[aa];
	int direction;
	int speed;
	int size;
	int score;
}p;
struct SsnackK {
	int score;
	int x; int y;
}s1,s2;

static int snacksum = 0;
static int is_snack_exist=0;
static int snackstate = 0;
static bool cuowu = 0;
static int swiftint = 0;
char ch[20];

void effectf() {
	mciSendString(_T("open ./资源/得.mp3 alias bgm2"), 0, 0, 0);
	mciSendString("setaudio bgm2 volume to 3000", NULL, 0, NULL);
	mciSendString(_T("play bgm2"), 0, 0, 0);
	
}
void bgmf() {
	mciSendString("open ./资源/BGM04.mp3 alias bgm1", 0, 0, 0);
	mciSendString("setaudio bgm1 volume to 200", NULL, 0, NULL);
	mciSendString("play bgm1 repeat", 0, 0, 0);
}
void init() {
	
	
	thread bgm_thread(bgmf);
	this_thread::sleep_for(std::chrono::seconds(3));
	bgm_thread.join();
	


	p.speed = 17;
	p.direction = 1;
	p.size = 3;
	p.a[0].x = 105;
	p.a[0].y = 105;
	p.a[1].x = 105;
	p.a[1].y = p.a[0].y+15;
	p.a[2].x = 105;
	p.a[2].y = p.a[1].y+15;
	p.score = 0;

	settextstyle(20, 0, _T("楷书"));
}
int dist(int x1, int y1, int x2, int y2)
{
	int dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	return dist;
}//两点距离

IMAGE imgameover;
void loading() {
	loadimage(&imgameover, "资源/gameover.png");
}
bool control() {
	


	if (GetAsyncKeyState(VK_UP)&&p.direction!=2) { 
		p.a[0].y -= p.speed; 
		Sleep(150);
		p.direction = 1; 
		return 1;
	}
	else if (GetAsyncKeyState(VK_DOWN) && p.direction != 1) {
		p.a[0].y += p. speed;
		Sleep(150);
		p.direction = 2;
		return 1;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && p.direction != 3) {
		p.a[0].x += p.speed;
		Sleep(150);
		p.direction = 4;
		return 1;
	}
	else if (GetAsyncKeyState(VK_LEFT) && p.direction != 4) {
		p.a[0].x -= p. speed;
		Sleep(150);
		p.direction = 3;
		return 1;
	}
	
	return 0;
}

bool draw() {
	
	

	sprintf(ch, "%d", p.score);
	outtextxy(chang - 30, 0, ch);
	

	
	if(is_snack_exist == 0)
	if (snacksum < 3) {
		while (1) {//不刷蛇身上
			s1.x = rand()%chang + 1-5;
			s1.y = rand()%kuan + 1-5;
			for (int i = 0; i < p.size; i++) {//碰撞
				if (dist(s1.x+3,s1.y+3,p.a[i].x+15,p.a[i].y + 15)<=13)
					goto f1;
			}
			break;
		
		}
	f1:
		is_snack_exist = 1;
		snacksum++;
		snackstate = 0;
	}
	else {
		while (1) {
			s1.x = rand() % chang + 1-15;
			s1.y = rand() % kuan + 1-15;
			for (int i = 0; i < p.size; i++) {
				if (i == p.size && dist(s1.x + 8, s1.y + 8, p.a[i].x + 15, p.a[i].y + 15) <= 23)cout << "1!!!" << endl;
				if (dist(s1.x + 8, s1.y + 8, p.a[i].x + 15, p.a[i].y + 15) <= 23)
					goto f2;
				
			}
			break;
		
		}
	f2:
		is_snack_exist = 1;
		snacksum = 0;
		snackstate = 1;
	}

	if(is_snack_exist==1)
	if(snackstate == 0)solidcircle(s1.x, s1.y, 5);
	else solidcircle(s1.x, s1.y, 15);

	//蛇
	for (int i = 0; i < p.size; i++)
		solidrectangle(p.a[i].x, p.a[i].y, p.a[i].x + 15, p.a[i].y + 15);
	for (int i = p.size; i >= 0; i--)
		p.a[i + 1] = p.a[i];
	

	
	



	
	if (snackstate==1)
	{
		if (dist(s1.x +8, s1.y + 8, p.a[0].x + 15, p.a[0].y + 15) <= 23)
		{
			mciSendString("seek bgm2 to start", 0, 0, 0); 
			// ※将音效文件的播放位置重置到起始位置  因为mciSendString("play bgm2", 0, 0, 0);只是继续播放，这样会导致第二次无音效
			mciSendString("play bgm2", 0, 0, 0); // 播放音效
			
			 p.score += 3; p.size += 3; 
			is_snack_exist = 0;
		
			

		}
	}
	else {
		if (dist(s1.x + 3, s1.y + 3, p.a[0].x + 15, p.a[0].y + 15) <= 13) {
			mciSendString("seek bgm2 to start", 0, 0, 0); // 将音效文件的播放位置重置到起始位置
			mciSendString("play bgm2", 0, 0, 0); // 播放音效
		
			p.score += 1; p.size += 1;
			is_snack_exist = 0;
			
		}
	}

	//穿越
	if (p.a[0].x >= chang)p.a[0].x = 0;
	if (p.a[0].x < 0)p.a[0].x = chang;
	if (p.a[0].y >= kuan)p.a[0].y = 0;
	if (p.a[0].y < 0)p.a[0].y = kuan;
	
	//自身碰撞
	for (int i = p.size; i >=3; i--) {
		if (p.a[0].x==p.a[i].x&& p.a[0].y == p.a[i].y)return 1;
	}
	return 0;
	


	
}
int main() {
	srand((unsigned)time(0));
	initgraph(chang, kuan);
	initgraph(chang, kuan, SHOWCONSOLE);
	
	
	init();
	while (true) {
		setbkcolor(RGB(28, 140, 119));
		cleardevice();
		
		int t1 = clock();
		if(draw())goto endd;
		int t2 = clock() - t1;
		if (t2 <= 1000 / 30)Sleep(1000 / 30 - t2);
	}
endd:
	while(1)
	putimage(50, 100, &imgameover);

	system("pause");
}
