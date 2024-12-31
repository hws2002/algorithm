#include <iostream>
#include <cstring>
#include <vector>

#define endl '\n'
using namespace std;

int N;
vector<int> A;

void manacher(const vector<int> & s){
    int n = s.size();
    
    int p = 0; int r = 0;
    for(int i = 0; i < n; i++){
        if( r < i){
            A[i] = 0; 
        } else { // r >= i
            A[i] = min(r-i, A[2*p - i]);
        }
        
        while( i - A[i] - 1 >=0  && i + A[i] + 1 < n && s[i-A[i] -1] == s[i + A[i] + 1]) {A[i]++;}
        if( r < i + A[i]){
            r = i + A[i];
            p = i;
        }
    }

}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>N;
    vector<int> augmented(2*N+1,-1);
    for(int i = 1; i < 2*N+1; i+=2){
        cin>>augmented[i];
    }

    A.resize(N<<1|1,0);
    manacher(augmented);

    int Q;
    cin>>Q;
    int s,e;
    while(Q--){
        cin>>s>>e; 
        s--; e--;
        s = s<<1 | 1; e = e<<1 | 1;
        if( A[(s+e)>>1]*2 >= e - s) cout<<1<<endl;
        else cout<<0<<endl;
    }
    
    return 0;
}