#include <iostream>
#include <cstring>
#include <stack>
#include <queue>

using namespace std;

stack<char> st;
string S;

int value(int s, int e){    
    if( e <= s) return 0;
    
    st.push(S[s]);
    for(int i = s+1; i < e; i++){
        if( S[i] == '(' || S[i] == '[') st.push(S[i]);
        else if (S[i] == ')' || S[i] == ']') {
            st.pop();
            if(st.empty()){       
                return S[s] == '(' ? 2 * max(1,value(s+1, i)) + value(i+1, e) : 3 * max(1, value(s+1, i)) + value(i+1,e);
            }
        }
    }
}

bool invalid(string & S){
    for(int i = 0; i < S.size(); i++){
        if( S[i] == '(' || S[i] == '[') st.push(S[i]);
        else {
            if( S[i] == ')' ){
                if( st.empty() || st.top() != '(') return true;
            } else{
                if( st.empty() || st.top() != '[') return true;
            }
            st.pop();
        }
    }
    
    return !st.empty();
}

int main(){
    cin>>S;
    
    //first check whether the expression is valid
    if( invalid(S))cout<<0<<endl;
    else {
        cout<<value(0, S.size())<<endl;
    }
    return 0;
}