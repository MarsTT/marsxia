#include<stdio.h>                        
int n=0;
int status;   //改动地点
void pp()
{
   n++;
   if(n>=10)return;
    wait(&status);   //改动地点 wait系统调用会使父进程阻塞直到一个子进程结束
   if(fork()==0)
    {
    printf("%d",n);
     for(n=0;n<1000000;n++)
       ;
    }
   else pp();
}

int main()
{
   int i;
   for(i=0;i<3;i++)
    { 
      pp();
      printf("\n");
    }
return 0;
}