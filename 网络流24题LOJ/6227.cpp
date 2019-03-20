#include<bits/stdc++.h>

using namespace std;
int max(const int& a,const int& b){
	return a>b?a:b;
}
const long long  inf = 0x3f7f7f7f7f7f7f7f;
const int N = 3000005;
long long dis[5000],pre[5000];
bool inq[5000];
long long l[5000],z[5000],y[5000],dic[5000],tp; 
struct Edges{
	int s,t,w,c,nxt;
	Edges(){}
	Edges(int ss,int tt,int ww,int cc,int nt):s(ss),t(tt),w(ww),c(cc),nxt(nt){}
}e[N];
int tot = 1,head[10000];
int n,k,s,t;
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
long long MCMF(){
	long long cost = 0;
	while(spfa()){
		int tmp = inf;
		for(int i=pre[t];i;i = pre[e[i].s]) tmp = min(tmp,e[i].c);
		for(int i=pre[t];i;i = pre[e[i].s]){
			e[i].c-=tmp;
			e[i^1].c+=tmp;
			cost+=(long long)tmp*(long long)e[i].w;
		}
	}
	return cost;
}
void init(){
	scanf("%d%d",&n,&k);
	for(int i=1,a,b,c,d;i<=n;++i){
		scanf("%d%d%d%d",&a,&b,&c,&d);
		if(a>c){
			a^=c^=a^=c;
			b^=d^=b^=d;
		}
		z[i] = a;
		y[i] = c;
		dic[++tp] = a;
		dic[++tp] = c;
		l[i] = (long long)sqrt((long long)1ll*(a-c)*(a-c)+(long long)1ll*(b-d)*(b-d));
	}
	sort(dic+1,dic+tp+1);
	for(int i=1;i<=n;++i){
		z[i] = lower_bound(dic+1,dic+tp+1,z[i])-dic;
		y[i] = lower_bound(dic+1,dic+tp+1,y[i])-dic;
	}
	tp = 0;
	for(int i=1;i<=n;++i){
		z[i]<<=1;
		y[i]<<=1;
		if(z[i] == y[i])++y[i];
		else ++z[i];
		dic[++tp] = z[i];
		dic[++tp] = y[i];
	}
	sort(dic+1,dic+tp+1);
	for(int i=1;i<=n;++i){
		//cout<<l[i]<<endl;
		z[i] = lower_bound(dic+1,dic+tp+1,z[i])-dic;
		y[i] = lower_bound(dic+1,dic+tp+1,y[i])-dic;
	}
	s = 0;
	t = n+n+n+n+1;
	add(s,1,0,k);
	add(n+n+n+n,t,0,k);
	
	for(int i=1;i<=n;++i){
		add(z[i],y[i],-l[i],1);
		//add(arr[i].s,arr[i].t,l[i],1);
	}
	for(int i=1;i<4*n;++i){
		add(i,i+1,0,inf);
	}
}
int main(){
	//freopen("line4.in","r",stdin);
	init();
	long long ans = -MCMF();
	printf("%lld\n",ans);
	return 0;
}
