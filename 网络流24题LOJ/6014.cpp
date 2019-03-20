#include<bits/stdc++.h>

using namespace std;
int max(const int& a,const int& b){
	return a>b?a:b;
}
const int inf = 2147483647;
const int N = 3000005;
int dis[5000],pre[5000];
bool inq[5000];
int l[5000],z[5000],y[5000],dic[5000],tp; 
struct Edges{
	int s,t,w,c,nxt;
	Edges(){}
	Edges(int ss,int tt,int ww,int cc,int nt):s(ss),t(tt),w(ww),c(cc),nxt(nt){}
}e[N];
int tot = 1,head[10000];
int n,k,s,t;
struct Qj{
	int s,t;
}arr[10100];
inline void add(int a,int b,int c,int d){
	e[++tot] = Edges(a,b,c,d,head[a]);
	head[a] = tot;
	e[++tot] = Edges(b,a,-c,0,head[b]);
	head[b] = tot;
}
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
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i){
		scanf("%d%d",&z[i],&y[i]);
		if(z[i]>y[i]){
			int ttt = z[i];
			z[i] = y[i];
			y[i] = ttt;
		}
	////	arr[i].s = aa;
		//arr[i].t = bb;
		dic[++tp] = z[i];
		dic[++tp] = y[i];
		l[i] = y[i]-z[i];
	}
	sort(dic+1,dic+tp+1);
	for(int i=1;i<=n;++i){
		z[i] = lower_bound(dic+1,dic+tp+1,z[i])-dic;
		y[i] = lower_bound(dic+1,dic+tp+1,y[i])-dic;
	}
	s = 0;
	t = n+n+1;
	add(s,1,0,k);
	add(n+n,t,0,k);
	
	for(int i=1;i<=n;++i){
		add(z[i],y[i],-l[i],1);
		//add(arr[i].s,arr[i].t,l[i],1);
	}
	for(int i=1;i<2*n;++i){
		add(i,i+1,0,inf);
	}
}
int main(){
	init();
	int ans = -MCMF();
	printf("%d\n",ans);
	return 0;
} 
