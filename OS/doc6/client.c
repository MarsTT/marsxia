#include "local.h"
void usage(char *name)
{
printf("input host IP: %s IpAddr\n",name);
}
int main(int argc, char **argv)
{
int servfd,clifd,length = 0;
struct sockaddr_in servaddr,cliaddr;
socklen_t socklen = sizeof(servaddr);
char buf[BUFFER_SIZE];
if (argc < 2)
{
usage(argv[0]); //argv[0]中就�?/client.out
exit(1);
}
if ((clifd = socket(AF_INET,SOCK_STREAM,0)) < 0)
{
printf("create socket error!\n");
exit(1);
}
srand(time(NULL)); //initialize random generator

bzero(&cliaddr,sizeof(cliaddr));
cliaddr.sin_family = AF_INET;
cliaddr.sin_port = htons(CLIENT_PORT);
cliaddr.sin_addr.s_addr = htons(INADDR_ANY);
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family = AF_INET;
inet_aton(argv[1],&servaddr.sin_addr);
servaddr.sin_port = htons(SERVER_PORT);
if (bind(clifd,(struct sockaddr*)&cliaddr,sizeof(cliaddr))<0)
{
printf("bind to port %d failure!\n",CLIENT_PORT);
exit(1);
}
if (connect(clifd,(struct sockaddr*)&servaddr, socklen) < 0)
{
printf("can't connect to %s!\n",argv[1]);
exit(1);
}
length = recv(clifd,buf,BUFFER_SIZE,0);
if (length < 0)
{
printf("error comes when recieve data from server %s!",argv[1]);
exit(1);
}
printf("from server %s :\n\t%s ",argv[1],buf);
close(clifd);
return 0;
} 
