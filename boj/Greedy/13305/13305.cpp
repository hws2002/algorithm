#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 100'000
using namespace std;
typedef long long ll;

int N;
ll dist[MAX_N+1] = {0};
vector< pair<ll,int> > Station;

bool compare(const pair<ll,int> & a, const pair<ll,int> & b){
    if(a.first == b.first) return a.second < b.second;
    return a.first < b.first;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    cin>>N;
    int price;
    
    /*
    0 1 2 3 4
    0 2 5 6 6
    */
    for(int i = 1; i <= N-1; i++){
        cin>>dist[i];
        dist[i] += dist[i-1];
    }
    dist[N] = dist[N-1];
    
    /*
    0 1 2
    5 2 4 
    */
    for(int i = 0 ; i < N-1; i++){
        cin>>price;
        Station.push_back({price,i});
    }
    
    cin>>price; //useless
    
    std::sort(Station.begin(), Station.end(), compare);
    
    ll res = 0;
    int midx = N;
    int i = 0;
    while(true){
        while(i < N-1 && Station[i].second >= midx) i++;
        if( i >= N-1) break;
        ll cheapest_price = Station[i].first;
        int idx = Station[i].second;
        res += cheapest_price * (dist[midx] - dist[idx]);
        midx = idx;
        if(midx <= 0) break;
    }    
    
    cout<<res<<endl;
    
    return 0;
}