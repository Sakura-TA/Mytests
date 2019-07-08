#include<iostream>
#include<unistd.h>
using namespace std;

int atoi(char * t)
{
	int c=0;
	for(int i=0;*(t+i)!='\0';i++)	c*=10,c+=*(t+i)-'0';
	return c;
}
char* itoa(int i)
{
	string s="";
	while(i) s=(char)(i%10+'0')+s,i/=10;
	return (char *)s.data();
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
		s="tail -n ",s+=args[2],s+=" ",s+=args[1],s+=" > ",s+=".tmp.",s+=args[1];
		system((char *)s.data());
		s="head -n ",s+=itoa(atoi(args[3])-atoi(args[2])),s+=" .tmp.",s+=args[1];
		system((char *)s.data());
		cout<<endl;
		s="rm ",s+=".tmp.",s+=args[1],s+=" >/dev/null";
		system((char *)s.data());
	}
	return 0;

}
