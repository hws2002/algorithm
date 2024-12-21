#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 51
using namespace std;


vector<int> getSuffixArray(const string & s){
    
    int n = s.size();
    vector<int> sa,g,ng;
    sa.resize(n,0); g.resize(n+1,0); ng.resize(n+1,0);
    for(int i = 0; i < n; i++){
        sa[i] = i;
        g[i] = s[i];
    }
    
    g[n] = 0;
    
    for(int d = 1 ; d < n; d<<=1){
        //sort
        auto cmp = [&](int i, int j){
            return g[i] < g[j] || (g[i] == g[j] && g[i+d] < g[j+d]);
        };
        sort(sa.begin(), sa.end(), cmp);
        
        //re-assign
        ng[sa[0]] = 1;
        for(int i = 1; i < n; i++){
            ng[sa[i]] = ng[sa[i-1]] + cmp(sa[i-1], sa[i]);
        }
        g = ng;
    }
    
    return sa;
}

int minAlphabet(const vector<int> & sa){
    
    int N = sa.size();
    
    bool priority[MAX_N][MAX_N] = {{0}};
    vector<bool> visit(N, false);
    
    for(int i = N-1; i >= 0; i--){
        visit[sa[i]] = true;
        for(int j = 0; j < N; j++){
            if(!visit[j]){
                priority[j][sa[i]] = true;
            }
        }
    }
    
    int ret = 1;
    
    for(int i = 1; i < N; i++){
        int sai = sa[i];
        int sai_1 = sa[i-1];
        
        if( sai_1+1 >= N) continue;
        if( sai+1>=N ) ret++;
        else if( priority[sai_1+1][sai+1]){
            // res+=0;
            // do nothing
        } else {
            ret++;
        }
    }
    
    return ret;
}

int main(){
    string s;
    cin>>s;
    vector<int> sa = getSuffixArray(s);
    // for(auto e : sa){
    //     cout<<e<<" ";
    // }
    // cout<<endl;
    int required = minAlphabet(sa);
    // cout<<"required : "<<required<<endl;
    
    vector<int> visit(26, false);
    int set_size = 0;
    for(const auto & c : s){
        if( !visit[c-'a'] ){
            set_size++;
            visit[c-'a'] = true;
        }
    }
    

        for(int a = 0; a < required; a++){
            if(!visit[a]){
                cout<<1<<endl;
                return 0;
            }
        }
        cout<<0<<endl;
    
    return 0;
}