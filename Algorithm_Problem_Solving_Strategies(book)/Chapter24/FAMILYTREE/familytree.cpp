#include <iostream>
#include <vector>

#define INF_MAX 2000000
#define MAX_N 100005
#define endl '\n'
// #define DEBUG_TRAVERSE
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

vector<int> children[MAX_N];
vector<int> floc(MAX_N); // nidx기준
// vector<int> nidx2tidx(MAX_N);
vector<int> tidx2nidx(MAX_N);
vector<int> prefix; // tidx가 들어가있음
vector<int> depth(MAX_N); // nidx 기준

int tnode = 0;

void prefixTraverse(int h, int d){
    depth[h] = d;
    // nidx2tidx[h] = tnode; 
	// nidx2tidx[h] 는 사실상 prefix[floc[h]] 아닌가?
	auto tidx = tnode;
    tidx2nidx[tnode] = h;
    floc[h] = prefix.size();
    prefix.push_back(tnode++);
#ifdef DEBUG_TRAVERSE
    printf("h, d, floc[%d], nidx2tidx[%d], tidx2nidx[%d], : %d, %d, %d, %d, %d \n",
            h,h,h, h, d, floc[h], nidx2tidx[h], tidx2nidx[h]);
#endif
    for(const auto & c : children[h]){
        prefixTraverse(c,d+1);
        prefix.push_back(tidx);
    }
}

void solve(){
    int N,Q;
    cin>>N>>Q;

    prefix.clear();
    for(int i = 0; i <= N; i++) children[i].clear();
    
    int p;
    for(int i = 1;  i <= N-1; i++){
        cin>>p;
        children[p].push_back(i);
    }
    
    //traverse
    tnode = 0;
    prefixTraverse(0,0);
    SegTree sgt(prefix);
    
    //query
    int a,b;
    while(Q--){
        cin>>a>>b;
        int posi_a = floc[a]; int posi_b = floc[b];
        if(posi_b < posi_a) swap(posi_a, posi_b);
        int ances_tidx = sgt.query(posi_a, posi_b);
        int ances_nidx = tidx2nidx[ances_tidx];
        cout<< depth[a] + depth[b] - 2*depth[ances_nidx]<< endl;
    }
}

int main(){
    int C;
    cin>>C;
    while(C--) solve();
    return 0;
}