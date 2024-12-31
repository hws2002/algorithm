#include <iostream>
#include <cstring>
#include <vector>

// #define DEBUG_MANACHER
using namespace std;
typedef long long ll;

ll ret = 0;

vector<int> manacher(const string & s){
    int n = s.length();
    vector<int> A(n,0);
    int p = 0; int r = 0;
    for(int i = 0; i < n; i++){
        if( r < i){
            A[i] = 0; 
        } else { // r >= i
            A[i] = min(r-i, A[2*p - i]);
        }
        
        while( i - A[i] - 1 >=0  && i + A[i] + 1 < n && s[i-A[i] -1] == s[i + A[i] + 1]) {A[i]++;}
        if(i%2){
            ret += (1LL * A[i])/2 + 1;//마지막 1은 자기자신
        } else {
            ret += (1LL * A[i] + 1) / 2;
        }
        
        if( r < i + A[i]){
            r = i + A[i];
            p = i;
        }
    }

    return A;
}

int main(){
    string S;
    cin>>S;
    string augmented;
    for(int i = 0; i < S.size(); i++){
        augmented+="#";
        augmented+=S[i];
    }
    augmented+="#";

    manacher(augmented);
    
#ifdef DEBUG_MANACHER
for(const auto e : A){
    cout<<e<<" ";
}
cout<<endl;
#endif

    cout<<ret<<endl;
    return 0;
}