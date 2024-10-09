#include <iostream>
#include <vector>

#define MAX_N 55
#define MAX_D 100

// #define DEBUG_W
// #define DEBUG_PROBA
using namespace std;

int n,d,p,t;

vector<double> P_X_d[2];
vector<int> outdegree(MAX_N);


// W[i][j] : i번째 마을에서 j번째 마을로 갈 확률
double W[MAX_N][MAX_N] = {0};

void solve(){
    cin>>n>>d>>p;
    
    // create weights
    for(int i = 0; i < n; i++){
		outdegree[i] = 0;
        for(int j = 0; j < n; j++){
            cin>>W[i][j];
            if( W[i][j] ) outdegree[i]++;
        }
        
        for(int j = 0; j < n; j++){
            W[i][j] /= outdegree[i];
        }
    }
#ifdef DEBUG_W
for(int i = 0 ; i < n; i++){
	for(int j = 0; j < n;j++){
		printf("%.3lf ", W[i][j]);	
	}
	cout<<endl;
}
cout<<endl;
#endif
	
    // calculate proba
	P_X_d[0].resize(n,0);
	P_X_d[1].resize(n,0);
	fill(P_X_d[0].begin(), P_X_d[0].begin() + n, 0);
    P_X_d[0][p] = 1;
    for(int iter = 0; iter < d; iter++){
        for(int i = 0; i < n; i++){
			P_X_d[(iter+1)%2][i] = 0;
            for(int j = 0 ; j < n; j++){
                P_X_d[(iter+1)%2][i] += P_X_d[iter%2][j] * W[j][i];
            }
        }
#ifdef DEBUG_PROBA
for(int i = 0; i < n; i++){
	printf("%.3lf ",P_X_d[(iter+1)%2][i]);
}	
cout<<endl;
#endif
    }
    
    //query
    cin>>t;
    int q;
    while(t--){
        cin>>q;
        printf("%.8lf ", P_X_d[d%2][q]);
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