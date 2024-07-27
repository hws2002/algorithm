#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

#define MAX_N 1'000
#define endl '\n'

// #define DEBUG_SORT
using namespace std;

int N;
vector<string> vs[MAX_N];

bool compare( const vector<string> & vs1, const vector<string> & vs2){
    int i = 0;
    while(vs1[i] == vs2[i]) i++;
    return vs1[i] < vs2[i];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // scanf("%d \n", &N);
    cin>>N;
    int K;
    string prey;
    for(int i = 0; i < N; i++){
        cin>>K;
        for(int j = 0; j < K; j++){
            cin>>prey;
            vs[i].push_back(prey);
        }
    }
    
    //create tree structure
    //sort
    std::sort( vs, vs + N, compare);

#ifdef DEBUG_SORT
for(int i = 0 ; i < N; i++){
    for(auto s : vs[i]){
        cout<<s<<" ";
    }
    cout<<endl;
}
#endif

    vector<string> prevRoute = vs[0];
    //print out prevRoute
    int cnt__ = 0;
    for(int i = 0; i < prevRoute.size(); i++){
        for(int j = 0; j < cnt__; j++) cout<<"--";
        cout<<prevRoute[i]<<endl;
        cnt__++;
    }
    cnt__ = 0;
    
    for(int i = 1; i < N; i++){
        auto vsi = vs[i];
        cnt__ = 0;
        bool same = true;
        prevRoute.resize(vsi.size(), "#");
        for(int j = 0; j < vsi.size(); j++){
            if(same && prevRoute[j] == vsi[j] ) {
                // cout<<"--";
                cnt__++;
            } else {
                // if(same == false) 
                for(int k = 0; k < cnt__;k++)cout<<"--";
                cout<<vsi[j]<<endl;
                same = false;
                cnt__++;
                //update prevRoute
                prevRoute[j] = vsi[j];
            }
        }
    }

    return 0;
}    

