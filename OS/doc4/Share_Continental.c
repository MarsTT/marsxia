#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define PERM S_IRUSR|S_IWUSR
int main(int argc,char **argv)
{
int shmid;
char *p_addr,*c_addr;

if((shmid=shmget(IPC_PRIVATE,1024,PERM))==-1)//���������ڴ���
{
fprintf(stderr,"Create Share Memory Error:%s\n\a",strerror(errno));
exit(1);
}
char s[1024];
 puts("Input the string you want the memory shared:\t");//����Ҫ���ݵ���Ϣ
 gets(s);
if(fork())
{
p_addr=shmat(shmid,0,0);
memset(p_addr,'\0',1024);//���
 strncpy(p_addr,s,1024);//�����ڴ���д
printf("parent sends: %s\t,the parent's pid is %d",p_addr,getpid());
exit(0);
}
else
{sleep(1);
c_addr=shmat(shmid,0,0);//�ӽ�����������������
printf("\n\tchild gets: %s\t,the child's pid is %d",c_addr,getpid());
exit(0);
}
return 0;
}
