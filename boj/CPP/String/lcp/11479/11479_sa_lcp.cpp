#include <iostream>
#include <vector>
#include <algorithm>


#define all(v) v.begin(), v.end()

using namespace std;
typedef long long ll;

string S;

vector<int> getSuffixArray(const string & S){
    int n = S.size();
    vector<int> sa(n, 0);
    vector<int> g(n+1, 0);
    vector<int> ng(n+1, 0);
    
    for(int i = 0; i < n; i++){
        g[i] = S[i]; 
        sa[i] = i;
    }
    g[n] = -1;
    
    for(int d = 1; d < n; d<<=1){
        
        //sort
        auto cmp = [&](int i, int j){
            return g[i] < g[j] || (g[i] == g[j] && g[i+d] < g[j+d]);
        };
        sort(all(sa),cmp);
        
        //regroup
        ng[sa[0]] = 1;
        
        for(int i = 1; i < n;i++){
            ng[sa[i]] = ng[sa[i-1]] + cmp( sa[i-1], sa[i]);
        }
        g = ng;
    }
    
    return sa;
}

vector<int> getLCP(const string & S, vector<int> & sa){
    if(sa.empty()) sa = getSuffixArray(S);
    
    int n = S.size();
    vector<int> isa(n,0);
    for(int i = 0; i < n; i++){
        isa[sa[i]] = i;
    }   
    
    vector<int> lcp(n,0);
    int i = 0; // i : index of S
    int pv = 0; // previous common
    
    for(; i < n; i++){
        if( isa[i] == 0){
            pv = 0;
            continue;
        }
        int si_1 = sa[isa[i] - 1];
        while( pv + si_1 < n && pv + i < n && S[pv + si_1] == S[pv + i] ) pv++;
        lcp[isa[i]] = pv;
        pv = max(0, pv-1);
    }
    
    return lcp;
}

int main(){
    cin>>S;
    ll n = S.size();
    ll ret = n*(n+1)>>1;
    
    //get suffix array and lcp
    vector<int> sa = getSuffixArray(S);
    // for(int e : sa){
    //     cout<<e<<" ";
    // }
    // cout<<endl;
    
    vector<int> lcp = getLCP(S,sa);
    
    // for(int e : lcp){
    //     cout<<e<<" ";
    // }
    // cout<<endl;

    for(const ll e : lcp)
        ret -= e;
    cout<<ret<<endl;
    return 0;
}

