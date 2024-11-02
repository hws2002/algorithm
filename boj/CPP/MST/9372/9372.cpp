#include <iostream>

#define endl '\n'
using namespace std;

int N,M;
void solve(){
    cin>>N>>M;
    int a, b;
    while(M--){
        cin>>a>>b;
    }
    cout<<N-1<<endl;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}