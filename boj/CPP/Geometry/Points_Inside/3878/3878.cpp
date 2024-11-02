#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>

#define PI (4*atan(1))
#define EPSILON 1e-9
#define endl '\n'
// #define DEBUG_GS
// #define DEBUG_SG
using namespace std;
typedef long long ll;

double L;

struct vector2{
public:
    double x,y,rex,rey;
    vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_), rex(1), rey(0){};
    
    bool operator < (const vector2 & rhs) const{
        if( y == rhs.y) return x < rhs.x;
        return y < rhs.y;
    }
    
    vector2 operator - (const vector2 & rhs){
        return vector2(x - rhs.x, y - rhs.y);
    }
    
    vector2 operator + (const vector2 & rhs){
        return vector2(x + rhs.x, y + rhs.y);
    }
    
    double norm(){
        return hypot(x,y); 
    }
    
    double dot(const vector2 & rhs){
        return x * rhs.x + y * rhs.y;
    }
    
    double cross(const vector2 & rhs){
        return x*rhs.y - y*rhs.x;
    }
    
    double crossRe(const vector2 & rhs) const {
        return rex*rhs.rey - rey*rhs.rex;
    }
};

double ccw(vector2 u, vector2 v){
    return u.cross(v);
}

double ccw(vector2 p, vector2 a, vector2 b){
    return ccw(a-p, b-p);
}

typedef vector<vector2> polygon;


bool compare(const vector2 & a, const vector2 & b){
    //일직선상에 있다면
    if( abs( a.crossRe(b) - 0) > EPSILON){
        return a.rey * b.rex < a.rex * b.rey;
    }
    
    return a < b;
}

int n,m;
vector<vector2> pointsb, pointsw;

polygon grahamScan(vector<vector2> & points, int psize){
	if(psize <= 2) {
		return points;
	}
	
    stack<int> st;
    
    sort(points.begin(), points.end(), compare);
    vector2 f = points[0];
    
    for(int i = 1 ; i < points.size(); i++){
        points[i].rex = points[i].x - f.x;
        points[i].rey = points[i].y - f.y;
    }
    
    sort(points.begin()+1, points.end(), compare);
    
    st.push(0);
    st.push(1);
    
    int first,second,next = 2;
    
    while(next < psize){
        while(st.size() >= 2){
            second = st.top(); st.pop();
            first = st.top();
            if( ccw( points[second] - points[first], points[next] - points[second] ) > 0){
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
    
    reverse(hull.begin() ,hull.end());
    return hull;
}

bool inBoundary(vector2 p, vector2 a, vector2 b){
    if( b < a) swap(a,b);
    return ( a < p && p < b);
}

bool onSegment(vector2 p, vector2 a, vector2 b){
    if( ccw(p,a,b) == 0 && inBoundary(p,a,b) ) return true;
    return false;
}

bool sign(double num){
    return num > 0 ? true : false;
}

bool decide(vector<vector2> & chb, vector<vector2>& chw){
    for(int i = 0; i < chb.size(); i++){ // 이자리에 size가 2보다 작거나 같은 ch
            if( onSegment(chb[i], chw[0],chw[1])) {
    #ifdef DEBUG_SG
    printf("returning false with onsegment chb[%d], chw[%d], chw[%d] \n", i, 0, 1);
    #endif
                return false;
            }
            
            bool initial_sign = sign( ccw( chb[i], chw[0], chw[1]) );
            bool inside = true;
            int njdx;
            for(int j = 1 ; j < chw.size(); j++){
                njdx = (j+1)%chw.size();
                if( onSegment(chb[i],chw[j],chw[njdx]) ) {
    #ifdef DEBUG_SG
    printf("returning false with onsegment chb[%d], chw[%d], chw[%d] \n", i, j, njdx);
    #endif
                    return false;
                }
                if( initial_sign != sign( ccw( chb[i], chw[j], chw[njdx]) ) ) {
    #ifdef DEBUG_SG
    printf("chb[%d] is outside of chw (checked with chw[%d], chw[%d]) \n", i, j, njdx);
    #endif 
                    // 구역 밖에 있다는것이 확정된 순간, 나머지 점들은 확인할 필요가 없다
                    inside = false;
                    break;
                }
                if( !inside ) break;
            }
            //한 점이라도 chw안에 있다면 구역을 나눌 수 없다
            if( inside ) {
    #ifdef DEBUG_SG
    printf("returning false with point chb[%d] \n", i);
    #endif
                return false;
            }
        }
        // 모든 점이 chw밖에 있다면 구역을 나눌 수 있다.
        return true;
}

bool Segregatable(polygon & chb, polygon & chw){
    
    // chb에 점이 하나, chw에 점이 하나있는 경우
    if( chb.size() <= 1 && chw.size() <= 1) return true;
    
    // chb에 점이 하나, chw에 점이 두개 이상 있는 경우
    if( chb.size() == 1 && chw.size() >= 2){
        if( onSegment( chb[0], chw[0], chw[1]) ) return false;
        bool initial_sign = sign( ccw(chb[0], chw[0],chw[1]));
        for(int widx = 1; widx < chw.size(); widx++){
            if( onSegment( chb[0], chw[widx], chw[(widx+1) % chw.size()] )) return false;
            if( initial_sign != sign( ccw( chb[0], chw[widx], chw[(widx+1)%chw.size()]))) return true;
        }
        return false;
    }
    
    // chb에 점이 두개 이상, chw에 점이 하나 있는 경우
    if ( chb.size() >= 2 && chw.size() <= 1){
        if( onSegment( chw[0], chb[0], chb[1]) ) return false;
            bool initial_sign = sign( ccw(chw[0], chb[0], chb[1]));
            for(int widx = 1; widx < chb.size(); widx++){
                if( onSegment( chw[0], chb[widx], chb[(widx+1) % chb.size()] )) return false;
                if( initial_sign != sign( ccw( chw[0], chb[widx], chb[(widx+1)%chb.size()]))) return true;
            }
            return false;
    }
    
    // chb에 점이 두개, chw에 점이 두개인 경우
    if( chb.size() == 2 && chw.size() == 2) {
        if ( onSegment( chb[0], chw[0], chw[1]) ) return false;
        if ( onSegment( chb[1], chw[0], chw[1]) ) return false;
        if ( onSegment( chw[0], chb[0], chb[1]) ) return false;
        if ( onSegment( chw[1], chb[0], chb[1]) ) return false;
        return !(( ccw(chb[0], chb[1], chw[0]) * ccw(chb[0], chb[1], chw[1]) < 0 ) &&
                ( ccw(chw[0], chw[1], chb[0]) * ccw(chw[0], chw[1], chb[1]) < 0) );
    }

    // 나머지 경우
    return  decide(chw,chb) && decide(chb,chw);
}

void solve(){
    
    cin>>n>>m;
	
    pointsb.resize(n); 
	pointsw.resize(m);
	
    for(int i = 0; i < n; i++){
        cin>>pointsb[i].x>>pointsb[i].y;
    }

    for(int i = 0; i < m; i++){
        cin>>pointsw[i].x>>pointsw[i].y;    
    }
    
    polygon chb = grahamScan(pointsb,n);
    polygon chw = grahamScan(pointsw,m);

#ifdef DEBUG_GS
for(auto v2 : chb){
    printf("(%f,%f) ", v2.x, v2.y);
}
cout<<endl;
#endif

#ifdef DEBUG_GS
for(auto v2 : chw){
    printf("(%f,%f) ", v2.x, v2.y);
}
cout<<endl;
#endif

    if( Segregatable(chb, chw)) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
    
    //reset
    pointsb.clear();
    pointsw.clear();
}


int T;
int main(){
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}