#include <iostream>

// #define DEBUG_INPUT
using namespace std;

int N; //1 <= N <= 1000
int A[1001] = {0};
int dp[1001] = {0};

int main(){
    cin>>N;
    int j;
    cin>>A[0]; dp[0] = 1;
    int res = dp[0];
    for(int i = 1 ; i < N; i++){
        cin>>A[i];
        j = i-1;
        while( j>=0 ) {
            while( j >= 0  && A[j] >= A[i]){
                j--;
            }
            dp[i] = j < 0 ? max(dp[i],1) : max(dp[i], dp[j]+1);
            j--;
        }
        res = max(res, dp[i]);
    }
#ifdef DEBUG_INPUT
for(int i = 0; i < N; i++){
    cout<<dp[i]<<" ";
}
cout<<endl;
#endif
    cout<<res<<endl;
    return 0;    
}