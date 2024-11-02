// graham scan

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

#define EPSILON 1e-9
// #define DEBUG_GS
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
        if( x == rhs.x) return y < rhs.y;
        return x < rhs.x;
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

};

typedef vector<vector2> polygon;

double ccw(vector2 u, vector2 v){
    return u.cross(v);
}   

int N;

vector<vector2> points;

bool compare( vector2 & u,  vector2 & v){
    //일직선상에 없다면
    if( abs( u.crossRe(v) ) > EPSILON ){
        return u.rey * v.rex < u.rex * v.rey;
    }
    
    //일직선상에 있다면
    return u < v;
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
    
    while(next < N){
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
    cin>>N;
    double x,y;
    for(int i = 0 ; i < N; i++){
        cin>>x>>y;
        points.push_back(vector2(x,y));
    }
    
    polygon hull =  grahamScan();
    
    cout<<hull.size()<<endl;

#ifdef DEBUG_GS
    for(auto e : hull){
        cout<<"("<<e.x<<","<<e.y<<") ";
    }
#endif
    return 0;
}