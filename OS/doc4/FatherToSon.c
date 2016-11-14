#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
int main(int argc,char **argv)
{
	int pipe_fd[2];//无名管道标示符
	pid_t pid;//进程号用以区分是父进程还是子进程
	char r_buf[11];//用于向管道写的数组
	char w_buf[argc][11];//用于向管道读的数组
      
	int i;
	memset(r_buf,0,sizeof(r_buf));//将写的字符数组清0
        memset(w_buf,0,sizeof(r_buf));// 将读的字符数组清0
if(pipe(pipe_fd)<0)//创建不成功
	{
		printf("pipe create erro\n");
		return -1;
	}
	if((pid=fork())==0)//子进程
	{
		printf("\n");
		close(pipe_fd[1]);//关闭写端口
		sleep(2);//等待关闭完成
	        for(i=0;i<argc-1;i++)
		{	
			read(pipe_fd[0],r_buf,10);
                       //从端口中读出10个字符		
printf("child: receive word from parent  is %s\n",r_buf);
			sleep(1);
		}
		close(pipe_fd[0]);//关闭写端口
		exit(1);
	}
	else if(pid>0)
	//父进程向管道里面写
	{
	close(pipe_fd[0]);//关闭读管道      
	for(i=1;i<argc;i++)
		{
             strcpy(w_buf[i],argv[i]);
             write(pipe_fd[1],w_buf[i],10);
               //将命令行中传来的参数写入管道
	        printf("parent:send word into the pipe %s\n",w_buf[i]);
                }
        close(pipe_fd[1]);//关闭写管道
          exit(1);
	}	
}
