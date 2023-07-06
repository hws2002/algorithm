#include <iostream>
#include <cmath>
using namespace std;

// 1<= N <=1e7
void factorize(int N){
    int n = N;
    for(int i=2; i <= sqrt(n); i++){
        if( N <= 1) return;
        while(N%i==0){
            cout<<i<<endl;
            N/=i;
        }
    }
    if(N!=1) cout<<N<<endl; // prime number
};
int main(){
    int N;
    cin>>N;
    factorize(N);
    return 0;
}