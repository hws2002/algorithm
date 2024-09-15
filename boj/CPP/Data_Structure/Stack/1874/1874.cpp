#include <iostream>
#include <vector>
#include <stack>
#include <cstring>

#define endl '\n'
using namespace std;

int n;
vector<int> v;
vector<string> res;
stack<int> st;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>n;
    int cur = 1;
    bool cant = false;
    int temp;
    for(int i = 0; i < n; i++){
        cin>>temp;
        v.push_back(temp);
    }
    int i = 0;
    while(i < n){
    // for(int i = 0; i < n;){
        if( cur > v[i]) {
            cant = true;
            break;
        }
        while(cur <= v[i]){
            st.push(cur);
            // cout<"+"<<endl;
            res.push_back("+");
            cur++;
        }
        
        while(!st.empty() && st.top() == v[i]){
            st.pop();
            res.push_back("-");
            i++;
        }
    }
    
    if(cant){
        cout<<"NO"<<endl;
    } else {
        for(auto e : res){
            cout<<e<<endl;
        }
    }
    return 0;
}