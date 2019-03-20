#include<bits/stdc++.h>

using namespace std;
const int INF = 2147483647;
const int N = 30005;
struct Edges{
	int s,t,w,c,nxt;
	Edges(){}
	Edges(int ss,int tt,int ww,int cc,int nt):s(ss),t(tt),w(ww),c(cc),nxt(nt){}
}e[N];
int tot = 1,head[5010];
int mx[2] = {0,1},my[2] = {1,0};
int arr[5010];
int cont = 0,al;
inline void add(int a,int b,int c,int d){
	e[++tot] = Edges(a,b,c,d,head[a]);
	head[a] = tot;
	e[++tot] = Edges(b,a,-c,0,head[b]);
	head[b] = tot;
}
int n,s,t,m,k;
int g[200][200];
int dis[5010],pre[5010];
bool inq[5010]; 
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
vector<int>road[100];
void print(int k){
	int len = road[k].size();
	for(int i=0;i<len;++i)printf("%d %d\n",k,road[k][i]);
} 
void dfs(int k,int x){
	if(x-al == n*m){
		print(k);
		return ;
	}
	for(int i = head[x];i;i = e[i].nxt){
		if(e[i^1].c>0 && e[i^1].s!=x-al){ 
			int u = x-al;
			int v = e[i^1].s;
			//cout<<u<<" "<<v<<endl;
			if(u%m == v%m) road[k].push_back(0);
			else road[k].push_back(1);
			e[i^1].c--;
			dfs(k,v+al);
			break;
		}
	}
}
void init(){
	scanf("%d",&k);
	scanf("%d%d",&m,&n);
	s = 0;
	t = n*m+n*m+1;
	al = n*m;
	add(s,1,0,k);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			scanf("%d",&g[i][j]);
			int now = (i-1)*m+j;
			int nxt = now+n*m;
			if(g[i][j] == 0){
				add(now,nxt,0,INF);
			}
			if(g[i][j] == 2){
				add(now,nxt,-1,1);
				add(now,nxt,0,INF);
			}
			for(int v = 0;v<2;++v){
				int x = i+mx[v];
				int y = j+my[v];
				if(x>0 && x<=n && y>0 && y<=m){
					int u = (x-1)*m+y;
					add(nxt,u,0,INF);
				}
				else continue;
			}
		}
	}
	add(n*m+n*m,t,0,INF);
	int ans = -MCMF();
	for(int i=1;i<=k;++i){
		dfs(i,1+al);
	}	
}
int main(){
	init();
	return 0;
} 
