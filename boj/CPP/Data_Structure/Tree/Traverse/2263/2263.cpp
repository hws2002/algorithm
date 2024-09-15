//재귀로 쉽게 구현 가능

// pre : ABC
// in : BAC
// post : BCA

#include <iostream>
#include <vector>

int n; // 1 <= n <= 100'000
using namespace std;
void inpost2pre(vector<int> & inorder, const int inStart, const int inEnd,
                 vector<int> & postorder, const int postStart, const int postEnd){
    if(inStart >= inEnd || postStart >= postEnd) return ;
    int root = postorder[postEnd-1];
    cout<<root<<" ";
    int lengthB = 0;
    while(inStart + lengthB < inEnd && inorder[inStart+lengthB] != root) lengthB++;
    
    inpost2pre(inorder, inStart, inStart + lengthB , postorder, postStart, postStart + lengthB);
    inpost2pre(inorder, inStart + lengthB + 1 , inEnd, postorder, postStart + lengthB, postEnd-1);
}

int main(){
    cin>>n;
    vector<int> inorder;
    vector<int> postorder;    
    int node;
    for(int i = 0; i < n; i++){
        cin>>node;
        inorder.push_back(node);
    }
    
    for(int i = 0; i < n ; i++){
        cin>>node;
        postorder.push_back(node);
    }
    
    inpost2pre(inorder,0,n, postorder, 0,n);
    cout<<endl;
    return 0;
}
