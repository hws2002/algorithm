#include <iostream>
#include <stack>
#include <vector>

#define MAX_N 1'000'000
#define endl '\n'

using namespace std;

stack<pair<int,int>> s;

int N;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N;
    int temp;
    vector<int> v(N);
    for(int i = 0; i < N; i++){
        cin>>temp;
            while(!s.empty() && s.top().first < temp){
                v[s.top().second] = temp;
                s.pop();
            }
            s.push({temp,i});
    }
    
    while(!s.empty()){
        v[s.top().second] = -1;
        s.pop();
    }
    
    for(auto e : v){
        cout<<e<<" ";
    }
    return 0;
}