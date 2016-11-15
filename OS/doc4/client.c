
//实现两个进程间的消息传递，消息发送程序
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
    struct msgbuf buf;    //消息缓冲区
    key=ftok("/home/mars/os_pratice/doc4", 'a');  //生成消息队列的键值
    if (key<0)
    {
        perror("ftok error");
        exit(1);
    }
    qid=msgget(key, IPC_CREAT|0666);  //创建一个消息队列
    if (qid<0)
    {
        perror("msgget error");
        exit(1);
    }
    while (1)
    {
        printf("input the message:");
        fgets(buf.mtext,MSG_SIZE,stdin);  //从键盘输入消息的内容
        if (strncmp(buf.mtext, "exit",4)==0)  //如果键盘输入exit，退出循环
        {
            buf.mtype=getpid();
            ret=msgsnd(qid, &buf, MSG_SIZE, 0);
            break;
        }
        buf.mtype=getpid();                //消息的类型，这里设置为当前进程的标识符
        ret=msgsnd(qid, &buf, MSG_SIZE, 0); //向消息队列中发送一个消息
        if (ret<0)
        {
            perror("msgsnd error");
            exit(1);
        }
        else
        {
            printf("send!\n");
        }
    }
    return 0;
}

