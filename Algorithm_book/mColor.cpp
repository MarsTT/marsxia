
//图的着色问题 回溯法求解
//#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

const int N = 5;//图的顶点数
const int M = 3;//色彩数
ifstream fin("mColoring.txt"); 

class Color
{
	friend int mColoring(int, int, int **);
	private:
		bool Ok(int k);
		void Backtrack(int t);
		int n,		//图的顶点数
			m,		//可用的颜色数
			**a,	//图的邻接矩阵
			*x;		//当前解
		long sum;	//当前已找到的可m着色方案数
};

int mColoring(int n,int m,int **a);

int main()
{
	int **a = new int *[N+1];  
    for(int i=1;i<=N;i++)    
    {    
        a[i] = new int[N+1];    
    } 
	
	cout<<"图G的邻接矩阵为:"<<endl;
	for(int i=1; i<=N; i++)  
    {  
        for(int j=1; j<=N; j++)  
        {  
            fin>>a[i][j];      
            cout<<a[i][j]<<" ";    
        }  
        cout<<endl;  
    }
	cout<<"图G的着色方案如下："<<endl;
	cout<<"当m="<<M<<"时，图G的可行着色方案数目为："<<mColoring(N,M,a)<<endl;
	for(int i=1;i<=N;i++)    
    {    
        delete[] a[i];   
    } 
	delete []a;
}

void Color::Backtrack(int t)
{
	if (t>n)
	{
		sum++;
		for (int i=1; i<=n; i++)
		cout << x[i] << " ";
		cout << endl;
	}
    else
	{
		for (int i=1;i<=m;i++) {
			x[t]=i;
			if (Ok(t)) Backtrack(t+1);
		}
	}
}

bool Color::Ok(int k)// 检查颜色可用性
{
	for (int j=1;j<=n;j++)
	{
		if ((a[k][j]==1)&&(x[j]==x[k])) //相邻且颜色相同
		{
			return false;
		}
	}
	return true;
}

int mColoring(int n,int m,int **a)
{
	Color X;

	//初始化X
	X.n = n;
	X.m = m;
	X.a = a;
	X.sum = 0;
	int *p = new int[n+1];
	for(int i=0; i<=n; i++)
	{
		p[i] = 0;
	}
	X.x = p;
	X.Backtrack(1);
	delete []p;
	return X.sum;
}