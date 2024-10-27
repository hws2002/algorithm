#include <iostream>
#include <vector>

#define MAX_N 123'456
// #define DEBUG_DFS
using namespace std;

typedef long long ll;
int N;

vector<int> parent[MAX_N];
vector<ll> sheep(MAX_N,0);


ll dfs(int h){
	ll ret = sheep[h];
	for(auto c : parent[h]){
		ret += dfs(c);
	}
	return max<ll>(0,ret);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    cin>>N;
    char t;
    ll a;
    int c;
    for(int i = 1 ; i < N; i++){
        cin>>t>>a>>c;
        if(t == 'S'){
            sheep[i] += a;
        } else {
            sheep[i] -= a;
        }
		parent[c-1].push_back(i);
    }
    
    cout<<dfs(0)<<endl;

    return 0;
}