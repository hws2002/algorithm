// 14:17 - 15:19

#include <iostream>
#include <vector>
#include <algorithm> 
#define MAX_N 100'001
#define INF_MAX 2'000'000

#define endl '\n'

// #define DEBUG_ST
// #define DEBUG_LCA

using namespace std;

struct SegTree{
    int n;
    vector<int> rangeMin;
    
    SegTree(const vector<int> & arr){
        n = arr.size();
        rangeMin.resize(4*n, INF_MAX);
        init(arr, 1, 0 , arr.size()-1);
    };
    
    int init(const vector<int> & arr, int nn, int nl, int nr){
        if(nr <= nl) return rangeMin[nn] = arr[nr];
        int mid = (nl + nr) >> 1;
        auto l = init(arr, nn<<1, nl, mid);
        auto r = init(arr, nn<<1 | 1, mid+1, nr);
        return rangeMin[nn] = min<int>(l, r);
    }
    
    int query(int l ,int r, int nn ,int nl, int nr){
        if( r < nl || nr < l) return INF_MAX;
        if(l <= nl && nr <= r) return rangeMin[nn];
        
        int mid = (nl + nr) >> 1;
        auto ql = query(l,r, nn<<1, nl, mid);
        auto qr = query(l,r, nn<<1 | 1, mid+1, nr);
        return min<int>(ql, qr);
    }
    
    int query(int l, int r){
        return query(l, r, 1, 0, n-1);
    }
};

vector<int> children[MAX_N]; //nidx
vector<int> floc(MAX_N);
vector<int> tidx2nidx(MAX_N);
vector<int> depth(MAX_N,-1);
vector<int> prefix; // tidx

int tidx = 0;

void traverse(int h, int r, int d){
    auto tidx_here = tidx;
    floc[h] = prefix.size();
	depth[h] = d;
    tidx2nidx[tidx] = h;
    prefix.push_back(tidx++);
    for(const auto & c : children[h]){
        if(c==r) continue;
        traverse(c,h,d+1);
        prefix.push_back(tidx_here);
    }
}

int lca(SegTree & sgt, const int u, const int v){
    int floc_u = floc[u]; int floc_v = floc[v];
    if(floc_v < floc_u) swap(floc_v, floc_u);
    int lca_tidx = sgt.query(floc_u, floc_v);
    return tidx2nidx[lca_tidx];
}

int query(SegTree & sgt, const int r, const int u, const int v){
    auto lca_u_r = lca(sgt, u, r); 
    auto lca_v_r = lca(sgt, v, r);
#ifdef DEBUG_LCA
    cout<<lca_u_r<<" "<<lca_v_r<<endl;
#endif
	auto lca_u_v = lca(sgt, u,v);
	int d1 = depth[lca_u_v];
	int d2 = depth[lca_u_r];
	int d3 = depth[lca_v_r];
	int max_d = std::max({d1,d2,d3});
	if(max_d == d1) return lca_u_v;
	else if (max_d == d2) return lca_u_r;
	else return lca_v_r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N,M;
    int u,v;
    cin>>N;
    for(int i = 0; i < N-1; i++){
        cin>>u>>v;
        children[u].push_back(v);
        children[v].push_back(u);
    }
    
    
    //make lca tree
    int root = 1;
    traverse(root, 0, 0);
    SegTree sgt(prefix);

#ifdef DEBUG_ST
for(auto p : prefix){
    cout<<p<<" ";
}
cout<<endl;

for(int i = 1; i <= N; i++){
    cout<<floc[i]<<" ";
}
cout<<endl;
#endif

    //query
    int r;
    cin>>M;
    while(M--){
        cin>>r>>u>>v;
        cout<<query(sgt,r,u,v)<<endl;
    }
    return 0;
}