#include <iostream>
#include <unistd.h>
using namespace std;

int main(int argv,char ** args)
{
	string s="\033[30m";
	cout<<s;
	if(argv==2)
	{
		int i=0;
		while(1)
		{
			s[3]=(char)('0'+i);
		//	system("clear");
			cout<<s;
			i++,i%=7;
			usleep(100000);
		}
	}
	return 0;
}
