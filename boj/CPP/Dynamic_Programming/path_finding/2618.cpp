// n choose 2?
// dp?
// dp! + sliding window?
#include <iostream>
#include <vector>

#define endl '\n'
#define MAX_N 1'000
#define MAX_W 1'000
#define FOR(i,s,e) for(int i = s; i < e; i++)
// #define DEBUG_DP

using namespace std;
typedef pair<int,int> pii;

int N, W;
vector<int> Wx(MAX_W+5);
vector<int> Wy(MAX_W+5);

pair<int,int> cache[MAX_W+2][MAX_W+2];

// dp (i,j) : 경찰차1의 위치가 ( Wx[i], Wy[i]), 경찰차2의 위치가 ( Wx[j], Wy[j]), 일때 
//              max(i,j) + 1번째 사건부터 모두 해결하기 위해 필요한 최소비용
int dp(const int alpha_posi, const int bravo_posi){
    int next_case = max(alpha_posi, bravo_posi) + 1;
    
    //base
    if( next_case >= W+2) return 0;
    pii & ret = cache[alpha_posi][bravo_posi];
    if(ret.second) return ret.first;
    
    int dp1 = abs(Wx[next_case] - Wx[alpha_posi]) + abs(Wy[next_case] - Wy[alpha_posi]) + dp(next_case, bravo_posi); // 경찰차1이 출동
    int dp2 = abs(Wx[next_case] - Wx[bravo_posi]) + abs(Wy[next_case] - Wy[bravo_posi]) + dp(alpha_posi, next_case); // 경찰차2가 출동

#ifdef DEBUG_DP
printf("alpha, bravo , dp1, dp2 : %d, %d, %d %d \n", alpha_posi, bravo_posi, dp1,dp2);
#endif
    if (dp1 >= dp2){
        ret = {dp2,2};
        return dp2;
    } else {
        ret = {dp1,1};
        return dp1;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin>>N>>W;
    Wx[0] = 1; Wy[0] = 1;
    Wx[1] = N; Wy[1] = N;
    
    FOR(i,2,W+2){
        cin>>Wx[i]>>Wy[i];
    }
    
    //pre

    cout<<dp(0, 1)<<endl;

    int a_idx = 0; int b_idx = 1;
    int police_idx;
    for(int i = 2; i < W+2; i++){
        police_idx = cache[a_idx][b_idx].second;
        cout<<police_idx<<endl;
        if(police_idx == 1){
            a_idx = i;
        } else {
            b_idx = i;
        }
    }

    return 0;
}

