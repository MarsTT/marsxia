#include <stdio.h>

// the quickSort
int partition(int s[],int low,int high){
	if(low > high) return 0;
	if(low == high) return low;
	s[0]=s[low];   //set the first_value as flag
	while(low < high){
		while(low < high && s[high]>s[0])
			high--;
		if(low < high)
			s[low++]=s[high];
		while(low < high && s[low]<s[0])
			low++;
		if(low < high)
			s[high--]=s[low];
	}
	s[low]=s[0];
	return low;
}

int SelectK(int s[],int low,int high,int k){
	int i=partition(s,low,high); // find the mid_value's location
	int j=i-low+1;  // the j is the length of left
	if(j == k)
		return s[i];
	else if(k<j)
		return SelectK(s,low,i,k);
	else
		return SelectK(s,i+1,high,k-j);
}

int main(){
	int n;
	int low,high,k;
	int a[20];
	int i;
	printf("please put the number:\n");
	scanf("%d",&n);
	printf("please put the datas:\n");
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
//	printf("\n");
	printf("please put the min_data:\n");
	scanf("%d",&k);
	printf("the min_k of %d is:%d\n",k,SelectK(a,1,n,k));
}