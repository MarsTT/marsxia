#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <time.h>
#define N 10		/*������еĳ���*/
#define B 3		/*�ڴ�ҳ����*/
/*----------------------------------------------------------------------
��������IsInBuf()
���ܣ�����ĳ����x��û����Buf[]�У����ڣ�������λ�ã������ڣ��򷵻�-1
----------------------------------------------------------------------*/
int IsInBuf(int buf[],int x)
{
	int i,j=-1;
	for(i=0;i<B;i++)
	{
		if(buf[i]==x)	/*��x��buf�У�������λ��*/
		{
			j=i;
			break;
		}
		else if(buf[i]==-1)	/*��x����buf�У���buf[i]Ϊ�գ����x����buf����������λ��*/
		{
			buf[i]=x;
			j=i;
			break;	
		}
	}
	return j;

}

/*----------------------------------------------------------------------
��������main
���ܣ�
	�����������list�е�����
	����ҳ���жϴ����Ĵ�ӡ
	�����˳�����
-----------------------------------------------------------------------*/
main()
{
	int list[N];
	int buf[B],i,f[N],j;
	int old=0;
	int change=0;

	/*��������������ҳ�ʼ��*/
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

	/*��ʾ�������̭ҳ�������*/
	printf("\n\n");
	printf("\nthe lost in FIFO:");
	change=0;			/*�жϵĴ���*/
	for(i=0;i<N;i++)
	{
		j=IsInBuf(buf,list[i]);
		if(j==-1)		/*���������û�У�����ۣ����ֱ�Ӳ���*/
		{
			printf(" %2d",buf[old]);
			buf[old]=list[i];
			old=(old+1)%(int)B;		/*�����ڣ�����еĴ�����ѭ����*/
			change++;
		}
		else
			printf(" orz");
	}
	printf("\n\nFIFO Change Is:%d times",change);	/*ȱҳ�жϴ����Ĵ�ӡ*/
	printf("\n\n");

}

