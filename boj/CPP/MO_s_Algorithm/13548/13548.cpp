#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define MAX_N 100'000
#define MAX_A 100'000
#define FOR(i,s,e) for(int i = s; i < e;i++)
#define endl '\n'
// #define DEBUG_MO
using namespace std;

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
vector<int> ans;
vector<Query> query;

int c2c[MAX_N+1] = {0}; // c2c[i] : i번 등장하는 수의 개수 (c2c[0]은 제외)
int n2c[MAX_A+1] = {0}; // n2c[i] : i가 몇 번 등장했는지

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin>>N;
    sqrtN = sqrt(N);
    arr.resize(N);
    FOR(i,0,N){
        cin>>arr[i];
    }
    
    cin>>M;
    int s,e;
    ans.resize(M);
    FOR(i,0,M){
        cin>>s>>e;
        s--;e--;
        query.push_back(Query(i,s,e));
    }
    
    sort(query.begin(), query.end());
    
    //initial query
    int res = -1;
    s = query[0].s; e = query[0].e;
    FOR(i, s, e+1){
        c2c[n2c[arr[i]]]--; // 만약 한번이상 등장했었더라면, 
        n2c[arr[i]]++;
        c2c[n2c[arr[i]]]++;
        res = max(res, n2c[arr[i]]);
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
            c2c[n2c[arr[s]]]--;
            n2c[arr[s]]++;
            c2c[n2c[arr[s]]]++;
            res = max(res, n2c[arr[s]]);
        }
        
        while( s < query[q].s ){
            c2c[n2c[arr[s]]]--;
            n2c[arr[s]]--;
            c2c[n2c[arr[s]]]++;
            if( res == n2c[arr[s]] + 1){ // 만약 제외된 숫자가 가장 많이 등장하는 숫자였었으면
                while( c2c[res] == 0) res--;
            }
            s++;
        }
        
        while( e > query[q].e ){
            c2c[n2c[arr[e]]]--;
            n2c[arr[e]]--;
            c2c[n2c[arr[e]]]++;
            if( res == n2c[arr[e]] + 1){ // 만약 제외된 숫자가 가장 많이 등장하는 숫자였었으면
                while( c2c[res] == 0) res--;
            }
            e--;
        }
        
        while( e < query[q].e ){
            ++e;
            c2c[n2c[arr[e]]]--;
            n2c[arr[e]]++;
            c2c[n2c[arr[e]]]++;
            res = max(res, n2c[arr[e]]);
        }
        

        ans[query[q].idx] = res;
    }
    
    //output
    for(auto a : ans) cout<<a<<endl;
    
    return 0;
}
