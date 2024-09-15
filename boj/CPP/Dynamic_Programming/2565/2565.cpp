#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 100
#define MAX_M 500
using namespace std;
typedef pair<int,int> pii;

int N,M;

vector<pii> lines;

bool compare(const pii & a, const pii & b){
    if(a.first == b.first) return a.second < b.second;
    return a.first < b.first;
}

int cache[MAX_N+1][MAX_N] = {0};

int dp(const int idx, const int previdx){
    //base
    if(idx>=N+1) return 0;
    if(previdx >=N) return 0;
    int& ret = cache[idx][previdx];
    if(ret) return ret;
    
    // lines[idx]를 선택할 경우
    int right1 = lines[idx].second;
    int next1 = idx+1;
    while(next1 <= N && lines[next1].second < right1){
        next1++;
    }
    
    // lines[idx]를 선택하지 않을 경우
    int right2 = lines[previdx].second;
    int next2 = idx+1;
    
    while(next2 <= N && lines[next2].second < right2){
        next2++;
    }
    
    return ret = max( 1 + dp(next1,idx), dp(next2,previdx) );
}

int main(){
    cin>>N;
    int a,fa;
    lines.push_back({-1,-1});
    for(int i = 0 ; i < N; i++){
        cin>>a>>fa;
        lines.push_back({a,fa});
    }
    std::sort(lines.begin(), lines.end(), compare);
    
    //solve
    cout<<N - dp(1,0)<<endl;
    
    return 0;
}