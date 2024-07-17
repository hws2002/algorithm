#include <iostream>
#include <limits.h>

#define MAX_N 8

using namespace std;


double dist[MAX_N][MAX_N] = {0};
double cache[MAX_N][(1<<MAX_N)] = {0};

int N;

double dp(int last, int visit){
	//base
	if(visit == (1<<N)-1){
		return 0;
	}
	
	double & ret = cache[last][visit];
	if(ret > -1) return ret;
	
	ret = INT_MAX;
	
	for(int next = 0 ; next < N; next++){
		if( !(visit & (1<<next)) ){
			ret = min(ret, dp( next, visit | (1<<next)) +  dist[last][next] );
		}
	}
	
	return ret;
}

void solve(){
	cin>>N;
	
	//pre


	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			cin>>dist[i][j];
	
	//solve
	double ret = INT_MAX;
	for(int start= 0 ; start < N; start++){
		for(int i = 0; i < N; i++)
			fill(cache[i], cache[i] + (1<<N), -1);
		ret = min(ret,dp(start,(1<<start)));
	}
	printf("%.10f \n",ret);
}

int main(){
	int C;
	cin>>C;
	while(C--){
		solve();
	}
	
	return 0;
}