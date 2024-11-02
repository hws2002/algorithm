#include <iostream>
#include <vector>
#include <stack>

#define MAX_N 1'000'000

using namespace std;

stack<pair<int,int>> s;
int F[MAX_N+1] = {0};
int A[MAX_N] = {0};

int N;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N;
    
    //make F table
    for(int i = 0; i < N; i++){
        cin>>A[i];
        F[A[i]] += 1;
    }
    
    //scan
    
    for(int i = 0; i < N; i++){
        while( !s.empty() && F[s.top().first] < F[A[i]]){
            A[s.top().second] = A[i];
            s.pop();
        }
        s.push({A[i],i});
    }
    
    while(!s.empty()){
        A[s.top().second] = -1;
        s.pop();
    }
    
    for(int i = 0; i < N; i++){
        cout<<A[i]<<" ";
    }
    
    return 0;
}