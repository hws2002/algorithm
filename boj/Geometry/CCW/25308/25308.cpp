#include <iostream>
#include <vector>
#include <cmath>

// #define DEBUG_BF
// #define DEBUG_CCW
using namespace std;

int n = 8;
vector<double> A(8);
int res = 0;

double dx[8] = {0, sqrt(2), 2, sqrt(2), 0, -sqrt(2), -2, -sqrt(2)};
double dy[8] = {2, sqrt(2), 0, -sqrt(2), -2, -sqrt(2),0, sqrt(2)};

struct vector2{
public:
    double x,y;
    
    //con
    vector2(double x_, double y_):x(x_), y(y_){};
    
    vector2 operator-(vector2 & rhs) const {
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

bool ccw(vector2 a,  vector2 b,  vector2 c){
    if( ccw(a-b,c-b) >= 0) return true;
    return false;
}

int cnt = 0;

bool ccwAll(vector<int> & selected){
    // double ux = A[selected[0]]*dx[0];
    // double uy = A[selected[0]]*dy[0];
    double ux,uy;
    double vx = A[selected[0]]*dx[0];
    double vy = A[selected[0]]*dy[0];
    double wx = A[selected[1]]*dx[1];
    double wy = A[selected[1]]*dy[1];
    for(int i = 2; i < n+2;i++){
        ux = vx; uy = vy; vx = wx; vy = wy;
        wx = A[selected[i%8]]*dx[i%8];
        wy = A[selected[i%8]]*dy[i%8];
#ifdef DEBUG_CCW
if(cnt < 4)
printf("a : (%f, %f) \n b : (%f, %f) \n c : (%f, %f) \n", ux,uy,vx,vy,wx,wy);
#endif  
        if(!ccw(vector2(ux,uy), 
                vector2(vx,vy), 
                vector2(wx,wy) )) return false;

    }
    return true;
}


void nchooser(vector<int> & selected, vector<bool> & visit,const int here, const int tochoose){
    if(tochoose <= 0){
#ifdef DEBUG_BF
cnt++;  
if(cnt< 4){
    for(auto e: selected){
        cout<<e<<" ";
    }
    cout<<endl;
}
#endif
        //try ccw
        if(ccwAll(selected)) res++;
        return ;
    }
    
    for(int i = 0; i < 8; i++){
        if(!visit[i]){
            selected.push_back(i);
            visit[i] = true;
            nchooser(selected, visit, i, tochoose-1);
            selected.pop_back();
            visit[i] = false;
        }
    }
}

int main(){   
    for(int i = 0 ; i < n; i++){
        cin>>A[i];
    }
    
    vector<int> selected;
    vector<bool> visit(8,false);
    nchooser(selected, visit, 0,8);
    cout<<res<<endl;
    return 0;
}
