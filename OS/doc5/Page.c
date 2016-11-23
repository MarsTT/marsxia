#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <time.h>
#define N 10		/*随机数列的长度*/
#define B 3		/*内存页面数*/
/*----------------------------------------------------------------------
函数名：IsInBuf()
功能：返回某个数x有没有在Buf[]中，若在，返回其位置；若不在，则返回-1
----------------------------------------------------------------------*/
int IsInBuf(int buf[],int x)
{
	int i,j=-1;
	for(i=0;i<B;i++)
	{
		if(buf[i]==x)	/*当x在buf中，返回其位置*/
		{
			j=i;
			break;
		}
		else if(buf[i]==-1)	/*当x不在buf中，且buf[i]为空，则把x填入buf，并返回其位置*/
		{
			buf[i]=x;
			j=i;
			break;	
		}
	}
	return j;

}

/*----------------------------------------------------------------------
函数名：main
功能：
	１、随机产生list中的数字
	２、页面中断次数的打印
	３、退出程序
-----------------------------------------------------------------------*/
main()
{
	int list[N];
	int buf[B],i,f[N],j;
	int old=0;
	int change=0;

	/*生成随机数，并且初始化*/
	srand((int)time(NULL));
	for(i=0;i<B;i++)
		buf[i]=f[i]=-1;
	printf("\n**********************************************");
	printf("\nThe Random List:");
	for(i=0;i<N;i++)
	{
		list[i]=(int) rand()%10;
		printf("%2d",list[i]);
	}
	printf("\n**********************************************");

	/*显示ｆｉｆｏ淘汰页面的序列*/
	printf("\n\n");
	printf("\nthe lost in FIFO:");
	change=0;			/*中断的次数*/
	for(i=0;i<N;i++)
	{
		j=IsInBuf(buf,list[i]);
		if(j==-1)		/*若ｂｕｆ中没有ｌｉｓｔ［ｉ］则直接插入*/
		{
			printf(" %2d",buf[old]);
			buf[old]=list[i];
			old=(old+1)%(int)B;		/*数据在ｂｕｆ中的储存是循环的*/
			change++;
		}
		else
			printf(" orz");
	}
	printf("\n\nFIFO Change Is:%d times",change);	/*缺页中断次数的打印*/
	printf("\n\n");

}

