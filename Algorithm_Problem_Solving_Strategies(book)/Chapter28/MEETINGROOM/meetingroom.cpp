#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

#define MAX_N 100
#define MAX_V (MAX_N*4)
#define all(v) v.begin(), v.end()

#define endl '\n'
using namespace std;
int n,V;

vector<int> adj[MAX_V];
vector<int> discovered;
vector<int> sccId;
stack<int> st;

int sCnt = 0; int vCnt = 0;

int scc(int h){
    discovered[h] = vCnt++;
    int minDis = discovered[h];
    st.push(h);
    for(const auto & nxt : adj[h]){
        if( discovered[nxt] == -1){
            minDis = min( minDis, scc(nxt));
        } else if( sccId[nxt] == -1){
            minDis = min( minDis, discovered[nxt]);
        }
    }
    
    if( minDis == discovered[h]){
        while(true){
            int t = st.top(); st.pop();
            sccId[t] = sCnt;
            if( t == h) break;
        }
        sCnt++;
    }
    
    return minDis;
}

vector<int> sccTarjan(){
    sccId = vector<int> (V, -1);
    discovered = vector<int> (V,-1);
    sCnt = 0 ; vCnt = 0;
    for(int i = 0; i < V; i++){
        if( discovered[i] == -1) scc(i);
    }
    return sccId;
}

vector<pair<int,int>> meetings;

void addInterWoven(int i, int j){
    int mif = meetings[i].first; int mis = meetings[i].second;
    int mjf = meetings[j].first; int mjs = meetings[j].second;
    
    if( (mjf < mif && mif < mjs) ||
        (mif <= mjf && mjs <= mis) ||
        (mjf < mis && mis < mjs)) {
			adj[i<<1].push_back(j<<1|1);
			adj[j<<1].push_back(i<<1|1);
		}
}

void checkInterWoven(int m1, int m2){
    int v11 = m1<<1; int v12 = m1<<1|1;
    int v21 = m2<<1; int v22 = m2<<1|1;
    
    addInterWoven( v11, v21);
    addInterWoven( v11, v22);
    addInterWoven( v12, v21);
    addInterWoven( v12, v22);
}

// V : 함의 그래프의 노드의 개수
vector<int> solve2SAT(){
    vector<int> ret(V>>1, -1);
    
    for(int variable = 0; variable < V>>1; variable++)
        if( sccId[variable<<1] == sccId[variable<<1|1]) return vector<int> ();
    
    vector< pair<int, int > > order;
    for(int vidx = 0 ; vidx < V; vidx++){
        order.push_back({-sccId[vidx], vidx});
    }
    
    sort(all(order));
    
    for(int i = 0; i < V; i++){
        int vidx = order[i].second;
        int variable = vidx>>1; bool isTrue = (vidx %2 == 0);
        if( ret[variable] == -1) ret[variable] = !isTrue;
    }
    return ret;
}

void solve(){
    cin>>n;
    V = 4*n;
    //reset
    meetings.clear();
    for(int i = 0; i < V; i++) adj[i].clear();
    int a,b,c,d;
    for(int i = 0; i <n; i++){
        cin>>a>>b>>c>>d;
        meetings.push_back({a,b});
        meetings.push_back({c,d});
        int m1 = i<<1; int m2 = i<<1|1;
        
        //두 회의 중 하나는 무조건 선택 해야 한다
        adj[m1<<1|1].push_back(m2<<1);
        adj[m2<<1|1].push_back(m1<<1);
    }
    
    for(int i = 0; i < n ; i++){
        for(int j = i + 1; j < n; j++){
            checkInterWoven(i,j);
        }
    }
    
    //함의 그래프 만들기
    sccTarjan();
    
    //2SAT
    auto ret = solve2SAT();
    if( ret.size()){
        cout<<"POSSIBLE"<<endl;
        for(int i = 0; i < V/2; i+=2){
            if( ret[i] ){
                cout<<meetings[i].first<<" "<<meetings[i].second<<endl;
            } else {
                cout<<meetings[i+1].first<<" "<<meetings[i+1].second<<endl;
            }
		}    
    } else cout<<"IMPOSSIBLE"<<endl;
}

int main(){
    int c; cin>>c; while(c--) solve(); return 0;
}