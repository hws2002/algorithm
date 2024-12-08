// 14:46 - 

#include <iostream>
#include <vector>
#include <algorithm>


#define endl '\n'
using namespace std;

int n;

vector<int> Prefix;
vector<int> Infix;

vector<int> PI2P(int ps, int pe, int is, int ie){
// printf("PI2P(%d,%d,%d,%d) \n", ps, pe, is, ie);
// for(int i = ps; i < pe; i++){
//     cout<<Prefix[i]<<" ";
// }
//     cout<<endl;
// for(int i = is; i < ie; i++){
//     cout<<Infix[i]<<" ";
// }
//     cout<<endl;
    vector<int> Post;
    if(pe <= ps || ie <= is) return Post;
    int M = Prefix[ps];
    int idx = -1;

    for(int i = is; i < ie; i++){
        if(Infix[i] == M){
            idx = i-is;
            break;
        }
    }
    
    // cout<<"M, idx : "<<M<<" "<<idx<<endl;
    auto L = PI2P(ps+1    , ps+1+idx,       is, is+idx);
    auto R = PI2P(ps+1+idx,       pe, is+idx+1,     ie);
    Post.insert(Post.end(), L.begin(), L.end());
    Post.insert(Post.end(), R.begin(), R.end());
    Post.push_back(M);
    return Post;
}


void solve(){
    cin>>n;
    Prefix.resize(n,0);
    for(int i = 0 ; i < n; i++){
        cin>>Prefix[i];
    }
    
    Infix.resize(n,0);
    for(int i = 0; i < n; i++){
        cin>>Infix[i];  
    }
    
    auto res = PI2P(0,n,0,n);
    for(const auto & e : res){
        cout<<e<<" ";
    }
    cout<<endl;
}

int main(){
    int c;
    cin>>c;
    while(c--) solve();
    return 0;
}