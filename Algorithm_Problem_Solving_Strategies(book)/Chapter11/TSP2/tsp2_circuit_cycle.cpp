// DP
#include <iostream>
#include <vector>
#include <limits>

#define MAX_N 15
using namespace std;

double dist[MAX_N][MAX_N] = {{0}};
vector<double> nearest[MAX_N];

int N;
int src = 0;
	
double cache[MAX_N][1<<MAX_N] = {{-1}};

double dp(int here, int visited){

    if( visited == (1<<N) -1) {
		return dist[here][src];
	}
	
    double & ret = cache[here][visited];
    if(ret > -1) return ret;
    ret = numeric_limits<double>::max();
	int tochoose = -1;
    for(int next = 0 ; next < N; next++){
        if( visited & (1<<next) ) continue;
		ret = min(ret, dp(next, visited | 1<<next) + dist[here][next] );
    }
    return ret;
}

void solve(){
    cin>>N;
	for(int i = 0 ; i < N; i++){
		fill(cache[i], cache[i] + (1<<MAX_N), -1);
	}
	
    for(int i = 0 ; i < N; i++){
        for(int j = 0 ; j < N; j++){
            cin>>dist[i][j];
        }
    }

    //tsp
	double res = dp(src,1);
	
	// find largest cost
	double tosub = -1;
	int visited = 1; int here = src; int next = -1;
	int iter = N-1;
	vector<int> path {src};
	while( iter--){	
		double smallest_dp = numeric_limits<double>::max();
		for(int i = 0 ; i < N; i++){
			if( visited & (1<<i)) continue;
			if( dp( i, visited | (1<<i) ) < smallest_dp){
				smallest_dp = dp(i,visited | (1<<i) );
				next = i;
			}
		}
		tosub = max(tosub, dist[here][next]);
		path.push_back(next);
		here = next;
		visited |= (1<<next);
	}
	tosub = max(tosub, dist[here][src]);
	for(const auto e :path){
		cout<<e<<" ";
	}
	cout<<endl;
	printf("%.10f \n", res);
	printf("%.10f \n", tosub);
	printf("%.10f \n", res - tosub);
}

int main(){
    int C; cin>>C; while(C--){ solve();} return 0;
}