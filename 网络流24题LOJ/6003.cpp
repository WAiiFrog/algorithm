#include<bits/stdc++.h>

using namespace std;
int n;
vector<int>s[60];
int main(){
	scanf("%d",&n);
	int i = 1;
	bool flag = 0;
	while(1){
		flag = 0;
		for(int j=1;j<=n;++j){
			if(s[j].empty()){
				s[j].push_back(i);
				flag = 1;
				break;
			}
			int k = s[j][s[j].size()-1]+i;
			int kk = sqrt(k);
			if(kk*kk == k){
				s[j].push_back(i);
				flag = 1;
				break;
			}
		}
		if(!flag)break;
		++i;
	}
		printf("%d\n",i-1);
	for(int j=1;j<=n;++j){
		for(vector<int>::iterator k = s[j].begin();k!=s[j].end();++k){
			printf("%d ",*k);
		}
		printf("\n");
	}

	return 0;
}
