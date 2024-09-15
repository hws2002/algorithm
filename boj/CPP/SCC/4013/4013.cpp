// scc + dp

#include <iostream>
#include <vector>
#include <stack>

#define MAX_N 500'000
#define MAX_M 500'000
#define INF -2'100'000'000
#define FOR(i,s,e) for(int i = s; i < e; i++)
#define endl '\n'

// #define DEBUG_SCC
// #define DEBUG_DP
using namespace std;


vector<int> adj[MAX_N];
vector<int> vmoney(MAX_N);
vector<bool> isRestaurant(MAX_N,false);

int N,M;
int S,P;

vector<int> discovered(MAX_N,-1);
vector<int> v2s(MAX_N,-1); //vertex id to scc id
vector<int> smoney(MAX_N); //smoney[i] : i번째 scc에 있는 현금의 총액
vector<bool> hasRestaurant(MAX_N,false); // hasRestaurant[i] : i번째 scc에 체인점이 있는지
vector<int> v2c[MAX_N]; // v2c[i] : i번째 node의 child scc idx

stack<int> st;
int startSCC = -1;

int sCnt = 0; int vCnt = 0;
int tarjan(const int here, const int parent){
    discovered[here] = vCnt++;
    int lowest_node = discovered[here];
    st.push(here);
    for(auto next : adj[here]){
        if(discovered[next] == -1){
            lowest_node = min(lowest_node, tarjan(next,here));
        } else {
            if( v2s[next] == -1){ // 역방향 간선이거나, 교차간선&&next가 scc에 묶여있지 않다면
                lowest_node = min(lowest_node, discovered[next]);
            } else { // 순방향 간선이거나, 교차간선&&next가 scc에 묶여 있다면
                v2c[here].push_back(v2s[next]);
            }
        }
    }
    
    if(lowest_node == discovered[here]){ // found another scc!
        while(true){
            int t = st.top();
            v2s[t] = sCnt;
            if(isRestaurant[t]) hasRestaurant[sCnt] = true;
            smoney[sCnt] += vmoney[t];
            st.pop();
            if(t == here) break;
        }
        
        if(here == S || parent == -1) startSCC = sCnt;
        if(parent != -1){
            v2c[parent].push_back(sCnt);
        }
        sCnt++;
    }
    return lowest_node;
}


// int cache[MAX_N] = {-1};

// dp(i) : i번째 scc에서 출발에서 어떤 레스토랑까지 이동하면서 인출할 수 있는 현금의 최대 액수
pair<int,bool> dp(const int sidx, vector<pair<int,bool>> & cache, const vector< vector<int> > & sadj){
    
    //base
    if(sidx >= sCnt){
        return {0,false};
    }
    
    pair<int,bool> & ret = cache[sidx];   
    if(ret.first > -1) return ret;
    
	ret.first = 0;
    for(auto next : sadj[sidx]) {
        auto pib = dp(next,cache,sadj);
        if(pib.second) {
            ret.second = true;
            ret.first = max(ret.first, pib.first);
        }
    }
    
    if( !ret.second ) ret.first = 0;
    if( hasRestaurant[sidx] || ret.second ) {
		ret.second = true;
		ret.first += smoney[sidx];
	}
	return {ret.first, ret.second};
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

    cin>>N>>M;
    int a,b;
    FOR(i,0,M){
        cin>>a>>b;
        adj[a-1].push_back(b-1);
    }
    
    FOR(i,0,N){
        cin>>vmoney[i];
    }
    
    cin>>S>>P;
    int temp;
    FOR(i,0,P){
        cin>>temp;
        isRestaurant[temp-1] = true;
    }
    
    //condensation
    //create - scc
    tarjan(S-1,-1);
#ifdef DEBUG_SCC
printf(" sCnt : %d \n", sCnt);
#endif
    //create adj over scc
    vector< vector<int> > sadj(sCnt); // 인접리스트
    // vector<int> outdegree(sCnt,0);
    
    FOR(i,0,N){
        if(v2s[i] != -1){
            int from = v2s[i];
            for(auto to : v2c[i]){
                sadj[from].push_back(to);
            }
        }
    }
#ifdef DEBUG_SCC
cout<<" sadj start "<<endl;
	
for(int sccid = 0; sccid < sCnt; sccid++){
	printf("scc[%d] has vertex : ", sccid);
	for(int i = 0; i < N; i++){
		if(v2s[i] == sccid) cout<<i+1<<" ";
	}
	printf("has money : %d ", smoney[sccid]);
	printf("has restaurant : %s ", hasRestaurant[sccid] ? "true" : "false");
	cout<<" ";
	printf("sadj[%d] : ", sccid);
    for(auto next : sadj[sccid]){
        cout<<next<<" ";
    }
    cout<<endl;
}
cout<<" sadj end "<<endl;
#endif
    // outdegree가 0이면서 hasRestaurant가 false인 scc들을 삭제한다
    // 로 하려 했는데, 여간 불편한게 많다    
    
	//dp
    vector< pair<int,bool> > cache(sCnt, {-1,false});
    cout<<dp(startSCC, cache, sadj).first<<endl;

#ifdef DEBUG_DP
for(int i = 0; i < sCnt; i++){
	printf(" cache[%d] : %d, %d \n", i, cache[i].first, cache[i].second);
}
#endif
    return 0;
}