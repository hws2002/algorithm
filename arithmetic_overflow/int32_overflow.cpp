#include <iostream>
using namespace std;

int main(){
    int a = 2147483647; // 2^31 - 1
    int overflow = 1<<31;
    int overflow2 = 4294967296;
    cout<<"Actuall number : 2147483647. Output : "<<a<<endl;
    cout<<"Actuall number : 2147483648. Output : "<<overflow<<endl;
    cout<<"Actuall number : 4294967296. Output : "<<overflow2<<endl;
}