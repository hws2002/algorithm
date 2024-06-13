#include <iostream>
#include <cmath>

#define tolerance (1.0e-8)
#define dist(a,b,c,d) ( sqrt( (a-c)*(a-c) + (b-d)*(b-d) ) )
using namespace std;

double x1,y_1,x2,y2;
double x3,y3,x4,y4;

bool EqualDouble(double x, double y){
    if( fabs(x-y) <= tolerance) return true;
    else return false;
}

int interSect2(){
    if( x1 == x2 && x3 == x4){ // 두선이 모두 y축과 평행할 경우 
        if(x1 != x3) return 0; // x 좌표가 다르다면 교차할 수 없다
        if( y4 >= y_1 ) return 1; // y4 의 위치가 y1의 위치보다 높거나 같다면 교차한다
        return 0;
    } else if (x1 == x2 && x3 != x4){ // L1만 y축과 평행할 경우
        double k2 = (y4-y3) / (x4-x3);
        double x0 = x1;
        double y0 = k2*(x0-x3) + y3;
        if( ( y_1<= y0 && y0 <= y2) && ( EqualDouble( dist(x3,y3,x4,y4) , (dist(x3,y3,x0,y0) + dist(x4,y4,x0,y0) ) ) ) )return 1;
        else return 0;
    } else if (x1 != x2 && x3 == x4){ // L2만 y축과 평행할 경우
        double k1 = (y2-y_1) / (x2-x1);
        double x0 = x3;
        double y0 = k1*(x0-x1) + y_1;
        if( (y3 <= y0 && y0 <= y4) && ( EqualDouble( dist(x1,y_1,x2,y2) , ( dist(x1,y_1,x0,y0) + dist(x2,y2,x0,y0) ) ) ) ) return 1;
        else return 0;
    } else { // 일반적인 경우
        double k1 = (y2-y_1) / (x2-x1);
        double k2 = (y4-y3) / (x4-x3);
        
        if(k1 == 0 && k2 == 0){
            //만약 둘다 0일 경우,
            if(y2 == y4){
                if(x2 < x1) swap(x1,x2);
                if( (x1 <= x3 && x3 <= x2) || ( x1 <= x4 && x4 <= x2) ) return 1;
                else return 0;
            } else
                return 0;
        }
        
        // L1과 L2가 평행할경우
        if(k1 == k2){
            // (x4,y4)가 L1위에 있는지 판단한다.
            if( EqualDouble( dist(x1,y_1,x2,y2) , ( dist(x1,y_1,x4,y4) + dist(x2,y2,x4,y4) ) ) ) return 1;
            else return 0;
        }
        
        // (x0,y0)을 구한다
        double x0 = ( y3 - y_1 + k1*x1 - k2*x3 ) / (k1-k2);
        double y0 = k1*x0 + y_1 -k1*x1;
        // (x0,y0)이 L1, L2 위에 있는지 판단한다  
        if( EqualDouble( dist(x1,y_1,x2,y2) , ( dist(x1,y_1,x0,y0) + dist(x2,y2,x0,y0) ) ) && 
            EqualDouble( dist(x3,y3,x4,y4) , ( dist(x3,y3,x0,y0) + dist(x4,y4,x0,y0) ) ) ) return 1;
        else return 0;
    }
}


int main(){
    cin>>x1>>y_1>>x2>>y2;
    if( y2 < y_1) { swap(x1,x2); swap(y_1,y2);}
    cin>>x3>>y3>>x4>>y4;
    if( y4 < y3) { swap(x3,x4); swap(y3,y4);}
    if( y2 < y4) { swap(x1,x3); swap(x2, x4); swap(y_1, y3); swap(y2,y4);}
    cout<<interSect2()<<endl;
}
