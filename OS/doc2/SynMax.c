#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#define MAXPRO 50       //此处定义估计最大的进程数，可以设为很大
#define SELLP 10000
int main(void)
{
	int max=0;
pid_t pid,pids[MAXPRO+1];
int i,l=0;
	for (max=1;max<MAXPRO;max++)
{
    pid=fork();             //不断创建进程
    if (pid<0) break;
	else if (pid>0)
	{
        printf("\nFork process %d %d:",pid,max);
		pids[max]=pid;
	}
	else
	{
		while(1)
               {
               	l++;    //进入死循环
               }
	}
}
for (i=1;i<max;i++)
{
	if(kill(pids[i],SIGKILL)<0)    //程序结束时将所有创建的进程强制关闭
	{
		printf("\nProcess %d cannot kill!",pids[i]);
	}
      else printf("\nProcess %d have been kill!",pids[i]);
}
printf("\nThe max processes number is :%d\n",max);  //输出最大值
return 1;
}