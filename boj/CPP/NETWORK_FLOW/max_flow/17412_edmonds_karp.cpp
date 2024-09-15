// bfs기반 포드 풀커슨 최대유량 알고리즘 - 에드먼드 카프
// array
#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 400
#define MAX_P 10'000
#define INF 10'000'000
using namespace std;

int N,P;
const int source = 0;
const int sink = 1;

// int adj[MAX_N][MAX_N] = {0};
vector<int> adj[MAX_N];
int capacity[MAX_N][MAX_N] = {0};
int flow[MAX_N][MAX_N] = {0};

int res = 0;
void maxflow(){
    int here;
    int amt;
    while(true){ // 증가 경로가 존재하는 한 끝나지 않는다 (최소 컷 최대 유량 정리)
        vector<int> parent(N,-1);
        queue<int> q;
        here = source;
        q.push(here);
        parent[here] = here;
        // 증가 경로를 찾는다
        while(!q.empty() && parent[sink] == -1){
            here = q.front();
            q.pop();
            for(int next = 0; next < N; next++){ //역방향 간선도 확인하기 위해 모든 노드를 다 검사하거나, 아니면 따로 radj를 만들어서 검사하자 
                if(parent[next] == -1 && capacity[here][next] - flow[here][next]){ // 잔여 용량이 있다면
                    q.push(next);
                    parent[next] = here; 
                }
            }
        }
        
        // 증가 경로를 찾지 못했다면 끝낸다
        if( parent[sink] < 0 ) break;
        
        // 증가 경로가 존재한다면 증가경로를 따라 추가 가능한 최대 유량을 흘려보낸다.
        // 추가 가능한 최대 유량을 찾는다 (amt)
        amt = INF;
        here = sink;
        while( here != source ){
            amt = min(amt, capacity[ parent[here] ][here] - flow[ parent[here] ][here] );
            here = parent[here];
        }
        
        here = sink;
        while( here != source ){
            flow[ parent[here] ][here] += amt;
            flow[ here ][ parent[here] ] -= amt;
            here = parent[here];
        }
        res += amt;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>P;
    int u,v;
    
    for(int i = 0 ; i < P; i++){
        cin>>u>>v;
        u--;v--;
        if(capacity[u][v] == 0) adj[u].push_back(v);
        capacity[u][v] += 1;
    }
    
    //edmond-karp
    maxflow();
    
    cout<<res<<endl;
    return 0;
}