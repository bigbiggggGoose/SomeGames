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
#include"��ͷ.h"

#include<windows.h>
#include<Mmsystem.h>
//sound:
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <thread>
/*
���� ������ʱ������
*/

static int timee[11]={0};
#define kuan 360
#define chang 510
bool timer(int ms,int id) {//!!!  ��ѭ����ʱ q��while�·���ȡֵ����ʱ�ŷ���1 ���඼��0
	int q = clock();
	if (q - timee[id] >= ms)
	{
		timee[id] = q;
		return 1;
	}
	return 0;
}
struct snake {
	POINT a[aa];//point��һ��map
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
	mciSendString(_T("open ./��Դ/��.mp3 alias bgm2"), 0, 0, 0);
	mciSendString("setaudio bgm2 volume to 3000", NULL, 0, NULL);
	mciSendString(_T("play bgm2"), 0, 0, 0);
	
}
void bgmf() {
	mciSendString("open ./��Դ/BGM04.mp3 alias bgm1", 0, 0, 0);//alias+nameΪȡС�� 0��0��0�����ֲ���
	mciSendString("setaudio bgm1 volume to 200", NULL, 0, NULL);
	mciSendString("play bgm1 repeat", 0, 0, 0);
}
void init() {
	
	//(1)��ȡ��������䣺
	//	char res[260];
	//mciSendString("status 01.mp3 volume", res, 260, NULL);
	thread bgm_thread(bgmf);
	this_thread::sleep_for(std::chrono::seconds(3));
	bgm_thread.join();
	//��׺����.wav Ҫmp3
	


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

	settextstyle(20, 0, _T("����"));
}
int dist(int x1, int y1, int x2, int y2)
{
	int dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	return dist;
}//�������

IMAGE imgameover;
void loading() {
	loadimage(&imgameover, "��Դ/gameover.png");
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
//void gameover() {
//	goto endd;
//};
bool draw() {
	
	

	sprintf(ch, "%d", p.score);//�����ת�����Ͳ���
	outtextxy(chang - 30, 0, ch);
	

	//����  С  ��  λ�ü��
	//snack  timer  issnackexist
	if(is_snack_exist == 0)
	if (snacksum < 3) {
		while (1) {//��ˢ������
			s1.x = rand()%chang + 1-5;
			s1.y = rand()%kuan + 1-5;
			for (int i = 0; i < p.size; i++) {//����������Ľ����ײ����
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
		while (1) {//��ˢ������
			s1.x = rand() % chang + 1-15;
			s1.y = rand() % kuan + 1-15;
			for (int i = 0; i < p.size; i++) {//����������Ľ����ײ����
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

	//��
	for (int i = 0; i < p.size; i++)
		solidrectangle(p.a[i].x, p.a[i].y, p.a[i].x + 15, p.a[i].y + 15);
	for (int i = p.size; i >= 0; i--)
		p.a[i + 1] = p.a[i];
	

	
	

	{//̰���߽ű�  ����
		if (!control()) {
			switch (p.direction) {
			case 1:p.a[0].y -= p.speed; Sleep(300); break;
			case 2:p.a[0].y += p.speed; Sleep(300); break;
			case 3:p.a[0].x -= p.speed; Sleep(300); break;
			case 4:p.a[0].x += p.speed; Sleep(300); break;
			default:cout << "JI" << endl; break;
			}
		}
	}

	//{//��ʱsize�Ѿ�++// !!!!!!!!!!!!! �������ÿ���������⣡��
	//	
	//	for (int i = p.size; i >0; i--) {
	//		p.a[i ] = p.a[i-1];
	//	}
	//}

	//��   
	if (snackstate==1)
	{//��
		if (dist(s1.x +8, s1.y + 8, p.a[0].x + 15, p.a[0].y + 15) <= 23)
		{
			mciSendString("seek bgm2 to start", 0, 0, 0); 
			// ������Ч�ļ��Ĳ���λ�����õ���ʼλ��  ��ΪmciSendString("play bgm2", 0, 0, 0);ֻ�Ǽ������ţ������ᵼ�µڶ�������Ч
			mciSendString("play bgm2", 0, 0, 0); // ������Ч
			
			 p.score += 3; p.size += 3; 
			is_snack_exist = 0;
		
			

		}
	}
	else {
		if (dist(s1.x + 3, s1.y + 3, p.a[0].x + 15, p.a[0].y + 15) <= 13) {
			mciSendString("seek bgm2 to start", 0, 0, 0); // ����Ч�ļ��Ĳ���λ�����õ���ʼλ��
			mciSendString("play bgm2", 0, 0, 0); // ������Ч
		
			p.score += 1; p.size += 1;
			is_snack_exist = 0;
			
		}
	}

	//��Խ
	if (p.a[0].x >= chang)p.a[0].x = 0;
	if (p.a[0].x < 0)p.a[0].x = chang;
	if (p.a[0].y >= kuan)p.a[0].y = 0;
	if (p.a[0].y < 0)p.a[0].y = kuan;
	
	//������ײ
	for (int i = p.size; i >=3; i--) {//������ײ1��2
		if (p.a[0].x==p.a[i].x&& p.a[0].y == p.a[i].y)return 1;
	}
	return 0;
	


	
}
int main() {
	srand((unsigned)time(0));
	initgraph(chang, kuan);
	initgraph(chang, kuan, SHOWCONSOLE);//debug����������������ҰѴ���ŵ����ڴ��������
	
	
	init();
	while (true) {
		setbkcolor(RGB(28, 140, 119));//���̻�
		cleardevice();//Ҫ���������Ĳ�����
		
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