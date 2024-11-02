#include <iostream>
#include <vector>

using namespace std;

int N,M;
vector<int> Vector_N;
vector<int> Vector_M;

int main(){
    //input
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 
    cout.tie(NULL);
    cin>>N>>M;
    
    int temp;
    for(int i = 0 ; i < N; i++){
        cin>>temp; Vector_N.push_back(temp);
    }
    for(int i = 0 ; i < M; i++){
        cin>>temp; Vector_M.push_back(temp);
    }
    
    //solve
    int index_n = 0; int index_m = 0;
    
    while(index_n < N && index_m < M){
        if(Vector_N[index_n] >= Vector_M[index_m]){
            cout<<Vector_M[index_m++]<<" ";
        } else if (Vector_N[index_n] < Vector_M[index_m]){
            cout<<Vector_N[index_n++]<<" ";
        } 
    }
    
    if(index_n >= N){
        while(index_m < M) cout<<Vector_M[index_m++]<<" ";
    } else {
        while(index_n < N) cout<<Vector_N[index_n++]<<" ";
    }
    
    return 0;
}