#include <iostream>
#include <vector>

using namespace std;
int remainders[42] = {0};

int main(){
    
    vector<int> A(10);
    for(int i = 0; i < 10; i++){
        cin>>A[i];
        A[i] %= 42;
    }
    
    int res= 0;
    
    std::fill(remainders, remainders + 42, 0);
    
    for(int i = 0; i < 10; i++){
        remainders[A[i]]++;
    }
    
    
    for(int i = 0; i < 42; i++){
        if(remainders[i]) res++;
    }
    
    cout<<res<<endl;
    return 0;
}