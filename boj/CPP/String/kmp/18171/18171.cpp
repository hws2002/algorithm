#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> p;
void getPartialTable(const string & s){
    int n = s.size();
    p.resize(n+1,0);
    int m = 0; int st = 1; p[0] = -1;
    while(st < n){
        while( st + m < n && s[st+m] == s[m]){
            m++;
            p[st+m] = m;
        }
        st = st + m - p[m];
        m = m == 0 ? m : p[m];
    }
}

int minimum(const string & H, const string & N){
    int h = H.size(); int n = N.size();
    int m = 0; int st = 0;
    while( st < h ){
        while( st + m < h && H[st+m] == N[m]){
            m++;   
        }
        if( st + m >= h) return h-m;
        
        st = st + m - p[m];
        m = m == 0 ? m : p[m];
    }
    return 2*h;
}

int main(){
    int N; cin>>N;
    string S;
    cin>>S;
    
    string rS = S;
    reverse(rS.begin(), rS.end());
    getPartialTable(rS);
    
    cout<<minimum(S,rS)<<endl;
    
    return 0;
}