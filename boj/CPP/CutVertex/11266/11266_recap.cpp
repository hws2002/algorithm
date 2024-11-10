#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_V 10'000
using namespace std;

int V,E;
vector<int> Edge[MAX_V];

vector<int> cutVertex;

vector<int> discovered(MAX_V,0);
int Vcnt = 1;

// h를 루트로 하는 서브트리에서 도달 할 수 있는 가장 작은 discovered를 반환한다.
int dfs(int h, int p){
    discovered[h] = Vcnt++;
    int minDis = discovered[h];
    
    int num_st = 0; // number of subtree
    for(auto nxt : Edge[h]){
        if(nxt == p) continue;
        if(discovered[nxt] == 0){
            int min_dfs = dfs(nxt,h);
            if( p!=-1 && min_dfs >= discovered[h])
                    cutVertex.push_back(h);
            num_st++;
			minDis = min(minDis, min_dfs);
        } else {
            minDis = min(minDis, discovered[nxt]);
        }
    }

    // 단절점인지 판별한다
    if( p == -1){ // root라면
        if(num_st >= 2)
            cutVertex.push_back(h);
    }
    
    return minDis;
}

int main(){
    cin>>V>>E;
    int u,v;
    for(int i = 0; i < E; i++){
        cin>>u>>v;
        u--;v--;
        Edge[u].push_back(v);
        Edge[v].push_back(u);
    }
    
    for(int i = 0 ; i < V; i++){
        if(!discovered[i]){
            dfs(i,-1);
        }
    }
    
    sort(cutVertex.begin(), cutVertex.end());
    cutVertex.erase(unique(cutVertex.begin(), cutVertex.end()), cutVertex.end());
    
    cout<<cutVertex.size()<<endl;
    for(auto cv : cutVertex){
        cout<<cv+1<<" ";
    }
    return 0;
}