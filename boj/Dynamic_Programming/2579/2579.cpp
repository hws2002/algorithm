#include <iostream>
#include <vector>
#include <limits.h>


using namespace std;
int cache[301][3] = {0};
int N; 
vector<int> scores;

int dp(const int start, const int chose1){
    if(cache[start][chose1]) return cache[start][chose1];
    
    if(start == N){
        return scores[start];
    }

    if(start == N-1){
        if(chose1 >= 2) return INT_MIN;
        else return scores[start] + scores[N];
    }

    if(chose1 >= 2){
        int res = scores[start] + dp(start+2, 1);
        cache[start][chose1] = res;
        return res;
    } else {
        int res = scores[start] + max( dp(start+1, chose1+1) , dp(start+2, 1));
        cache[start][chose1] = res;
        return res;
    }
}

int main(){

    //input
    cin>>N;
    int temp;
    scores.push_back(0);
    for(int i = 0 ; i < N; i++){
        cin>>temp;
        scores.push_back(temp);
    }

    cout<<dp(0, 0)<<endl;

    return 0;
}
