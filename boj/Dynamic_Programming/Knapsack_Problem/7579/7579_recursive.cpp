// 재귀

#include <iostream>

#define MAX_N 101
using namespace std;

int N,M;

int cost[MAX_N] = {0};
int memory[MAX_N] = {0};
int cache[MAX_N][10001] = {0};

int dp(int idx, int capacity){
    //base
    if(idx > N || capacity < 0) return 0;
    int& ret = cache[idx][capacity];
    if(ret) return ret;
    if( capacity < cost[idx] ) return ret = dp(idx+1,capacity);
    return ret = max( dp(idx+1, capacity - cost[idx]) + memory[idx], dp(idx+1, capacity));
}

int main(){
    cin>>N>>M;
    for(int i = 1 ; i <= N; i++){
        cin>>memory[i];
    }
    
    for(int i = 1; i <= N; i++){
        cin>>cost[i];
    }
    
    // dp
    // dp(i, capacity) : i번 물건부터 N번 물건까지 고려했을때, capacity로 얻을 수 있는 최대 가치
    for(int capacity = 0; capacity <= 10000; capacity++){
        dp(1,capacity);
    }
    
    for(int capacity = 0 ; capacity <= 10000; capacity++){
        if( cache[1][capacity] >= M) {
            cout<<capacity<<endl;
            break;
        }
    }
    return 0;
}