#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;

int main()
{
	pid_t pid;
	int i=0;
	if(pid=fork())
	{
	//	wait(NULL);
		for(;i<100;i++) cout<<i<<" ";
	}
	else
	{
		if(fork()) cout<<1;
		else
		{
			wait(NULL);
			cout<<2;
		}
	}
}
