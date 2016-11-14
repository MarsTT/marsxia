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

int semid;
int count=0;
FILE *fp,*fp1,*fp2;
struct sembuf prmutex={0,-1,0},pwmutex={1,-1,0},ps={2,-1,0};//��һ����������,�ڶ���-1��p������1��v������
struct sembuf vrmutex={0,1,0},vwmutex={1,1,0},vs={2,1,0};
int initsem()   /*�ź�����ʼ��*/
{
 semun x;
 x.val=1;
 if((semid=semget(SEMKEY,3,0600|IPC_CREAT|IPC_EXCL))==-1)
  {
   if(errno==EEXIST)
    semid=semget(SEMKEY,3,0);
   }
 if(semctl(semid,0,SETVAL,x)==-1)
  {
   perror("semctl failed\n");
   return(-1);
  }
 if(semctl(semid,1,SETVAL,x)==-1)
  {
   perror("semctl failed\n");
   return(-1);
  }
  if(semctl(semid,2,SETVAL,x)==-1)
   {
   perror("semctl failed\n");
   return(-1);
  }
   return(semid);
}

 
main()     /*������*/
{int i,j,k;
 int a[30];
 
 for(i=0;i<30;i++)
 {
      a[i]=i;
 }
 semid=initsem();
 if(fork()==0)
 {
      //reader
     semop(semid,&prmutex,1);/*������p����*/
     if(count==0)  semop(semid,&pwmutex,1);/*����д����*/
     count=count+1;/*������*/
      printf("count=%d\n",count);
     semop(semid,&vrmutex,1);
     for(i=0;i<30;i++)
      {
        printf(" reader 1 %d\n",a[i]);
        sleep(1);
       }
     semop(semid,&prmutex,1);
     count=count-1;
     printf("count=%d\n",count);
     if(count==0)  semop(semid,&vwmutex,1);/*����д����*/
     semop(semid,&vrmutex,1);
     exit(0);
 }
 else
 { 
     if(fork()==0)
      {   //writer
        semop(semid,&pwmutex,1);
        printf("I am writer:");
        for(k=0;k<30;k++)
          {
              a[k]=3*k;
              //sleep(1);
           }
        printf("write  finish!!!!\n");
        semop(semid,&vwmutex,1);
        exit(0);

      }
     else 
      {  if(fork()==0)  //reader
         {
         semop(semid,&prmutex,1);/*������p����*/
         //if(count==0)  semop(semid,&pwmutex,1);/*����д����*/
           //printf("count=%d\n",count);
         count=2;/*������*/
         printf("count=%d\n",count);
         semop(semid,&vrmutex,1);
         for(j=0;j<30;j++)
           {
              printf(" reader 2 %d\n",a[j]);
              sleep(1);
           }
         semop(semid,&prmutex,1);
         count=count-1;
         printf("count=%d\n",count);
         if(count==0)  semop(semid,&vwmutex,1);/*����д����*/
         semop(semid,&vrmutex,1);
         exit(0);
           }
      }
   }
  
}

