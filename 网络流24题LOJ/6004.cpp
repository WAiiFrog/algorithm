#include<bits/stdc++.h>
using namespace std;
const int N = 400010;
const int inf = 2147483647;
struct Edges{
	int s,t,w,nxt;
	Edges(){}
	Edges(int a,int b,int c,int d):s(a),t(b),w(c),nxt(d){} 
}e[N];
int tot = 1;
int n,m;
int head[1010],cur[1010];
int s,t;
int cont  = 0;
void add(int a,int b,int c){
	e[++tot] = Edges(a,b,c,head[a]);
	head[a] = tot;
	e[++tot] = Edges(b,a,0,head[b]);
	head[b] = tot;
}
void init(){
	scanf("%d%d",&n,&m);
	s = 0;
	t = n+m+1;
	for(int i=1;i<=n;++i){
		int a;
		scanf("%d",&a);
		cont+=a;
		add(0,i,a);
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			add(i,n+j,1);
		}
	}
	for(int i=1;i<=m;++i){
		int a;
		scanf("%d",&a);
		add(n+i,n+m+1,a);
	}
	return ;
}
int ans = 0;
int dep[1010];
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
			if(dep[v] == 0 && e[i].w>0){
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
		for(int i=0;i<=n+m+1;++i){
			cur[i] = head[i];
		}
		while(int di = dfs(s,inf))ret+=di;
	}
	return ret;
}
int main(){
	init();
	ans = dinic();
	if(ans!=cont){
		printf("0\n");
	}
	else{
		printf("1\n");
		for(int i=1;i<=n;++i){
			for(int j=head[i];j;j = e[j].nxt){
				if(e[j].w == 0){
					printf("%d ",e[j].t-n);
				}
			}
			printf("\n");
		}
	}
	return 0;
}
