#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define MAX_N 100
// #define DEBUG_KRUSKAL
using namespace std;

int n;

vector< pair<double, pair<int,int> > > Edges;


double X[MAX_N];
double Y[MAX_N];

struct DisjointSet{
public:
    vector<int> parent;
    vector<int> rank;
    //con
    DisjointSet(const int N){
        parent.resize(N);
        rank.resize(N,0);
        for(int i = 0; i < N; i++){
            parent[i] = i;
        }
    }
    //find
    int find(int u){
        if(parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }
    
    //merge
    bool merge( int u, int v){
        u = find(u); v = find(v);
        // if( u == v) return false;
        if( rank[u] > rank[v]) swap(u,v);
        parent[u] = v;
        if(rank[u] == rank[v]) rank[v]++;
        return true;
    }
};

double kruskal(){
    DisjointSet set(n);
    
    double w;
    int u,v;
    int cnt = 0;
    double ret = 0;
    for(auto e : Edges){
        w = e.first; u = e.second.first; v = e.second.second;
#ifdef DEBUG_KRUSKAL
printf("w, u, v: %lf, %d, %d \n", w,u,v);
#endif
        if( set.find(u) == set.find(v)) continue;
        set.merge(u,v); cnt++;
        ret += w;
        if(cnt >= n-1) break;
    }
    
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>n;
    
    // double x, y;
    for(int i = 0; i < n; i++){
        cin>>X[i]>>Y[i];
    }
    //create edges
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            // printf("hypot , i, j : %lf, %d, %d \n", hypot(X[i] - X[j], Y[i] - Y[j]), i, j);
            Edges.push_back({ /*w*/ hypot(X[i] - X[j] , Y[i] - Y[j]),{i,j}});
        }
    }
    
    std::sort(Edges.begin(), Edges.end());
    
    //kruskal
    // double res = kruskal();
    // cout<<kruskal()<endl;
    printf("%f",kruskal());
    return 0;
}
