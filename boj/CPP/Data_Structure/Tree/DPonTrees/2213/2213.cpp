//dfs
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 10'000
using namespace std;


int n;
int weights[MAX_N];
vector<int> adj[MAX_N];

int cache[10'000][2] = {0};
bool choice[10'000][2] = {false}; 
/*
choice[i][j] : dp(i,j)에서 본인을 포함하는 독립집합이 더 크다면 true, 아니라면 false (전체적으로)
*/

// lastchosen이 "here"노드의 parent노드를 독립 집합에 포함했는지 여부일때, 
// here의 서브트리에서의 최대 독립집합의 크기를 반환한다.
int dp(int here, const bool lastchosen, const int last){
    //base
    if(here >= n) return 0;
    int & ret = cache[here][lastchosen];
    if(ret > -1) return ret;
    
    // int w_n_choose = 0;
    ret = 0;
    int w_choose = weights[here];
    
    for(auto child : adj[here]){
        if(child == last) continue;
        ret += dp(child, 0, here);
        w_choose += dp(child, 1, here);
    }
    
    if(lastchosen){ // 이 노드는 독립집합에 포함될 수 없다.
        // choice[here][1] 은 자동으로 0 이 된다.
        choice[here][1] = false;
        return ret;
    } else { // 이 노드는 독립집합에 포함될 수도 있고 없을 수도 있다.
        if(ret >= w_choose){ 
            choice[here][0] = false;
            return ret;
        }  else {
            choice[here][0] = true;
            return ret = w_choose;
        }
    }
}

vector<int> res;

void dfs(int here, const int last, const bool lastchosen){
    if(!lastchosen && choice[here][0])
        res.push_back(here);
        
    for(auto next : adj[here]){
        if(next == last) continue;
        dfs(next, here, choice[here][lastchosen]);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>n;
    //pre
    for(int i = 0; i < n; i++){
        cache[i][0] = cache[i][1] = -1;
    }
    for(int i = 0; i < n; i++){
        cin>>weights[i];
    }
    
    int u,v;
    for(int i = 0; i < n-1; i++){
        cin>>u>>v;
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);
    }
    
    //dp on tree
    cout<<dp(0,0,-1)<<endl;
    
    //recon choice  - dfs
    dfs(0,-1, false);
    std::sort(res.begin(), res.end());
    
    for(auto e : res){
        cout<<e+1<<" ";
    }
    return 0;
}

/*
1(10)--2(30)--3(40)--4(10)--5(20)
       |
       6(20)--7(70)

ans : 7(70) + 1(10) + 3(40) + 5(20)


*/