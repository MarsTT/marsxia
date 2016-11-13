#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string> 
#include <time.h>
using namespace std;
#define max 100
struct chocolate{
	int tag;
	char cho;
};

char s='p';
int t=7;
chocolate p[max][max];
void coutcho(chocolate p[max][max],int m,int n);
void choosecutcho(int m,int n,int x0,int y0);
int  main(){
	int m,n,x0,y0,h;
	int z=2;
	cout<<" **************************************"<<endl;
	cout<<" **      欢迎来到掰巧克力的游戏      **"<<endl;
	cout<<" **请输入游戏的模式(1为单人，2为双人)**"<<endl;
	cout<<" **************************************"<<endl;
	cin>>h;

	if(h==1)
		cout<<"你选择了单人游戏！"<<endl;
	else if(h==2)
		cout<<"你选择了双人游戏！"<<endl;
	cout<<"请输入巧克力的长度和宽度："<<endl;
	cin>>n>>m;
	srand((unsigned)time( NULL )); 
	x0=rand()%m+1;
	y0=rand()%n+1;
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			p[i][j].cho='@';
		p[x0-1][y0-1].cho='*';
		cout<<"巧克力初始化如下："<<endl;
		coutcho(p,m,n);
		while(m!=1||n!=1){

			if(z%2==0&&h==1)
			{
				choosecutcho(m,n,x0, y0);
				cout<<"电脑走步，经分析决定沿"<<s<<"="<<t<<"位置掰巧克力！"<<endl;
				cout<<"电脑走完后的巧克力形状如下："<<endl;
			}
			else if(z%2==0&&h==2)
			{
				cout<<"玩家一走走步！"<<endl;
				cin>>s>>t;
				while((s=='x'&&(t<=0||t>=n))||(s=='y'&&(t<=0||t>=m)))
				{
					cout<<"输入错误！请重新输入："<<endl;
					cin>>s>>t;
				}
				cout<<"玩家一掰完后的巧克力如下："<<endl;
			}
			else if(z%2!=0&&h==1)

			{
				cout<<"轮到你走步,请输入你要掰的方向（x或y）和要掰的位置: "<<endl;

				cin>>s>>t;
				while((s=='x'&&(t<=0||t>=n))||(s=='y'&&(t<=0||t>=m)))
				{
					cout<<"输入错误！请重新输入："<<endl;
					cin>>s>>t;
				}
				cout<<"你掰玩后的巧克力如下："<<endl;
			}
			else if(z%2!=0&&h==2)
			{
				cout<<"玩家二走走步！"<<endl;
				cin>>s>>t;
				while((s=='x'&&(t<=0||t>=n))||(s=='y'&&(t<=0||t>=m)))
				{
					cout<<"输入错误！请重新输入："<<endl;
					cin>>s>>t;
				}
				cout<<"玩家二掰完后的巧克力如下："<<endl;
			}
			if(s=='x')
			{
				if(y0>t)
				{	
					n=n-t;
					p[x0-1][y0-t-1].cho=p[x0-1][y0-1].cho;
					p[x0-1][y0-1].cho='@';
					y0=y0-t;
				}
				else
					if(y0<=t)
						n=t;
				}


				else if(s=='y')
				{
					if(x0>t)
					{
						m=m-t;
						p[x0-t-1][y0-1].cho=p[x0-1][y0-1].cho;
						p[x0-1][y0-1].cho='@';
						x0=x0-t;
					}
					else 
						if(x0<=t)
							m=t;
					}
					coutcho(p,m,n);
					z++;
				}

				if(z%2!=0&&h==1)
					cout<<"电脑获胜！"<<endl;
				else if(z%2==0&&h==1) 
					cout<<"你获胜了！"<<endl;
				else if(z%2!=0&&h==2) 
					cout<<"玩家一获胜了！"<<endl;
				else if(z%2==0&&h==2) 
					cout<<"玩家二获胜了！"<<endl;
			}

			void coutcho(chocolate p[max][max],int m,int n){
				int i,k;
				cout<<" x ";
				for(k=1;k<=n;k++)
					cout<<k%10<<" ";
				cout<<endl;
				cout<<"y"<<endl;
				for(i=0;i<m;i++)
					{  cout<<(i+1)%10<<"  ";
				for(int j=0;j<n;j++)
					cout<<p[i][j].cho<<" ";
				cout<<endl;
			}
		}
		void choosecutcho(int m,int n,int x0,int y0){
			int p1,p2,p3,p4,i,j,k,l,p,q1;
			p1=y0-1;
			p2=x0-1;	  
			p3=n-y0;
			p4=m-x0;
			p=p1^p2^p3^p4;

			if(p!=0)
			{  

				for(i=0;i<p1;i++)
				{
					q1=i^p2^p3^p4;
					if(q1==0)
					{
						t=p1-i;
						s='x';
						goto T1;
					}
				}


				for(j=0;j<p2;j++)
				{
					q1=p1^j^p3^p4;
					if(q1==0)
					{
						t=p2-j;
						s='y';
						goto T1;
					}
				}


				for(k=0;k<p3;k++)
				{
					q1=p1^p2^k^p4;
					if(q1==0)
					{
						t=y0+k;
						s='x';
						goto T1;
					}
				}


				for(l=0;l<p4;l++)
				{
					q1=p1^p2^p3^l;
					if(q1==0)
					{
						t=x0+l;
						s='y';
						goto T1;
					}
				}
			}


			else

			{
				if(p1!=0)
				{
					s='x';
					t=1;
				}
				else
					if(p2!=0)
					{
						s='y';
						t=1;
					}
					else
						if(p3!=0)
						{
							s='x';
							t=n-1;
						}
						else
							if(p4!=0)
							{
								s='y';
								t=m-1;
							}


						}

						T1:
						;
					}