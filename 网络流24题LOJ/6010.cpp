#include<bits/stdc++.h>

using namespace std;
const int INF = 2147483647;
const int N = 1000010;
int g[50][50];
struct Edges{
	int s,t,w,c,nxt;
	Edges(){}
	Edges(int ss,int tt,int ww,int cc,int nt):s(ss),t(tt),w(ww),c(cc),nxt(nt){}
}e[N];
int head[10010],dis[10010],pre[10010];
bool inq[10010];
int s,t,n,m,tot = 1;
void add(int a,int b,int c,int d){
	e[++tot] = Edges(a,b,c,d,head[a]);
	head[a] = tot;
	e[++tot] = Edges(b,a,-c,0,head[b]);
	head[b] = tot;
}
bool spfa(){
	for(int i=s;i<=t;++i){
		dis[i] = INF;
		pre[i] = 0;
		inq[i] = false;
	}
	queue<int>q;
	q.push(s);
	dis[s] = 0;
	inq[s] = true;
	while(!q.empty()){
		int u = q.front();
		//cout<<u<<endl;
		q.pop();
		inq[u] = false;
		for(int i=head[u];i;i = e[i].nxt){
			int v = e[i].t;
			if(dis[v]>dis[u]+e[i].w && e[i].c>0){
				dis[v] = dis[u] + e[i].w;
				pre[v] = i;
				if(inq[v] == false){
					q.push(v);
					inq[v] = true;
				}
			}
		}
	}
	//cout<<dis[t]<<endl;
	if(dis[t] == INF)return false;
	else return true;
}
int MCMF(){
	int cost = 0;
	while(spfa()){
		int tmp = INF;
		for(int i = pre[t];i;i = pre[e[i].s]) tmp = min(tmp,e[i].c);
		for(int i = pre[t];i;i = pre[e[i].s]) {
			e[i].c -= tmp;
			e[i^1].c += tmp;
			cost += e[i].w*tmp;
		}
	}
	return cost;
}
void init(){
	scanf("%d%d",&n,&m);
	int ap = (n+(n+m-1))*m/2;
	s = 0;
	t = ap+ap+1;
	for(int i=1;i<=n;++i) add(s,i,0,1);
	for(int i=1;i<=m;++i){
		for(int j=1;j<=i+n-1;++j){
			scanf("%d",&g[i][j]);
			int np = (n+(i+n-2))*(i-1)/2+j; 
			add(np,np+ap,-g[i][j],1);
			if(i==1)continue;
			if(j!=i+n-1) add(np-(i+n-2)+ap,np,0,1);
			if(j!=1) add(np-(i+n-2)-1+ap,np,0,1);
			if(i==m){
				add(np+ap,t,0,1);
			}
		}
	}
	int ans = -MCMF();
	printf("%d\n",ans);
	s = 0;
	t = ap+1;
	tot = 1;
	memset(head,0,sizeof(head));
	for(int i=1;i<=n;++i)add(s,i,0,1);
	for(int i=1;i<=m;++i){
		for(int j=1;j<=i+n-1;++j){
			int np = (n+(i+n-2))*(i-1)/2+j;
			if(i!=m){
				add(np,np+i+n-1,-g[i][j],1);
				add(np,np+i+n,-g[i][j],1);
			}
			if(i==m) add(np,t,-g[i][j],INF);
		}
	}
	ans = -MCMF();
	printf("%d\n",ans);
	s = 0;
	t = ap+1;
	tot = 1;
	memset(head,0,sizeof(head));
	for(int i=1;i<=n;++i)add(s,i,0,1);
	for(int i=1;i<=m;++i){
		for(int j=1;j<=i+n-1;++j){
			int np = (n+(i+n-2))*(i-1)/2+j;
			if(i!=m){
				add(np,np+i+n-1,-g[i][j],INF);
				add(np,np+i+n,-g[i][j],INF);
			}
			if(i==m)add(np,t,-g[i][j],INF);
		}
	}
	ans = -MCMF();
	printf("%d\n",ans);
}
int main(){
	init();
	return 0;
} 
