#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

char dir[8][2]={{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};

class gameMap
{
	int width;
	int height;
	int seed=-1;
	char **drawing;
	void initMap()
	{
		if(seed==-1) setSeed(time(0));
		srand(seed);
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<width;j++) drawing[i][j]=rand()&1?1:0;     //覆盖率            	
		}										
	}											
	bool isInMap(int x,int y) {return x>0&&y>0&&x<width&&y<height;}
	int countRoundWalls(int x,int y)
	{
		int c=0;
		for(int i=0;i<8;i++)
		{
			int ty=y+dir[i][0],tx=x+dir[i][1];
			if(isInMap(tx,ty))
			{
				if(drawing[ty][tx]!=0) c++;
			}
			else if(rand()&1) c++;                    //封闭率
		}
		return c+drawing[y][x];
	}
	void fillMap(int fc)
	{
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				drawing[i][j]=(countRoundWalls(j,i)>fc);
			}
		}
	}
public:
	void printMap()
	{
//		system("clear");
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				switch(drawing[i][j])
				{
					case 0: cout<<" ";break;
					case 1: cout<<(char)219;break;
					default: cout<<"?";
				}
			}
			cout<<endl;
		}
	}

	void setSeed(int s)
	{
		seed=s;
	}

	void init(int h,int w)
	{
		width=w,height=h;
		drawing=(char **)malloc(this->height*sizeof(char *));
       		for(int i=0;i<w;i++) drawing[i]=(char *)malloc((width+1)*sizeof(char));
	}


	gameMap(int h,int w,int s,int ft,int fc) //height width seed filltimes,fill const;
	{
		init(h,w);
		setSeed(s);
		initMap();
		for(int i=0;i<ft;i++) fillMap(fc);
	}
};

int main()
{
	int h,w,s,ft,fc=4;
	while(1)
	{
		cout<<"Enter test height,width,seed,filltimes"<<endl;
		cin>>h>>w>>s>>ft;
		gameMap test(h,w,s,ft,fc);
		test.printMap();
	}
}
