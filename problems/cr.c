#include <stdio.h>



int main()
{
	int n,a[400];
	scanf("%d",&n);
	for(int i =0;i<n;i++) scanf("%d",a+i);
	printf("来源:\n(");
	for(int i=0;i<n;i++)
	{
		if(i) printf(" ");
		printf("%d",a[i]);
	}
	printf(")\nInsert Sort:\n");
	for(int i=1;i<n;i++)
	{
		int num=i,j;
		for(j=0;j<=i;j++) if(a[j]>=a[num]) break;
	       		
		if(j!=i)
		{
			int tmp=a[i];
			for(int k=i;k>j;k--) a[k]=a[k-1];
			a[j]=tmp;
		}
		for(j=0;j<n;j++)
		{
			if(!j) printf("(");
			else printf(" ");
			printf("%d",a[j]);
			if(j==i) printf(")");
		}
		printf("\n");
	}
	printf("结果:\n");
	for(int i=0;i<n;i++)
	{
		if(i) printf(" ");
		printf("%d",a[i]);
	}
	return 0;
}
