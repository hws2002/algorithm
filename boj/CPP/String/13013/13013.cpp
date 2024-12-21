#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>


#define endl '\n'
using namespace std;

vector<int> getSuffixArray(const string & s){
    int n = s.size();
    vector<int> sa,g,ng;
    sa.resize(n,0); g.resize(n+1, 0); ng.resize(n+1,0);
    for(int i = 0; i < n; i++){
        g[i] = s[i];
        sa[i] = i;
    }
    
    g[n] = 2;
    
    for(int d = 1; d < n; d<<=1){
        //sort
        auto cmp = [&](int i, int j){
            return g[i] < g[j] || (g[i] == g[j] && g[i+d] < g[j+d]);
        };
        
        sort(sa.begin(), sa.end(), cmp);
        
        //re-assign group value
        ng[sa[0]] = 3;
        for(int i = 1; i < n; i++){
            ng[sa[i]] = ng[sa[i-1]] + cmp(sa[i-1], sa[i]);   
        }
        
        g = ng;
    }
    
    return sa;
}

int main(){
    string S;
    cin>>S;
    if(S.empty()) return 0;
    for(const auto & e : getSuffixArray(S)){
        cout<<e<<endl;
    }
    return 0;
}