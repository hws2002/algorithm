#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_N 1'00'001
#define MAX_Xi 1'000'001
using namespace std;

int N;
vector<int> x;
int num2idx[MAX_Xi] = {0};
int largestXi = -1;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N;
    vector<int> res(N,0);    
    int temp;
    for(int i = 0; i < N ;i++){
        cin>>temp;
        x.push_back(temp);
        num2idx[temp] = i+1;
        largestXi = max(largestXi, temp);
    }
   
    std::sort(x.begin(), x.end());
    
    for(int i = 0 ; i < 10 && i < x.size(); i++){
        if( x[i] <= 10){
            int xi = x[i];
            for(auto num : x){
                if(num!= xi && num%xi == 0){
                    res[num2idx[xi]-1]  += 1;
                    res[num2idx[num]-1] -= 1;
                }
            }
        }
    }
    
    for(auto xi : x){
        if(xi <= 10) continue;
        // if(!checktable[xi].empty()){
            // for(auto divisor : checktable[xi]){
                // res[num2idx[divisor]] += 1;
                // res[num2idx[xi]] -= 1;
            // }
        // }
        
        int m = 2*xi;
        while(m <= largestXi){
            if( num2idx[m] ) {
                res[num2idx[m]-1] -= 1;
                res[num2idx[xi]-1] += 1;
            }
            m += xi;
        }
    }
    
    
    //output
    for(auto r : res){
        cout<<r<<" ";
    }
    return 0;
}