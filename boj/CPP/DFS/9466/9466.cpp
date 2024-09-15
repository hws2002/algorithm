#include <iostream>
#include <vector>
#include <stack>
#define MAX_N 100'000
#define endl '\n'
using namespace std;

int N;
vector<int> adj;
vector<int> discovered(MAX_N, -1);
vector<bool> finished(MAX_N, false);
int cnt = 0;
int res = 0;
stack<int> st;

void dfs(int here){
    st.push(here);
    discovered[here] = cnt++;
    if( discovered[adj[here]] == -1){
        //tree 간선
        dfs(adj[here]);
    } else if ( adj[here] == here){
        // 본인을 항햔 간선
        res--;
    } else { // 순방향 간선은 나올 수 없으므로, 역방향간선과 교차 간선만 고려한다
        if(!finished[adj[here]]){
            // 역방향 간선 -> 사이클!
            while( !st.empty() && st.top() != adj[here]){
                res--;
                st.pop();
            }
            if(st.top() == adj[here]) res--;
            
        } else{
            // 교차 간선
            // do nothing
        }
    }
    finished[here] = true;
    return ;
}

void solve(){
    cin>>N;
    int want;
    cnt = 0;
    res = N;
    for(int i = 0 ; i < N; i++){
        cin>>want;
        adj.push_back(want-1);
        discovered[i] = -1;
        finished[i] = false;
    }
    
    //dfsAll
    for(int i = 0; i < N; i++){
        if(discovered[i] == -1) {
            dfs(i);
            while(!st.empty()){
                st.pop();
            }
        }
    }
    
    cout<<res<<endl;
    
    //reset
    adj.clear();
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
}