
#include<bits/stdc++.h>

using namespace std;

 

const int maxn=10000;

const int maxm=300000;

const int inf=0x3f3f3f3f;

 

struct Edge{

	int to,nxt,cap,flow,cost;

}edge[maxm];

 

char str[maxn][50],st[50];

int Head[maxn],tol;

int pre[maxn];

int dis[maxn];

int n,m,s,t,tot;

bool vis[maxn];

 

void init(){

	tol=0;

	memset(Head,-1,sizeof(Head));

}

 

void addedge(int u,int v,int cap,int cost){

	edge[tol].to=v;

	edge[tol].cap=cap;

	edge[tol].cost=cost;

	edge[tol].flow=0;

	edge[tol].nxt=Head[u];

	Head[u]=tol++;

	edge[tol].to=u;

	edge[tol].cap=0;

	edge[tol].cost=-cost;

	edge[tol].flow=0;

	edge[tol].nxt=Head[v];

	Head[v]=tol++;

}

 

bool spfa(int s,int t){

	queue<int> q;

	for(int i=0;i<=tot+1;i++){

		dis[i]=inf;

		vis[i]=false;

		pre[i]=-1;

	}

	dis[s]=0;

	vis[s]=true;

	q.push(s);

	while(!q.empty()){

		int u=q.front();

		q.pop();

		vis[u]=false;

		for(int i=Head[u];i!=-1;i=edge[i].nxt){

			int v=edge[i].to;

			if (edge[i].cap>edge[i].flow&&dis[v]>dis[u]+edge[i].cost){

				dis[v]=dis[u]+edge[i].cost;

				pre[v]=i;

				if (!vis[v]){

					vis[v]=true;

					q.push(v);

				}

			}

		}

	}

	if (pre[t]==-1) return false;

	return true;

}

 

int minCostMaxflow(int s,int t,int &cost){

	int flow=0;

	cost=0;

	while(spfa(s,t)){

		int Min=inf;

		for(int i=pre[t];i!=-1;i=pre[edge[i^1].to])

			if (Min>edge[i].cap-edge[i].flow)

				Min=edge[i].cap-edge[i].flow;

		for(int i=pre[t];i!=-1;i=pre[edge[i^1].to]){

			edge[i].flow+=Min;

			edge[i^1].flow-=Min;

			cost+=edge[i].cost*Min;

		}

		flow+=Min;

	}

	return flow;

}

 

void dfs(int u){

	if (u<=n&&!vis[u]) cout<<str[u]<<endl;

	vis[u]=true;

	for(int i=Head[u];i!=-1;i=edge[i].nxt){

		int v=edge[i].to;

		if (edge[i].flow&&!vis[v]) dfs(v);

	}

	return;

}

 

int main(){

	//freopen("input.txt","r",stdin);

	while(scanf("%d%d",&n,&m)!=EOF){

		init();

		for(int i=1;i<=n;i++) scanf("%s",str[i]);

		for(int i=2;i<n;i++) addedge(i,i+n,1,-1);

		addedge(1,1+n,2,-1);

		addedge(n,n+n,2,-1);

		s=1;

		t=n+n;

		tot=n+n;

		for(int i=1;i<=m;i++){

			int pos1,pos2;

			scanf("%s",st);

			for(int j=1;j<=n;j++)

				if (strcmp(str[j],st)==0){

					pos1=j;

					break;

				}

			scanf("%s",st);

			for(int j=1;j<=n;j++)

				if (strcmp(str[j],st)==0){

					pos2=j;

					break;

				}

			if (pos1>pos2) swap(pos1,pos2);

			addedge(pos1+n,pos2,1,0);

			if (pos1==1&&pos2==n) addedge(n+1,n,2,0);

		}

		int Cost,Maxflow;

		Maxflow=minCostMaxflow(s,t,Cost);

		if (Maxflow<2){

			//printf("Maxflow: %d\n",Maxflow);

			puts("No Solution!");

		}

		else{

			printf("%d\n",-Cost-2);

			memset(vis,false,sizeof(vis));

			dfs(1);

			cout<<str[1]<<endl;

		}

	}

	return 0;

}

