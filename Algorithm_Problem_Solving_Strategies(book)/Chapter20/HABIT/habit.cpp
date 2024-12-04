#include <iostream>
#include <vector>
#include <algorithm>

// #define DEBUG_COMP
// #define DEBUG_SUFARR
#define endl '\n'
using namespace std;

vector<int> perm;
struct Comparator{
public:
    const vector<int> & group;
    int t;

    Comparator(const vector<int> & group_, int t_) : group(group_), t(t_){};
    
    bool operator() (int i, int j){
        if(group[i] != group[j]) return group[i] < group[j];
        return group[i+t] < group[j+t];
    }
};


void getSuffixArray(const string & s){
    int n = s.size();
    perm.resize(n,0);
    vector<int> group(n+1,0);
    for(int i = 0 ; i < n; i++){
        group[i] = s[i];
        perm[i] = i;
    }
    group[n] = -1; // a와 ab중 먼저 오는 것은 a
    
    int t = 1;
    while(t < n){
        // perm을 group 을 기반으로 정렬시킨다
        Comparator c(group, t);
        sort(perm.begin(), perm.end(), c);
        //이제 perm은 앞 2t개의 문자를 기준으로 정렬되어 있다.
#ifdef DEBUG_COMP
for(auto & e : perm){
    cout<<e<<" ";
}   
cout<<endl;
#endif
        t<<=1;
        if( t>=n ) break;
        // perm을 기반으로 group을 다시 지정한다
        vector<int> new_group(n+1,0);
        new_group[n] = -1;
        new_group[perm[0]] = 0;
        for(int i = 1; i < n; i++){
            if(c(perm[i-1], perm[i]))
                new_group[perm[i]] = new_group[perm[i-1]] + 1;
            else 
                new_group[perm[i]] = new_group[perm[i-1]];
        }
        group = new_group;
    }
    
    return;
}

int k;
string draft;
int l;
int res = 0;
void solve(){
    cin>>k;
    cin>>draft;
    l = draft.size();
    if( k == 1) {
        cout<<l<<endl;
        return ;
    }
    
    getSuffixArray(draft);
    
#ifdef DEBUG_SUFARR
    for(auto & s : perm){
        for(int i = s; i < l; i++){
            cout<<draft[i];
        }
        cout<<endl;
    }
#endif
    
    res = 0;
    for(int i = 0; i + k - 1 < l; i++){
        // 
        int s1 = perm[i];
        int s2 = perm[i + k - 1];
        int candid = 0;
        while( s1 < l && s2 < l && draft[s1] == draft[s2]){
            s1++; s2++; candid++;
        }
        res = max(res, candid);
    }
    cout<<res<<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int c;
    cin>>c;
    while(c--) solve();
    return 0;
}