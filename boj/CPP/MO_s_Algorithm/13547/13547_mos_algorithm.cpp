#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define MAX_A 1'000'001
#define endl '\n'
using namespace std;

int N,M;
vector<int> arr;
vector<int> ans;

int sqrtN;

struct Query{
public:
    int idx, s, e;
    
    Query(int idx_, int s_, int e_) : idx(idx_), s(s_), e(e_){};
    
    bool operator < (const Query & rhs) const{
        if( s / sqrtN == rhs.s / sqrtN) return e < rhs.e;
        return s / sqrtN < rhs.s / sqrtN;  
    }
};

vector<Query> query;

int num_exist[MAX_A] = {0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N;
    sqrtN = sqrt(N);
    arr.resize(N);

    for(int i = 0 ; i < N; i++){
        cin>>arr[i];
    }
    
    cin>>M;
    ans.resize(M);
    
    int s,e;
    for(int i = 0; i < M; i++){
        cin>>s>>e;
        s--;e--;
        query.push_back(Query(i,s,e));
    }
    
    sort(query.begin(), query.end());
    
    int res = 0;
    
    s = query[0].s; e = query[0].e;
    for(int i = s; i <= e; i++){
        if( num_exist[arr[i]] == 0) res++;
        num_exist[arr[i]]++;
    }
    
    ans[query[0].idx] = res;
    
    for(int q = 1; q < M; q++){
        while( s < query[q].s) {
            num_exist[arr[s]]--;
            if( num_exist[arr[s]] == 0) res--;
            s++;
        }
        
        while( s > query[q].s){
            s--;
            if( num_exist[arr[s]] == 0) res++;
            num_exist[arr[s]]++;
        }
        
        while( e < query[q].e){
            e++;
            if( num_exist[arr[e]] == 0) res++;
            num_exist[arr[e]]++;
        }
        
        while( e > query[q].e){
            num_exist[arr[e]]--;
            if( num_exist[arr[e]] == 0) res--;
            e--;
        }
        ans[query[q].idx] = res;
    }
    
    for(auto e : ans) cout<<e<<endl;
    
    return 0;
}