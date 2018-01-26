#include<iostream>
#include<windows.h>
#include <string>
#include<time.h>
#include <stdio.h>
#include<fstream>
using namespace std;
void gotoxy(int x, int y)    //输出坐标 
{
        COORD pos;
        pos.X = x; 
        pos.Y = y; 
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void color(int b)         //颜色函数 
{
    HANDLE hConsole = GetStdHandle((STD_OUTPUT_HANDLE)) ; 
    SetConsoleTextAttribute(hConsole,b) ;
} 
void opensnake()
{
	cout<<"           ";
	cout<<"贪";
	Sleep(100);
	cout<<"吃";
	Sleep(100);
	cout<<"蛇";
	Sleep(100);
	cout<<"启";
	Sleep(100);
	cout<<"动";
	Sleep(100);
	cout<<"中";
	Sleep(100);
	cout<<".";
	Sleep(100);
	cout<<".";
	Sleep(100);
	cout<<".";
	Sleep(500);
	PROCESS_INFORMATION information;
	STARTUPINFO si = { sizeof(si) };
	//si.dwX=0x000e0140;
	si.dwX=MAKEWORD(240,0001);
	CreateProcess(".\\Debug\\snake2.exe",NULL,NULL,NULL,1,CREATE_NEW_CONSOLE,NULL,NULL,&si,&information);
}
void opensnakerecord()
{
	cout<<"           ";
	cout<<"游";
	Sleep(100);
	cout<<"戏";
	Sleep(100);
	cout<<"记";
	Sleep(100);
	cout<<"录";
	Sleep(100);
	cout<<"打";
	Sleep(100);
	cout<<"开";
	Sleep(100);
	cout<<"中";
	Sleep(100);
	cout<<".";
	Sleep(100);
	cout<<".";
	Sleep(100);
	cout<<".";
	Sleep(500);
	PROCESS_INFORMATION information;
	STARTUPINFO si = { sizeof(si) };
	CreateProcess(".\\snakerecord.exe",NULL,NULL,NULL,1,CREATE_NEW_CONSOLE,NULL,NULL,&si,&information);
}
void showtime()
{
	time_t timep;
	struct tm *p;
	time (&timep);
	p=localtime(&timep);
	cout<<p->tm_year+1900<<"."<<p->tm_mon+1<<"."<<p->tm_mday<<" "<<p->tm_hour<<":"<<p->tm_min<<":"<<p->tm_sec;
}
void showtime(time_t timep)
{
	
	struct tm *p=localtime(&timep);
	cout<<p->tm_year+1900<<"."<<p->tm_mon+1<<"."<<p->tm_mday<<" "<<p->tm_hour<<":"<<p->tm_min<<":"<<p->tm_sec;
}
struct senddate
{
	int a,b;
	time_t c;
};
struct senddate maxdate;
void showstart()
{
	SetConsoleTitle("贪吃蛇2服务器");
	cout<<"           ";
	cout<<"服";
	Sleep(100);
	cout<<"务";
	Sleep(100);
	cout<<"器";
	Sleep(100);
	cout<<"启";
	Sleep(100);
	cout<<"动";
	Sleep(100);
	cout<<"中";
	Sleep(100);
	cout<<".";
	Sleep(100);
	cout<<".";
	Sleep(100);
	cout<<"."<<endl<<endl<<endl<<endl<<endl;
	opensnake();
	cout<<endl<<endl<<endl<<endl<<endl;
	opensnakerecord();
	cout<<endl<<endl<<endl<<endl<<endl;
	Sleep(1000);
	system("cls");
	//gotoxy(6,4);
//	cout<<"           游戏未开始";
	gotoxy(16,9);
	cout<<"游戏最高记录"<<endl;
	gotoxy(6,12);
	ifstream max;
	max.open("maxdate");
	if(max)
	{
		
	max>>maxdate.a>>maxdate.b>>maxdate.c;
	if(maxdate.c==0)
		goto zzzz;
	showtime(maxdate.c);
	cout<<" "<<"level:"<<maxdate.a<<"  "<<"最大分数:"<<maxdate.b<<endl;
	max.close();
	}
	else
	{
zzzz:
		cout<<"     暂无最高游戏记录"<<endl;
	}

}
CRITICAL_SECTION linjiequ;
void currentDate(char *cdate)
{
	gotoxy(15,4);
	cout<<"  游戏未进行";
	HANDLE currentsnakedate=CreateNamedPipe("\\\\.\\pipe\\currentdatepipe",PIPE_ACCESS_INBOUND,PIPE_TYPE_BYTE,PIPE_UNLIMITED_INSTANCES,0,0,1000,NULL);
	while(1)
	{
	//	HANDLE hCounter = OpenSemaphore(SEMAPHORE_ALL_ACCESS,FALSE,"MySemaphone");
	//	WaitForSingleObject(hCounter,INFINITE);
		EnterCriticalSection(&linjiequ);
		ConnectNamedPipe(currentsnakedate,NULL);
		ReadFile(currentsnakedate,cdate,50,NULL,NULL);
		if(cdate[0]=='0')
		{
			//EnterCriticalSection(&linjiequ);
			gotoxy(13,4);
			cout<<"                                     ";
			gotoxy(13,4);
			cout<<"    游戏未进行";
			//LeaveCriticalSection(&linjiequ);
		}
		else
		{
			//EnterCriticalSection(&linjiequ);
			gotoxy(13,4);
			cout<<"                                     ";
			gotoxy(13,4);
	//		cout<<"level:"<<cdate[2]<<cdate[3]<<" "<<"当前分数:"<<cdate[5]<<cdate[6]<<cdate[7];
			/*	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  
                            BACKGROUND_GREEN |  
                            BACKGROUND_BLUE |  
                            BACKGROUND_INTENSITY);*/
			cout<<"    游戏进行中";
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  BACKGROUND_BLACK);
			//LeaveCriticalSection(&linjiequ);
		}
		DisconnectNamedPipe(currentsnakedate);
		LeaveCriticalSection(&linjiequ);
	//	ReleaseSemaphore(hCounter,1,NULL);
		
	}
}
void main()
{
	::InitializeCriticalSection(&linjiequ);
	//HANDLE hSemaphore = CreateSemaphore(NULL,1,1,"MySemaphone");
	system("mode con cols=50 lines=20");
	HANDLE sharefile=CreateFileMapping((HANDLE)0xFFFFFFFF,NULL,PAGE_READWRITE,0,1024,"myMapFile");
	showstart();
	char *cdate=new char[50];

	HANDLE hthread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)currentDate,cdate,0,NULL);
	//char   buffer[MAX_PATH];   
	 //getcwd(buffer, MAX_PATH);   
    //printf( "The   current   directory   is:   %s ",   buffer); 
	char date[100];
	int level,score;
	int maxscore=maxdate.b;
	//char *p="\\\\.\\pipe\\datepipe";
	HANDLE snakedate=CreateNamedPipe("\\\\.\\pipe\\datepipe",PIPE_ACCESS_INBOUND,PIPE_TYPE_BYTE,PIPE_UNLIMITED_INSTANCES,0,0,1000,NULL);
	struct senddate *p1=(struct senddate*)MapViewOfFile(sharefile,FILE_MAP_ALL_ACCESS,0,0,0);
	p1->c=0;
//	HANDLE event=CreateEvent(0,0,0,0);
//	OVERLAPPED overlap={0,0,0,0,event};
    
	while(1)
	{
    ConnectNamedPipe(snakedate,NULL);
//	WaitForSingleObject(event,INFINITE);
	ReadFile(snakedate,date,100,NULL,NULL);
	sscanf(date,"%d %d",&level,&score);
	p1->a=level;
	p1->b=score;
	time(&p1->c);
	if(score>maxscore)
	{
		Sleep(100);
		//HANDLE hCounter = OpenSemaphore(SEMAPHORE_ALL_ACCESS,FALSE,"MySemaphone");
		//WaitForSingleObject(hCounter,INFINITE);
		//EnterCriticalSection(&linjiequ);
		maxscore=score;
		//system("cls");
			gotoxy(16,9);
	cout<<"游戏最高记录"<<endl;
	gotoxy(6,12);
	cout<<"                                                 ";
		gotoxy(6,12);
	showtime();
	cout<<" "<<"level:"<<level<<"  "<<"最大分数:"<<score;
//	LeaveCriticalSection(&linjiequ);
//	ReleaseSemaphore(hCounter,1,NULL);
	}
	memset(date,0,100);
	DisconnectNamedPipe(snakedate);
	}
	CloseHandle(hthread);
	
}