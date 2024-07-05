// dp 
#include <iostream>
#include <vector>
#include <string>

#define MAX_L 2'500
// #define DEBUG_PALIN
using namespace std;


int cache[MAX_L] = {0};

// palin[i] : i에서부터 시작하는 길이 2 이상의 팰린드롬의 end index를 저장한다
vector<int> palin[MAX_L];
string H;

int dp(const int idx){
    //base
    if( idx >= H.size()){
        return 0;
    }
    
    int& ret = cache[idx];
    if(ret) return ret;
    
    ret = 1 + dp(idx+1);
    for(auto end_idx : palin[idx]){
        ret = min(ret, 1 + dp(end_idx+1)); 
    }
    return ret;
}

int main(){

    cin>>H;
    
    //get palindrome
    for(int i = 0 ; i < H.size(); i++){
        for(int j = 1; 0 <= i - j && i + j <= H.size(); j++){
            if(H[i-j] == H[i+j]){
                palin[i-j].push_back(i+j);
            } else break;
        }
    }
    
    for(int i = 0; i < H.size() - 1; i++){
        for(int j = 1; 0 <= i - j + 1 && i + j <= H.size(); j++){
            if(H[i-j+1] == H[i+j]){
                palin[i-j+1].push_back(i+j);
            } else break;
        }
    }
    
#ifdef DEBUG_PALIN
for(int i = 0 ; i < H.size(); i++){
    cout<<"palin starts from "<<i<<" : ";
    for(auto p : palin[i]){
        cout<<p<<" ";
    }    
    cout<<endl;
}
#endif
    //solve - dp
    cout<<dp(0)<<endl;
    
    return 0;
}