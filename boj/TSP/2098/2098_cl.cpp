// TSP
// dp, memoization, dfs

#include <iostream>
#include <vector>
#include <limits.h>
#define MAX (int)1e8

int N;
int W[16][16] = {0};
int cache[16][1<<16] = {0};
int start = 0;

using namespace std;

int shortestPathDP(const int last, int visit, int cl){
    if( visit == (1<<N)-1) {
        if( W[last][start] == 0) return MAX;
        else return cl + W[last][start];
    }
    int & ret = cache[last][visit];
    if(ret) return ret;
    ret = MAX;
    for(int next = 0; next < N; next++){
        if(W[last][next] == 0) continue;
        if( (visit & (1<<next)) == 0){
            ret = min(ret, shortestPathDP(next, visit + (1<<next), cl + W[last][next]) );
        }
    }
    return ret;
}

int main(){
    //input
    cin>>N;
    for(int i = 0 ; i < N; i++){
        for(int j = 0 ; j < N; j++){
            cin>>W[i][j];
        }
    }
    
    //solve - dp
    //starts with City num `start`
    cout<<shortestPathDP(start, 1<<start, 0)<<endl;
    return 0;
}