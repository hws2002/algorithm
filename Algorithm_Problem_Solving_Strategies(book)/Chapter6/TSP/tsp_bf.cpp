#include <iostream>
#include <vector>
#include <limits>

#define MAX_N 8
using namespace std;

double cost[MAX_N][MAX_N] = {0};
int N;

double shortestPath(vector<int> & path, double currentLength, int visited){

    if(path.size() >= N){
        return currentLength;
    }
	
    int here = path.back();
	
    double ret = numeric_limits<double>::max();
    for(int next = 0 ; next < N; next++){
        if( visited & (1<<next)) continue;
        path.push_back(next);
        ret = min(ret, 
            shortestPath(path, currentLength + cost[here][next], visited + (1<<next) ));
        path.pop_back();
    }
    
    return ret;
}

void solve(){
    cin>>N;
    
    for(int i = 0 ; i < N; i++){
        for(int j = 0 ; j < N; j++){
            cin>>cost[i][j];
        }
    }
    
    //tsp
    vector<int> path;
	double ret = numeric_limits<double>::max();
	for(int here = 0; here < N; here++){
		path.push_back(here);
		ret = min(ret,
				 shortestPath(path, 0, (1<<here)));
		path.pop_back();
	}
    printf("%.10f \n", ret);
}

int main(){
    int C;
    cin>>C;
    while(C--){
        solve();
    }
    return 0;
}