#include<iostream>
#include<stdio.h>
#define  max(x,y)    (x)>(y)?(x):(y)
#define V 100
using namespace std;
int f[10][V]={0};
int w[10]={0};
int v[10]={0};
int temp[10]={0};
int N,C;

int main()
{
    cout<<"����0-1��������ʵ����c=50, n=5, w={5, 15, 25, 27, 30}, v={12, 30, 44, 46, 50}�����ս̿����ϵ��㷨���г���ʵ�֡�"<<endl;
    cout<<"�����̬�滮�㷨�и����׶ε�����ֵm[i,j]��������ԭ���������ֵ�����Ž⡣"<<endl;

    cin>>N>>C;
    for(int i=1;i<=N;i++)
    {
        cin>>w[i]>>v[i];
    }

    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=C;j++)
        {
            if(j>=w[i])
            {
                f[i][j]=max(f[i-1][j],f[i-1][j-w[i]]+v[i]);
                //f[i][j]=max(f[i-1][j],f[i-1][j-w[i]]+v[i]);
            }else
            {
                f[i][j]=f[i-1][j];
            }
        }
    }

    int c=C;
    for(int i=N;i>1;i--)
    {
        if(f[i][c]==f[i-1][c])
        {
            temp[i]=0;
        }else
        {
            temp[i]=1;
            c-=w[i];
        }
    }
    temp[1]=(f[1][c])?1:0;

   for(int j=0;j<=C;j++)
   {
       printf("%4d",j);
   }
   cout<<endl;

   for(int i=1;i<=N;i++)
   {
       printf("%4d",i);
       for(int j=1;j<=C;j++)
       {
           printf("%4d",f[i][j]);
       }
       cout<<endl;
   }

   cout<<endl;
   cout<<f[N][C]<<endl;
   for(int i=1;i<=N;i++)
   {
       cout<<temp[i]<<"  ";
   }


    return 0;
}
