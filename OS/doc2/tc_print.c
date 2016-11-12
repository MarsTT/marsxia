#include<stdio.h>
int main(int argc,char *argv[])
{
    printf("Thead %s has start!\n ",argv[1]);
    sleep(3); 
    printf("Thread %s ended\n",argv[1]);
    return(0);
}