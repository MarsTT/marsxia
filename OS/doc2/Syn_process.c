#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#define SEMKEY (key_t)0x200

typedef union _senum{
   int val;
   struct semid_ds *buf;
   ushort *array;
}semun;

static int semid;
struct sembuf p1={0,-1,0};//第一个是索引量,第二个-1是p操作，1是v操作。
struct sembuf v1={0,1,0};
int initsem()   /*信号量初始化*/
{
 semun x;
 x.val=0;  //用于付信号量初值    
 if((semid=semget(SEMKEY,1,0600|IPC_CREAT|IPC_EXCL))==-1)//创建信号量集
 //1为信号量集中信号量个数
  {
   if(errno==EEXIST)  //已经存在,则获得ID号.
    semid=semget(SEMKEY,1,0);
   }
 if(semctl(semid,0,SETVAL,x)==-1)
  {
   perror("semctl failed\n");
   return(-1);
  }
  return(semid);
}
 
main()     /*主操作*/
{
 int i=0,semid;
 int j;
 semid=initsem();
 if(fork()==0)
 {      
    semop(semid,&p1,1);/*p操作*/ 
    for(j=0;j<1000;j++)
     {
       printf("reader1  %d \n",2*j+1);
       sleep(1);
     } 
    printf("reader1 finish!!!\n");
 }
 else
 {      
     if(fork()==0)
      {
        for(i=0;i<1000;i++)
          {
            printf("reader2  %d \n",2*i);
            sleep(1);
           }
         printf("reader2 finish!!!\n");
         semop(semid,&v1,1);
      }
   }
}