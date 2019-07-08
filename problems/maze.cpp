#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <termio.h>
using namespace std;

string blockX=" ";
string blockY=" ";
int zp;
int size[2];
int startPoint[2];
int endPoint[2];
int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};

int scanKeyBoard()
{
	int in;
	struct termios new_settings;
	struct termios stored_settings;
	tcgetattr(0,&stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ICANON);
	new_settings.c_cc[VTIME] = 0;
	tcgetattr(0,&stored_settings);
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0,TCSANOW,&new_settings);
 
	in = getchar();
	tcsetattr(0,TCSANOW,&stored_settings);
	return in;
}

class randQueue
{
private:
	int data[1001];
	int top=-1;
public:
	void push(int ptr)
	{
		data[++top]=ptr;
	}
	bool empty()
	{
		return top<0;
	}
	int pop()
	{
		int ptr=rand()%(top+1);
		int tmpData=data[ptr];
		memcpy(&data[ptr],&data[ptr+1],sizeof(int)*(top-ptr));
		top--;
	//	for(int i=0;i<=top;i++) cout<<i<<":"<<data[i]<<endl;
	//	cout<<"out:"<<tmpData<<endl<<endl;
		return tmpData;
	}
};

randQueue rq;

class gameMap
{
private:
	char theMap[1000][1000];
	char flagMap[1000][1000]={0};
public:
	void roundPush(int x,int y)
	{
		for(int i=0;i<4;i++)
		{
			if(x+dir[i][0]>=0&&y+dir[i][1]>=0&&x+dir[i][0]<size[0]&&y+dir[i][1]<size[1]) //图样函数
			{
				if(!flagMap[x+dir[i][0]][y+dir[i][1]]) 
				{
					flagMap[x+dir[i][0]][y+dir[i][1]]=1;
					rq.push((x+dir[i][0])*10000+y+dir[i][1]);
				}
			}
			
		}
	}
	void randConnect(int x,int y)
	{
		int connections=0;
		bool used[4]={0};
		for(int i=0;i<4;i++)
		{
			if(x+dir[i][0]>=0&&y+dir[i][1]>=0&&x+dir[i][0]<size[0]&&y+dir[i][1]<size[1]) //同上
			{
				if(flagMap[x+dir[i][0]][y+dir[i][1]]==2) 
					if(!(rand()%50)) 						//连通概率
						theMap[x*2+1+dir[i][0]][y*2+1+dir[i][1]]=1,connections++;
			}
		}
		while(connections<1)           //最低连通数
		{
			int t;
			while(t=rand()%4,used[t]||!(x+dir[t][0]>=0&&y+dir[t][1]>=0&&x+dir[t][0]<size[0]&&y+dir[t][1]<size[1]&&flagMap[x+dir[t][0]][y+dir[t][1]]==2));
			theMap[x*2+1+dir[t][0]][y*2+1+dir[t][1]]=1,connections++;
		}
		flagMap[x][y]++;
		roundPush(x,y);
	}
	void print()
	{
		for(int i=0;i<=(size[1]<<1);i++)
		{
			for(int j=0;j<=(size[0]<<1);j++)
			{
				if(theMap[j][i]<2)
				{
					if(!theMap[j][i]) printf("\033[47m \033[40m");
					else printf(" ");
				}
				else 
				{
					if(theMap[j][i]=='S') printf("\033[s");
					cout<<theMap[j][i];
				}
			}
			printf("\n");
		}
		printf("\033[u");

	}


	void initMap(int width,int height)
	{
		for(int i=0;i<=(width<<1);i++)
		{
			for(int j=0;j<=(height<<1);j++)
			{
				theMap[i][j]=(i&1 && j&1);
			}
		}
		theMap[startPoint[0]*2+1][startPoint[1]*2+1]='S';
		theMap[endPoint[0]*2+1][endPoint[1]*2+1]='E';
		flagMap[startPoint[0]][startPoint[1]]=2;
		roundPush(startPoint[0],startPoint[1]);
		while(!rq.empty())
		{
			int nptr=rq.pop();
			randConnect(nptr/10000,nptr%10000);
			int t;
		//	print();
		//	cin>>t;
		}       		
	}
	gameMap(int width,int height)
	{
		size[0]=width,size[1]=height;
		initMap(width,height);
	}
	bool checkDir(int n)
	{
		return (theMap[startPoint[0]*2+1+dir[n][0]][startPoint[1]*2+1+dir[n][1]]);
	}
	void eraInput()
	{
		printf("\033[%dD%c",1,theMap[startPoint[0]][startPoint[1]]);
	}
};

class weakPointer
{
public:
	weakPointer(int x,int y)
	{
		coor[0]=x,coor[1]=y;
	}
	int getx(){return coor[0];}
	int gety(){return coor[1];}
	void moveTo(int x,int y)
	{
		if(x>coor[0])
		{
			printf("\33[%dC",(x-coor[0])*(1+blockX.length()));
		}
		else printf("\33[%dD",(coor[0]-x)*(1+blockX.length()));
		coor[0]=x;
		if(y>coor[1])
		{
			printf("\33[%dA",(y-coor[1])*(1+blockY.length()));
		}
		else printf("\33[%dB",(coor[1]-y)*(1+blockY.length()));
		coor[1]=y;
	}
	void printLine(int type,string s)
	{
		int tmp=s.length();
		if(!type) for(int i=0;i<tmp;i++) cout<<s[i]<<blockX,coor[0]+=1+blockX.length();
		else if(type)
		{
			for(int i=0;i<tmp;i++)
			{
				cout<<s[i],coor[0];
				for(int j=0;j<blockY.length();j++)
				{
					printf("\033[%dD",1);
					switch(type)
					{
						case 3:printf("\033[%dB",2);break;
						case 2:printf("\033[%dD",2);break;
						case 1:printf("\033[%dA",2);break;
					}
					coor[1]--;
					cout<<blockY[j],coor[0];
				}
				printf("\033[%dD",1);
				coor[1]--;
			}
		}
	}

private:
	int coor[2];
};

int main()
{
	srand(time(0));
	startPoint[0]=0,startPoint[1]=0,endPoint[0]=99,endPoint[1]=24;
	gameMap test(100,25);
	test.print();
	weakPointer p(3,3);
	char key;
	while(startPoint[0]!=endPoint[0]&&startPoint[1]!=endPoint[1])
	{
		key=scanKeyBoard();
		test.eraInput();
		if(key=='s') key=3;
		else if(key=='a') key=2;
		else if(key=='w') key=1;
		else if(key=='d') key=0;
		else continue;
		if(test.checkDir(key))
		{
			startPoint[0]+=dir[key][0],startPoint[1]+=dir[1][0];
			p.printLine(key,"S");	
		}

	}
}
