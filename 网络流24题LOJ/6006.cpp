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
int n,m,k;
int head[2010],cur[2010];
int s,t,ans;
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
		for(int i=0;i<=n+k+1;++i)	cur[i] = head[i];
		int d = 0;
		while(d = dfs(s,inf)) ret+=d;
		//printf("%d\n",d);
	}
	return ret;
}
void init(){
	scanf("%d%d",&k,&n);
	s = 0;
	t = n+k+1;
	for(int i=1,x;i<=k;++i){
		scanf("%d",&x);
		m+=x;
		add(i+n,k+n+1,x);
	}
	for(int i=1,x;i<=n;++i){
		add(0,i,1);
		scanf("%d",&x);
		for(int j=1,y;j<=x;++j){
			scanf("%d",&y);
			add(i,y+n,1);
		}
	}
}
int main(){
	init();
	ans = dinic();
	if(ans<m){
		printf("No Solution!\n");
		return 0;
	}
	for(int i=1;i<=k;++i){
		printf("%d: ",i);
		for(int j=head[n+i];j;j = e[j].nxt){
			if(e[j].t>=1 && e[j].t<=n && e[j].w == 1){
				printf("%d ",e[j].t);
			}
		}
		printf("\n");
	}
	return 0;
}
