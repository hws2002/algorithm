// kruskal

#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 100'001
#define MAX_M 1'000'000
// #define DEBUG_KRUSKAL
using namespace std;

int N,M;
vector<pair<int, pair<int,int> > > Edges;

struct DisJointSet{
public:
    vector<int> parent, rank;
    
    //constructor
    DisJointSet(int n){
        parent = vector<int> (n);
        rank = vector<int> (n);
        for(int i = 0; i < n; i++){
            parent[i] = i;
            rank[i] = 1;
        }
    }
    
    int find(int u){
        if(parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }
    
    void merge(int u , int v){
        u = find(u); v = find(v);
        if( u == v ) return ;
        if( rank[u] > rank[v]) swap(u,v);
        parent[u] = v;
        if( rank[u] == rank[v]) rank[v]++;
    }
} set(MAX_N);

int kruskal(){
    int largestC =  0;
    int res = 0;
    int cnt = 0;
    //sort Edges
    std::sort(Edges.begin(), Edges.end());
    for(auto edge : Edges){
        int cost = edge.first;
        int u = edge.second.first; int v = edge.second.second;
#ifdef DEBUG_KRUSKAL
cout<<"edge info cost, u ,v : "<<cost<<", "<<u<<", "<<v<<endl;
#endif
        if( set.find(u) == set.find(v)) continue;
        set.merge(u,v); 
        res += cost;
        largestC = max(largestC, cost);
        cnt++; if( cnt >= N-1) break;
    }
    
    return res-largestC;
}

int main(){
    cin>>N>>M;
    int A,B,C;
    for(int i = 0 ; i < M; i++){
        cin>>A>>B>>C;
        Edges.push_back( { C ,  { A-1, B-1} } );
    }
    //kruskal
    cout<<kruskal()<<endl;
    return 0;
}