#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define MAX_N 100'000
#define MAX_A 1'000'000
#define FOR(i,s,e) for(int i = s; i < e;i++)
#define endl '\n'
// #define DEBUG_MO
using namespace std;
typedef long long ll;

int N,M;
int sqrtN;
struct Query{
public:
    int idx, s, e;
    Query(int idx_, int s_, int e_) : idx(idx_), s(s_), e(e_){};
    
    bool operator < (const Query & rhs) const {
        if( s / sqrtN == rhs.s / sqrtN) return e < rhs.e;
        return s / sqrtN < rhs.s / sqrtN;
    }
};

vector<int> arr;
vector<ll> ans;
vector<Query> query;

int n2c[MAX_A+1] = {0}; // n2c[i] : 숫자 i가 몇 번 등장했는지

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin>>N>>M;
    sqrtN = sqrt(N);
    arr.resize(N);
    FOR(i,0,N){
        cin>>arr[i];
    }

    int s,e;
    ans.resize(M);
    FOR(i,0,M){
        cin>>s>>e;
        s--;e--;
        query.push_back(Query(i,s,e));
    }
    
    sort(query.begin(), query.end());
    
    //initial query
    ll res = 0;
    s = query[0].s; e = query[0].e;
    FOR(i, s, e+1){
        res -= 1LL * n2c[arr[i]] * n2c[arr[i]] * arr[i];
        n2c[arr[i]]++;
        res += 1LL * n2c[arr[i]] * n2c[arr[i]] * arr[i] ;
    }

#ifdef DEBUG_MO
printf("initial s,e, res :%d, %d, %d \n", s, e, res);
#endif
    ans[query[0].idx] = res;

    FOR(q,1,M){
#ifdef DEBUG_MO
printf("s,e, res : %d, %d ,%d \n", query[q].s, query[q].e, res);
#endif
        while( s > query[q].s ){
            --s;
            res += 1LL * arr[s] * (2*n2c[arr[s]] + 1);
            n2c[arr[s]]++;
        }

        while( s < query[q].s ){
            res += 1LL * arr[s] * (1 - 2*n2c[arr[s]]);
            n2c[arr[s]]--;
            s++;
        }
        
        while( e > query[q].e ){
            res += 1LL * arr[e] * (1 - 2*n2c[arr[e]]);
            n2c[arr[e]]--;
            e--;
        }
        
        while( e < query[q].e ){
            ++e;
            res += 1LL * arr[e] * (2*n2c[arr[e]] + 1);
            n2c[arr[e]]++;
            
        }
        
        ans[query[q].idx] = res;
    }
    
    //output
    for(auto a : ans) cout<<a<<endl;
    
    return 0;
}
