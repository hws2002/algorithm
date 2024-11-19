#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <limits.h>

// #define DEBUG_INPUT
#define MAX_N 20
#define endl '\n'
using namespace std;

int n,m;

int cache[201] = {0};

void solve(){
    cin>>n>>m;
	m/=100;
    int p,l;
	map<int,int> s;
	
	//reset
    vector<pair<int,int>> sushi;
    
    for(int i = 0 ; i < n ; i++){
        cin>>p>>l; p/=100;
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
	
	//solve
	fill(cache, cache + 201, 0);
	
	int ret = 0;
	for(int budget = 1; budget <= m; budget++){
		
		for(const auto & e : sushi){
			p = e.first; l = e.second;
			if( budget - p >= 0) {
				cache[ budget % 201] = max(cache[budget%201], cache[(budget-p) % 201] + l);
			}
		}
		
		ret = max(ret, cache[budget % 201]);
	}
	cout<<ret<<endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    int c;
    cin>>c;
    while(c--) solve();
    return 0;
}

