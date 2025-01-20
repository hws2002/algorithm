// DP
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

#define all(v) v.begin(), v.end()
#define MAX_N 15
#define endl '\n'
using namespace std;

double dist[MAX_N][MAX_N] = {{0}};
vector<int> nearest[MAX_N];

int N;
int src;
	
double cache[MAX_N][1<<MAX_N] = {{-1}};

double dp(int here, int visited){

    if( visited == (1<<N) -1) {
		return 0;
	}
	
    double & ret = cache[here][visited];
    if(ret > -1) return ret;
    ret = numeric_limits<double>::max();
	int tochoose = -1;
    for(const auto next : nearest[here]){
        if( visited & (1<<next) ) continue;
		ret = min(ret, dp(next, visited | 1<<next) + dist[here][next] );
    }
    return ret;
}



void solve(){
    cin>>N;
	for(int i = 0 ; i < N; i++){
		fill(cache[i], cache[i] + (1<<MAX_N), -1);
		nearest[i].clear();
	}
	
    for(int i = 0 ; i < N; i++){
		vector< pair<double,int> > adj;
        for(int j = 0 ; j < N; j++){
            cin>>dist[i][j];
			if(i!=j) adj.push_back({dist[i][j], j});
        }
		sort(all(adj));
		for(const auto & p : adj)
			nearest[i].push_back(p.second);
    }

    //tsp
	double res = numeric_limits<double>::max();
	for(src = 0; src < N; src++){
		res = min(res, dp(src, 1<<src));
	}

	printf("%.10f \n", res);

}

int main(){
    int C; cin>>C; while(C--){ solve();} return 0;
}