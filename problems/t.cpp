#include<iostream>

using namespace std;

int mod(int a,int b)
{
	return a-a/b*b;
}
int main()
{
	cout<<mod(7,2);
}
