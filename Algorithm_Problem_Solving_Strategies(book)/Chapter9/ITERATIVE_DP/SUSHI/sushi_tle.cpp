#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

// #define DEBUG_INPUT
#define MAX_N 20
#define MAX_M INT_MAX
using namespace std;

vector<pair<int,int>> sushi;

int n,m;

int cache[MAX_N][MAX_M/100 + 1];

int dp(int idx, int budget){
	// printf("dp(%d, %d) \n", idx, budget);
	if( idx >= n) return 0;
	if( budget <= 0 ) return 0;
	
	int & ret = cache[idx][budget/100];
	if(ret >= 0) return ret;
	
	int p = sushi[idx].first; int l = sushi[idx].second;
	ret = 0;
	for(int i = 0; i <= budget/p; i++){
		ret = max(ret, l*i + dp(idx+1, budget - p*i));
	}
	// printf("dp(%d, %d) end, ret : %d \n", idx, budget,ret);
	return ret;
}

void solve(){
    cin>>n>>m;
	for(int i = 0 ; i < n; i++)
		fill(cache[i], cache[i] + MAX_M/100+1, -1);
    int p,l;
	map<int,int> s;
	
	//reset
	sushi.clear();
    for(int i = 0 ; i < n ; i++){
        cin>>p>>l;
        if(s.find(p) != s.end()) s[p] = max(s[p], l);
        else s[p] = l;
    }
    
    for(const auto & e : s){
        sushi.push_back({e.first, e.second});
    }
	
#ifdef DEBUG_INPUT
    for(const auto & e: sushi){
        cout<<e.first<<" "<<e.second<<endl;
    }
#endif
    cout<<dp(0,m)<<endl;
}

int main(){
    int c;
    cin>>c;
    while(c--) solve();
    return 0;
}

