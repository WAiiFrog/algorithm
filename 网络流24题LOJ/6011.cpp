#include<bits/stdc++.h>

using namespace std;
const int inf = 2147483647;
const int N = 500005;
struct Edges{
	int s,t,w,c,f,nxt;
	Edges(){}
	Edges(int ss,int tt,int ww,int cc,int ff,int nt):s(ss),t(tt),w(ww),c(cc),f(ff),nxt(nt){}
}e[N],e2[N];
int tot = 1,head[2500];
inline void add(int a,int b,int c,int d){
	e[++tot] = Edges(a,b,c,d,0,head[a]);
	head[a] = tot;
	e[++tot] = Edges(b,a,-c,0,0,head[b]);
	head[b] = tot;
}
int tot2 = 1,head2[2500];
inline void add2(int a,int b,int c,int d){
	e2[++tot2] = Edges(a,b,c,d,0,head2[a]);
	head2[a] = tot2;
	e2[++tot2] = Edges(b,a,-c,0,0,head2[b]);
	head2[b] = tot2;
}
int n,m,s,t;
bool inq[2500];
int dis[2500];
int pre[2500];
int aa[2500],bb[2500],g[510][510];
inline bool spfa(){
	for (register int i = s; i <= t; ++i) {
        inq[i] = false;
        dis[i] = inf;
        pre[i] = 0;
    }
	queue<int>q;
	q.push(s);
	dis[s] = 0;
	inq[s] = 1;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		inq[u] = false;
		for(register int i=head[u];i;i = e[i].nxt){
			int v = e[i].t;
			if(dis[v] > dis[u] + e[i].w && e[i].c){
				dis[v] = dis[u] + e[i].w;
				pre[v] = i;
				if(!inq[v]){
					q.push(v);
					inq[v] = 1;
				}
			}
		}
	}
	if(dis[t] == inf)return 0;
	return 1;
}
inline bool spfa2(){
	for (register int i = s; i <= t; i++) {
        inq[i] = false;
        dis[i] = inf;
        pre[i] = 0;
    }
	queue<int>q;
	q.push(s);
	dis[s] = 0;
	inq[s] = 1;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		inq[u] = false;
		for(register int i=head2[u];i;i = e2[i].nxt){
			int v = e2[i].t;
			if(dis[v] > dis[u] + e2[i].w && e2[i].c){
				dis[v] = dis[u]+e2[i].w;
				pre[v] = i;
				if(!inq[v]){
					q.push(v);
					inq[v] = 1;
				}
			}
		}
	}
	if(dis[t] == inf)return 0;
	return 1;
}
inline int MCMF(){
	int cost = 0;
	while(spfa()){
		int tmp = inf;
		for (register int i = pre[t]; i; i = pre[e[i].s]) 
			tmp = min(tmp, e[i].c);
        for (register int i = pre[t]; i; i = pre[e[i].s]) {
            e[i].c -= tmp;
            e[i ^ 1].c += tmp;
            cost += tmp * e[i].w;
        }
	}
	return cost;
}
inline int MCMF2(){
	int cost = 0;
	while(spfa2()){
		int tmp = inf;
		for (register int i = pre[t]; i; i = pre[e2[i].s]) tmp = min(tmp, e2[i].c);
        for (register int i = pre[t]; i; i = pre[e2[i].s]) {
            e2[i].c -= tmp;
            e2[i ^ 1].c += tmp;
            cost += tmp * e2[i].w;
        }
	}
	return cost;
}
inline void init(){
	scanf("%d%d",&n,&m);
	s = 0;
	t = n+m+1;
	for(register int i=1;i<=n;++i){
		scanf("%d",&aa[i]);
		add(s,i,0,aa[i]);
		add2(s,i,0,aa[i]);
	}
	for(register int i=1;i<=m;++i){
		scanf("%d",&bb[i]);
		add(i+n,t,0,bb[i]);
		add2(i+n,t,0,bb[i]);
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			scanf("%d",&g[i][j]);
			add(i,j+n,g[i][j],inf);
			add2(i,j+n,-g[i][j],inf);
		}
	}
}
int main(){
	init();	
	int ans1 = MCMF();
	printf("%d\n",ans1);
	int ans2 = MCMF2();
	printf("%d\n",-ans2);
	return 0;
} 
