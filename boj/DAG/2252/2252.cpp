// 역방향 간선이 없는 dag의 위상정렬
#include <iostream>
#include <vector>

#define MAX_N 32'000
#define MAX_M 100'000
using namespace std;

int N,M;
vector<int> adj[MAX_N];
vector<int> discovered(MAX_N, -1);
vector<int> res;
int cnt = 0;

void dag(int here){
    discovered[here] = cnt++;
    
    for(int i = 0 ; i < adj[here].size(); i++){
        int there = adj[here][i];
        if(discovered[there] == -1){ //트리 간선
            dag(there);
        } else if(discovered[there] > discovered[here] ) { // 순방향 간선
            //do nothing
        } else { // 교차 간선
            //do nothing
        }
    }
    
    res.push_back(here);
    return ;
}

int main(){
    cin>>N>>M;

    int a,b;    
    for(int i = 0 ; i < M; i++){
        cin>>a>>b;
        adj[a-1].push_back(b-1);
    }
    
    //dag
    
    for(int i = 0 ; i < N; i++){
        if(discovered[i] == -1) dag(i);
    }
    
    //reconstruct
    for(int i = res.size()-1; i>=0; i--){
        cout<<res[i]+1<<" ";
    }
    return 0;
}    