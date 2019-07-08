#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
using namespace std;

class node
{
	node *lson;
	node *rson;
	node *parent;
	int value;
public:
	node(int val,node *p)
	{
		value=val;
		lson=NULL;
		rson=NULL;
		parent=p;
	}
	node* getlson(){return lson;}
	node* getrson(){return rson;}
	int getvalue(){return value;}	
	void setlson(node * l){lson=l;}
	void setrson(node * r){rson=r;}
	void insert(int val)
	{
		if(val<value)
		{
			if(lson==NULL) lson=new node(val,this);
			else lson->insert(val);
		}
		else if(val==value) return;
		else
		{
			if(rson==NULL) rson=new node(val,this);
			else rson->insert(val);
		}
	}
	void mprint()
	{
		if(lson!=NULL) lson->mprint();
		cout<<" "<<value<<" ";
		if(rson!=NULL) rson->mprint();
	}
};

int main()
{
	srand(time(0));
	node *root=NULL,*t=NULL;
	int x;
	for(int i=0;i<10;i++)
	{
		x=rand()%100;
		if(root==NULL) root=new node(x,NULL);
		else root->insert(x);
	}
	root->mprint();
	cout<<endl;
}
