#include <iostream>
using namespace std;

bool absoluteEqual(double a, double b){
    return fabs(a-b) < 1e-10;
}
int countObvious(int n){
    int same = 0;
    for (int x = 1; x<=n; ++x){
        double y = 1.0/x;
        if (absoluteEqual(x*y, 1.0))
            ++same;
    }
    return same;
}
int main(){
    cout<<countObvious(50)<<endl;
    return 0;
}