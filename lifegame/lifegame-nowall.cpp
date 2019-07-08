#include<iostream>
#include<cstring>
#include<cstdlib>
#include<unistd.h>
using namespace std;

int height,width;
int dir[8][2]={{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
class lg
{
public:
	char ** mp;
	int lives=0,gene=0;
	void init()
	{
		mp=(char **)malloc(sizeof(char*)*height);
		for(int i=0;i<width;i++)
		{
			mp[i]=(char *)malloc(sizeof(char)*(width+1));
		}
	}
	int calcSurround(int y,int x)
	{
		int c=0;
		for(int i=0;i<8;i++)
		{
			if((mp[(y+dir[i][1]<0?height-1:(y+dir[i][1])%height)][(x+dir[i][1]<0?width-1:(x+dir[i][0])%width)]>1)) c++;
		}
		return c;
	}
	lg()
	{
		cout<<"Enter height width:"<<endl;
		cin>>height>>width;
		this->init();
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				mp[i][j]=rand()&1<<1;
				if(mp[i][j]) lives++;
			}
		}
	}
	lg(lg *t)
	{
		int c;
		this->init();
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				c=t->calcSurround(i,j);
				if(t->mp[i][j]>1)
				{
					if(c==2||c==3) mp[i][j]=2,lives++;
					else mp[i][j]=1;
				}					// 0 死 1新死 2生 3新生
				else if(c==3) mp[i][j]=3,lives++;
				else mp[i][j]=0;
			}
		}
		gene=t->gene+1;
	} 
	void print()
	{
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				switch(mp[i][j])
				{
					case 0: cout<<" ";break;
					case 1: cout<<" ";break;
					case 2: cout<<"O";break;
					case 3: cout<<"0";break;
					default:cout<<"?";break;
				}
			}
			cout<<endl;
		}
		cout<<"Lives :"<<lives<<endl;
		cout<<"Generation :"<<gene<<endl;
	}
};

int main()
{
	srand(time(0));
	lg *l=new lg();
	char t;
	while(l->lives)
	{
		l->print();
		l=new lg(l);
	//	cin>>t;
		usleep(100000);
	}
}
