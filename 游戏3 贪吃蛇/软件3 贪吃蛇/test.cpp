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
#include"БъЭЗ.h"

static int timee[11] = { 0 };
bool timer(int ms, int id) {
	int q = clock();
	cout << "ege";
	if (q - timee[id] >= ms)
	{
		timee[id] = q;
		return 1;
	}
	return 0;
}
int main() {
	if (timer(400, 2))cout<< timer(400, 2);

	system("pause");
}