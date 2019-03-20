#include<bits/stdc++.h>

using namespace std;
int n,m;
const int N = 1<<21;
int f1[N],f2[N],b1[N],b2[N],cost[110];
bool inq[N];
int dis[N];
int main(){
	scanf("%d%d",&n,&m);
	string st1,st2;
	memset(dis,0x3f,sizeof(dis));
	int s = 0; 
	for(int i=0;i<n;++i)s+=(1<<i);
	for(int i=1;i<=m;++i){
		scanf("%d",&cost[i]);
		cin>>st1>>st2;
		for(int j=0;j<n;++j){
			if(st1[j] == '+'){
				b1[i]+= (1<<j);
			}
			if(st1[j] == '-'){
				b2[i]+= (1<<j);
			}
			if(st2[j] == '-'){
				f1[i]+= (1<<j);
			}
			if(st2[j] == '+'){
				f2[i]+= (1<<j);
			}
		}
	}
	queue<int >q;
	q.push(s);
	dis[s] = 0;
	inq[s] = true;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		inq[u] = false;
		for(int i=1;i<=m;++i){
			//if(i==2)cout<<u<<" "<<b1[i]<<" "<<b2[i]<<" "<<(u&b1[i])<<" "<<(u&b2[i])<<endl;
			if(((u&b1[i]) == b1[i]) && ((u&b2[i]) == 0)){
				int v = (u|f1[i])^f1[i];
				v|=f2[i];
				//cout<<u<<" "<<v<<" "<<i<<endl;
				if(dis[v] > dis[u]+cost[i]){
					dis[v] = dis[u]+cost[i];
					//cout<<"dis="<<dis[v]<<endl;
					if(!inq[v]){
						q.push(v);
						inq[v] = true;
					}
				}
			}
			
		}
	}
	if(dis[0] == dis[105])printf("0\n");
	else printf("%d\n",dis[0]);
	return 0;
}
