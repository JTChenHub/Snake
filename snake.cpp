#include<iostream>
#include<windows.h>
#include <conio.h>
#include<time.h>
using namespace std;
class snake;

struct snakebody
{
	int x,y;
	struct snakebody *next;
};
struct snakebody *headinsert(struct snakebody *p,int a,int b)//头插
{
	struct snakebody *q=new struct snakebody;
	q->next=p;
	q->x=a;
	q->y=b;
	return q;
}
struct snakebody *tailinsert(struct snakebody *p,int a,int b)//尾插
{
	struct snakebody *q=new struct snakebody;
	p->next=q;
	q->x=a;
	q->y=b;
	q->next=NULL;
	return q;
}
int findpoint(struct snakebody *p,int a,int b)
{
	while(p!=NULL)
	{
		if(p->x==a&&p->y==b)
			return 1;
		else
			p=p->next;
	}
	return 0;

}
void gotoxy(int x, int y)    //输出坐标 
{
        COORD pos;
        pos.X = x; 
        pos.Y = y; 
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
class snake
{
public:
	int W,H,part;
	int level;//游戏难度
	int x,y;//食物位置
	char state;//是否被吃
	struct snakebody  *snakehead,*snaketail;//蛇的头尾
	int length;//蛇长
	char sportstate,nextsportstate;//蛇的运动方向 和下一运动方向
	snake(int w=40,int h=40,int part=1)
	{
		w=w/2*2;
		W=w;
		H=h;
		x=0;
		y=0;
		state='n';
		this->part=part;
		snakehead=new struct snakebody;
		
		snakehead->x=6;
		snakehead->y=2;
		snaketail=new struct snakebody;
		snakehead->next=snaketail;
		snaketail->x=4;
		snaketail->y=2;
		snaketail->next=NULL;
		length=0;
		sportstate='D';
		nextsportstate='D';
	}
	void initial()
	{
		snakebody *p=snakehead;
		while(p=NULL)
		{
			p=p->next;
			delete snakehead;
			snakehead=p;
		}
		x=0;
		y=0;
		state='n';
		this->part=part;
		snakehead=new struct snakebody;
		
		snakehead->x=6;
		snakehead->y=2;
		snaketail=new struct snakebody;
		snakehead->next=snaketail;
		snaketail->x=4;
		snaketail->y=2;
		snaketail->next=NULL;
		length=0;
		sportstate='D';
		nextsportstate='D';
		

	}
	

	
		void go_w()
	{
			gotoxy(snaketail->x,snaketail->y);
				cout<<"  ";
			gotoxy(snakehead->x,snakehead->y);
				cout<<"■";
			gotoxy(snakehead->x,snakehead->y-1);
				cout<<"★";
		if (snaketail==snakehead)
		{
			snakehead->y=snakehead->y-1;
			snakehead->x=snakehead->x;
			return ;
		}
		else 
		{
		struct snakebody *p=snakehead;
		while(p->next->next!=NULL)
		{
			p=p->next;
	
		
		}
		p->next=NULL;
	
		
		snaketail->y=snakehead->y-1;
		snaketail->x=snakehead->x;
		snaketail->next=snakehead;
		snakehead=snaketail;
		snaketail=p;
		}
		
	}
	void go_s()
	{
		gotoxy(snaketail->x,snaketail->y);
				cout<<"  ";
			gotoxy(snakehead->x,snakehead->y);
				cout<<"■";
			gotoxy(snakehead->x,snakehead->y+1);
				cout<<"★";
		if (snaketail==snakehead)
		{
			snakehead->y=snakehead->y+1;
			snakehead->x=snakehead->x;
			return ;
		}
		else 
		{
		struct snakebody *p=snakehead;
		while(p->next->next!=NULL)
		{
			p=p->next;
	
		
		}
		p->next=NULL;
	
		
		snaketail->y=snakehead->y+1;
		snaketail->x=snakehead->x;
		snaketail->next=snakehead;
		snakehead=snaketail;
		snaketail=p;
		}
	}
	void go_a()
	{
		gotoxy(snaketail->x,snaketail->y);
				cout<<"  ";
			gotoxy(snakehead->x,snakehead->y);
				cout<<"■";
			gotoxy(snakehead->x-2,snakehead->y);
				cout<<"★";
		if (snaketail==snakehead)
		{
			snakehead->y=snakehead->y;
			snakehead->x=snakehead->x-2;
			return ;
		}
		else 
		{
		struct snakebody *p=snakehead;
		while(p->next->next!=NULL)
		{
			p=p->next;
	
		
		}
		p->next=NULL;
	
		
		snaketail->y=snakehead->y;
		snaketail->x=snakehead->x-2;
		snaketail->next=snakehead;
		snakehead=snaketail;
		snaketail=p;
		}
	}
	void go_d()
	{
		gotoxy(snaketail->x,snaketail->y);
				cout<<"  ";
			gotoxy(snakehead->x,snakehead->y);
				cout<<"■";
			gotoxy(snakehead->x+2,snakehead->y);
				cout<<"★";
		if (snaketail==snakehead)
		{
			snakehead->y=snakehead->y;
			snakehead->x=snakehead->x+2;
			return ;
		}
		else 
		{
		struct snakebody *p=snakehead;
		while(p->next->next!=NULL)
		{
			p=p->next;
	
		
		}
		p->next=NULL;
	
		
		snaketail->y=snakehead->y;
		snaketail->x=snakehead->x+2;
		snaketail->next=snakehead;
		snakehead=snaketail;
		snaketail=p;
		}
	}
	int judge_end()
	{
	
		if(snakehead->y==0||snakehead->y==(H-1)||snakehead->x==0||snakehead->x==(W*2-2))
			return 1;
		else if(part==2&&(snakehead->x==(W-1)*2||snakehead->x==(W/2)))
			return 1;
		
		if(snakehead!=snaketail)
		{
			if(findpoint(snakehead->next,snakehead->x,snakehead->y))
		return 1;
		}
		return 0;
	}
	int judge_eat()
	{
		if(x==snakehead->x&&y==snakehead->y)
		{
			state='n';
			return 1;
		}
		return 0;
	}
	void grow(int a,int b)
	{
		snaketail=tailinsert(snaketail,a,b);
		length++;
		gotoxy(a,b);
		cout<<"■";//a
	}
	int go()
	{
		if((sportstate=='W'&&nextsportstate=='W')||(sportstate=='W'&&nextsportstate=='S')||(sportstate=='D'&&nextsportstate=='W')||(sportstate=='A'&&nextsportstate=='W'))
		{	go_w();sportstate='W';}
		if((sportstate=='S'&&nextsportstate=='S')||(sportstate=='S'&&nextsportstate=='W')||(sportstate=='D'&&nextsportstate=='S')||(sportstate=='A'&&nextsportstate=='S'))
		{	go_s();sportstate='S';}
		if((sportstate=='A'&&nextsportstate=='A')||(sportstate=='A'&&nextsportstate=='D')||(sportstate=='W'&&nextsportstate=='A')||(sportstate=='S'&&nextsportstate=='A'))
		{	go_a();sportstate='A';}
		if((sportstate=='D'&&nextsportstate=='D')||(sportstate=='D'&&nextsportstate=='A')||(sportstate=='W'&&nextsportstate=='D')||(sportstate=='S'&&nextsportstate=='D'))
		{	go_d();sportstate='D';}
		if(nextsportstate=='0')
			return 1;
		Sleep(500-10*level);
		return 0;
	}
	~snake()
	{
		snakebody *p=snakehead;
		while(p=NULL)
		{
			p=p->next;
			delete snakehead;
			snakehead=p;
		}
	}
};


void window()
{
	SetConsoleTitle("贪吃蛇2");
	system("mode con cols=100 lines=45");//改变宽高
    system("color B0");//改变颜色

}
void showmap(snake a)
{
	system("cls");
	for(int i=0;i<a.W;i++)
		cout<<"■";
	cout<<endl;
	for(i=1;i<a.H-1;i++)
		{	int j=0;
			cout<<"■";
			for(j=2;j<(a.W-1)*2;j++)
				cout<<' ';
			cout<<"■"<<endl;
		}
	for(i=0;i<a.W;i++)
		cout<<"■";
	cout<<endl;
	gotoxy(82,4);
	cout<<"level:"<<a.level;
	gotoxy(82,6);
	cout<<"分数:"<<a.length;
}
void showdate(snake a)
{
	gotoxy(88,4);
	cout<<a.level;
	gotoxy(87,6);
	cout<<a.length;
}
void senddcdate();
void control();
void makefood();
void showfood();
snake c;
int flog=1;
int main()
{

	window();
	char date[100];
	HANDLE send,sendcdate;
	char temp[50];
	char *cdate=temp;
	snake *a=&c;
	int x1,y1,i;
	HANDLE hthread[3];
	for(i=0;i<50;i++)
		cdate[i]=' ';
	//cout<<endl<<endl<<endl<<"                        "<<"欢迎来到贪吃蛇游戏"<<endl<<endl<<endl
	//	<<"                          "<<"请选择游戏类型"<<endl<<"                          "<<"1,单人游戏"<<endl<<"                          "<<"2,双人游戏"<<endl<<"                          "<<"0,退出游戏"<<endl;
	//cout<<endl<<"                      "<<"请输入序号1,2或0来选择"<<endl;
	//a->part=int(getch())-48;
	//while((a->part!=1)&&(a->part!=2)&&(a->part!=0))	
	//a->part=int(getch())-48;
	//if(a->part==0)
	//	return 1;
	cout<<endl<<endl<<endl<<"                        "<<"欢迎来到贪吃蛇游戏";
		Sleep(500);
start:	system("cls");
	cout<<endl<<endl<<endl<<"                        "<<"请选择游戏难度"<<endl<<"                "<<"可在0~50中选择，级别越高越难"<<endl<<"level:";
	cin>>a->level;
	while(a->level<0||a->level>50)
	{
		cout<<"输入不合法，请重新输入"<<endl<<"level:";
		cin>>a->level;
	}
again:	system("cls");
	cout<<endl<<endl<<endl<<endl<<"               "<<"通过W S A D控制上下左右,按Q键退出"<<endl<<"              为了更好的游戏建议将字体调小页面调大";

	Sleep(1000);
	hthread[0]=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)control,NULL,0,NULL);
	hthread[1]=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)makefood,NULL,0,NULL);
	showmap(c);
	sendcdate=CreateFile("\\\\.\\pipe\\currentdatepipe",GENERIC_WRITE,0,NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	cdate[0]='1';cdate[2]=(char)(c.level/10+48);cdate[3]=(char)(c.level%10+48);cdate[5]='0';cdate[6]='0';cdate[7]='0';//0是状态位 2与3存level 567存分数
	WriteFile(sendcdate,cdate,50,NULL,NULL);
	flog=1;
    //hthread[2]=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)senddcdate,cdate,0,NULL);
	while(1)
	{
		if(a->judge_end())
			break;
		x1=a->snaketail->x;
		y1=a->snakehead->y;
		showfood();
		a->go();
		showdate(c);
		if(a->judge_eat())
			a->grow(x1,y1);
		if(c.nextsportstate=='0')
			break;
	

	}
//	CloseHandle(hthread[2]);
	sendcdate=CreateFile("\\\\.\\pipe\\currentdatepipe",GENERIC_WRITE,0,NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	for(i=0;i<50;i++)
		cdate[i]=' ';
	cdate[0]='0';
	WriteFile(sendcdate,cdate,50,NULL,NULL);
	flog=0;
	CloseHandle(hthread[0]);
	CloseHandle(hthread[1]);
	system("cls");
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<"                         "<<"GAME OVER"<<endl<<endl<<endl<<"                  "<<"本次分数:"<<a->length<<"   "<<"level:"<<a->level<<endl<<endl<<endl<<endl;
	send=CreateFile("\\\\.\\pipe\\datepipe",GENERIC_WRITE,0,NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	sprintf(date,"%d %d",c.level,c.length);
	WriteFile(send,date,strlen(date),NULL,NULL);
	memset(date,0,100);
	cout<<"                    输入"<<"1"<<"再来一次"<<endl;
	cout<<"                    输入"<<"2"<<"回到开始"<<endl;
	cout<<"                    输入"<<"0"<<"退出游戏"<<endl;
	while(1)
	{
		c.nextsportstate=getch();
		if(c.nextsportstate=='1')
		{
			c.initial();
			goto again;
		}
		else if(c.nextsportstate=='2')
		{
			c.initial ();
			goto start;
		}
		else if(c.nextsportstate=='0')
			return 0;
	}
		
	//Sleep(10000);
//	cin.get();
	//cin.get();
//	return 0;
}
void control()
{
	char b;
	while(1)
	{
	b=getch();
	
	if(flog==0)
		return;
		if(b=='w'||b=='W')
			c.nextsportstate='W';
		else if(b=='s'||b=='S')
			c.nextsportstate='S';
		else if(b=='a'||b=='A')
			c.nextsportstate='A';
		else if(b=='D'||b=='d')
			c.nextsportstate='D';
	else if(b=='1')
		c.nextsportstate='1';
	else if(b=='2')
		c.nextsportstate='2';
	else if(b=='0')
	{
		c.nextsportstate='0';
		return;
	}
	}
	return ;
}
void makefood()
	{
		while(1)
		if(c.state=='n')
		{
			srand(time(0));
			int m=rand()%c.H;
			int n=rand()%c.W*2;
			if(m==0||m>=c.H-1||n==0||n>=(c.W-1)*2)
				continue;
			if(c.part==2&&(n==(c.W/2-1)||n==(c.W/2)))
				continue;
			if(findpoint(c.snakehead,n,m))
				continue;
			c.x=n;
			c.y=m;
			c.state='y';
		}
		return ;
	}
void showfood()
{
	if(c.state=='y')
	{
		gotoxy(c.x,c.y);
		cout<<"●";
	}
}
/*void senddcdate(char *cdate)
{
	HANDLE sendcdate1;
	int a=c.level,b=0;
	while(1)
	{
	if(b!=c.length)
	{
		b=c.length;
		sendcdate1=CreateFile("\\\\.\\pipe\\currentdatepipe",GENERIC_WRITE,0,NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		cdate[5]=(char)(c.length/100+48);cdate[6]=(char)(c.length/10%10+48);cdate[7]=(char)(c.length%10+48);//0是状态位 2与3存level 567存分数
		WriteFile(sendcdate1,cdate,50,NULL,NULL);
	}
	}
	while(1)
		;
	return;
}*/