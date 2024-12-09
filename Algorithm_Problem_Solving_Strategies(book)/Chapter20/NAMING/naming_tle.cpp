#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

string F,M;

vector<int> res;


// F[s...e)의 접두사이면서 접미사인 문자열중 가장 긴 문자열의 길이를 반환한다.
int longestPS(int s, int e){
    vector<int> p(e-s+1,0);
    p[s] = -1; p[s+1] = 0;
    int st = s+1; int m = 0;
    while(st < e){
        while(st + m < e - s && F[s + st + m] == F[s + m]){
            m++;
            p[st+m] = m; 
        }
        //if(p[e-s]) return p[e-s];
        st = st + m - p[m];
        m = m == 0 ? 0 : p[m];
    }
    return p[e-s];
}

int main(){
    cin>>F;
    cin>>M;
    F = F+M;
    int e = F.size();
    while(e){
        res.push_back(e);
        e = longestPS(0, e);
    }
    for(int i = res.size()-1; i>=0; i--){
        cout<<res[i]<<" ";
    }    
    cout<<endl;
    return 0;
}    