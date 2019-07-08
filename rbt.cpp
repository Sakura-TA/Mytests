#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
using namespace std;

class node
{
public:
	node *lson;
	node *rson;
	node *parent;
	int value;
	bool islson;
	bool red;
	void turn(bool l)
	{
		if(!l)
		{
			if(lson!=NULL)parent->rson=lson,lson->islson=false,lson->parent=parent;
			else parent->rson=NULL;
			islson=parent->islson,lson=parent;
			if(parent->parent==NULL);
			else if(parent->islson) parent->parent->lson=this;
			else parent->parent->rson=this;
			parent=lson->parent,lson->parent=this,lson->islson=true;
		}
		else
		{
			parent->lson=rson;
			if(rson!=NULL) rson->islson=true,rson->parent=parent;
			islson=parent->islson,rson=parent;
			if(parent->parent==NULL);
			else if(parent->islson) parent->parent->lson=this;
			else parent->parent->rson=this;
			parent=rson->parent,rson->parent=this,rson->islson=false;
		}
	}
	void checkinsert()
	{
		if(parent==NULL) red=false;
		else if(!parent->red) return;
		else{
			node *pp=parent->parent;
			if(pp->lson!=NULL&&pp->rson!=NULL&&pp->lson->red&&pp->rson->red)
			{
				pp->lson->red=pp->rson->red=false;
				pp->red=true;
				pp->checkinsert();
			}
			else
			{
				if(parent->islson==islson)
				{
					parent->red=false;
					parent->parent->red=true;
					parent->turn(islson);
				}
				else
				{
					node *t=parent;
					turn(islson);
					t->checkinsert();
				}
			}
		}
	}
	node(int val,node *p,bool l)
	{
		value=val;
		lson=NULL;
		rson=NULL;
		islson=l;
		parent=p;
		red=true;
		checkinsert();
	}
	node* getlson(){return lson;}
	node* getrson(){return rson;}
	int getvalue(){return value;}	
	void insert(int val)
	{
		if(val<value)
		{
			if(lson==NULL) lson=new node(val,this,true);
			else lson->insert(val);
		}
		else if(val==value) return;
		else
		{
			if(rson==NULL) rson=new node(val,this,false);
			else rson->insert(val);
		}
	}
	void mprint()
	{
		if(lson!=NULL) lson->mprint();
		cout<<value<<" "<<islson<<" "<<(lson==NULL?"NULL":"L")<<" "<<(rson==NULL?"NULL":"R")<<endl;
		if(rson!=NULL) rson->mprint();
	}
};

int main()
{
	srand(time(0));
	node *root=NULL,*t=NULL;
	int x;
	for(int i=0;i<3;i++)
	{
		cin>>x;
		if(root==NULL) root=new node(x,NULL,false);
		else root->insert(x);
		while(root->parent!=NULL) root=root->parent;
	}
	root->mprint();
	cout<<endl;
}
