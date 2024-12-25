#include <iostream>
#include <fstream>
#include <vector>

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
        rangeMin.resize(4*n);
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
vector<int> prefix; // tidx

int tidx = 0;

void traverse(int h, int r){
    auto tidx_here = tidx;
    floc[h] = prefix.size();
    tidx2nidx[tidx] = h;
    prefix.push_back(tidx++);
    for(const auto & c : children[h]){
        if(c==r) continue;
        traverse(c,h);
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
    if(lca_u_r != r && lca_v_r!= r){
        if( lca_u_r == u){
            if( lca(sgt,u,v) != u) return u;
            else return lca_v_r;
        } else if (lca_v_r == v){
            if( lca(sgt,u,v) != v) return v;
            else return lca_u_r;
        } else { // lca(u,r) != u && lca(v,r) != v
            return lca(sgt,u,v);
        }
    } else {
        if(lca_u_r == r){
            if ( lca_v_r == r) return lca(sgt, u, v);
            else return r;
        } else { // lca(v,r) == r
            if ( lca_u_r == r) return lca(sgt, u, v);
            else return r;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // Open the input and output files
    ifstream inputFile("input.in");
    ofstream outputFile("output_.out");

    if (!inputFile.is_open()) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }

    if (!outputFile.is_open()) {
        cerr << "Error opening output file!" << endl;
        return 1;
    }

    int N, M;
    int u, v;

    inputFile >> N;

    // Read the tree edges
    for (int i = 0; i < N - 1; i++) {
        inputFile >> u >> v;
        children[u].push_back(v);
        children[v].push_back(u);
    }
    
    // Make LCA tree
    int root = 1;
    traverse(root, 0);
    SegTree sgt(prefix);

    // Process queries
    inputFile >> M;
	int r;
    while (M--) {
        inputFile >> r >> u >> v ;
        outputFile << query(sgt, r, u, v) << endl;
    }

    // Close the files
    inputFile.close();
    outputFile.close();

    return 0;
}
