#include<bits/stdc++.h>

using namespace std;
int min(const int &xx,const int &yy){
	return xx<yy?xx:yy;
}
int mx[4] = {-1,0,1,0},my[4] = {0,1,0,-1};
struct Node{
	int x,y,key;
	Node(){}
	Node(int a,int b,int c):x(a),y(b),key(c){}
};
const int INF = 2147483647;
int n,m,k,p,s;
int dis[20][20][5000];
bool inq[20][20][5000];
int e[20][20][20][20];
int g[20][20];
void spfa(){
	memset(dis,0x3f,sizeof(dis));
	memset(inq,false,sizeof(inq));
	queue<Node>q;
	q.push(Node(1,1,g[1][1]));
	inq[1][1][g[1][1]] = true;
	dis[1][1][g[1][1]] = 0;
	while(!q.empty()){
		Node u = q.front();
		q.pop();
		int ux = u.x;
		int uy = u.y;
		int uk = u.key;
		inq[ux][uy][uk] = false;
		for(int i = 0;i<4;++i){
			int vx = ux + mx[i];
			int vy = uy + my[i];
			if(vx<1 || vx>n || vy<1 || vy>m) continue;
			if(e[ux][uy][vx][vy] == 0) continue;
			if(e[ux][uy][vx][vy] == -1){
				int tt = g[vx][vy];
				if(dis[vx][vy][tt|uk]>dis[ux][uy][uk]+1){
					dis[vx][vy][tt|uk] = dis[ux][uy][uk]+1;
					if(!inq[vx][vy][tt|uk]){
						q.push(Node(vx,vy,tt|uk));
						inq[vx][vy][tt|uk] = true;
					}
				}
				continue;
			}
			int tmp = 1<<(e[ux][uy][vx][vy]-1);
			if(tmp&uk){
				int tt = g[vx][vy];
				if(dis[vx][vy][tt|uk]>dis[ux][uy][uk]+1){
					dis[vx][vy][tt|uk] = dis[ux][uy][uk]+1;
					if(!inq[vx][vy][tt|uk]){
						q.push(Node(vx,vy,tt|uk));
						inq[vx][vy][tt|uk] = true;
					}
				}
				continue;
			}
		}
	}
	int ans = INF;
	for(int i=0;i<=(1<<p);++i){
		ans = min(ans,dis[n][m][i]);
	}
	if(ans==dis[0][0][0])printf("-1\n");
	else printf("%d\n",ans);
}
void init(){
	scanf("%d%d%d",&n,&m,&p);
	scanf("%d",&k);
	memset(e,-1,sizeof(e));
	for(int i=1;i<=k;++i){
		int a,b,c,d,t;
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&t);
		e[a][b][c][d] = e[c][d][a][b] = t;
	}
	scanf("%d",&s);
	for(int i=1;i<=s;++i){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		g[a][b] |= (1<<(c-1));
	}
	spfa();
}
int main(){
	init();
	
	return 0;
} 
