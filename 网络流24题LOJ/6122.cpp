#include<bits/stdc++.h>

using namespace std;
const int inf = 2147483647;
const int N = 30005;
map<string,int>mp;
struct Edges{
	int s,t,w,c,f,nxt;
	Edges(){}
	Edges(int ss,int tt,int ww,int cc,int ff,int nt):s(ss),t(tt),w(ww),c(cc),f(ff),nxt(nt){}
}e[N];
int tot = 1,head[300];
inline void add(int a,int b,int c,int d){
	e[++tot] = Edges(a,b,c,d,0,head[a]);
	head[a] = tot;
	e[++tot] = Edges(b,a,-c,0,0,head[b]);
	head[b] = tot;
}
int n,m,s,t;
int dis[400],pre[400];
bool inq[400]; 
string ct[400];
inline bool spfa(){
	for(register int i=1;i<=n+n;++i){
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
			if((dis[v] > dis[u]+e[i].w) && (e[i].c>e[i].f)){
				dis[v] = dis[u]+e[i].w;
				pre[v] = i;
				if(!inq[v]){
					q.push(v);
					inq[v] = true;
				}
			}
		} 
	}
	//cout<<dis[t]<<endl;
	if(dis[t] == inf) return false;
	return true;
}
inline int MCMF(int &flow){
	int cost = 0,tt = 0;
	while(spfa()){
		int tmp = inf;
		for(register int i=pre[t];i;i = pre[e[i].s]) tmp = min(tmp,e[i].c-e[i].f);
		for(register int i=pre[t];i;i = pre[e[i].s]){
			e[i].f+=tmp;
			e[i^1].f-=tmp;
			cost += e[i].w*tmp;
			tt+=tmp;
		}
	}
	flow = tt;
	return cost;
}
inline void init(){
	scanf("%d%d",&n,&m);
	string st1,st2;
	//add(n+1,n+n+1,0,inf);
	s = 1;
	t = n+n;
	for(register int i=1;i<=n;++i){
		cin>>st1;
		mp[st1] = i;
		ct[i] = st1;
	}
	for(register int i=2;i<=n-1;++i){
		add(i,i+n,-1,1);
	}
	add(1,1+n,-1,2);
	add(n,n+n,-1,2);
	for(register int i=1;i<=m;++i){
		cin>>st1>>st2;
		int u = mp[st1];
		int v = mp[st2];
		if(u>v)u^=v^=u^=v;
		if(u == 1 && v == n){
			add(u+n,v,0,2);
		}
		add(u+n,v,0,1);
	}
}
vector<int>city;
void search(int x){
	if(x == n+n)return;
	for(register int i=head[x];i;i = e[i].nxt){
		if(e[i].f > 0 && e[i].w == 0){
			city.push_back(e[i].t);
			--e[i].f;
			search(e[i].t+n);
			break;
		}
	}
	return ;
}
int main(){
	//std::ios::sync_with_stdio(false);
	init();
	int ss = 0;
	int ans = -MCMF(ss);
	if(ss<2){
		printf("No Solution!\n");
		return 0;
	}
	printf("%d\n",ans-2);
	city.push_back(1);
	search(n+1);
	for(vector<int>::iterator i = city.begin();i!=city.end();++i){
		cout<<ct[*i]<<endl;
	}
	city.clear();
	city.push_back(1);
	search(n+1);
	for(register int i = city.size()-2;i>=0;--i){
		cout<<ct[city[i]]<<endl;
	}
	return 0; 
}
