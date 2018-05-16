#include<iostream>
#define MAX 100
using namespace std;

int N,C;
int x[MAX]={0};
int y[MAX]={0};
int cw=0,cp=0,bestp=0;

struct Item
{
    int w;  //物品的重量
    int v;  //物品的价值
    int i;  //物品的编号
}item[MAX];


void BackTrack(int i);

int main()
{
    cout<<"给定0-1背包问题实例：c=50, n=5, w={5, 15, 25, 27, 30}, v={12, 30, 44, 46, 50}，参照教科书上的算法进行程序实现。"<<endl;
    cout<<"输出回溯算法中数组x取值及状态变量cw,cp,bestp的变化过程，并给出原问题的最优值和最优解。"<<endl;
    cin>>N>>C;
    for(int i=1;i<=N;i++)
    {
        cin>>item[i].w>>item[i].v;
        item[i].i=i;
    }
    BackTrack(1);
    cout<<bestp<<endl;

    return 0;
}

void BackTrack(int i)
{
    if(i>N)
    {
        if(cp>bestp)
        {
            bestp=cp;
            for(int i=1;i<=N;i++)
            {
                x[i]=y[i];
            }
        }
        return;
    }

    cout<<"cw= "<<cw<<",cp="<<cp<<",bestp="<<bestp<<endl;

    //左子树
    if(C>=cw+item[i].w)
    {
        cw=cw+item[i].w;
        cp=cp+item[i].v;
        y[item[i].i]=1;
        BackTrack(i+1);
        y[item[i].i]=0;
        cw=cw-item[i].w;
        cp=cp-item[i].v;
    }

    //右子树
    BackTrack(i+1);
}

