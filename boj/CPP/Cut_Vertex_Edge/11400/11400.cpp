#include <iostream>
#include <vector>
#include <algorithm>

#define endl '\n'
#define MAX_V 100'000
using namespace std;

vector<int> edges[MAX_V];
vector<pair<int,int>> cutEdge;

int V,E;

vector<int> discovered(MAX_V,0);
int Vcnt = 1;

int dfs(int h,int p){
    discovered[h] = Vcnt++;
    int minDis = discovered[h];
    
    for(auto nxt : edges[h]){
        if(nxt == p) continue;
        if( discovered[nxt] == 0){
            int min_dfs = dfs(nxt, h);
            if( min_dfs > discovered[h]){
                cutEdge.push_back({min(h,nxt), max(h,nxt)});
            }
            minDis = min(minDis, min_dfs);
        } else {
            minDis = min(minDis, discovered[nxt]);
        }
    }
    
    return minDis;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>V>>E;
    int u,v;

    for(int i = 0 ; i < E; i++){
        cin>>u>>v;
        u--;v--;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    
    dfs(0,-1);
    
    sort(cutEdge.begin(), cutEdge.end());
    cutEdge.erase(unique(cutEdge.begin() , cutEdge.end()), cutEdge.end());

    cout<<cutEdge.size()<<endl;
    for(auto ce : cutEdge){
        cout<<ce.first+1<<" "<<ce.second+1<<endl;
    }

    return 0;
}