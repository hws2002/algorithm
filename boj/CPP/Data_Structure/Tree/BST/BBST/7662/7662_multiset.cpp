// multiset 해법

#include <iostream>
#include <set>
#define endl '\n'
using namespace std;

void solve(){
    multiset<int> ms;
    int k; // k <= 1'000'000
    cin>>k;
    while(k--){
        char op;
        int n;
        cin>>op>>n;
        if(op == 'I'){
            ms.insert(n);
        } else {
            if(ms.empty()) continue;
            if(n == 1){
                auto it = ms.find(*(--ms.end()));
                ms.erase(it);
            } else {
                auto it = ms.find(*(ms.begin()));
                ms.erase(it);
            }
        }
    }
    if(ms.empty()) cout<<"EMPTY"<<endl;
    else cout<<*(--ms.end())<<" "<<*(ms.begin())<<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}