#include <iostream>
#include <vector>

#define endl '\n'
#define MAX_N 2'000
using namespace std;

vector<int> H;
vector<int> pi;

bool isPalindrome[MAX_N][MAX_N] = {false};



int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    
    //input
    int N,M;
    cin>>N;
    H.resize(N);
    for(int i = 0; i < N; i++){
        cin>>H[i];
    }
    
    for(int i = 1; i <= N-2; i++){
        for(int j = 0; 0 <= i-j && i + j <= N-1; j++){
            if(H[i-j] == H[i+j]) isPalindrome[i-j][i+j] = true;
            else break;
        }
    }
    
    for(int i = 1; i <= N-1; i++){
        for(int j = 1; 0 <= i-j && i + j - 1 <= N-1;j++){
            if(H[i-j] == H[i+j-1]) isPalindrome[i-j][i+j-1] = true;
            else break;
        }
    }
    
    //query
    cin>>M;
    int S,E;
    for(int i = 0; i < M; i++){
        cin>>S>>E;
        if( S==E) {cout<<1<<endl; continue;};
        if(isPalindrome[S-1][E-1])cout<<1<<endl;
        else cout<<0<<endl;
    }

    return 0;    
}