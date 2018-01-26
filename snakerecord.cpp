#include<iostream>
#include<windows.h>
#include <conio.h>
#include<time.h>
#include<fstream>
using namespace std;
struct senddate
{
	int a,b;
	time_t c;
};
void showtime(time_t timep)
{
	
	struct tm *p=localtime(&timep);
	cout<<p->tm_year+1900<<"."<<p->tm_mon+1<<"."<<p->tm_mday<<" "<<p->tm_hour<<":"<<p->tm_min<<":"<<p->tm_sec;
}
void writetime(time_t timep,ofstream &a)
{
	struct tm *p=localtime(&timep);
	a<<p->tm_year+1900<<"."<<p->tm_mon+1<<"."<<p->tm_mday<<" "<<p->tm_hour<<":"<<p->tm_min<<":"<<p->tm_sec;
}
void gotoxy(int x, int y)    //输出坐标 
{
        COORD pos;
        pos.X = x; 
        pos.Y = y; 
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void main()
{
	system("mode con cols=40 lines=45");
	time_t t=0;
	SetConsoleTitle("贪吃蛇2游戏记录");
	senddate maxd;
	fstream snakedate1("snakedate");
	char  z[100];
	while(snakedate1.getline(z,sizeof(z)))
	{
		
		cout<<z<<endl;
	}
	ifstream maxdate("maxdate");
	maxdate>>maxd.a>>maxd.b>>maxd.c;
	maxdate.close();
	snakedate1.close();
	ofstream snakedate("snakedate",ofstream::app);
	HANDLE sharefile=OpenFileMapping(FILE_MAP_ALL_ACCESS,0,"myMapFile");
	 if(sharefile == NULL)
				{	
				  DWORD dwInfo = GetLastError();
				  printf("服务器未启动\n");
				  Sleep(1000);
				  return;
				}
	struct senddate *date=(struct senddate*)MapViewOfFile(sharefile,FILE_MAP_ALL_ACCESS,0,0,0);
	while(1)
	{
		if(t!=date->c)
		{
		showtime(date->c);
		t=date->c;
		cout<<" level:"<<date->a<<" score:"<<date->b<<endl;
		writetime(date->c,snakedate);
		snakedate<<" level:"<<date->a<<" score:"<<date->b<<endl;
		if(date->b>maxd.b)
		{
			ofstream maxdate("maxdate");
			maxdate<<date->a<<" "<<date->b<<" "<<date->c;
			maxd.b=date->b;
			maxdate.close();
		}
		}
		
	}
}