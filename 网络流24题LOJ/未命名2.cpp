
#include<cstdio>
#include<cmath>
#include<ctime>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<set>
#define ll long long
#define mod 1000000007
#define inf 1000000000
using namespace std;
int read()
{
    int f=1,x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int ans;
int T,n,K,top,cnt=1;
int l[505],r[505],t[505];
int disc[1005];
int last[1005],q[1005],d[1005];
bool inq[1005],mark[1005];
struct edge{
	int to,next,v,c;
}e[100005];
void insert(int u,int v,int w,int c)
{
	e[++cnt].to=v;e[cnt].next=last[u];last[u]=cnt;e[cnt].v=w;e[cnt].c=c;
	e[++cnt].to=u;e[cnt].next=last[v];last[v]=cnt;e[cnt].v=0;e[cnt].c=-c;
}
bool spfa()
{
	memset(d,-1,sizeof(d));
	int head=0,tail=1;
	q[0]=T;d[T]=0;
	while(head!=tail)
	{
		int now=q[head];head++;inq[now]=0;
		if(head==1005)head=0;
		for(int i=last[now];i;i=e[i].next)
			if(e[i^1].v&&d[now]+e[i^1].c>d[e[i].to])
			{
				d[e[i].to]=d[now]+e[i^1].c;
				if(!inq[e[i].to])
				{
					q[tail++]=e[i].to;
					if(tail==1005)tail=0;
					inq[e[i].to]=1;
			}
		}
	}
	return d[0]!=-1;
}
int dfs(int x,int f)
{
	mark[x]=1;
	if(x==T)return f;
	int w,used=0;
	for(int i=last[x];i;i=e[i].next)
		if(e[i].v&&!mark[e[i].to]&&d[x]-e[i].c==d[e[i].to])
		{
			w=dfs(e[i].to,min(f-used,e[i].v));
			e[i].v-=w;e[i^1].v+=w;
			ans+=w*e[i].c;
			used+=w;if(used==f)return f;
		}
	return used;
}
void zkw()
{
	while(spfa())
	{
		mark[T]=1;
		while(mark[T])
		{
			memset(mark,0,sizeof(mark));
			dfs(0,inf);
		}
	}
}
void build()
{
	T=2*n+1;
	insert(0,1,K,0);insert(2*n,T,K,0);
	for(int i=1;i<2*n;i++)insert(i,i+1,inf,0);
	for(int i=1;i<=n;i++)
		insert(l[i],r[i],1,t[i]);
}
int main()
{
	n=read();K=read();
	for(int i=1;i<=n;i++)
	{
		
		l[i]=read(),r[i]=read();
		if(l[i]>r[i])swap(l[i],r[i]);t[i]=r[i]-l[i];
		disc[++top]=l[i];disc[++top]=r[i];
	}
	sort(disc+1,disc+top+1);
	for(int i=1;i<=n;i++)
	{
		l[i]=lower_bound(disc+1,disc+top+1,l[i])-disc;
		r[i]=lower_bound(disc+1,disc+top+1,r[i])-disc;
	}
	for(int i=1;i<=n;i++)cout<<l[i]<<" "<<r[i]<<endl;
	build();
	zkw();
	printf("%d\n",ans);
	return 0;
}
