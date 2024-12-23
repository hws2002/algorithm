#include <iostream>
#include <vector>

#define INF_MAX 2000000
using namespace std;

struct SegTree{
    int n;
    vector<pair<int,int>> rangeMaxMin;
    
    SegTree(const vector<int> & arr){
        n = arr.size();
        rangeMaxMin.resize(4*n);
        init(arr, 1, 0 , arr.size()-1);
    };
    
    pair<int,int> init(const vector<int> & arr, int nn, int nl, int nr){
        if(nr <= nl) return rangeMaxMin[nn] = {arr[nr], arr[nr]};
        int mid = (nl + nr) >> 1;
        auto l = init(arr, nn<<1, nl, mid);
        auto r = init(arr, nn<<1 | 1, mid+1, nr);
        return rangeMaxMin[nn] = {
                max<int>(l.first, r.first),
                min<int>(l.second, r.second)
            };
    }
    
    pair<int,int> query(int l ,int r, int nn ,int nl, int nr){
        if( r < nl || nr < l) return {-1, INF_MAX};
        if(l <= nl && nr <= r) return rangeMaxMin[nn];
        int mid = (nl + nr) >> 1;
        auto ql = query(l,r, nn<<1, nl, mid);
        auto qr = query(l,r, nn<<1 | 1, mid+1, nr);
        return {
                max<int>(ql.first, qr.first),
                min<int>(ql.second, qr.second)
            };
    }
    
    pair<int,int> query(int l, int r){
        return query(l, r, 1, 0, n-1);
    }
};

void solve(){
    int N,Q;
    cin>>N>>Q;
    vector<int> arr(N);
    
    for(int i = 0;  i < N; i++){
        cin>>arr[i];
    }
    
    SegTree sgt(arr);
    
    //query
    int a,b;
    while(Q--){
        cin>>a>>b;
        auto m_m = sgt.query(a,b);
        cout<<m_m.first - m_m.second<<endl;
    }
}

int main(){
    int C;
    cin>>C;
    while(C--) solve();
    return 0;
}