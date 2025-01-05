#include <iostream>
#include <stack>
#include <vector>

using namespace std;



void printStack(stack<int> st){
    while(!st.empty()){
        cout<<st.top()<<" ";
        st.pop();
    }
    cout<<endl;
}

int main(){
    int n;
    cin>>n;
    
    int res = 0;
    int x,h;
    stack<int> st;
    
    for(int i = 0 ; i < n ; i++){
        cin>>x>>h;
        
        if(st.empty()){
            st.push(h);
        } else {
            if(st.top() < h){
                st.push(h);
            } else { // st.top() > h
                
                while(!st.empty()){
                    int t = st.top(); 
                    if( t <= h ) break;
                    st.pop();
                    while(!st.empty() && st.top() == t){
                        st.pop();
                    }
                    res++;
                }

                st.push(h);                

                // printStack(st);
            }
        }
    }
    // cout<<"Res : "<<res<<endl;
    // printStack(st);
    while(!st.empty()){
        int t = st.top(); st.pop();
        // cout<<"t : "<<t<<endl;
        while(!st.empty() && st.top() == t){
            st.pop();
        }
        if(t!=0) res++;
    }
    
    cout<<res<<endl;
    return 0;
}