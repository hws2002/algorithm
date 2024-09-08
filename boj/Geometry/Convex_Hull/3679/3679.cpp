// graham scan
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <cmath>

#define endl '\n'
using namespace std;
typedef long long ll;

struct vector2{

public:
    ll x,y;
    ll rex,rey;
    
    vector2(ll x_ = 0, ll y_ = 0) : x(x_), y(y_), rex(1), rey(0){};
    
    vector2 operator + (const vector2 & rhs){
        return vector2(x + rhs.x, y + rhs.y);
    }
    
    vector2 operator - (const vector2 & rhs){
        return vector2( x - rhs.x, y - rhs.y);
    }
    
    bool operator == (const vector2 & rhs){
        return x == rhs.x && y == rhs.y;
    }
    
    bool operator < ( vector2 & rhs) const {
        if( y == rhs.y) return x < rhs.x;
        return y < rhs.y;
    }

    ll cross(const vector2 & rhs){
        return x*rhs.y - y*rhs.x;
    }

    ll crossRe(const vector2 & rhs) const {
        return rex*rhs.rey - rey*rhs.rex;
    }
};

ll ccw(vector2 u, vector2 v){
    return u.cross(v);
}

ll ccw(vector2 p, vector2 a, vector2 b){
    return ccw(a-p, b-p);
}

int n,c;
vector< pair<vector2,int> > points;

bool compare( pair<vector2,int> & p1,  pair<vector2,int> & p2){
    auto u = p1.first; auto v = p2.first;
    
    //일직선상에 없다면
    if( u.crossRe(v) != 0 ){
        return u.rey * v.rex < u.rex * v.rey;
    }
    
    //일직선상에 있다면
    return u < v;
}

void solve(){
    cin>>n;
    ll x,y;
    
    points.resize(n);
    for(int i = 0 ; i < n; i++){
        cin>>x>>y;
        points[i] = {vector2(x,y), i};
    }

    // find left bottom point
    sort( points.begin(), points.end(), compare);

    vector2 lb = points[0].first;

    for(int i = 1; i < points.size(); i++){
        points[i].first.rex = points[i].first.x - lb.x;
        points[i].first.rey = points[i].first.y - lb.y;
    }

    sort( points.begin() + 1, points.end(), compare);
    
    auto last = points.back();
    int numponline = 1;
    while( ccw(lb, last.first, (points.end()-numponline-1)->first) == 0){
        numponline++;
    }
    reverse( points.end()-numponline, points.end());
    
    for(auto pvi : points) cout<<pvi.second<<" ";
    cout<<endl;

    //reset
    points.clear();
}

int main(){
    cin>>c;
    while(c--){
        solve();
    }
    return 0;
}