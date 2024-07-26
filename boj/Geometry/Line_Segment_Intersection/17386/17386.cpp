#include <iostream>

using namespace std;

struct vector2{
public:
    double x,y;
    
    //con
    vector2(double x_, double y_): x(x_), y(y_){};
    
    // - 
    vector2 operator-(const vector2 & rhs) const {
        return vector2(x - rhs.x, y - rhs.y);
    }
    
    //cross
    double cross(const vector2 & rhs){
        return x*rhs.y - y*rhs.x;
    }
};

double ccw(vector2 a, vector2 b){
    return a.cross(b);
}

double ccw(vector2 a, vector2 b, vector2 c){
    return ccw(b-a,c-a);
}

// 선분 ab와 선분 cd가 서로 교차하는가?
// 세 점이 일직선 위에 있는 경우는 제외한다.
bool segmentIntersect(vector2 a, vector2 b, vector2 c, vector2 d){
    double ab = ccw(a,b,c) * ccw(a,b,d);
    double cd = ccw(c,d,a) * ccw(c,d,b);
    return ab < 0 && cd < 0; // 세 점이 일직선 위에 있는 경우가 업으므로 <=가 아닌 < 만써도 충분하다.
}


int main(){
    double x_1,y_1,x_2,y_2,x_3,y_3,x_4,y_4;
    cin>>x_1>>y_1>>x_2>>y_2;
    cin>>x_3>>y_3>>x_4>>y_4;
    cout<<segmentIntersect(vector2(x_1,y_1), vector2(x_2,y_2), vector2(x_3, y_3), vector2(x_4,y_4))<<endl;
    return 0;
}