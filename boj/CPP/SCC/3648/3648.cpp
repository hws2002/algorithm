#include <iostream>
#include <vector>
#include <stack>

#define MAX_N 1'000
#define FOR(i,s,e) for(int i = s; i < e; i++)
#define endl '\n'
// #define DEBUG_TJ
using namespace std;

int n,m;
vector<int> adj[MAX_N<<1];
vector<int> sadj[MAX_N<<1];
vector<int> rsadj[MAX_N<<1];

vector<int> discovered(MAX_N<<1, -1);
vector<int> v2scc(MAX_N<<1,-1); // v2scc[i] : i번째 vertex가 속해있는 scc
vector<int> scc2v[MAX_N<<1]; // scc2v[i] : i번째 scc에 속해있는 vertex들
vector<int> p_scc[MAX_N<<1]; // p_scc[i] : i번째 scc의 parent vertex들

vector<int> values(MAX_N,-1);
vector<int> svalues(MAX_N<<1,-1);

stack<int> st;
int sCnt = 0; int vCnt = 0;

int tarjan(const int here, const int parent){
    discovered[here] = vCnt++;
    int lowest_node = discovered[here];
    st.push(here);
    for(auto next : adj[here]){
        if( discovered[next] == -1){ // 트리간선
            lowest_node = min(lowest_node, tarjan(next, here));
        } else {
            if(v2scc[next] == -1){ // 교차간선이고 아직 scc에 묶이지 않은 경우
                // 혹은 역방향 간선일 경우 lowest_node를 갱신해준다
                lowest_node = min(lowest_node, discovered[next]);
                //순방향 간선인 경우 갱신이 일어나지 않지만 위 연산을 해주어도 상관이 없다.
            } else { //이미 scc에 묶인 경우, 해당 scc의 parent scc는 v2scc[here]이 되어야 한다.    
                p_scc[v2scc[next]].push_back(here);
            }
        }
    }
    
    if(lowest_node == discovered[here]){
        while(true){
            int t = st.top();
            v2scc[t] = sCnt;
            scc2v[sCnt].push_back(t);
            st.pop();
            if( t == here) break;
        }
        if(parent != -1){
            p_scc[sCnt].push_back(parent);
        }
        sCnt++;
    }
    
    return lowest_node;
}

void tarjanAll(){
    sCnt = 0; vCnt = 0;
    // scc 분리
    FOR(i, 0, n<<1){
        if(discovered[i] == -1) tarjan(i,-1);
    }
#ifdef DEBUG_TJ
for(int i = 0; i < sCnt; i++){
    printf("scc[%d] : ", i);
    for(auto v : scc2v[i]){
        cout<<v<<" ";
    }
    cout<<endl;
}
#endif
    
    // scc간에 adj 만들기
    for(int sccid = 0; sccid < sCnt; sccid++){
        vector<bool> alreadyadded(sCnt,false);
        for(auto pv : p_scc[sccid]){
            if( !alreadyadded[v2scc[pv]]){
                sadj[v2scc[pv]].push_back(sccid);
                rsadj[sccid].push_back(v2scc[pv]); // rsadj[0] = {1,2,3} 이라면 1->0, 2->0, 3->0 인 간선들이 존재하는셈
                alreadyadded[v2scc[pv]] = true;
            }
        }
    }    
#ifdef DEBUG_TJ
for(int sccid = 0; sccid < sCnt; sccid++){
    printf("sadj[%d] : ", sccid);
    for(auto cs : sadj[sccid]){
        cout<<cs<<" ";
    }
    cout<<endl;
}
#endif
}


// sccId번 scc에 `assignTrue` 값을 주입하는 것이 conflict를 만들지 않는다면 true를, conflict를 만든다면 false를 반환한다.
bool assignValue(const int sccId, const bool assignTrue){
    int valueIdx;
    bool isvnot;
    svalues[sccId] = assignTrue;
    if(assignTrue){ // scc2v[sccId] 에 속한 변수들이 모두 true가 되도록 한다.
        for(auto vIdx : scc2v[sccId]){
            valueIdx = vIdx>>1;
            isvnot = ( (vIdx % 2) == 1);
            if(isvnot) {
                //valueIdx번 변수는 false가 되어야 하는데 이미 true가 주입되었다면 conflict
                if( values[valueIdx] == 1) return false;
                values[valueIdx] = 0;
            } else {
                //valueIdx번 변수는 true가 되어야 하는데 이미 false가 주입되었다면 conflict
                if( values[valueIdx] == 0) return false;
                values[valueIdx] = 1;
            }
        }
        
        // sccId번 scc의 child scc들은 모두 true가 되어야 하고
        for(auto cscc : sadj[sccId]){
            if( svalues[cscc] == 0) return false;
            if( svalues[cscc] == 1) continue;
            if( !assignValue(cscc, 1)) return false;
        }
        
        // 현 scc에 속해있는 친구들
        for(auto vIdx : scc2v[sccId]){
            bool isvnot = (vIdx % 2 == 1);
            if(isvnot){
                if( svalues[v2scc[vIdx-1]] == 1) return false;
                if( svalues[v2scc[vIdx-1]] != -1) continue;
                if( !assignValue(v2scc[vIdx-1], 0)) return false;
            } else {
                if( svalues[v2scc[vIdx+1]] == 1) return false;
                if( svalues[v2scc[vIdx+1]] != -1) continue;
                if( !assignValue(v2scc[vIdx+1], 0)) return false;
            }
        }
        
    } else {
        for(auto vIdx : scc2v[sccId]){
            valueIdx = vIdx>>1;
            bool isvnot =  (vIdx % 2 == 1);
            if (isvnot){
                if( values[valueIdx] == 0) return false;
                values[valueIdx] = 1;
            } else {
                if( values[valueIdx] == 1) return false;
                values[valueIdx] = 0;
            }    
        }
        
        for(auto cscc : rsadj[sccId]){
            if( svalues[cscc] == 1) return false;
            if( svalues[cscc] == 0) continue;
            if( !assignValue(cscc,0)) return false;
        }
        
        for(auto vIdx : scc2v[sccId]){
            isvnot = (vIdx % 2 == 1);
            if(isvnot){
                if( svalues[v2scc[vIdx-1]] == 0) return false;
                if( svalues[v2scc[vIdx-1]] != -1) continue;
                if( !assignValue(v2scc[vIdx-1], 1)) return false;
            } else {
                if( svalues[v2scc[vIdx+1]] == 0) return false;
                if( svalues[v2scc[vIdx+1]] != -1) continue;
                if( !assignValue(v2scc[vIdx+1], 1)) return false;
            }
        }
    }
    return true;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int a,b;
    bool isanot, isbnot;
    while(cin>>n>>m){
        // create edges
        FOR(i,0,m){
            cin>>a>>b;
            isanot = a < 0 ? true : false;
            isbnot = b < 0 ? true : false;
            a = abs(a); b = abs(b);
            a--;b--;
            if(!isanot && !isbnot){ // a || b
                adj[(b<<1) + 1].push_back((a<<1));
                adj[(a<<1) + 1].push_back((b<<1));
            } else if ( !isanot && isbnot){ // a || ~b
                adj[(b<<1)].push_back((a<<1));
                adj[(a<<1) + 1].push_back((b<<1) + 1);
            } else if ( isanot && !isbnot){ // ~a || b
                adj[(a<<1)].push_back((b<<1));
                adj[(b<<1) + 1].push_back((a<<1) + 1);
            } else { // ~a || ~b
                adj[(a<<1)].push_back((b<<1) + 1);
                adj[(b<<1)].push_back((a<<1) + 1);
            }
        }
        
        // condensation
        tarjanAll();

        // assign values
        // 상근이와 상관없이 애초에 불가능하다면 no를 출력한다
        bool dubious = false;
        for(int i = 0; i < n<<1; i+=2){
            if( v2scc[i] == v2scc[i+1]) {
                cout<<"no"<<endl;
                dubious = true;
                break;
            }
        }
        
        if(!dubious){
            if(!assignValue(v2scc[0], true)){
                cout<<"no"<<endl;
            } else {
                cout<<"yes"<<endl;
            }
        }
        
        //reset
        for(int i = 0 ; i < n<<1; i++){
            adj[i].clear();
            sadj[i].clear();
            rsadj[i].clear();
            scc2v[i].clear();
            p_scc[i].clear();
        }
    
        discovered.clear(); discovered.resize(MAX_N<<1, -1);
        v2scc.clear(); v2scc.resize(MAX_N<<1, -1);
        values.clear(); values.resize(MAX_N, -1);
        svalues.clear(); svalues.resize(MAX_N<<1, -1);
    }
    return 0;
}