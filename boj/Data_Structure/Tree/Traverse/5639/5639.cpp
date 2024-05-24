#include <iostream>
#include <vector>
#include <stdio.h>
// #define endl '\n'
// #define DEBUG_INPUT
// #define DEBUG_SOLVE
using namespace std;


void prefix2postfix(const vector<int> & prefix, const int & start, const int & end){
    if (start >= end) return ;
#ifdef DEBUG_SOLVE
cout<<"printing out prefix : ";
for(int i = start; i < end; i++){
    cout<<prefix[i]<<" ";
}
cout<<endl;
#endif
    int root = prefix[start];
    // vector<int> leftTree;
    // vector<int> rightTree;
    int idx = start + 1;

    while(idx < end && prefix[idx] < root){
        idx++;
    }
    
    int l_end = idx;
#ifdef DEBUG_SOLVE
cout<<"lefttree : ";
for(int i = start+1; i < l_end; i++){
    cout<<prefix[i]<<" ";
}
cout<<endl;

cout<<"righttree : ";
for(int i = l_end; i < end; i++){
    cout<<prefix[i]<<" ";
}
cout<<endl;


#endif
    prefix2postfix(prefix, start+1, l_end);
    
    prefix2postfix(prefix, l_end, end);
    
    cout<<root<<endl;
    
    return;
}

int main(){
    vector<int> prefix;
    int root = 0;
    cin>>root;
    int leftTreeElem = -1;
    int rightTreeElem = -1;
    prefix.push_back(root);
    while( cin>>leftTreeElem){
        // cout<<leftTreeElem<<endl;
        if( root > leftTreeElem)
            prefix.push_back(leftTreeElem);
        else break;
    }
    int l_end = prefix.size();
    if( root <= leftTreeElem )
        prefix.push_back(leftTreeElem);
    while( cin>>rightTreeElem ){
        // cout<<rightTreeElem<<endl;
        prefix.push_back(rightTreeElem);
    }

#ifdef DEBUG_INPUT
for(int i = 0 ; i < l_end; i++){
    cout<<prefix[i]<<" ";
}
cout<<endl;
for(int i = l_end; i < prefix.size(); i++){
    cout<<prefix[i]<<" ";
}
cout<<endl;
#endif

    //solve
    prefix2postfix(prefix, 1, l_end);
    prefix2postfix(prefix, l_end, prefix.size() );
    cout<<root<<endl;
    return 0;
}