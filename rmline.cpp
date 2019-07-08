#include<iostream>
#include<unistd.h>
using namespace std;

int atoi(char * t)
{
	int c=0;
	for(int i=0;*(t+i)!='\0';i++)	c*=10,c+=*(t+i)-'0';
	return c;
}
int main(int argv,char **args)
{
	string s;
	if(argv==2)
	{
		s="cat ",s+=args[1];
		system((char *)s.data());
	}
	if(argv==3) cout<<'?';
	if(argv==4)
	{
		s="head -n ",s+=args[2],s+=" ",s+=args[1],s+=" > ",s+=".tmp.",s+=args[1];
		system((char *)s.data());
		s="tail -n ",atoi(args[3]),s+=args[1],s+=" > ",s+=".tmp.",s+=args[1];
		system((char *)s.data());
		s="cat ",s+=".tmp.",s+=args[1];
		cout<<endl;
		s="rm ",s+=".tmp.",s+=args[1],s+=" >/dev/null";
		system((char *)s.data());
	}
	return 0;

}
