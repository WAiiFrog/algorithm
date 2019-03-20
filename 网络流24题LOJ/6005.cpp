#include<bits/stdc++.h>

using namespace std;
const int inf = 2147483647; 
int n,a[510],ml[510],tot = 1,len[510],s,t;
int head[1010],cur[1010];
int cont,ans;
struct Edges{
	int s,t,w,nxt;
	Edges(){}
	Edges(int a,int b,int c,int d):s(a),t(b),w(c),nxt(d){} 
}e[100010];
void add(int a,int b,int c){
	e[++tot] = Edges(a,b,c,head[a]);
	head[a] = tot;
	e[++tot] = Edges(b,a,0,head[b]);
	head[b] = tot;
}
void init(){
	scanf("%d",&n);
	memset(ml,0x3f,sizeof(ml));
	ml[0] = 0;
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		for(int j=cont;j>=0;--j){
			if(a[i]>=ml[j]){
				len[i] = j+1;
				ml[j+1] = min(a[i],ml[j+1]);
				break;
			}
		}
		cont = max(len[i],cont);
	}
	printf("%d\n",cont);
	s = 0;
	t = n+1;
	for(int i = n;i>=1;--i){
		if(len[i] == cont) add(0,i,1);
		if(len[i] == 1) add(i,n+1,1);
		for(int j = i-1;j>=1;--j){
			if(len[i] - 1 == len[j]){
				add(i,j,1);
			}
		}	
	}
}
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
		for(int i=0;i<=n+1;++i)	cur[i] = head[i];
		while(int d = dfs(s,inf)) ret+=d;
	}
	return ret;
}
int main(){
	init();
	ans = dinic();
	printf("%d\n",ans);
	if(n == 1){
		printf("1\n");
		return 0;
	}
	s = 0;
	t = n+1;
	tot = 1;
	memset(head,0,sizeof(head));
	for(int i = n;i>=1;--i){
		if(len[i] == cont) {
			if(i == n) add(0,i,inf);
			else add(0,i,1);
		}
		if(len[i] == 1){
			if(i==1) add(i,n+1,inf);
			else add(i,n+1,1);
		}
		for(int j = i-1;j >= 1;--j){
			if(len[i] - 1 == len[j] && a[i]>=a[j]){
				add(i,j,1);
			}
		}	
	}
	ans = dinic();
	printf("%d\n",ans);
	return 0;
} 
