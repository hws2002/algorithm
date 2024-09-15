// scc
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

#define MAX_N 100'000
#define MAX_M 100'000

#define FOR(i,s,e) for(int i = s; i < e; i++)
#define endl '\n'
using namespace std;

int N,M;
int res;

vector<int> discovered;
vector<int> sccId; // vertex idx -> scc idx
vector<int> adj[MAX_N];
vector<bool> sccParent; // sccParent[i] : i번째 scc가 부모가 있는가? (indegree 가 0인가를 알아보기 위해)

stack<int> st;
int sccCnt = 1; int vCnt = 1;

int tarjan(const int here, const int parent){
    discovered[here] = vCnt++;
    int lowest_node = discovered[here];
    st.push(here);
    for(auto next : adj[here]){
        if(!discovered[next]){ //트리 간선!
            lowest_node = min(lowest_node, tarjan(next,here));
        } else { //순방향 간선은 신경쓸 필요 없고 (어차피 discovered[next]가 discovered[here] 보다 무조건 크기 때문) 
            if( !sccId[next] ){ //(역방향 간선)이거나, (교차간선이고 next가 scc로 묶이지 않은 상태)만 고려하면 된다.
                lowest_node = min(lowest_node, discovered[next]);
            } else { // 만약 next가 scc에 묶여 있다면,
                sccParent[sccId[next]] = true; // 해당 scc또한 꼭 쓰러뜨릴 필요가 없음
            }
        }
    }
    
    if(lowest_node == discovered[here]){ // scc 발견!
        while(true){
            int t = st.top();
            sccId[t] = sccCnt;
            st.pop();
            if( t == here) break;
        }
        sccCnt++;
        
        if(parent != -1){ //해당 scc를 자식으로 가지는 노드가 있다면, 이 scc는 indegree 가 0이 아님( 꼭 쓰러뜨릴 필요가 없음)
            sccParent[sccId[here]] = true;
        }
    }
    
    return lowest_node;
}

void tarjanAll(){
    for(int src = 0; src < N; src++){
        if(!discovered[src])
            tarjan(src,-1);
    }
}

void solve(){
    cin>>N>>M;
    discovered.resize(N,0);
    sccId.resize(N,0);
    sccParent.resize(N,false);
    
    sccCnt = 1; vCnt = 1;
    int x,y;
    res = 0;
    FOR(i,0,M){
        cin>>x>>y;
        adj[x-1].push_back(y-1);
    }
    
    //tarjanAll
    tarjanAll();
    
    //output
    res = 0;
    
    for(int sccid = 1; sccid <= sccCnt-1; sccid++){
        if(!sccParent[sccid]) res++;
    }
    
    cout<<res<<endl;
    
    //reset
    for(int i = 0; i <N; i++){
        adj[i].clear();
    }
    discovered.clear();
    sccId.clear();
    sccParent.clear();
    while(!st.empty()) st.pop();
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