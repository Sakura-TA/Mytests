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
	printf(")\nBubble Sort:\n");
	for(int i=n-1;i>0;i--)
	{
		int tmp,j;
		for(j=0;j<i;j++) if(a[j]>=a[j+1]) tmp=a[j],a[j]=a[j+1],a[j+1]=tmp;
		for(j=0;j<n;j++)
		{
			if(!j) printf("(");
			else printf(" ");
			printf("%d",a[j]);
			if(j==i-1) printf(")");
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
