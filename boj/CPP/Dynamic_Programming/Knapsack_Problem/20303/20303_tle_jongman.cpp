#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 30'0
#define MAX_K 3'000
#define endl '\n'
// #define DEBUG_MERGE

using namespace std;

int N,M,K;
// int cache[MAX_N][MAX_K] = {0};
int cache[MAX_N][MAX_K] = {0};

vector<int> candy;
vector<int> Group;

vector<int> gsize; // groupsize

struct DisjointSet{
public:
    vector<int> parent;
    vector<int> rank;
    vector<bool> isRoot;
    
    //constructor
    DisjointSet(int n){
        parent.resize(n);
        rank = vector<int> (n,0);
        isRoot = vector<bool> (n, true);
        gsize = vector<int> (n,1);
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }
    }
    
    //find
    int find(int u){
        if(parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }
    
    // merge
    // returns number of candies this group have
    int merge(int u, int v){
        u = find(u); v = find(v);
        if( u == v ) return candy[v];
        if( rank[u] > rank[v]) swap(u,v);
        parent[u] = v;
        if( rank[u] == rank[v]) rank[v]++;
        isRoot[u] = false; gsize[v] += gsize[u];
        return candy[v] += candy[u];
    }
};

int dp(const int idx, const int capacity){
    if( capacity <= 0 || idx >= Group.size()) return 0;
    int& ret = cache[idx][capacity];
    if(ret) return ret;
    
    if( capacity >= gsize[Group[idx]] )
        return ret = max( candy[Group[idx]] + dp(idx+1, capacity - gsize[Group[idx]]) , dp(idx+1, capacity) );
    else 
        return ret = dp(idx+1, capacity);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>M>>K;
    candy.resize(N);
    for(int i = 0 ; i < N; i++){
        cin>>candy[i];
    }
    
    //create disjointset
    DisjointSet set(N);
    
    int a,b;
    for(int i = 0; i < M; i++){
        cin>>a>>b;
        set.merge(a-1,b-1);
    }
    
    // create stuffs
    for(int i = 0 ; i < N; i++){
        if( set.isRoot[i]) Group.push_back(i);
    }
#ifdef DEBUG_MERGE
for(auto g : Group){
    cout<<candy[g]<<" ";
}
cout<<endl;
for(auto g : Group){
    cout<<gsize[g]<<" ";
}
cout<<endl;
#endif
    // knapsack problem
    cout<<dp(0,K-1)<<endl;
    return 0;
}