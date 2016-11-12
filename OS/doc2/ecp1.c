#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
void main()
{
 	int *status;
 	char *f="./tc_print";       /*要执行的程序名*/
 	char *argv1[3],*argv2[3],*argv3[3],*argv4[3]; /*执行程序所需的参数*/
 	argv1[0]="./tc_print";
 	argv1[1]="1";
 	argv1[2]=0;       /*参数结束的标志*/

  argv2[0]="./tc_print";
 	argv2[1]="2";
 	argv2[2]=0;
 
 	argv3[0]="./tc_print";
 	argv3[1]="3";
 	argv3[2]=0;

 	argv4[0]="./tc_print";
 	argv4[1]="4";
 	argv4[2]=0;
 
 	if(fork()==0)     /*创建进程*/
 	{ 
    	execvp(f,argv1);   /*执行程序*/
    	sleep(1);
    	execvp(f,argv2);
   	   sleep(1);
  	}
  	else 
   {
     	if(fork()==0)     /*创建进程*/
       {
         execvp(f,argv3);
         sleep(1);
}   
     	else
       {   wait(status);
           execvp(f,argv3);
           sleep(1);
        }
   }
printf("End program!\n");
}