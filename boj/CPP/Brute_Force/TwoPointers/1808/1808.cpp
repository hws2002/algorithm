#include <iostream>

#define MAX_N 100'000
using namespace std;

int N,S;
int A[MAX_N] = {0};

int res = MAX_N+1;

int main(){
    cin>>N>>S;
    
    for(int i = 0; i < N; i++){
        cin>>A[i];
    }
    
    //solve
    int leftP = 0; int rightP = 0;
    int sum = 0;
    for(int i = 0 ; i < N; i++){
        if( A[i] + sum < S){
            sum += A[rightP++];
        } else if ( A[i] + sum >= S){
            sum += A[rightP++];
            while( sum - A[leftP] >= S) {
                sum -= A[leftP++];
            }
            res = min(res, rightP - leftP);
        }
    }
    
    //output
    if(res > MAX_N) cout<<0<<endl;
    else cout<<res<<endl;
    return 0;
}

