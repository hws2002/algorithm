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


// vector<int> discovered(MAX_N<<1, -1);
int discovered[MAX_N<<1];
// vector<int> v2scc(MAX_N<<1,-1); // v2scc[i] : i번째 vertex가 속해있는 scc
int v2scc[MAX_N<<1];

vector<int> scc2v[MAX_N<<1]; // scc2v[i] : i번째 scc에 속해있는 vertex들

// vector<int> values(MAX_N,-1);
int values[MAX_N];

// vector<int> svalues(MAX_N<<1,-1);
int svalues[MAX_N<<1];

stack<int> st;
int sCnt = 0; int vCnt = 0;

int tarjan(const int here){
    discovered[here] = vCnt++;
    int lowest_node = discovered[here];
    st.push(here);
    for(auto next : adj[here]){
        if( discovered[next] == -1){ // 트리간선
            lowest_node = min(lowest_node, tarjan(next));
        } else {
            if(v2scc[next] == -1){ // 교차간선이고 아직 scc에 묶이지 않은 경우
                // 혹은 역방향 간선일 경우 lowest_node를 갱신해준다
                lowest_node = min(lowest_node, discovered[next]);
                //순방향 간선인 경우 갱신이 일어나지 않지만 위 연산을 해주어도 상관이 없다.
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
        sCnt++;
    }
    
    return lowest_node;
}

void tarjanAll(){
    // scc 분리
    FOR(i, 0, n<<1){
        if(discovered[i] == -1) tarjan(i);
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

}


// sccId번 scc에 `assignTrue` 값을 주입하는 것이 conflict를 만들지 않는다면 true를, conflict를 만든다면 false를 반환한다.
bool assignValue(const int sccId, const int assignTrue){
    int candidIdx;
    bool isvnot;
	bool candidshouldb;
    svalues[sccId] = assignTrue;
    if(assignTrue){ // scc2v[sccId] 에 속한 변수들이 모두 true가 되도록 한다.
        for(auto vIdx : scc2v[sccId]){
            candidIdx = vIdx>>1;
            isvnot = ( vIdx % 2 == 1);
			candidshouldb = isvnot ?  0 : 1;
			if(values[candidIdx] == !candidshouldb) return false;
			values[candidIdx] = candidshouldb;
        }

        
        // 현 scc에 속해있는 친구들
        
        for(auto vIdx : scc2v[sccId]){
            // isvnot = (vIdx % 2 == 1);
            int sidx = (vIdx % 2 == 1) ? v2scc[vIdx -1] : v2scc[vIdx + 1];
            if( svalues[sidx] == 1) return false;
            if( svalues[sidx] != -1) continue;
            if(!assignValue(sidx, 0)) return false;
        }
        
    } else {
        for(auto vIdx : scc2v[sccId]){
            candidIdx = vIdx>>1;
            isvnot = ( vIdx % 2 == 1);
			candidshouldb = isvnot ?  1 : 0;
			if( values[candidIdx] == !candidshouldb) return false;
			if( values[candidIdx] != -1) continue;
			values[candidIdx] = candidshouldb;
        }

        
        for(auto vIdx : scc2v[sccId]){
            // isvnot = (vIdx % 2 == 1);
			int sidx = (vIdx % 2 == 1) ? v2scc[vIdx - 1]: v2scc[vIdx + 1];
			if( svalues[sidx] == 0) return false;
			if( svalues[sidx] != -1) continue;
			if(!assignValue(sidx, 1)) return false;
        }
    }
    return true;
}

int main(){
    int a,b;
    bool isanot, isbnot;
    while(cin>>n>>m){

		std::fill(discovered, discovered + n*2, -1);
		std::fill(svalues, svalues + n*2, -1);
		std::fill(v2scc, v2scc + n*2, -1);		
		std::fill(values, values + n, -1);
		
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
            if(!assignValue(v2scc[0], 1)){
                cout<<"no"<<endl;
            } else {
                cout<<"yes"<<endl;
            }
        }
        
        //reset
		FOR(i, 0, n*2){
            adj[i].clear();
            scc2v[i].clear();
        }
		
        while(!st.empty()) st.pop();
    }
    
    return 0;
}