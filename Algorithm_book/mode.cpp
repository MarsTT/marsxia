#include<stdio.h>
int main()
{
	int a[10]={1,2,3,3,3,3,4,4,4,5};
	int i=0,modefrequency=0,runlength,runvalue,modevalue;
  	while(i<=9)
	{
		runlength=1;
		runvalue=a[i];
		while((i+runlength)<=9 && (a[i+runlength]==runvalue))
		{
				runlength=runlength+1;
			//	i=i+runlength;
				if(runlength>modefrequency)
				{
					modefrequency=runlength;
					modevalue=runvalue;
				}			
		}
		i=i+runlength;
		
	}
		printf("modevalue is %d\n",modevalue);
}