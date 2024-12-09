#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

string F,M;

vector<int> res;
vector<int> p;

// F[s...e)의 접두사이면서 접미사인 문자열중 가장 긴 문자열의 길이를 반환한다.
void getPTable(){
    p.resize(F.size()+1,0);
    int f = F.size();
    p[0] = -1; p[1] = 0;
    int st = 1; int m = 0;
    while(st < f){
        while(st + m < f && F[ st + m] == F[m]){
            m++;
            p[st+m] = m; 
        }
        st = st + m - p[m];
        m = m == 0 ? 0 : p[m];
    }
}

int main(){
    cin>>F;
    cin>>M;
    F = F+M;
    getPTable();
    
    res.push_back(F.size());
    int e = p[F.size()];
    while(e){
        res.push_back(e);
        e = p[e];
    }
    
    for(int i = res.size()-1; i>=0; i--){
        cout<<res[i]<<" ";
    }    
    cout<<endl;
    
    return 0;
}    