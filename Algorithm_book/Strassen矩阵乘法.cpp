/*
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<ctime>
using namespace std;
 
int getnum(){
 
    int n=rand()%1000;
    return n;
}
double** input(int n,double **a){
 a=(double **)malloc(n*sizeof(double *));
 for(int t=0;t<n;t++)
  a[t]=(double *)malloc(n*sizeof(double));
 return a;
}
double** inputziji(int n,double **a){
 a=(double **)malloc(n*sizeof(double *));
 for(int t=0;t<n;t++)
  a[t]=(double *)malloc(n*sizeof(double));
 for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
         cin>>a[i][j];
 return a;
}
double** init(int n,double **a){
    a=(double **)malloc(n*sizeof(double *));
    for(int t=0;t<n;t++)
        a[t]=(double *)malloc(n * sizeof(double));
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            a[i][j]=0;
    return a;
}
void output(int n,double **a){
     for(int i=0;i<n;i++)
     {cout<<"\n";
     for(int j=0;j<n;j++)
         cout<<a[i][j]<<"   ";}
     cout<<"\n";
}
void addArrey(int n,double **a,double **b,double **c){
    for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
         c[i][j]=a[i][j]+b[i][j];
}
void subArrey(int n,double **a,double **b,double **c){
    for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
         c[i][j]=a[i][j]-b[i][j];
}
void mixArrey(int n,double **a,double **b,double **c){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            {c[i][j]=0;
            for(int k=0;k<n;k++)
                c[i][j]+=a[i][k]*b[k][j];}
    }
}
void mixStrassen(int n,double **a,double **b,double **c){
    if(n==2)
        mixArrey(n,a,b,c);
    else
    {
        double **a11,**a12,**a21,**a22;
        double **b11,**b12,**b21,**b22;
        double **c11,**c12,**c21,**c22;
        double **m1,**m2,**m3,**m4,**m5,**m6,**m7;
        double **aend,**bend,**m8,**m9,**m;m=NULL;m=init(n/2,m);
 
        a11=NULL;a11=init(n/2,a11);     a12=NULL;a12=init(n/2,a12);     a21=NULL;a21=init(n/2,a12);     a22=NULL;a22=init(n/2,a12);
        b11=NULL;b11=init(n/2,a11);     b12=NULL;b12=init(n/2,a12);     b21=NULL;b21=init(n/2,a12);     b22=NULL;b22=init(n/2,a12);
        c11=NULL;c11=init(n/2,c11);     c12=NULL;c12=init(n/2,c12);     c21=NULL;c21=init(n/2,c12);     c22=NULL;c22=init(n/2,c12);
        m1=NULL;m1=init(n/2,m1);        m2=NULL;m2=init(n/2,m2);        m3=NULL;m3=init(n/2,m3);        m4=NULL;m4=init(n/2,m4);
        m5=NULL;m5=init(n/2,m5);        m6=NULL;m6=init(n/2,m6);        m7=NULL;m7=init(n/2,m7);        m8=NULL;m8=init(n/2,m8);
        m9=NULL;m9=init(n/2,m9);        aend=NULL;aend=init(n/2,aend);  bend=NULL;bend=init(n/2,bend);
 
        for(int i=0;i<n/2;i++)
            for(int j=0;j<n/2;j++)
            {
                a11[i][j]=a[i][j];
                a21[i][j]=a[i+n/2][j];
                a12[i][j]=a[i][j+n/2];
                a22[i][j]=a[i+n/2][j+n/2];
                b11[i][j]=b[i][j];
                b21[i][j]=b[i+n/2][j];
                b12[i][j]=b[i][j+n/2];
                b22[i][j]=b[i+n/2][j+n/2];
            }
 
        addArrey(n/2,a11,a22,aend);
        addArrey(n/2,b11,b22,bend);
        mixStrassen(n/2,aend,bend,m1);//m1=(a11+a22)(b11+b22)
        addArrey(n/2,a21,a22,aend);
        mixStrassen(n/2,aend,b11,m2);//m2=(a21+a22)b11 q
        subArrey(n/2,b12,b22,bend);
        mixStrassen(n/2,a11,bend,m3);//m3=a11(b12-b22）r
        subArrey(n/2,b21,b11,bend);
        mixStrassen(n/2,a22,bend,m4);//m4=a22(b21-b11) s
        addArrey(n/2,a11,a12,aend);
        mixStrassen(n/2,aend,b22,m5);//m5=(a11+a12)b22 t
        subArrey(n/2,a21,a11,aend);
        addArrey(n/2,b11,b12,bend);
        mixStrassen(n/2,aend,bend,m6);//m6=(a21-a11)(b11+b22) u
        subArrey(n/2,a12,a22,aend);
        addArrey(n/2,b21,b22,bend);
        mixStrassen(n/2,aend,bend,m7);//m7=(a12-a22)(b21+b22) v
        addArrey(n/2,m1,m4,m8);
        subArrey(n/2,m8,m5,m9);
        addArrey(n/2,m9,m7,c11);//c11=m1+m4-m5+m7
        addArrey(n/2,m3,m5,c12);//c12=m3+m5
        addArrey(n/2,m2,m4,c21);//c21=m2+m4
        addArrey(n/2,m1,m3,m8);
        subArrey(n/2,m8,m2,m9);
        addArrey(n/2,m9,m6,c22);//c22=m1+m3-m2+m6
        for(int i=0;i<n/2;i++)
            for(int j=0;j<n/2;j++)
            {
                c[i][j]=c11[i][j];
                c[i+n/2][j]=c21[i][j];
                c[i][j+n/2]=c12[i][j];
                c[i+n/2][j+n/2]=c22[i][j];
            }
    }
}
int main(){
 
    srand((int)time(NULL));
 
    int n;
    cout<<"请输入要计算的矩阵的行数（与列数相同，并且值为2的整数次方）：\n";
    cin>>n;
    ofstream out;
    out.open("shuruA.txt",ios::app);
    for(int i=0;i<n;i++)
    {   out<<"\n";
        for(int j=0;j<n;j++)
    out<<getnum()<<"   ";}
    out.close();
    ofstream out2;
    out2.open("shuruB.txt",ios::app);
    for(int i=0;i<n;i++)
    {
        out2<<"\n";
        for(int j=0;j<n;j++)
            out2<<getnum()<<"   ";
    }
    out2.close();
 
    double **A,**B,**C;
    ifstream in_stream;
    C=NULL;B=NULL;A=NULL;
    C=init(n,C);
    cout<<"从shuruA文件中读入A矩阵：\n";
    A=input(n,A);
    in_stream.open("shuruA.txt");
    if(in_stream.fail()){
     cout<<"打开文件失败！";
     }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            in_stream>>A[i][j];
    in_stream.close();
 
    cout<<"从shuruB文件中读入B矩阵：\n";
    B=input(n,B);
    in_stream.open("shuruB.txt");
    if(in_stream.fail()){
     cout<<"打开文件失败！";
     }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            in_stream>>B[i][j];
        in_stream.close();
 
        clock_t start,end;
        start=clock();
    mixStrassen(n,A,B,C);
    end= clock();
        cout<<"strassen矩阵乘法的运行时间为: "<<(double)(end - start) / CLOCKS_PER_SEC<<"S\n";
 
        ofstream out3;
    out3.open("strassen.txt",ios::app);
    for(int i=0;i<n;i++)
    {   out3<<"\n";
        for(int j=0;j<n;j++)
    out3<<C[i][j]<<"   ";}
    out3.close();
 
    clock_t start1,end1;
        start1=clock();
    mixArrey(n,A,B,C);
    end1 = clock();
        cout<<"用一般的矩阵乘法的运行时间为: "<<(double)(end1 - start1) / CLOCKS_PER_SEC<<"S\n";
            ofstream out4;
            cout<<"理论上";
    out4.open("yibanchengfa.txt",ios::app);
    for(int i=0;i<n;i++)
    {   out4<<"\n";
        for(int j=0;j<n;j++)
    out4<<C[i][j]<<"   ";}
    out4.close();
    system("pause");
    return 0;
}
*/

#include <iostream>
#include <ctime>
#include <Windows.h>
using namespace std;
#include "Strassen.h"

int main()
{
    Strassen_class<int> stra;//定义Strassen_class类对象
    int MatrixSize = 0;

    int** MatrixA;    //存放矩阵A
    int** MatrixB;    //存放矩阵B
    int** MatrixC;    //存放结果矩阵

    clock_t startTime_For_Normal_Multipilication ;
    clock_t endTime_For_Normal_Multipilication ;

    clock_t startTime_For_Strassen ;
    clock_t endTime_For_Strassen ;
    srand(time(0));

    cout<<"\n请输入矩阵大小(必须是2的幂指数值(例如:32,64,512,..): ";
    cin>>MatrixSize;

    int N = MatrixSize;//for readiblity.

    //申请内存
    MatrixA = new int *[MatrixSize];
    MatrixB = new int *[MatrixSize];
    MatrixC = new int *[MatrixSize];

    for (int i = 0; i < MatrixSize; i++)
    {
        MatrixA[i] = new int [MatrixSize];
        MatrixB[i] = new int [MatrixSize];
        MatrixC[i] = new int [MatrixSize];
    }

    stra.FillMatrix(MatrixA,MatrixB,MatrixSize);  //矩阵赋值

  //*******************conventional multiplication test
        cout<<"朴素矩阵算法开始时钟:  "<< (startTime_For_Normal_Multipilication = clock());

        stra.MUL(MatrixA,MatrixB,MatrixC,MatrixSize);//朴素矩阵相乘算法 T(n) = O(n^3)

        cout<<"\n朴素矩阵算法结束时钟: "<< (endTime_For_Normal_Multipilication = clock());

        cout<<"\n矩阵运算结果... \n";
        stra.PrintMatrix(MatrixC,MatrixSize);

  //*******************Strassen multiplication test
        cout<<"\nStrassen算法开始时钟: "<< (startTime_For_Strassen = clock());

        stra.Strassen( N, MatrixA, MatrixB, MatrixC ); //strassen矩阵相乘算法

        cout<<"\nStrassen算法结束时钟: "<<(endTime_For_Strassen = clock());


    cout<<"\n矩阵运算结果... \n";
    stra.PrintMatrix(MatrixC,MatrixSize);

    cout<<"矩阵大小 "<<MatrixSize;
    cout<<"\n朴素矩阵算法: "<<(endTime_For_Normal_Multipilication - startTime_For_Normal_Multipilication)<<" Clocks.."<<(endTime_For_Normal_Multipilication - startTime_For_Normal_Multipilication)/CLOCKS_PER_SEC<<" Sec";
    cout<<"\nStrassen算法:"<<(endTime_For_Strassen - startTime_For_Strassen)<<" Clocks.."<<(endTime_For_Strassen - startTime_For_Strassen)/CLOCKS_PER_SEC<<" Sec\n";
    system("Pause");
    return 0;

}