#include <iostream>
#include <vector>

#define MAX_N 30
#define MAX_MARBLE_W 15'000
// #define DEBUG_PRE
// #define DEBUG_DP
using namespace std;
typedef pair<int,int> pii;

int N;
int Weights[MAX_N] = {0};
int preSum[MAX_N+1] = {0};

// bool solved[MAX_N][MAX_MARBLE_W] = {0};
int cache[MAX_N][ (MAX_MARBLE_W<<1) + 1] = {0};

bool dp(const int idx, const int weight){
#ifdef DEBUG_DP
printf("dp(%d, %d) \n", idx, weight);
#endif
    //base
    if(weight == 0) return true;
    if(idx>=N) return false;
    if(abs(weight) > preSum[N] - preSum[idx]) return false;
    int & ret = cache[idx][weight + MAX_MARBLE_W];
    // if(solved[idx][weight]) return ret;
    // solved[idx][weight] = true;
	if(ret > -1) return ret;
    if(weight == Weights[idx]) return ret = 1;
    // if(weight > Weights[idx]) 
		return ret = (dp(idx+1, weight - Weights[idx]) || dp(idx+1, weight) ||dp(idx + 1,weight + Weights[idx]));
    // return ret = dp(idx+1, weight + Weights[idx]) || dp(idx+1, weight);
}

int main(){
	//pre

    cin>>N;
    int w,n;
    for(int i = 0; i < N; i++){    
        cin>>Weights[i];
        preSum[i+1] = Weights[i] + preSum[i];
    }
	
#ifdef DEBUG_PRE
for(int i = 0; i <= N; i++){
    cout<<preSum[i]<< " ";
}
cout<<endl;
#endif
	for(int i = 0; i < N; i++){
		fill(cache[i], cache[i] + (MAX_MARBLE_W<<1) + 1, -1);
	}
	
    int n_marbles;
    cin>>n_marbles;
    int w_marble;
    for(int i = 0; i < n_marbles; i++){
        cin>>w_marble;
        if ( dp(0,w_marble) ) cout<<"Y ";
        else cout<<"N ";
    }
    
    return 0;
}


