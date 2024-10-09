// top-down
#include <iostream>
#include <vector>

#define MAX_N 55
#define MAX_D 101
using namespace std;


vector<double> outdegree(MAX_N);
double W[MAX_N][MAX_N] = {0};
double cache[MAX_N][MAX_D] = {-1};

int n,p;

double search3(int here, int days){
	if (days <= 0) return here == p ? 1.0 : 0.0;
	double & ret = cache[here][days];
	if(ret > -1) return ret;
	
	ret = 0;
	for(int prev = 0; prev < n; prev++){
		if(W[prev][here])
			ret += search3(prev,days-1) * W[prev][here];
	}
	return ret;
}

void solve(){
	int d,t,q;
	cin>>n>>d>>p;
	for(int i = 0; i < n; i++){
		outdegree[i] = 0;
		for(int j = 0; j < n; j++){
			cin>>W[i][j];
			if(W[i][j]) outdegree[i]++;
		}
		for(int j = 0; j < n; j++){
			W[i][j] /= outdegree[i];
		}
	}
	
	//reset
	for(int i= 0 ; i < n; i++){
		fill(cache[i], cache[i] + d + 1, -1);
	}
	
	cin>>t;
	while(t--){
		cin>>q;
		printf("%.8lf ", search3(q,d));
	}
	printf("\n");
}

int main(){
	int C;
	cin>>C;
	while(C--){
		solve();
	}
	return 0;
}