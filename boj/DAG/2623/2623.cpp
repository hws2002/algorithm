// 12:22 - 12:47
// DAG
/*
우선 위상정렬 DAG를 생각해 볼 수 있다.  
그래프에서 사이클이 존재한다면, 순서를 정하는 것이 불가능하므로 0을 출력
만약 사이클이 존재하지 않는다면, DFS통한 위상 정렬 ㄱㄱ
*/


#include <iostream>
#include <vector>

#define MAX_N 1'000
#define MAX_M 100
using namespace std;

int N,M;

vector<int> adj [MAX_N];
vector<int> discovered(MAX_N, -1);
vector<bool> finished(MAX_N, false);;
vector<int> res;
int cnt = 0;

bool dfs(int here){
    discovered[here] = cnt++;
    for(int i = 0 ; i < adj[here].size(); i++){
        int there = adj[here][i];
        // 트리간선인지, 순방향 간선인지, 역방향 간선인지, 교차간선인지 파악한다
        if(discovered[there] == -1){ //트리 간선
            dfs(there);
        } else if (discovered[there] > discovered[here]){ //순방향 간선
            //do nothing
        } else { //역방향 혹은 교차
            if(finished[there]){ // 교차
                //do nothing
            } else { //역방향 -> 사이클이 존재하므로 바로 return true
                return true;
            }
        }
    } 
    finished[here] = true;
    res.push_back(here);
    return false;
}

//return true if cycle exists
bool dfsAll(){
    for(int i = 0 ; i < N; i++) if(discovered[i] == -1) if(dfs(i)) return true;
    return false;
}

int main(){
    cin>>N>>M;
    int num,prev_u,u;
    for(int i = 0 ; i < M; i++){
        cin>>num>>u;
        num--;
        while(num--){
            prev_u = u;
            cin>>u;
            adj[prev_u-1].push_back(u-1);
        }
    }
    
    //dfs
    if(dfsAll())
        cout<<0<<endl;    
    else {
        for(int i = res.size()-1; i>=0 ;i--){
            cout<<res[i]+1<<endl;
        }
    }
    return 0;
}