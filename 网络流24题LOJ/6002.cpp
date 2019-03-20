#include<bits/stdc++.h>

using namespace std;
int n,m,ans;
int x[500],y[500];
int match[500];
bool used[500];
bool vis[500];
int mx[500];
struct Edges{
	int s,t,nxt;
	Edges(int a,int b,int c):s(a),t(b),nxt(c){}
	Edges(){} 
}ex[6060],ey[6060];
int tot = 1,cont = 1;
int headx[210],heady[210];
void init(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		ex[++tot] = Edges(u,v,headx[u]);
		headx[u] = tot;
	}
} 
bool find(int x){
	for(int i = headx[x];i;i = ex[i].nxt){
		int v = ex[i].t;
		if(used[v])continue;
		used[v] = 1;
		if(match[v] == 0 || find(match[v])){
			match[v] = x;
			mx[x] = v;
			return 1;
		}
	}
	return 0;
}
int main(){
	init();
	for(int i=1;i<=n;++i){
		memset(used,0,sizeof(used));
		if(find(i))++ans;
	}
/*	for(int i=1;i<=n;++i){
		printf("%d %d %d\n",i,match[i],mx[i]);
	}*/
	set<int>q[500];
	for(int t = 1;t<=n-ans;++t){
		int i,j,k;
		for(i=1;i<=n;++i){
			if(vis[i] == 0){
				break;
			}
		}
		j = i,k = i;
		q[t].insert(i);
		vis[i] = 1;
		while(match[j]!=0){
			j = match[j];
			vis[j] = 1;
			q[t].insert(j);
		}
		while(mx[k]!=0){
			k = mx[k];
			q[t].insert(k);
			vis[k] = 1;
		}
	}
	for(int i=1;i <= n-ans;++i){
		for(set<int>::iterator j = q[i].begin();j!=q[i].end();++j){
			printf("%d ",*j);
		}
		printf("\n");
	}
	printf("%d\n",n-ans);
	return 0;
} 
