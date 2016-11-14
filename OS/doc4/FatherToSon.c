#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
int main(int argc,char **argv)
{
	int pipe_fd[2];//�����ܵ���ʾ��
	pid_t pid;//���̺����������Ǹ����̻����ӽ���
	char r_buf[11];//������ܵ�д������
	char w_buf[argc][11];//������ܵ���������
      
	int i;
	memset(r_buf,0,sizeof(r_buf));//��д���ַ�������0
        memset(w_buf,0,sizeof(r_buf));// �������ַ�������0
if(pipe(pipe_fd)<0)//�������ɹ�
	{
		printf("pipe create erro\n");
		return -1;
	}
	if((pid=fork())==0)//�ӽ���
	{
		printf("\n");
		close(pipe_fd[1]);//�ر�д�˿�
		sleep(2);//�ȴ��ر���ɧ�
	        for(i=0;i<argc-1;i++)
		{	
			read(pipe_fd[0],r_buf,10);
                       //�Ӷ˿��ж���10���ַ�		
printf("child: receive word from parent  is %s\n",r_buf);
			sleep(1);
		}
		close(pipe_fd[0]);//�ر�д�˿�
		exit(1);
	}
	else if(pid>0)
	//��������ܵ�����д
	{
	close(pipe_fd[0]);//�رն��ܵ�      
	for(i=1;i<argc;i++)
		{
             strcpy(w_buf[i],argv[i]);
             write(pipe_fd[1],w_buf[i],10);
               //���������д����Ĳ���д��ܵ�
	        printf("parent:send word into the pipe %s\n",w_buf[i]);
                }
        close(pipe_fd[1]);//�ر�д�ܵ�
          exit(1);
	}	
}
