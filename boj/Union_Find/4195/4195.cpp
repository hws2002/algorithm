#include <iostream>
#include <vector>
#include <string>
#include <map>

#define MAX_F 100'000
#define endl '\n'
// #define DEBUG_UF
using namespace std;

struct DisjointSet{
public:
    vector<int> parent;
    vector<int> rank;
    vector<int> gsize;
    
    DisjointSet(const int n){
        parent.resize(n);
        rank.resize(n,0);
        gsize.resize(n,1);
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }
    }
    
    //find
    int find(const int u){
        if( parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }
    
    //merge
    bool merge(int u, int v){
        u = find(u);
        v = find(v);
        if( u == v ) return false;
        
        // int temp = gsize[u];
        // gsize[u] += gsize[v];
        // gsize[v] += temp;
        
        if( rank[u] > rank[v]) swap(u,v);
        parent[u] = v;
        gsize[v] += gsize[u];
        if(rank[u] == rank[v]) rank[v]++;
        return true;
    }
    
    //
    int getGsize(int u){
        return gsize[find(u)];
    }
};


int F;
void solve(){
    cin>>F;
    string f1,f2;
    DisjointSet set(2*F);
    
    map<string,int> s2Idx;
    int idx1,idx2;
    for(int i = 0; i < F; i++){
        cin>>f1>>f2;
        idx1 = s2Idx.size();
        auto it1 = s2Idx.find(f1);
        if(it1 == s2Idx.end()){
            s2Idx.insert({f1,idx1});
        } else idx1 = it1->second;
        idx2 = s2Idx.size();
        auto it2 = s2Idx.find(f2);
        if(it2 == s2Idx.end()){
            s2Idx.insert({f2,idx2});
        } else idx2 = it2->second;
        
        set.merge(idx1,idx2);
        cout<<set.getGsize(idx1)<<endl;
#ifdef DEBUG_UF
cout<<"parent : ";
for(auto p : set.parent){
    cout<<p<<" ";
}
cout<<endl<<"rank : ";
for(auto r : set.rank){
    cout<<r<<" ";
}
cout<<endl<<"gsize : ";
for(auto s : set.gsize){
    cout<<s<<" ";
}
cout<<endl;
#endif
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}