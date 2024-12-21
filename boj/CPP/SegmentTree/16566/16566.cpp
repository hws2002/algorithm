#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 4'000'001
#define MAX_K 10'000
#define INF 4'000'002

// #define DEBUG_COMPRESS
#define endl '\n'
using namespace std;

int N,M,K;

vector<int> resources;
vector<int> allNumbers;
vector<int> query;

int c2o[MAX_N] = {0}; // compressed coodinate to original coordinate
int o2c[MAX_N] = {0};

int max_c = -1;
void compressCoordinate(){
    
    sort(allNumbers.begin(), allNumbers.end());
    allNumbers.erase(unique(allNumbers.begin(), allNumbers.end()), allNumbers.end());
    max_c = allNumbers.size();
    
    for(int i = 0 ; i < max_c; i++){
        o2c[allNumbers[i]] = i;
        c2o[i] = allNumbers[i];
        allNumbers[i] = i;
    }
    
    for(int i = 0 ; i < M; i++){
        resources[i] = o2c[resources[i]];
        allNumbers[resources[i]] = resources[i];
    }
    
    for(int i = 0; i < K; i++){
        query[i] = o2c[query[i]];
    }
}

struct SegTree{
public:
    int n;
    vector<int> rangeMin;
    vector<int> idx2stidx;
    
    SegTree(const vector<int> & raw){
        n = raw.size();
        rangeMin.resize(4*n);
        idx2stidx.resize(n);
        init(raw,1,0, n-1);
    }
    
    int init(const vector<int> & raw, int nn, int nl, int nr){
        if(nr <= nl) {
            idx2stidx[nl] = nn;
            return rangeMin[nn] = raw[nl];
        }
        
        int mid = (nl + nr) >> 1;
        return rangeMin[nn] = min(
            init(raw, nn<<1, nl, mid),
            init(raw, nn<<1|1, mid+1, nr)
        );
    }

    int query(int l, int r, int nn, int nl, int nr){
        if(r < nl || nr < l) return INF;
        if(l <= nl && nr <= r) return rangeMin[nn];
        int mid = (nl + nr) >> 1;
        return min(
            query(l, r, nn<<1, nl, mid),
            query(l, r, nn<<1|1, mid+1, nr)
        );
    }
    
    //query - interface
    int query(const int l, const int r){   
        return query(l, r , 1, 0, n-1);
    }
    
    int update(int at,int to, int nn, int nl, int nr){
        if(at < nl || nr < at) return rangeMin[nn];
        if( at <= nl && nr <= at) return rangeMin[nn] = to;
        int mid = (nl + nr) >> 1;
        return rangeMin[nn] = min(
            update(at, to, nn<<1, nl, mid),
            update(at, to, nn<<1|1, mid+1, nr)
        );
    }
    
    //update - interface
    void update(int at, int to){
        update(at, to ,1 ,0 ,n-1 );
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>M>>K;
    resources.resize(M);
    allNumbers.resize(M+K);
    for(int i = 0 ; i < M; i++){
        cin>>resources[i];
        allNumbers[i] = resources[i];
    }
    
    query.resize(K);
    for(int i = 0; i < K; i++){
        cin>>query[i];
        allNumbers[M+i] = query[i];
    }
    
    compressCoordinate();
#ifdef DEBUG_COMPRESS
for(auto e : resources){
    cout<<e<<" ";
}
cout<<endl;
for(auto e : query){
    cout<<e<<" ";
}
cout<<endl;
#endif

    // vector<int> span(max_c, INF);
    
    // for(const auto & r : resources){
    //     span[r] = r;
    // }
    
    // SegTree t(span);
    SegTree t(allNumbers);
    //solve
    for(const auto & q : query){
        int idx = t.query(q+1, max_c);
        cout<<c2o[idx]<<endl;
        t.update(idx, INF);
    }
    
    return 0;
}    