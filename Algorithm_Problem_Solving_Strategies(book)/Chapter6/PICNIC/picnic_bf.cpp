//https://www.algospot.com/judge/problem/read/PICNIC
/*
1. brute force : 매 recursive function call마다 free한 가장 작은 index를 구하는 방식으로 센다
2. dfs
*/
#include <iostream>
#include <vector>

#define BF1
#define BF2
#define DFS
#define MAX_N 10
using namespace std;


int n,m;
vector<int> friends[MAX_N];
bool arefriends[MAX_N][MAX_N] = {false};

#ifdef BF1
int res = 0;

void choose(vector<bool> & visit){
    
    //먼저 free한 idx를 찾는다
    int idx = -1;
    for(int i = 0 ; i < n ; i++){
        if(!visit[i]){
            idx = i;
            break;
        }
    }
    
    if(idx == -1) { res++; return; }
    visit[idx] = true;
    for(int i = 0; i < friends[idx].size() ; i++){
        int next = friends[idx][i];
        if(!visit[next]){
            visit[next] = true;
            choose(visit);
            visit[next] = false;
        }
    }
    visit[idx] = false;
    return ;
}
#endif

void solve(){

    cin>>n>>m;
    
    for(int i = 0 ; i < m; i++){
        int a,b;
        cin>>a>>b;
        friends[a].push_back(b);
        friends[b].push_back(a);
        arefriends[a][b] = true;
        arefriends[b][a] = true;
    }
    
#ifdef BF1
    vector<bool> visit(n,false);
    choose(visit);
#endif
    cout<<res<<endl;
    for(int i =0 ; i < n ;i++) friends[i].clear();
    for(int i = 0; i < n; i++)
        for(int j = 0 ; j< n; j++)
            arefriends[i][j] = false;
    res = 0;
}

int main(){
    int C;
    cin>>C;
    
    while(C--){
        solve();
    }
    
    return 0;
}