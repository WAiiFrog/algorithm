#include<bits/stdc++.h>

using namespace std;
int n,m,k;
const int inf = 2147483647;
const int N = 2000010;
int h[1010],len[1010];
int g[1011][1011];
bool flag;
struct Edges{
	int s,t,w,nxt;
	Edges(){}
	Edges(int a,int b,int c,int d):s(a),t(b),w(c),nxt(d){} 
}e[N];
int tot = 1;
int head[20010],cur[20010];
int s,t,ans;
void add(int a,int b,int c){
	e[++tot] = Edges(a,b,c,head[a]);
	head[a] = tot;
	e[++tot] = Edges(b,a,0,head[b]);
	head[b] = tot;
}
int dep[20010];
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
	//printf("%d\n",dep[t]);
	if(dep[t] == 0)return 0;
	else return 1;
}
int dfs(int u,int dist){
	if(u == t)return dist;
	for(int i=head[u];i;i = e[i].nxt){
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
		//for(int i=s;i<=t;++i)	cur[i] = head[i];
		int d = 0;
		while(d = dfs(s,inf)) ret+=d;
		//printf("%d\n",d);
	}
	return ret;
}
void init(){
	scanf("%d%d%d",&n,&m,&k);
	s = 0;
	t = 9999;
	n+=2;
	for(int i=1;i<=m;++i){
		scanf("%d%d",&h[i],&len[i]);
		for(int j=0;j<len[i];++j){
			scanf("%d",&g[i][j]);
			g[i][j]+=2;
		}
	}
	for(int time = 0;time<=500;time++){
		add(s,time*n+2,inf);
		add(time*n+1,t,inf);
		if(time!=0){
			for(int i=1;i<=m;++i){
				int u = g[i][(time-1)%len[i]];
				int v = g[i][time%len[i]];
				add((time-1)*n+u,time*n+v,h[i]);
			}
			for(int i=1;i<=n;++i) add((time-1)*n+i,time*n+i,inf);
		}
		ans += dinic();
		//printf("%d\n",ans);
		if(ans>=k){
			printf("%d\n",time);
			flag = 1;
			break;
		}
	}
}
int main(){
	init();
	if(!flag)printf("0\n");
	return 0;
} 
