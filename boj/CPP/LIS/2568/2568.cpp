#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 100'000
#define all(v) v.begin(), v.end()
#define endl '\n'
// #define DEBUG_B
// #define DEBUG_LIS
using namespace std;
typedef pair<int,int> pii;
int N;

vector<pii> a;
vector<pii> b;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N;
    a.resize(N);
    for(int i = 0; i < N;i++){
        cin>>a[i].first>>a[i].second;
    }
    
    sort(all(a), [](const pii & p1, const pii & p2){
            if( p1.first == p2.first) return p1.second < p2.second;
            return p1.first < p2.first;
        });
    
    b.resize(N);
    for(int i = 0;  i < N; i++){
        b[i] = {a[i].second, i};
    }
    
    sort(all(b), [](const pii & p1, const pii & p2){
            if( p1.first == p2.first) return p1.second < p2.second;
            return p1.first < p2.first;
        });
    
#ifdef DEBUG_B
for(auto e :b){
    cout<<e.second<<" ";    
}
cout<<endl;
#endif
    //LIS
    vector<pair<int,int>> lis;
    vector<int> choice(N);
    for(int i = 0 ; i < N; i++){
        int v = b[i].second;
        if(lis.empty()){
            lis.push_back({v,i});
            choice[i] = i;
        } else if(  v > lis.back().first) {
            choice[i] = lis.back().second;
            lis.push_back({v,i});
        }
        else {
            auto it = lower_bound(all(lis), make_pair(v,-1), [](const pair<int,int> & v, const pair<int,int> & p){
                    return v.first < p.first;
                }) - lis.begin();
            lis[it] = {v,i};
            if(it == 0)
                choice[i] = i;
            else 
                choice[i] = lis[it-1].second;
        }
    }
    
    // recon
#ifdef DEBUG_LIS
for(int i = 0; i < lis.size(); i++){
    printf("(%d, %d) ", lis[i].first, lis[i].second);
}
cout<<endl;
#endif
    int ret = N;
    // 제거해야 하는 전깃줄의 위치의 번호 : a[b[i].second].first;
    int it = lis.back().second;
    int previt = -1;
    vector<bool> left(N, false);
    while( it != previt){
        // ret.push_back(a[b[it].second].first);
        // cout<<a[b[it].second].first<<endl;
        left[ b[it].second ] = true;
        ret--;
        previt = it;
        it = choice[it];
    }
    
    cout<<ret<<endl;    
    for(int i = 0; i < N; i++){
        if(!left[i]) cout<<a[i].first<<endl;
    }
    
    return 0;
}