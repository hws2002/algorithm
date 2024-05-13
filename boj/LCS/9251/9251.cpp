#include <iostream>
#include <cstring>
#define endl '\n'
using namespace std;
int dp[1000][1000] = {0};
string A,B;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //input
    cin>>A>>B;
    
    //solve
    int value = 0;
    for(int i = 0; i < B.size(); i++){
        if(A[0] == B[i]) value = 1;
        dp[0][i] = value;
    }
    value = 0;
    for(int i = 0; i < A.size(); i++){
        if(A[i] == B[0]) value = 1;
        dp[i][0] = value;
    }
    
    for(int i = 1; i < A.length(); i++){
        for(int j = 1; j < B.length(); j++){
            if(A[i] == B[j]){
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    //output
    cout<<dp[A.length()-1][B.length()-1]<<endl;
    return 0;
}
