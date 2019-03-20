#include<bits/stdc++.h>

using namespace std;
const int inf = 2147483647;
const int N = 30005;
struct Edges{
	int s,t,w,c,nxt;
	Edges(){}
	Edges(int ss,int tt,int ww,int cc,int nt):s(ss),t(tt),w(ww),c(cc),nxt(nt){}
}e[N];
int tot = 1,head[300];
int arr[300];
inline void add(int a,int b,int c,int d){
	e[++tot] = Edges(a,b,c,d,head[a]);
	head[a] = tot;
	e[++tot] = Edges(b,a,-c,0,head[b]);
	head[b] = tot;
}
int n,s,t;
int g[200][200];
int dis[400],pre[400];
bool inq[400]; 
bool spfa(){
	for(int i=s;i<=t;++i){
		dis[i] = inf;
		inq[i] = false;
		pre[i] = 0;
	}
	queue<int>q;
	q.push(s);
	inq[s] = true;
	dis[s] = 0;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		inq[u] = false;
		for(int i=head[u];i;i = e[i].nxt){
			int v = e[i].t;
			if(dis[v] > dis[u]+e[i].w && e[i].c){
				dis[v] = dis[u]+e[i].w;
				pre[v] = i;
				if(!inq[v]){
					q.push(v);
					inq[v] = true;
				}
			}
		} 
	}
	if(dis[t] == inf) return false;
	return true;
}
int MCMF(){
	int cost = 0;
	while(spfa()){
		int tmp = inf;
		for(int i=pre[t];i;i = pre[e[i].s]) tmp = min(tmp,e[i].c);
		for(int i=pre[t];i;i = pre[e[i].s]){
			e[i].c-=tmp;
			e[i^1].c+=tmp;
			cost+=tmp*e[i].w;
		}
	}
	return cost;
}
void init(){
	scanf("%d",&n);
	int sum = 0;
	for(int i=1;i<=n;++i){
		scanf("%d",&arr[i]);
		sum+=arr[i];
	}
	sum/=n;
	s = 0;t = n+1;
	for(int i=1;i<=n;++i){
		arr[i]-=sum;
		if(arr[i]>0){
			add(0,i,0,arr[i]);
		}
		if(arr[i]<0){
			add(i,n+1,0,-arr[i]);
		}
	}
	add(1,n,1,inf);
	add(1,2,1,inf);
	add(n,1,1,inf);
	add(n,n-1,1,inf);
	for(int i = 2;i <= n-1;++i){
		add(i,i-1,1,inf);
		add(i,i+1,1,inf);
	}
}
int main(){
	init();
	int ans = MCMF();
	printf("%d\n",ans);
	return 0;
}
