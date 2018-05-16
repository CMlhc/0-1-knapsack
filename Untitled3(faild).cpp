#include<iostream>
#include<cstring>
#include<stdio.h>
#include<cmath>
#include <algorithm>
#include<queue>
#define nMAX 1000
#define eps 1e-7
using namespace std;

int N,C,W,n;


struct Node
{
    int cw;
    int cv;
    int cnt;
    bool x[nMAX];
    Node()
    {
        memset(x,0,sizeof(x));
        cnt=1;
        cw=0;
        cv=0;
    }
    double ub;
    friend bool operator<(Node n1,Node n2)
    {
        return n1.ub<n2.ub;
    }
}node[nMAX],maxn;

struct Item
{
    int w;  //物品的重量
    int v;  //物品的价值
    int i;  //物品的编号
    double p;
}item[nMAX];

bool cmp1(Item a,Item b);
void output_way(bool x[]);

//分支限界法
double calculate_ub(int v, int w, double p);    //启发函数
void Insert(bool flag, int i, int Cv, int Cw, double ub, Node temp);//判断和入队
void bfs(); //优先队列搜索

priority_queue<Node> Q;
double Max_ub;
double Min_ub;


int main()
{
    cout<<"给定0-1背包问题实例：c=50, n=5, w={5, 15, 25, 27, 30}, v={12, 30, 44, 46, 50}，参照教科书上的算法进行程序实现。"<<endl;
    cout<<"输出分支限界算法中数组x取值及状态变量cw,cp,bestp的变化过程，并给出原问题的最优值和最优解。"<<endl;
    cin>>N>>C;
    for(int i=1;i<=N;i++)
    {
        cin>>item[i].w>>item[i].v;
        item[i].i=i;
        item[i].p=1.0*item[i].v/item[i].w;
    }
    W=C;
    n=N;
    double Min=1e20;
    double Max=-1;
    Max_ub=W*Max;
    Min_ub=W*Min;
    sort(item+1, item+n+1, cmp1);
    bfs();

    cout<<maxn.cv<<endl;
    output_way(maxn.x);

    return 0;
}

double calculate_ub(int v, int w, double p)
{
    return v+(W-w)*p;
}

void Insert(bool flag, int i, int Cv, int Cw, double ub, Node temp)
{
    //符合要求，则把这一个点放如队列
    if((ub>Min_ub-eps)&&(ub<Max_ub+eps)&&(Cw<=W))
    {
        Node cm;
        cm.cw=Cw;
        cm.cv=Cv;
        cm.ub=ub;
        for(int j=1;j<=n;j++)
        {
            cm.x[j]=temp.x[j];
        }
        if(flag)
        {
            cm.x[item[i].i]=1;
            cm.cnt=i+1;
            Q.push(cm);
        }
    }
}

void bfs()
{
    Node node;
    node.cw=0;
    node.cv=0;
    node.ub=calculate_ub(0,0,item[1].p);
    Q.push(node);
    while(!Q.empty())
    {
        Node temp=Q.top();
        Q.pop();
        if(abs(temp.ub-temp.cv)<eps || temp.cnt>n)
        {
            if(maxn.cv<temp.cv+eps)
                maxn=temp;
            break;
        }

        int Cw=temp.cw;
        int Cv=temp.cv;
        for(int flag=0; flag<2; flag++)
        //flag=0时，计算不放第temp.cnt+1件物品
        //flag=1时，计算放入第temp.cnt+1件物品
        {
            int i=temp.cnt;
            if(flag)
            {
                Cw+=item[i].w;
                Cv+=item[i].v;
            }
            double ub=calculate_ub(Cv, Cw, item[i+1].p);
            Insert(flag, i, Cv, Cw, ub, temp);
        }

    }
    return;
}

bool cmp1(Item a, Item b)
{
    return a.p>b.p;
}

void output_way(bool x[])
{
    for(int i=1; i<=n; i++)
    {
        if(x[i])
            printf("%d ", i);
    }
    cout<<endl;
}

