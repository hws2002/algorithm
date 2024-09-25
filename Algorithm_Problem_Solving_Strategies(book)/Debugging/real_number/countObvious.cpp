#include <iostream>
using namespace std;
int countObvious(int n){
    int same = 0;
    for (int x = 1; x<=n; ++x){
        double y = 1.0/x;
        if (y*x == 1.0)
            ++same;
    }
    return same;
}
int main(){
    cout<<countObvious(50)<<endl;
    return 0;
}