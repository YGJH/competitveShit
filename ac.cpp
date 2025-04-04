#include<iostream>
#include<cmath>
#include<cstdio>
#include<iomanip>
#include<cstring>
#include<stdlib.h>
#include<string>
#include<algorithm>
#include<queue>
using namespace std;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int  maxn =50001;
int  sum[maxn<<2];//sum为在范围内的花数
int ql,qr,ans;
int n,m;
int  lazy[maxn<<2];//lazy为判断是否全为空或全为满则为1，否则为0
void pushup(int rt,int m)//将当前结点的信息更新的父节点
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
	if(sum[rt]==m||!sum[rt])
		lazy[rt]=1;
	else
		lazy[rt]=0;
}
void pushdown(int rt,int  m)//延迟标记向下推 m为长度
{
	if(sum[rt]==m)//全为满
	{
		sum[rt<<1]=m-(m>>1);
		sum[rt<<1|1]=(m>>1);
	}
	else
		sum[rt<<1]=sum[rt<<1|1]=0;
	lazy[rt<<1]=lazy[rt<<1|1]=1;
}
void build(int l,int r,int rt)//建立线段树
{
	lazy[rt]=1;
	sum[rt]=0;
	if(l==r)
	{
		return ;
	}
	int  m=(l+r)>>1;
	build(lson);
	build(rson);
}
int R;
void query(int L,int c,int l,int r,int rt)
{
	if(c<=0)return ;
	if(L<=l&&r<=R&&lazy[rt])//在范围内  且全为空或者全为满
	{
		if(!sum[rt])//全为空
		{
			ans-=(r-l+1);
			sum[rt]=(r-l+1);
			if(ql<0)ql=l;
			qr=r;
		}
		else//如果全为满 不能插花 想要跳过 因此右的边界范围扩大
		{
			R+=(r-l+1);
			if(R>n)
				R=n;
		}
		return ;
	}
	if(lazy[rt])
	pushdown(rt,r-l+1);
	lazy[rt]=0;
	int  m=(l+r)>>1;
	if(L<=m)query(L,c,lson);
	if(R>m)query(L,c,rson);
	pushup(rt,r-l+1);
}
void update(int L,int R,int l,int r,int rt)
{
	if(L<=l&&r<=R)
	{
		ans+=sum[rt];
		lazy[rt]=1;
		sum[rt]=0;
		return ;
	}
	if(lazy[rt])
	pushdown(rt,r-l+1);
	lazy[rt]=0;
	int  m=(l+r)>>1;
	if(L<=m)update(L,R,lson);
	if(R>m) update(L,R,rson);
	pushup(rt,r-l+1);
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		build(1,n,1);
		int a,b,c;
		while(m--)
		{
			scanf("%d%d%d",&a,&b,&c);
			if(a==1)
			{
				b++;
				ql=qr=-1;//左右两个花瓶
				R=b+c-1;
				query(b,c,1,n,1);
				if(qr>0)printf("%d %d\n",ql-1,qr-1);
				else  printf("Can not put any one.\n");
			}
			else
			{
				b++,c++;
				ans=0;
				update(b,c,1,n,1);
				printf("%d\n",ans);
			}
		}
		printf("\n");
	}
	return 0;
}