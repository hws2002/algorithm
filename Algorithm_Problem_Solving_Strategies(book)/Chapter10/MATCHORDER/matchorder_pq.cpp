#include <iostream>
#include <vector>
#include <algorithm>
#include <set>


#define endl '\n'
using namespace std;

int N;
vector<int> R;
multiset<int> K; // 오름차순(default)

void solve(){
    cin>>N;
    R.resize(N);
    for(int i = 0; i < N; i++){
        cin>>R[i];
    }
    
    int temp;
    for(int i = 0 ; i < N; i++){
        cin>>temp;
        K.insert(temp);
    }
    
    int ret = 0;
    for(auto r : R){
        if( r > *K.rbegin()){
            K.erase(K.begin());
        } else {
            K.erase(K.lower_bound(r));
            ret++;
        }
    }
    cout<<ret<<endl;
}

int main(){
    int c;
    cin>>c;
    while(c--) solve();
    return 0;
}