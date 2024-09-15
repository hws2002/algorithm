// graham scanm, rotating calipers

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <cmath>

#define EPSILON 1e-9
// #define DEBUG_GS
// #define DEBUG_RC
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

    ll dot(const vector2 & rhs){
        return x*rhs.x + y*rhs.y;
    }
    
    ll norm(){
        return x*x + y*y;
    }

};

typedef vector<vector2> polygon;


ll ccw(vector2 u, vector2 v){
    return u.cross(v);
}   

int n;

vector<vector2> points;

bool compare( vector2 & u,  vector2 & v){
    //일직선상에 없다면
    if( abs( u.crossRe(v) ) > EPSILON ){
        return u.rey * v.rex < u.rex * v.rey;
    }
    
    //일직선상에 있다면
    return u < v;
}

vector2 a,b;

//hull에 존재하는 점들중, 가장 먼 두 점의 거리를 반환한다.
double rotatingCalipers(polygon hull){
    ll res = -1;
    int n = hull.size();
    int cidx = 1;
    for(int aidx = 0; aidx < n; aidx++){
        
        //move cidx
        while( cidx+1 != aidx && ccw( hull[(aidx+1)%n] - hull[aidx] , hull[(cidx+1)%n] - hull[cidx%n]) > 0){
#ifdef DEBUG_RC
printf("aidx, cidx : %d, %d \n", aidx, cidx);
#endif
            if( res < (hull[aidx] - hull[cidx%n]).norm() ){
                res = (hull[aidx] - hull[cidx%n]).norm();
                a = hull[aidx];
                b = hull[cidx];
            }
            cidx++;
        }
        
#ifdef DEBUG_RC
printf("aidx, cidx : %d, %d \n", aidx, cidx);
#endif

        //move aidx
        if( res < (hull[aidx] - hull[cidx%n]).norm() ){
            res = (hull[aidx] - hull[cidx%n]).norm();
            a = hull[aidx];
            b = hull[cidx];
        }
    }
    return res;
}

polygon grahamScan(){
    stack<int> st;

    // find left bottom point
    sort( points.begin(), points.end(), compare);

    vector2 f = points[0];
#ifdef DEBUG_GS
cout<<"first points of hull : ("<<f.x<<","<<f.y<<")"<<endl;
#endif

    for(int i = 1; i < points.size(); i++){
        points[i].rex = points[i].x - f.x;
        points[i].rey = points[i].y - f.y;
    }
    
    sort( points.begin() + 1, points.end(),compare);

#ifdef DEBUG_GS
    for(auto e : points){
        cout<<"("<<e.x<<","<<e.y<<") ";
    }
    cout<<endl;
#endif

    st.push(0);
    st.push(1);

    int first, second, next = 2;

    while(next < n){
        while( st.size() >= 2 ){
            second = st.top(); st.pop();
            first = st.top();
            if( ccw( points[second] - points[first], points[next] - points[second]) > 0){
                st.push(second);
                break;
            }
        }
        st.push(next++);
    }

    polygon hull;
    while(!st.empty()){
        hull.push_back(points[st.top()]);
        st.pop();
    }
    return hull;
}

int T;

void solve(){

    cin>>n;
    ll x,y;
    for(int i = 0 ; i < n; i++){
        cin>>x>>y;
        points.push_back(vector2(x,y));
    }

    polygon hull = grahamScan();
    reverse(hull.begin()+1,hull.end());

#ifdef DEBUG_GS
    cout<<"convex hull size : "<<hull.size()<<endl;
    for(auto e : hull){
        cout<<"("<<e.x<<","<<e.y<<") ";
    }
    cout<<endl;
#endif

    rotatingCalipers(hull);
    cout<<a.x<<" "<<a.y<<" "<<b.x<<" "<<b.y<<endl;
    
    //reset
    points.clear();
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}