#include <pthread.h>
#include <iostream>
#include <unistd.h>
using namespace std;

void * tes(void *args)
{
	cout<<"test"<<*(int *)args<<endl;
	return 0;
}

int main()
{
	pthread_t tids[10];
	for(int i=0;i<10;i++)
	{
		int ret = pthread_create(&tids[i],NULL,tes,&i);
		if(ret!=0)
		{
			cout<<"pthread_create error: error_code="<<ret<<endl;

		}
	}
	 
	pthread_exit(NULL);
	return 0;
}

