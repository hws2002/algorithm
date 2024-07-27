// brute force

#include <iostream>
#include <vector>

#define DEBUG_INPUT
using namespace std;


int N,S;
vector<int> prefixSum;

int solve(){
    int res = 0;
    for(int lo = 1; lo < prefixSum.size(); lo++){
        for(int hi = lo; hi < prefixSum.size(); hi++){
            if( prefixSum[hi] - prefixSum[lo-1] == S) res++;
        }
    }
    return res;
}

int main(){
    cin>>N>>S;
    int temp;
    prefixSum.push_back(0);
    for(int i = 0 ; i < N; i++){
        cin>>temp;
        prefixSum.push_back(temp);
        prefixSum.back() += prefixSum[prefixSum.size()-2];
    }    

#ifdef DEBUG_INPUT
for(auto s : prefixSum){
    cout<<s<<" ";
}
cout<<endl;
#endif

    //solve
    int res = solve();
    
    //output
    cout<<res<<endl;
    return 0;
}