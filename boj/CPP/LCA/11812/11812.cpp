#include <iostream>
#include <map>

#define endl '\n'
using namespace std;
typedef long long ll;

ll N,k;
int Q;


ll shortestPath(ll x, ll y){
    map<int,int> route;
    ll dist = 0;
    route[x] = dist;
    while (x){
        x = (x-1)/k;
        dist+=1;
        route[x] = dist;
    }
    
    dist = 0;
    if(route.find(y) != route.end()) return route[y];
    while (y){
        y = (y-1)/k;
        dist+=1;
        if(route.find(y) != route.end()){
            return dist + route[y];
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>k>>Q;
    ll x,y;
    while(Q--){
        cin>>x>>y;
        x--;y--;
        // printf("x, y : %lld, %lld \n", x,y);
        if(k==1)
            cout<<abs(x-y)<<endl;
        else
            cout<<shortestPath(x,y)<<endl;
    }
    return 0;
}