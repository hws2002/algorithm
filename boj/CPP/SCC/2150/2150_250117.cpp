// tarjan
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

#define MAX_V 10'000
#define MAX_E 100'000

#define FOR(i,s,e) for(int i = s; i < e; i++)
#define endl '\n'
using namespace std;

vector<int> adj[MAX_V];

int V,E;

vector<int> discovered(MAX_V, -1);
vector<int> sccId;

vector< vector<int> > SCC;
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
		vector<int> v;
        while(true){
            int t = st.top(); st.pop();
            sccId[t] = sCnt;
            v.push_back(t);
            if( t == h) break;
        }
		SCC.push_back(v);
        sCnt++;
    }
    
    return minDis;
}

vector<int> sccTarjan(){
    sccId = vector<int> (V, -1);
    sCnt =0 ; vCnt = 0;
    for(int i = 0; i < V; i++){
        if( discovered[i] == -1) scc(i);
    }
    return sccId;
}


bool compare(const vector<int> & v1, const vector<int> & v2){
    return v1[0] < v2[0];
}

int main(){
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);
    cin>>V>>E;
    
    int a,b;
    FOR(i,0,E){
        cin>>a>>b;
        adj[a-1].push_back(b-1);
    }
    
    //scc
    sccTarjan();
    
    //output
    cout<<sCnt<<endl;
    
    //sort
    for(int sccid = 0; sccid < sCnt; sccid++){
        std::sort(SCC[sccid].begin(), SCC[sccid].end());
    }
	
    std::sort(SCC.begin(), SCC.end(), compare);
    
    for(auto v: SCC){
        for(auto e : v){
            cout<<e+1<<" ";
        }
        cout<<-1<<endl;
    }
    
    return 0;
}