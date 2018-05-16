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
    int w;  //��Ʒ������
    int v;  //��Ʒ�ļ�ֵ
    int i;  //��Ʒ�ı��
    double p;
}item[nMAX];

bool cmp1(Item a,Item b);
void output_way(bool x[]);

//��֧�޽編
double calculate_ub(int v, int w, double p);    //��������
void Insert(bool flag, int i, int Cv, int Cw, double ub, Node temp);//�жϺ����
void bfs(); //���ȶ�������

priority_queue<Node> Q;
double Max_ub;
double Min_ub;


int main()
{
    cout<<"����0-1��������ʵ����c=50, n=5, w={5, 15, 25, 27, 30}, v={12, 30, 44, 46, 50}�����ս̿����ϵ��㷨���г���ʵ�֡�"<<endl;
    cout<<"�����֧�޽��㷨������xȡֵ��״̬����cw,cp,bestp�ı仯���̣�������ԭ���������ֵ�����Ž⡣"<<endl;
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
    //����Ҫ�������һ����������
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
        //flag=0ʱ�����㲻�ŵ�temp.cnt+1����Ʒ
        //flag=1ʱ����������temp.cnt+1����Ʒ
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

