#include<bits/stdc++.h>
const int N = 3000000;
const int INF = 2147483647;
using namespace std;
int s,t,n,m;
int st,ed;
struct Edges{
	int s,t,w,c,nxt;
	Edges(){}
	Edges(int ss,int tt,int ww,int cc,int nt):s(ss),t(tt),w(ww),c(cc),nxt(nt){}
}e[N];
int tot = 1,head[30000];
inline void add(int a,int b,int c,int d){
	e[++tot] = Edges(a,b,c,d,head[a]);
	head[a] = tot;
	e[++tot] = Edges(b,a,-c,0,head[b]);
	head[b] = tot;
}
int dis[4000],pre[4000];
bool inq[4000]; 
bool spfa(){
	for(int i=s;i<=t;++i){
		dis[i] = INF;
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
			//cout<<"ssssssss"<<dis[3]<<" "<<dis[0]+e[i].w<<" "<<e[i].c<<endl;
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
	if(dis[t] == INF) return false;
	return true;
}
int MCMF(){
	int cost = 0;
	while(spfa()){
		int tmp = INF;
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
	scanf("%d%d",&st,&ed);
	scanf("%d%d",&n,&m);
	s = 0;
	t = (n+1)*(m+1)+1;
	for(int i=1;i<=n+1;++i){
		for(int j=1;j<=m;++j){
			int value;
			scanf("%d",&value);
			add((i-1)*(m+1)+j,(i-1)*(m+1)+j+1,-value,1);
			add((i-1)*(m+1)+j,(i-1)*(m+1)+j+1,0,INF);
		}
	}
	for(int i=1;i<=m+1;++i){
		for(int j=1;j<=n;++j){
			int value;
			scanf("%d",&value);
			add((j-1)*(m+1)+i,j*(m+1)+i,-value,1);
			add((j-1)*(m+1)+i,j*(m+1)+i,0,INF);
		}
	}
	for(int i=1;i<=st;++i){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		b+=1;
		c+=1;
		add(s,(b-1)*(m+1)+c,0,a);
	}
	//cout<<"sssssssssss"<<e[head[0]].t<<endl;
	for(int i=1;i<=ed;++i){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		b+=1;
		c+=1;
		add((b-1)*(m+1)+c,t,0,a);
	}
	/*for(int i=1;i<=n+1;++i){
		for(int j=1;j<=m+1;++j){
			cout<<e[head[(i-1)*(m+1)+j]].t<<" ";
		} 
		cout<<endl;
	}*/
	int ans = -MCMF();
	printf("%d\n",ans);
}
int main(){
	init();
	return 0;
} 
