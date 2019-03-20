#include<bits/stdc++.h>

using namespace std;
int min(const int &xx,const int &yy){
	return xx<yy?xx:yy;
}
int g[110][110];
int dis[110][110][110];
bool inq[110][110][110];
int mx[4] = {-1,0,1,0},my[4] = {0,1,0,-1};
const int INF = 0x3f3f3f3f;
int n,k,a,b,c;
struct Node{
	int x,y,k;
	Node(int aa,int bb,int cc):x(aa),y(bb),k(cc){}
	Node(){}
};
void spfa(){
	queue<Node>q;
	dis[1][1][k] = 0;
	q.push(Node(1,1,k));
	inq[1][1][k] = true;
	while(!q.empty()){
		Node u = q.front();
		int ux = u.x;
		int uy = u.y;
		int uk = u.k;
		q.pop();
		inq[ux][uy][uk] = false;
		if(g[ux][uy] && uk != k){
			if(dis[ux][uy][k]>dis[ux][uy][uk]+a){
				dis[ux][uy][k] = dis[ux][uy][uk] + a;
				if(inq[ux][uy][k] == false){
					q.push(Node(ux,uy,k));
					inq[ux][uy][k] == true;
				}
			}
			continue;
		}
		else{
			if(dis[ux][uy][k]>dis[ux][uy][uk]+a+c){
				dis[ux][uy][k] = dis[ux][uy][uk]+a+c;
				if(inq[ux][uy][k] == false){
					q.push(Node(ux,uy,k));
					inq[ux][uy][k] = true;
				}
			}
		}
		if(uk>0){
			for(int i=0;i<4;++i){
				int vx = ux + mx[i];
				int vy = uy + my[i];
				if(vx<1 || vx>n || vy<1 || vy>n) continue;
				int cost = 0;
				if(vx<ux || vy<uy) cost = b;
				if(dis[vx][vy][uk-1]>dis[ux][uy][uk]+cost){
					dis[vx][vy][uk-1] = dis[ux][uy][uk]+cost;
					if(inq[vx][vy][uk-1] == false){
						q.push(Node(vx,vy,uk-1));
						inq[vx][vy][uk-1] = true;
					}	
				}
			}
		}
		
	}
	int ans = INF;
	for(int i=0;i<=k;++i) ans = min(ans,dis[n][n][i]);
	printf("%d\n",ans);
}
void init(){
	scanf("%d%d%d%d%d",&n,&k,&a,&b,&c);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j) scanf("%d",&g[i][j]);
	memset(inq,false,sizeof(inq));
	memset(dis,0x3f,sizeof(dis));
	spfa();
}
int main(){
	init();
	return 0;
}
