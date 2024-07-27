#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

// #define DEBUG_INPUT
// #define DEBUG_SUM
using namespace std;
typedef long long ll;

int N,S;
ll res = 0;

void sumall(int subset, vector<int> & A, map<int,ll> & m){
    int f = 0;
    for(int i = 0; i < A.size(); i++){
        if(subset & (1<<i)) f += A[i];
    }
    if(m.find(f) == m.end()){
        m[f] = 1;
    } else {
        m[f] += 1;
    }
    if(f == S) res++;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin>>N>>S;
    N--;
    vector<int> A1(N/2 + 1);
    for(int i = 0; i < N/2+1; i++){
        cin>>A1[i];
    }
    
    vector<int> A2(N - N/2);
    for(int i = 0; i < N - N/2; i++){
        cin>>A2[i];
    }
#ifdef DEBUG_INPUT
cout<<"A1 : ";
for(auto a : A1){
    cout<<a<<" ";
}

cout<<endl<<"A2 : ";
for(auto a : A2){
    cout<<a<<" ";
}
cout<<endl;
#endif

    map<int,ll> m;
    int all = (1<<N/2+1)-1;
    for(int subset = all; subset; subset--){
        sumall(subset,A1,m);
    }
#ifdef DEBUG_SUM
cout<<"m elems"<<endl;
for(auto pii : m){
    printf("(%d, %d) \n", pii.first, pii.second);
}
cout<<endl;
#endif

    all = (1<<(N - N/2)) - 1;
    for(int subset = all; subset; subset--){
        int s = 0;
        for(int i = 0; i < A2.size(); i++){
            if(subset & (1<<i)) s += A2[i];
        }
        if(s == S) res++;
        auto upit = m.lower_bound(S - s);
        if(upit == m.end()) continue;
        if(upit->first + s == S) res += upit->second;
    }
    
    cout<<res<<endl;
    return 0;
}


/*

#ifdef DEBUG_SUM
cout<<"m1 elems"<<endl;
for(auto pii : m1){
    printf("(%d, %d) \n", pii.first, pii.second);
}
cout<<endl<<"m2 elems"<<endl;
for(auto pii : m2){
    printf("(%d, %d) \n", pii.first, pii.second);
}
cout<<endl;
#endif

*/