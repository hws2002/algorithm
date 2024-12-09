#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

// #define DEBUG_GETP
#define endl '\n'
using namespace std;

string S;
string rS;

vector<int> getPTable(const string & s){
    int n = s.size();
    vector<int> p(n+1,0);
    p[0] = -1; p[1] = 0;
    int st = 1; int m = 0;
    
    while(st < n){
        while(st + m < n && s[st+m] == s[m]){
            m++;
            p[st+m] = m;
        }
        st = st + m - p[m];
        m = m == 0 ? 0 : p[m];
    }
    return p;
}


// H에서 N을 찾는다
// H의 접미사이면서 N의 접두사인 문자열 중 가장 긴 문자열의 길이를 반환한다.
int KMP(const string & H, const string & N, const vector<int> & p){
    int h = H.size(); 
    // assert(h==n) 
    int st = 0; int m = 0; 
    while( st < h){ 
        while( st + m < h && H[st+m] == N[m]) 
            m++; 
        if( st + m >= h) return m;
        st = st + m - p[m];
        m = m==0 ? m : p[m];
    } 
    return 0; 
}

void solve(){
    cin>>S; 
    rS = S; 
    reverse(rS.begin(), rS.end()); 
    vector<int> p = getPTable(rS); 
#ifdef DEBUG_GETP
    for(const auto & e : p){
        cout<<e<<" ";
    }    
cout<<endl;
#endif 
    cout<<2*S.size() - KMP(S,rS,p)<<endl;
}

int main(){
    int C;
    cin>>C;
    while(C--) solve();
}