
//实现两个进程间的消息传递，编写消息接收程序
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSG_SIZE 128
struct msgbuf           //定义消息结构
{
    long mtype;         //消息类型
    char mtext[MSG_SIZE];//消息的内容
};
int main()
{
    int qid;
    key_t key;
    int ret;
    struct msgbuf buf;
    key=ftok("/home/mars/os_pratice/doc4", 'a');
    if (key<0)
    {
        printf("ftok error");
        exit(1);
    }
    qid=msgget(key,IPC_EXCL|0666);  //打开消息队列
    if (qid<0)
    {
        perror("msgget error");
        exit(1);
    }
    while (1)
    {
        memset(&buf, 0, sizeof(buf));
        ret=msgrcv(qid, &buf, MSG_SIZE, 0, 0); //读取消息队列中的一个的消息
        if (ret<0)
        {
            perror("msgrcv error");
            exit(1);
        }
        else
        {
            if (strncmp(buf.mtext, "exit",4)==0)
            {
                break;
            }
            printf("received message:\n");
            printf("type=%ld,length=%ld,text:%s\n",buf.mtype,strlen(buf.mtext)-1,buf.mtext); 
        }
    }
    
    return  0;
    
}