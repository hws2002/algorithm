#include <iostream>
#include <algorithm>
#include <vector>

// #define DEBUG_PRE
// #define DEBUG_CON_M
// #define DEBUG_BS

using namespace std;
typedef long long ll;

vector<int> preA;
vector<int> preB;

int main(){g
    int T;
    cin>>T;
    int n;
    
    cin>>n;
    preA.resize(n+1);
    preA[0] = 0;
    for(int i = 1 ; i <= n ; i++){
        cin>>preA[i];
        preA[i] += preA[i-1];
    }

    int M;
    cin>>M;
    preB.resize(M+1);
    preB[0] = 0;
    for(int i = 1; i <= M; i++){
        cin>>preB[i];
        preB[i] += preB[i-1];
    }
#ifdef DEBUG_PRE
for(auto a : preA){
    cout<<a<<" ";
}
cout<<endl;

for(auto b : preB){
    cout<<b<<" ";
}
cout<<endl;

#endif
    //solve
    ll res = 0;
    vector<int> m;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < i; j++){
            m.push_back(preA[i] - preA[j]);
        }
    }
#ifdef DEBUG_CON_M
for(auto elem : m){
    cout<<elem<<" ";    
}
cout<<endl;
#endif
    //sort
    std::sort(m.begin(), m.end());

#ifdef DEBUG_CON_M
for(auto elem : m){
    cout<<elem<<" ";    
}
cout<<endl;
#endif

    for(int i = 1; i <= M; i++){
        for(int j = 0; j < i; j++){
            int tofind = T - (preB[i] - preB[j]);
            if( tofind < m[0] || m.back() < tofind) continue;
            int lo_idx = lower_bound(m.begin(), m.end(), tofind) - m.begin();
#ifdef DEBUG_BS
cout<<"tofind, lo_idx : "<<tofind<<", "<<lo_idx;
#endif
            if( m[lo_idx] != tofind) continue;
            int up_idx = upper_bound(m.begin(), m.end(), tofind) - m.begin();

            res += (up_idx - lo_idx);
#ifdef DEBUG_BS
cout<<" up_idx, res  : "<<up_idx<<", "<<res<<endl;
#endif
        }
    }
    
    cout<<res<<endl;
    
    return 0;
}
