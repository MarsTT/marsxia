#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/wait.h>
#define MAXPRO 200      //创建200个进程
#define SELLP 10000
#define TESTTIME 10
int max=0,l=0;
void myfork()        //递归函数
{
pid_t pid;
int status;
//if (max>=MAXPRO) exit(1);
max++;
pid=fork();           //递归创建进程
if (pid<0) exit(1);
	if (pid>0)
	{
		waitpid(pid,&status,0);   //等待子进程结束
		if (max<2) return;
		exit(1);
	}
	if (pid==0)
	{
		if (max>=MAXPRO) exit(1);
		myfork();
		exit(1);
	}
}

int main(void)
{
int  ave=0;
time_t time1;
struct tm *t1,*t2;
pid_t pid,pids[MAXPRO+1];
int i,ti;
int status;
struct timeval tv1[TESTTIME],tv2[TESTTIME];
struct timezone tz;

for (l=0;l<TESTTIME;l++)       //做十组测试
{
max=0;
gettimeofday (&tv1[l],&tz);    //记录开始时间  取得目前的时间
myfork();
gettimeofday (&tv2[l],&tz);    //记录结束时间
}

for(l=0;l<TESTTIME;l++)        //计算输出
{
printf("\nRound %d :The star time is %ds%dus \n",l+1, tv1[l].tv_sec,tv1[l].tv_usec);
printf("Round %d :The end time is %ds%dus \n", l+1,tv2[l].tv_sec,tv2[l].tv_usec);
ti=(tv2[l].tv_sec-tv1[l].tv_sec)*1000000+(tv2[l].tv_usec-tv1[l].tv_usec);
printf("Round %d :All time is %d us\n",l+1,ti);
ave+=ti/MAXPRO;
printf("Round %d :The average time is %dus \n", l+1,ti/MAXPRO);
}
printf("Last the average time is %dus \n",ave/TESTTIME);
return 1;
}