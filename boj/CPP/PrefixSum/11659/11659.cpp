#include <iostream>
#define endl '\n'

using namespace std;

int A[100001] = {0};
int SUMTILLI[100001] = {0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //input
    int N,M;
    cin>>N>>M;
    A[0] = 0;
    SUMTILLI[0] = A[0];
    for(int i = 1 ; i <= N; i++){
        cin>>A[i];
        SUMTILLI[i] = A[i] + SUMTILLI[i-1];
    }
    
    //solve
    int i, j;
    for(int k = 0 ; k < M; k++){
        cin>>i>>j;
        cout<<SUMTILLI[j] - SUMTILLI[i-1]<<endl;
    }
    
    return 0;
}