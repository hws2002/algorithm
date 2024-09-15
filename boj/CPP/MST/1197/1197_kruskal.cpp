// 11:28 ~ 11"38
// kruskal

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

#define MAX_V 10'000
using namespace std;

vector< pair< int, pair<int,int> > >Edges;

int V,E;

struct DisjointSet {
public:
    vector<int> parent;
    vector<int> rank;
    
    DisjointSet ( const int N){
        parent = vector<int>(N);
        rank = vector<int>(N);
        for(int i = 0 ; i < N; i++){
            parent[i] = i;
            rank[i] = 1;
        }
    }
    
    int find(int u){
        if(parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }
    
    int merge(int u , int v){
        u = find(u); v = find(v);
        if(u == v) return u;
        if(rank[u] > rank[v]) swap(u,v);
        parent[u] = v;
        if(rank[u] == rank[v]) rank[v]++;
        return v;
    }
} set(MAX_V);


bool compare(const pair<int, pair<int, int> > & a , const pair<int, pair<int,int> > & b){
    return a.first < b.first;
}

int prim(){
    std::sort(Edges.begin(), Edges.end(), compare);
    int res = 0;
    int cnt = 0;
    for(auto edge : Edges){
        int cost = edge.first;
        int u = edge.second.first; int v = edge.second.second;
        if( set.find(u) == set.find(v)) continue;
        set.merge(u,v);
        res += cost;
        cnt++; if(cnt >= V-1) break;
    }
    
    return res;
}

int main(){
    cin>>V>>E;
    
    int a,b,c;
    for(int i = 0 ; i < E ; i++){
        cin>>a>>b>>c;
        Edges.push_back( {c, {a,b} });
    }
    
    //prim
    cout<<prim()<<endl;
    return 0;
}