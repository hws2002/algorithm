#include <iostream>
#include <vector>

#define endl '\n'
#define MAX_N 5'00
using namespace std;

int n,m;
vector<int> ranking;
bool adj[MAX_N][MAX_N] = {false};
int cnt = 0;
vector<int> res;

bool dfs(int here, vector<int> & discovered, vector<bool> & finished){
    discovered[here] = cnt++;
    for(int next = 0; next < n; next++){
        if(!adj[here][next]) continue;
        if(!discovered[next]){ // 트리 간선
            if(!dfs(next, discovered, finished)) return false; // 사이클을 발견한 경우 일찍 종료시킨다
        } else {
            if(!finished[next]){//사이클 발견
                // res.clear();
                return false; // 사이클을 발견한 경우 일찍 종료시킨다.
            } // 나머지 경우는 스킵한다
        }
    }

    finished[here] = true;
    res.push_back(here);
    return true;
}

bool dag(const int src){
    
    //init
    vector<int> discovered(n,0);
    vector<bool> finished(n,false);
    cnt = 1;
    return dfs(src,discovered, finished);
}

void solve(){
    cin>>n;

    //pre
    ranking.resize(n);
    for(int i = 0; i < n; i++){
        std::fill(adj[i], adj[i] + n, false);
    }

    for(int i = 0; i < n; i++){
        cin>>ranking[i];
        ranking[i]--;
    }
    
    for(int i = 0; i < n ; i++){
        for(int j = i+1; j < n; j++){
            adj[ranking[i]][ranking[j]] = true;
        }
    }

    cin>>m;
    int a,b;
    for(int i = 0; i < m; i++){
        cin>>a>>b;
        a--;b--;
        if(adj[a][b]) {adj[a][b] = false; adj[b][a] = true;}
        else if (adj[b][a]) {adj[b][a] = false; adj[a][b] = true;}
    }
    
    // indegree가 0 인 vertex가 두개 이상이라면, 
    int src = -1;
    int num_indegree_0 = 0;
    for(int i = 0; i < n; i++){
        bool indegree = false;
        for(int j = 0; j < n; j++){
            if(adj[j][i]) {
                indegree = true;
                break;
            }
        }

        if(!indegree) {
            num_indegree_0++;
            if(src != -1 ) break;
            src = i;
        }
    }

    if(num_indegree_0 > 1){ // 시작점이 여러개라면, 확실한 순위를 찾을 수 없다.
        cout<<"?"<<endl;
        return ;
    } else if( num_indegree_0 == 0){ // 시작점을 못찾는다면 데이터에 일관성이 없다.
        cout<<"IMPOSSIBLE"<<endl;
        return ;
    }

    //output
    // dag(src);
    if(!dag(src)) cout<<"IMPOSSIBLE"; // 사이클이 발견된 경우
    else // 확실한 순위를 찾을 수 있는 경우
        for(int i = res.size()-1; i >= 0; i--)
            cout<<res[i]+1<<" ";
    cout<<endl;
    res.clear();
} 

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}