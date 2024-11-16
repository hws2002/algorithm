#include <iostream>
#include <vector>
#include <algorithm>


#define endl '\n'
using namespace std;

int N;
vector<int> R;
// multiset<int> K; // 오름차순(default)
vector<int> K;

void solve(){
    cin>>N;
    R.resize(N); K.resize(N);
    for(int i = 0; i < N; i++){
        cin>>R[i];
    }
    
    // int temp;
    for(int i = 0 ; i < N; i++){
        // cin>>temp;
        // K.insert(temp);
        cin>>K[i];
    }
    
    sort(R.begin(), R.end());
    sort(K.begin(), K.end());
    vector<int>::iterator it = K.begin();
    int ret = 0;
    for(const auto r : R){
        if( r > K.back()) break;
        it = lower_bound(it, K.end(), r);
        it++;
		ret++;
		if( it == K.end()) break;
    }
    cout<<ret<<endl;
}

int main(){
    int c;
    cin>>c;
    while(c--) solve();
    return 0;
}