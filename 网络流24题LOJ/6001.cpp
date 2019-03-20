#include<bits/stdc++.h>

using namespace std;
const long long inf = 2147483647;
int n,m,w[55],dep[150],v[55],tot = 1,head[150],s,t,cur[150];
vector<int>us[55]; 
long long ans;
struct Edges{
	long long s,t,w,nxt;
	Edges(){}
	Edges(int a,int b,int c,int d):s(a),t(b),w(c),nxt(d){}
}e[50050];

inline long long min(const long long &a,const long long &b){
	return a<b?a:b;
}
inline void add(int a,int b,int c){
	e[++tot] = Edges(a,b,c,head[a]);
	head[a] = tot;
	e[++tot] = Edges(b,a,0,head[b]);
	head[b] = tot;
}

inline void init(){
		scanf("%d%d",&m,&n);
	for(register int i=1;i<=m;++i){
		scanf("%d",&w[i]);
		ans+=w[i];
		getchar();
		while(1){
			int a;
			scanf("%d",&a);
			us[i].push_back(a);
			char ch = getchar();
			if(ch=='\n' || ch == '\r')break;
		}
	}
	for(register int i=1;i<=n;++i) scanf("%d",&v[i]);
	
	for(register int i=1;i<=m;++i) add(0,i,w[i]);
	
	for(register int i = 1;i<=m;++i){
		for(vector<int>::iterator j = us[i].begin();j!=us[i].end();++j){
			add(i,(*j)+m,inf);
		}
	}
	for(register int i=1;i<=n;++i) add(i+m,n+m+1,v[i]);
	s = 0;
	t = n+m+1;
	return ;
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
long long dfs(int u,long long dist){
	if(u == t)return dist;
	int v;
	for(int &i = cur[u];i;i = e[i].nxt){
		v = e[i].t;
		if(dep[u]+1 == dep[v] && e[i].w!=0){
			long long di = dfs(v,min(dist,e[i].w));
			if(di){
				e[i].w-=di;
				e[i^1].w+=di;
				return di;
			}
		}
	}
	return 0;
}
inline long long dinic(){
	long long ret = 0;
	while(bfs()){
		for(register int i=s;i<=t;++i)cur[i] = head[i];
		while(long long d = dfs(s,inf))ret+=d;
	}
	return ret;
}
inline void solve(){
	ans -= dinic();
	int flag = 0;
	for(register int i = 1;i <= m;++i)
        if(dep[i] >= 0){
            if(flag)printf(" ");
			printf("%d",i);
			flag = 1;
		}
	puts("");
	flag = 0;
	for(register int i = 1;i <=n;++i)
        if(dep[i + m] >= 0){
            if(flag)printf(" ");
			printf("%d",i);
			flag = 1;
		}
	puts("");
	printf("%lld\n",ans);
}
int main(){
	init();
	solve();
	return 0;
} 
