//solve : bottom-up
//recon : topdown

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int dp[1001][1001] = {0};
int choice[1001][1001] = {0};
string s1,s2;

void backtrackLCS(int r, int c, string & res){
    if(r  < 0 || c < 0) return;
    int val = dp[r][c];
    if(val == 0) return;
    while(r-1 >= 0 && dp[r-1][c] == val) r--;
    while(c-1 >= 0 && dp[r][c-1] == val) c--;
    res.push_back(s1[r]);
    backtrackLCS(r-1,c-1,res);
}

int lcs2(const int i, const int j){
    //base
    int val = 0;
    for(int i = 0; i < s1.size(); i++){
        if(s1[i] == s2[0]) val = 1;
        dp[i][0] = val;
    }
    val = 0;
    for(int i = 0; i < s2.size(); i++){
        if(s1[0] == s2[i]) val = 1;
        dp[0][i] = val;
    }
    
    for(int i = 1; i < s1.size(); i++){
        for(int j = 1 ; j < s2.size(); j++){
            if(s1[i] == s2[j]){
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = max( dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return dp[s1.size()-1][s2.size()-1];
}

int main(){
    cin>>s1>>s2;
    
    //construct dp-road
    int length = lcs2(0,0);
    cout<<length<<endl;
    
    //backtrack - todo
    string res;
    if(length) {
        backtrackLCS(s1.size()-1, s2.size()-1, res);
        reverse(res.begin(), res.end());
        cout<<res<<endl;
    }
    return 0;
}