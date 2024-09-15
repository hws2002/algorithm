// lazy
#include <iostream>
#include <vector>

#define MAX_N 100'000
#define FOR(i,s,e) for(int i = s; i < e; i++)
#define endl '\n'
// #define DEBUG_INPUT
using namespace std;
typedef long long ll;

int N,M;

vector< pair<int,int> > boundary(MAX_N); // boundary[i]: {f,s} f: i가 가장 먼저 발견된 순서, s : i가 return 될떄의 순서
vector<int> mentee[MAX_N];
vector<int> discovered(MAX_N,-1);

int Vcnt = 0;

void dfs(const int here){
// cout<<"dfs("<<here<<")"<<endl;
    discovered[here] = Vcnt++;
    boundary[here].first = discovered[here];

    for(auto ment : mentee[here]){
        if( discovered[ment] != -1) continue;
        dfs(ment);
    }

    boundary[here].second = Vcnt-1;
    return ;
}

struct RSQ{ // range sum query
public:
    int n;
    vector<ll> rangeSum;
    vector<ll> lazy;
    
    RSQ(){
        n = N;
        rangeSum = vector<ll> (4*n,0);
        lazy = vector<ll> (4*n,0);
    }

    void propagate(const int nn, const int nl, const int nr){
        
        if( lazy[nn] ){
            rangeSum[nn] += 1LL * (nr - nl + 1) * lazy[nn];
            if( nl < nr){
                lazy[nn*2] += lazy[nn];
                lazy[nn*2+1] += lazy[nn];
            }
        }
        
        lazy[nn] = 0;
    }
    
    //update
    ll update(const int l, const int r, const ll w, const int nn, const int nl, const int nr){

        //push
        propagate(nn, nl, nr);
        
        // out of range
        if( r < nl || nr < l ) return 0;
        
        // inside range
        if( l <= nl && nr <= r) {
            rangeSum[nn] += 1LL * (nr - nl + 1) * w;
            
            if( nl < nr ){
                lazy[nn*2] += w;
                lazy[nn*2+1] += w;
            }

            return rangeSum[nn];
        }
        
        int mid = (nl + nr) >> 1;
        return update(l, r, w, nn*2, nl, mid) + update(l, r, w, nn*2+1, mid+1, nr);
    }
    
    // update - interface
    void update(const int l, const int r, const ll w){
        update(l, r, w, 1, 0, n-1);
    }

    ll query(const int idx, const int nn, const int nl, const int nr){
        //push
        propagate(nn,nl,nr);
        
        //out of range
        if( idx < nl || nr < idx) return 0;
        
        //inside range
        if( idx <= nl && nr <= idx){
            return rangeSum[nn];
        }

        int mid = (nl + nr) >> 1;
        return query(idx, nn*2, nl, mid) + query(idx, nn*2 + 1, mid+1, nr);
    }
    
    //query - interface
    ll query(const int idx){
        return query(idx, 1, 0, n-1);
    }
};



int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin>>N>>M;
    
    int temp; cin>>temp;
    FOR(i,1,N){
        cin>>temp;
        temp--;
        mentee[ temp ].push_back(i);
    }
    
    //dfs
    dfs(0);

#ifdef DEBUG_INPUT
for(int i = 0 ; i < N; i++){
    cout<<"mentee["<<i<<"] : ";
    for(auto ment : mentee[i]){
        cout<<ment<<" ";
    }
    cout<<endl;
}

cout<<"discovered : "<<endl;
for(int i = 0 ; i< N; i++){
    cout<<discovered[i]<<" ";
}
cout<<endl;

cout<<"boundary : "<<endl;
for(int i = 0 ; i < N; i++){
    cout<<boundary[i].first<<" ";
}
cout<<endl;

for(int i = 0 ; i < N; i++){
    cout<<boundary[i].second<<" ";
}
cout<<endl;
#endif

    
    //segtree
    RSQ rsq;

    //query
    int op,i;
    ll w;

    while(M--){
        cin>>op>>i;
        i--;
        if(op == 1) { // update
            cin>>w;
            rsq.update( boundary[i].first, boundary[i].second , w);
        } else { // query
            cout<<rsq.query(boundary[i].first)<<endl;
        }
    }
    
    return 0;
}
