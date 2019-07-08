#include<iostream>
using namespace std;

int atoi(char * t)
{
	int c=0;
	for(int i=0;*(t+i);i++)	c*=10,c+=*(t+i)-'0';
	return c;
}

int main(int argv,char ** args)
{
	int i=atoi(args[1]);
	int n=atoi(args[2]);
	while(i<=n) cout<<i<<endl,i++;
}

