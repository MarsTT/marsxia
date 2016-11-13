#include <stdio.h>
#include <stdlib.h>

//BOOL win(int n,int m);
//enum BOOL {False,Ture};
//#define f 0
#define False 0
#define True 1
int win(int n,int m);
int main()
{
	int n,m;
	while(1)
	{
		scanf("%d%d",&n,&m);
		printf("%d \n",win(n,m));
	}
	
	return 0;
}

int win(int n,int m)
{
//	bool f=0;
	int i;
	n%=(m+1)*2;//
	if(n>=1&&n<=m)
		return True;    
	else
	{
		for(i=1;i<=m;i++)
			if(n>=i)
				False+=!win(n-i,m);
		return False;
	}
}