#include<iostream>
#define MAX 100
using namespace std;

int N,C;
int x[MAX]={0};
int y[MAX]={0};
int cw=0,cp=0,bestp=0;

struct Item
{
    int w;  //��Ʒ������
    int v;  //��Ʒ�ļ�ֵ
    int i;  //��Ʒ�ı��
}item[MAX];


void BackTrack(int i);

int main()
{
    cout<<"����0-1��������ʵ����c=50, n=5, w={5, 15, 25, 27, 30}, v={12, 30, 44, 46, 50}�����ս̿����ϵ��㷨���г���ʵ�֡�"<<endl;
    cout<<"��������㷨������xȡֵ��״̬����cw,cp,bestp�ı仯���̣�������ԭ���������ֵ�����Ž⡣"<<endl;
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

    //������
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

    //������
    BackTrack(i+1);
}

