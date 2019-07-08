#include<pthread.h>
#include<iostream>
using namespace std;

void* q(void* args)
{
	cout<<1;
	return 0;
}

int main()
{
	pthread_t a;
	pthread_create(&a,NULL,q,NULL);
	return 0;
}
