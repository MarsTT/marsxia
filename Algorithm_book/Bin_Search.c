#include <stdio.h>



int Binary_Search(int a[],int n,int key){
	int low,high,mid;
	low = 0;
	high = n-1;
	while(low<=high){
		mid = low + (high-low)*(key-a[low])/(a[high]-a[low]);
		if(key<a[mid])
			high = mid -1;
		else if(key>a[mid])
			low = mid +1;
		else
			return key;
	}
	return -1;
}

int main(){
	//int test_data[5]={34,35,36,89,96};
	//int ret_data=Binary_Search(test_data,5,89);
	//printf("ret_data:%d\n",ret_data);
	int i,val,ret;
	int a[8]={-32,12,16,24,36,45,59,98};
	for(i=0;i<8;i++)
		printf(" %d",a[i]);
	printf("\nplease input the search_key:");
	scanf("%d",&val);
	ret=Binary_Search(a,8,val);
	if(-1==ret)
		printf("search fail!\n");
	else
		printf("search succeed!\n");
	return 0;
}