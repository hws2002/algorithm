#include <iostream>
using namespace std;

int gcd(int a, int b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}
int lcm(int a, int b){
    return (a*b)/gcd(a,b);
}

int main(){
    int a = 50000;
    int b = 100000;
    cout<<"GCD of "<<a<<" and "<<b<<" is "<<gcd(a,b)<<endl;
    cout<<"LCM of "<<a<<" and "<<b<<" is "<<lcm(a,b)<<endl;
    return 0;
}