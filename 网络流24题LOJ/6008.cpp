#include<bits/stdc++.h>

using namespace std;
const int inf = 2147483647;
const int N = 3000005;
struct Edges{
	int s,t,w,c,nxt;
	Edges(){}
	Edges(int ss,int tt,int ww,int cc,int nt):s(ss),t(tt),w(ww),c(cc),nxt(nt){}
}e[N];
int tot = 1,head[30010];
int arr[1010];
inline void add(int a,int b,int c,int d){
	e[++tot] = Edges(a,b,c,d,head[a]);
	head[a] = tot;
	e[++tot] = Edges(b,a,-c,0,head[b]);
	head[b] = tot;
}
int n,s,t;
int dis[10010],pre[10010];
bool inq[10010]; 
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
		//cout<<u<<endl;
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
	int P,M,F,N,S;
	scanf("%d%d%d%d%d%d",&n,&P,&M,&F,&N,&S);
	s = 0;
	t = n+n+1;
	for(int i=1;i<=n;++i){
		scanf("%d",&arr[i]);
		if(i+1<=n)add(n+i,n+i+1,0,inf);
		add(s,i,P,arr[i]);
		add(s,n+i,0,arr[i]);
		//add(i,i+n,0,inf);
		if(i+M<=n)add(i+n,i+M,F,inf);
		if(i+N<=n)add(i+n,i+N,S,inf);
		add(i,t,0,arr[i]);
	}
	int ans = MCMF();
	printf("%d\n",ans);
}
int main(){
	init();

	return 0;
}
