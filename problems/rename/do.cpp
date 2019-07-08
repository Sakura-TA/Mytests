#include<iostream>
#include<fstream>
#include<cstdlib>
#include<sstream>
using namespace std;



int main()
{
	cout<<1;
	ifstream f;
	stringstream sstr;
	int num,t;
	string cmd="move Dirs/";
	system("ls Dirs >tmp.txt");
	f.open("tmp.txt",ios::in);
	string read,snum;
	while(f>>read)
	{
		snum="",t=0;
		while(read[t]<'0'||read[t]>'9') t++;
		while(read[t]>='0'||read[t]<='9') num*=10,num+=read[t]-'0';
		sstr<<num;
		system((char *)(cmd+read+" result/"+sstr.str()).data());
		cout<<cmd+read+" result/"+sstr.str()<<endl;
		num++;
		sstr.str("");
	}
}
