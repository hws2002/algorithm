#include <iostream>
#include <vector>

using namespace std;

using namespace std;

struct vector2{
public:
    double x,y;
    vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_){};
    
    vector2 operator * (const vector2 & rhs){
        return vector2(x * rhs.x, y * rhs.y);
    }
    
    vector2 operator + (const vector2 & rhs){
        return vector2(x + rhs.x, y + rhs.y);
    }
    
    vector2 operator - (const vector2 & rhs){
        return vector2(x - rhs.x, y - rhs.y);
    }
    
    double dot(const vector2 & rhs){
        return x * rhs.x + y * rhs.y;
    }    
    
    double cross(const vector2 & rhs){
        return x * rhs.y - y * rhs.x;
    }
};

double ccw(vector2 u, vector2 v){
    return u.cross(v);
}

double ccw(vector2 p, vector2 a, vector2 b){
    return ccw(a-p, b-p);
}

bool lineIntersect(vector2 p1, vector2 p2, vector2 p3, vector2 p4){
    return (ccw(p1,p2,p3) * ccw(p1,p2,p4) < 0) && 
           (ccw(p3,p4,p1) * ccw(p3,p4,p2) < 0);
}

int main(){
    vector2 p1,p2,p3,p4;
    cin>>p1.x>>p1.y;
    cin>>p2.x>>p2.y;
    cin>>p3.x>>p3.y;
    cin>>p4.x>>p4.y;
    if( lineIntersect(p1,p2,p3,p4) ) cout<<1<<endl;
    else cout<<0<<endl;
    
    return 0;
}