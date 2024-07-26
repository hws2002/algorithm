#include <iostream>
#include <cmath>

#define EPSILON 1e-9
using namespace std;
typedef long double ld;

struct vector2{
public:
    ld x,y;
    //con
    vector2(ld x_, ld y_): x(x_), y(y_){};
    vector2():x(0),y(0){};
    
    // <
    bool operator<(const vector2 & rhs) const{
        return (x == rhs.x) ? y < rhs.y : x < rhs.x;
    }
    
    // ==
    bool operator==(const vector2 & rhs) const{
        return (fabs(x-rhs.x) < EPSILON) && fabs(y - rhs.y) < EPSILON;
    }
    
    // +
    vector2 operator+(const vector2 & rhs) const{
        return vector2( x + rhs.x, y + rhs.y);
    }
    
    // - 
    vector2 operator-(const vector2 & rhs) const {
        return vector2(x - rhs.x, y - rhs.y);
    }
    
    //*
    vector2 operator*(const ld v) const{
        return vector2(x*v, y*v);    
    }
    
    //cross
    ld cross(const vector2 & rhs){
        return x*rhs.y - y*rhs.x;
    }
    
};

ld ccw(vector2 a, vector2 b){
    return a.cross(b);
}

ld ccw(vector2 a, vector2 b, vector2 c){
    return ccw(b-a,c-a);
}

// a + (b-a)p = c + (d-c)q
// a + mp = c + nq
bool lineIntersect(vector2 a, vector2 b, vector2 c, vector2 d, vector2 & p){

    vector2 m = b - a; vector2 n = d - c;
    ld det = n.cross(m);
    
    if(fabs(det) < EPSILON) return false;
    // 평행 하지않다면
    p = a + m*( (n.cross(c-a)) / det);
    return true;
}

bool inBoundingRectangle(const vector2 & p, vector2 a, vector2 b){
    if(b < a) swap(a,b);
    return p == a || p == b || (a < p && p < b);
}

bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2 & p){
    if( b < a) swap(a, b);
    if( d < c) swap(c, d);
    
    if(ccw(a,b,c) != 0 || b < c || d < a) return false;
    
    if(a < c) p = c;
    else p = a;
    return true;
}

// 선분 ab와 선분 cd가 서로 교차하는가? (교차한다면 교차점까지 구한다)
bool segmentIntersect(vector2 a, vector2 b, vector2 c, vector2 d, vector2 & p){
    // if( b < a) swap(a, b);
    // if( d < c) swap(c, d);
    
    if(!lineIntersect(a,b,c,d,p))
        return parallelSegments(a,b,c,d,p);
    
    return inBoundingRectangle(p,a,b) && inBoundingRectangle(p,c,d);    
}
    

ld norm(vector2 a, vector2 b){
    return hypot(a.x - b.x, a.y - b.y);
}

int main(){
    ld x_1,y_1,x_2,y_2,x_3,y_3,x_4,y_4;
    cin>>x_1>>y_1>>x_2>>y_2;
    cin>>x_3>>y_3>>x_4>>y_4;
    vector2 p;

    vector2 a = vector2(x_1,y_1);
    vector2 b = vector2(x_2,y_2);
    vector2 c = vector2(x_3,y_3);
    vector2 d = vector2(x_4,y_4);
    if( b < a) swap(a, b);
    if( d < c) swap(c, d);
    
    if( (a == b) && ( c == d)){
        if(a == c) {
            cout<<1<<endl;
            cout<<a.x<<" "<<a.y<<endl;
        } else  cout<<0<<endl;
    } else if ( (a == b) && !(c == d) ){
        if( fabs( norm(a,c) + norm(a,d) - norm(c,d) ) < EPSILON){
            cout<<1<<endl;
            cout<<a.x<<" "<<a.y<<endl;
        } else cout<<0<<endl;
    } else if ( !(a==b) && (c==d)){ 
        if( fabs( norm(c,a) + norm(c,b) - norm(a,b) ) < EPSILON ){
            cout<<1<<endl;
            cout<<c.x<<" "<<c.y<<endl;
        } else cout<<0<<endl;
    } else {
        if(segmentIntersect(a, b, c, d, p)){
            cout<<1<<endl;
            // 한 점에서 교차하지 않는 경우 출력하지 않는다
            if( !(ccw(a,b,c) == 0 && ccw(a,b,d) == 0 && (a == c|| b ==d ||(a < c && c < b)||(a < d && d < b) || (c < a && a < d) || (c <b && b < d))) ) 
                printf("%.10Lf %.10Lf\n",p.x,p.y);
                // cout<<p.x<<" "<<p.y<<endl;
        } else 
            cout<<0<<endl;
    }
    return 0;
}