// graham scanm, rotating calipers

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <cmath>

#define EPSILON 1e-9
// #define DEBUG_GS
// #define DEBUG_RC
using namespace std;

struct vector2{

public:
    double x,y;
    double rex,rey;
    
    vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_), rex(1), rey(0){};
    
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

    double cross(const vector2 & rhs){
        return x*rhs.y - y*rhs.x;
    }

    double crossRe(const vector2 & rhs) const {
        return rex*rhs.rey - rey*rhs.rex;
    }

    double dot(const vector2 & rhs){
        return x*rhs.x + y*rhs.y;
    }
    
    double norm(){
        return hypot(x,y);
    }

};

typedef vector<vector2> polygon;

double ccw(vector2 u, vector2 v){
    return u.cross(v);
}   

int C;

vector<vector2> points;

bool compare( vector2 & u,  vector2 & v){
    //일직선상에 없다면
    if( abs( u.crossRe(v) ) > EPSILON ){
        return u.rey * v.rex < u.rex * v.rey;
    }
    
    //일직선상에 있다면
    return u < v;
}

//hull에 존재하는 점들중, 가장 먼 두 점의 거리를 반환한다.
double rotatingCalipers(polygon hull){
    double res = -1;
    int n = hull.size();
    int cidx = 1;
    for(int aidx = 0; aidx < n; aidx++){
        
        //move cidx
        while( cidx+1 != aidx && ccw( hull[(aidx+1)%n] - hull[aidx] , hull[(cidx+1)%n] - hull[cidx%n]) > 0){
#ifdef DEBUG_RC
printf("aidx, cidx : %d, %d \n", aidx, cidx);
#endif
            res = max( res, (hull[aidx]-hull[cidx%n]).norm() );
            cidx++;
        }
        
#ifdef DEBUG_RC
printf("aidx, cidx : %d, %d \n", aidx, cidx);
#endif

        //move aidx
        res = max(res, (hull[aidx] - hull[cidx % n]).norm());
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

    while(next < C){
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

int main(){
    cin>>C;
    double x,y;
    for(int i = 0 ; i < C; i++){
        cin>>x>>y;
        points.push_back(vector2(x,y));
    }
    
    polygon hull =  grahamScan();
    reverse(hull.begin()+1,hull.end());
#ifdef DEBUG_GS
    cout<<"convex hull size : "<<hull.size()<<endl;
    for(auto e : hull){
        cout<<"("<<e.x<<","<<e.y<<") ";
    }
    cout<<endl;
#endif
    
    printf("%.7f\n", rotatingCalipers(hull));

    return 0;
}