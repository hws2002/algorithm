#include <iostream>

#define MAX_N 101
using namespace std;

int N,M;

int cost[MAX_N] = {0};
int memory[MAX_N] = {0};
int cache[MAX_N][10001] = {0};

int main(){
    cin>>N>>M;
    for(int i = 1 ; i <= N; i++){
        cin>>memory[i];
    }
    
    for(int i = 1; i <= N; i++){
        cin>>cost[i];
    }
    
    //dp
    for(int i = 1; i <= N; i++){
        
        for(int capacity = 0; capacity <= 10000 ; capacity++){
            if( cost[i] > capacity ){
                cache[i][capacity] = cache[i-1][capacity];
            } else {
                cache[i][capacity] = max( cache[i-1][capacity], memory[i] + cache[i-1][capacity - cost[i]]);
            }
        }
    }
    
    for(int capacity = 0 ; capacity <= 10000; capacity++){
        if( cache[N][capacity] >= M) {
            cout<<capacity<<endl;
            break;
        }
    }
    return 0;
}