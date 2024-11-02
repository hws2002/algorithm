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

int dp[MAX_C];

void solve(){
    cin>>n>>W;
    
    //reset
    fill(dp, dp+W, 0);
    obj.resize(n);
    for(int i = 0; i < n; i++){
        cin>>obj[i]>>weight[i]>>value[i];
    }
	
    for(int i = 0 ; i < n; i++){
        for(int w = W; w >= 0; w--){
            if(w >= weight[i]) dp[w] = max(dp[w], value[i] + dp[w-weight[i]] );
        }
    }
    cout<<dp[W]<<endl;
}

int main(){
    int c;
    cin>>c;
    while(c--) solve();
    return 0;
}