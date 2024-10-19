//15:09 ~ 
#include <iostream>
#include <string>
#include <vector>

#define MAX_N 100
#define MAX_C 1001
using namespace std;

int n,W;
int value[MAX_N];
int weight[MAX_C];
vector<string> obj;

int dp[MAX_N][MAX_C];

void solve(){
	//input
    cin>>n>>W;
    
    //reset
	for(int i = 0 ; i < n ;i++)
    	fill(dp[i], dp[i]+W, 0);
	
    obj.resize(n);
    for(int i = 0; i < n; i++){
        cin>>obj[i]>>weight[i]>>value[i];
    }
	
	// dp
	for(int w = W; w >= 0; w--){
		if (w >= weight[0])
			dp[0][w] = value[0];
	}

    for(int i = 1; i < n; i++){
        for(int w = W; w >= 0; w--){
            if(w >= weight[i])
				dp[i][w] = max( dp[i-1][w], value[i] + dp[i-1][w - weight[i]]);
			else dp[i][w] = dp[i-1][w];
        }
    }
	
	//최대 절박도
    cout<<dp[n-1][W]<<" ";
	vector<int> ans = { 0, 4, 6, 10, 11, 13, 21, 24, 26, 27, 28, 29, 30 };
	int s = 0; int cw =0;
	for(auto i : ans){
		s += value[i];
		cw += weight[i];
	}
	// printf("s ,cw : %d, %d \n", s, cw);
	//가져갈 물건들의 개수와 그 목록
	vector<string> ret;
	int w = W;
	for(int i = n-1; i>=0; i--){
		if( dp[i][w] != dp[i-1][w]){ // 다를 경우 obj[i]를 선택했다
			ret.push_back(obj[i]);
			w -= weight[i];
		} else { // 같은 경우, obj[i]를 선택하지 않았으므로, 아무것도 하지 않는다.
			//do nothing
		}
		if(w<=0) break;
	}
	cout<<ret.size()<<endl;
	for(auto e : ret)
		cout<<e<<endl;
}

int main(){
    int c;
    cin>>c;
    while(c--) solve();
    return 0;
}