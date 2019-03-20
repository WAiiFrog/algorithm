#include<bits/stdc++.h>

using namespace std;
const int INF = 2147483647;
int n,m,w[40010],dep[40010],v[40010],tot = 1,head[40010],s,t,cur[40010],ans;
int mx[8] = {-2,-1,1,2,2,1,-1,-2},my[8] = {1,2,2,1,-1,-2,-2,-1};
struct Edges{
	int s,t,w,nxt;
	Edges(){}
	Edges(int a,int b,int c,int d):s(a),t(b),w(c),nxt(d){}
}e[1000050];
inline void add(int a,int b,int c){
	e[++tot] = Edges(a,b,c,head[a]);
	head[a] = tot;
	e[++tot] = Edges(b,a,0,head[b]);
	head[b] = tot;
}
inline bool bfs(){
	memset(dep,-1,sizeof(dep));
	queue<int>q;
	q.push(s);
	dep[s] = 0;
	int u,v;
	while(!q.empty()){
		u = q.front();
		q.pop();
		for(int i = head[u];i;i = e[i].nxt){
			v = e[i].t;
			if(dep[v] == -1 && e[i].w>0){
				q.push(v);
				dep[v] = dep[u]+1;
			}
		}
	}
	if(dep[t] == -1)return 0;
	else return 1;
}
int dfs(int u,int dist){
	if(u == t)return dist;
	int v;
	for(int &i = cur[u];i;i = e[i].nxt){
		v = e[i].t;
		if(dep[u]+1 == dep[v] && e[i].w!=0){
			int di = dfs(v,min(dist,e[i].w));
			if(di){
				e[i].w-=di;
				e[i^1].w+=di;
				return di;
			}
		}
	}
	return 0;
}
inline int dinic(){
	int ret = 0;
	while(bfs()){
		for(register int i=s;i<=t;++i)cur[i] = head[i];
		while(int d = dfs(s,INF))ret+=d;
	}
	return ret;
}
inline void init(){
	scanf("%d%d",&n,&m);
	s = 0;
	t = n*n+1;
	bool g[300][300];
	memset(g,0,sizeof(g));
	for(int i=1;i<=m;++i){
		int a,b;
		scanf("%d%d",&a,&b);
		g[a][b] = 1;
	} 
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			int u = (i-1)*n+j;
			int pd = i+j;
			if(pd&1){
				if(!g[i][j])add(s,u,1);
				for(int l=0;l<8;++l){
					int x = i+mx[l];
					int y = j+my[l];
					if(x>0 && x<=n && y>0 && y<=n){
						int v = (x-1)*n+y;
						add(u,v,INF); 
					}
				}
			} 
			else{
				if(!g[i][j])add(u,t,1);
			}
		}
	}
	int ans = dinic();
	cout<<n*n-ans-m;
}
int main(){
	init();
	return 0;
}
