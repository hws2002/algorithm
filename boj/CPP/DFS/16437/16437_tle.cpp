#include <iostream>
#include <vector>

#define MAX_N 123'456
// #define DEBUG_DFS
using namespace std;

typedef long long ll;
int N;

vector<int> children(MAX_N);
vector<ll> sheep(MAX_N,0);
vector<int> isleaf(MAX_N, true);

ll ret = 0;

void dfs(int h, ll amt){
#ifdef DEBUG_DFS
	printf("dfs(%d, %lld) \n", h, amt);
#endif
    if(h == 0){
		// printf("amt : %lld \n", amt);
        ret+=amt;
        return ;
    }

    if(sheep[h] < 0){
        if( amt < abs(sheep[h])){
            sheep[h] += amt;
            amt = 0;
        } else {
            amt += sheep[h];
            sheep[h] = 0;
        }
    } else {
        amt += sheep[h];
        sheep[h] = 0;
    }

    dfs(children[h], amt);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    cin>>N;
    char t;
    ll a;
    int p;
    for(int i = 1 ; i < N; i++){
        cin>>t>>a>>p;
        if(t == 'S'){
            sheep[i] += a;
        } else {
            sheep[i] -= a;
            // isleaf[i] = false;
        }
        children[i] = p-1;
        isleaf[p-1] = false;
    }
    
    for(int i = 1; i < N; i++){
        if(isleaf[i]){
#ifdef DEBUG_DFS
            printf("dfs(%d) \n", i);
#endif
            dfs(i,0);
        }
    }
    
    cout<<ret<<endl;

    return 0;
}