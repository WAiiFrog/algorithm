#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring> 

using namespace std;

int n,m,tot = 0;
int g[120][120];
int mark[120];
int visit[120];
int p,f;
void init(){
	scanf("%d%d",&n,&m);
	p = m;
	f = n;
	int a = 0,b = 0;
	while(scanf("%d %d",&a,&b)!=EOF){
		g[a][b] = 1;
		g[b][a] = 1;
	}
}
bool find(const int &k){
	for(int j = p+1;j<=f;++j){
		if(g[k][j] && !visit[j]){
			visit[j] = 1;
			if(mark[j]==0 || find(mark[j])){
				mark[j] = k;
				return 1;
			}
		}
	}
	return 0;
}
int main(){
	int ans = 0;
	init();
	for(int i=1;i<=p;++i){
		memset(visit,0,sizeof(visit));
		if(find(i))++ans;
	}
	cout<<ans;
	return 0; 
} 
