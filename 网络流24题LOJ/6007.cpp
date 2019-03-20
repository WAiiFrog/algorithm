#include<bits/stdc++.h>

using namespace std;
const int inf = 2147483647;
const int N = 2000010;
struct Edges{
	int s,t,w,nxt;
	Edges(){}
	Edges(int a,int b,int c,int d):s(a),t(b),w(c),nxt(d){} 
}e[N];
int tot = 1;
int ans = 0;
int n,m,k;
int head[2010],cur[2010];
int g[50][50];
int s,t;
void add(int a,int b,int c){
	e[++tot] = Edges(a,b,c,head[a]);
	head[a] = tot;
	e[++tot] = Edges(b,a,0,head[b]);
	head[b] = tot;
}
int dep[2010];
bool bfs(){
	memset(dep,0,sizeof(dep));
	queue<int >q;
	q.push(s);
	dep[s] = 1;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int i=head[u];i;i = e[i].nxt){
			int v = e[i].t;
			if(dep[v] == 0 && e[i].w > 0){
				dep[v] = dep[u]+1;
				q.push(v);
			}
		}
	}
	if(dep[t] == 0)return 0;
	else return 1;
}
int dfs(int u,int dist){
	if(u == t)return dist;
	for(int &i=cur[u];i;i = e[i].nxt){
		int v = e[i].t;
		if(dep[u]+1 == dep[v] && e[i].w>0){
			int di = dfs(v,min(dist,e[i].w));
			if(di>0){
				e[i].w-=di;
				e[i^1].w+=di;
				return di;
			}
		}
	}
	return 0;
}
int dinic(){
	int ret = 0;
	while(bfs()){
		for(int i=0;i<=n*m+1;++i)	cur[i] = head[i];
		int d = 0;
		while(d = dfs(s,inf)) ret+=d;
		//printf("%d\n",d);
	}
	return ret;
}
void init(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			scanf("%d",&g[i][j]);
			ans+=g[i][j];
			int u = (i-1)*m+j;
			int z = i+j;
			if(z%2 != 0){
				add(0,u,g[i][j]);
				int v = (i-2)*m+j;
				if(i-1>0) add(u,v,inf);
				v = i*m+j;
				if(i+1<=n) add(u,v,inf);
				v = (i-1)*m+j-1;
				if(j-1>0) add(u,v,inf);
				v = (i-1)*m+j+1;
				if(j+1<=m) add(u,v,inf);
			}
			else add(u,n*m+1,g[i][j]);
		}
		
	}
	s = 0;
	t = n*m+1;
} 
int main(){
	init();
	int tt = dinic();
	printf("%d\n",ans - tt);
	return 0;
} 
