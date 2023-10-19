#include <iostream>
using namespace std;

class Solution {
public:
    char getLastChar(const string & s, int & i, int & jump){ 
        if(i<0) return '-';
        if(s[i] == '#') {
            jump++; i--;
        } else{
            if(jump >= 1){
                jump--;i--;
            } else {
                return s[i];
            }
        }
        return getLastChar(s,i,jump);
    }

    bool backspaceCompare(string s, string t) {
        char s_last;
        char t_last;
        int i = s.length()-1; int j = t.length()-1;
        while(i > -1 || j > -1){
            int s_jump = 0;
            int t_jump = 0;
            s_last = getLastChar(s,i,s_jump);
            t_last = getLastChar(t,j,t_jump);
            //printf("s_last : %c , t_last : %c \n",s_last,t_last);
            i--;j--;
            if(s_last != t_last) return false;
        }
        return true;
    }
};

int main(){
    string s = "bbbextm";
    string t = "bbb#extm";
    Solution solution;
    bool res = solution.backspaceCompare(s,t);
    printf("output : %s",res ? "true" : "false");
    return 0;
}