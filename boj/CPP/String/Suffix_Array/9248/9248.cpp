#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

string s;
vector<int> sa;
vector<int> lcp;
vector<int> isa;

void getSuffixArray(const string & s){
    int n = s.size();
    // sa는 순서를 기준으로 접미사의 시작점을 찾아주고, g는 접미사의 시작점을 기준으로 그룹을 찾아줌
    vector<int> g, dg;
    sa.resize(s.size()); g.resize(n+1); dg.resize(n+1);
    for(int i = 0 ; i < n; i++){
        g[i] = s[i];    
        sa[i] = i;
    }
    g[n] = -1;
    
    for(int d = 1; d < n; d<<=1){
        //sort 
        auto cmp = [&](int i, int j){
            return g[i] < g[j] || ( g[i] == g[j] && g[i+d] < g[j+d]);
        };
        sort(sa.begin(), sa.end(), cmp);
        
        //regroup
        dg[sa[0]] = 1;
        for(int i = 1; i < n ; i++){
            dg[sa[i]] = dg[sa[i-1]] + cmp(sa[i-1], sa[i]);
        }
        g = dg;
    }
}

void getLCP(){
    
    int n = s.size();
    lcp.resize(n,0);
    int i = 0; // i : index of s
    int pv = 0; // previous common 
    
    for(; i < n; i++){
        if( isa[i] == 0) {
            pv = 0;
            continue;
        }
        int si_1 = sa[isa[i]-1];
        while( pv + si_1 < n &&  pv + i < n && s[si_1 + pv] == s[i + pv]){
            pv++;
        }
        lcp[isa[i]] = pv;
        pv = max(0, pv-1);
    }
}

int main(){
    cin>>s;
    
    getSuffixArray(s);
    isa.resize(s.size());
    for(int i = 0 ; i < s.size(); i++){
        cout<<sa[i]+1<<" ";
        isa[sa[i]] = i;
    }
    cout<<endl;
    
    getLCP();
    cout<<"x ";
    for(int i = 1; i < s.size(); i++){
        cout<<lcp[i]<<" ";
    }
    cout<<endl;
    return 0;
}