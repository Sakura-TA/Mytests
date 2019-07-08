#include<iostream>
#include<cstring>
#include<cstdlib>
#include<unistd.h>
#include<cstdio>
using namespace std;

int height,width;
int dir[8][2]={{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
int c[50];
int Round=0,maxgene=0,maxseed=0;
void printline(int n,char t)
{
	for(int i=0;i<n;i++) cout<<t;
}
class lg
{
public:
	char ** mp;
	int lives=0,gene=0,seed=0;
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
			if((mp[(y+height+dir[i][0])%height][(x+width+dir[i][1])%width])>1) c++;
		}
		return c;
	}
	lg()
	{
		srand(seed=time(0));
		cout<<"Enter height width:"<<endl;
		cin>>height>>width;
		this->init();
		Round=1;
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				mp[i][j]=rand()&1<<1;
				if(mp[i][j]) lives++;
			}
		}
	}
	lg(int t)
	{
		srand(seed=time(0));
		this->init();
		Round++;
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
		this->seed=t->seed;
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
		cout<<"+";
		printline(width,'-');
		cout<<"+"<<endl;
		for(int i=0;i<height;i++)
		{
			cout<<"|";
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
			cout<<"|"<<endl;
		}
		cout<<"+";
		printline(width,'-');
		cout<<"+"<<endl;
		printf("Generation :%12d MaxGene :%12d Lives :%12d\n",gene,maxgene,lives);
		printf("Seed       :%12d MaxSeed :%12d Round :%12d\n",seed,maxseed,Round);
	//	cout<<"Lives      :"<<lives<<"MaxGene :"<<maxgene<<endl;
	//	cout<<"Generation :"<<gene<<"MaxSeed :"<<maxseed<<endl;
	//	cout<<"Seed       :"<<seed<<"Round   :"<<Round<<endl;
	}
};
bool checkSame()
{
	int t=c[0];
	for(int i=1;i<50;i++) if(t!=c[i]) return 0;
	return 1;
}
int main()
{
	lg *l=new lg();
	char t;
	while(1)
	{
		while(c[l->gene%50]=l->lives)
		{
			if(checkSame()) 
			{
				break;
			}
			l->print();
			l=new lg(l);
	//		cin>>t;
			usleep(100000);
			system("clear");
		}
		if(l->lives) if(l->gene-50>maxgene) maxgene=l->gene-50,maxseed=l->seed;
		else if(l->gene>maxgene) maxgene=l->gene,maxseed=l->seed;
	
		l=new lg(1);
	}
}
