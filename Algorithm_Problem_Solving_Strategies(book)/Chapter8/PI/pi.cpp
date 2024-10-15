#include <iostream>
#include <cstring>

#define MAX_N 10000
#define endl '\n'
#define INF 2000000000
using namespace std;

int cache[MAX_N] = {0};

string seq;

// seq[idx ~ idx + stp)를 외우는데 필요한 난이도
int cost(int idx, int stp){
    if( idx + stp > seq.size()) return 10;
    bool d1 = true;
    for(int i = idx+1; i < idx + stp; i++){
        if(seq[i] != seq[idx]) {d1 = false; break;}
    }
    if(d1) return 1;

    bool d2 = true;
    for(int i = idx+2; i < idx + stp; i++){
        if((seq[i] - seq[i-1]) != seq[1] - seq[0]){ d2 = false; break;}
    }
    if(d2 && abs(seq[1] - seq[0]) == 1) return 2;

    bool d4 = true;
    int l = seq[idx];
    int r = seq[idx+1];
    for(int i = 2; i < stp; i++){
        if(i%2){ // 홀수
            if(seq[idx+i] != r) { d4 = false; break;}
        } else { // 짝수
            if(seq[idx+i] != l) { d4 = false; break;}
        }
    }
    if(d4) return 4;
    
    bool d5 = true;
    int dff = seq[idx+1] - seq[idx];
    for(int i = idx+2; i < idx + stp; i++){
        if( seq[i] - seq[i-1] != dff) { d5 = false; break;}
    }
    if(d5) return 5;
    
    return 10;
}

// dp(i) : i번쨰 숫자에서부터 외운다고 할때, 최소 난이도
int dp(int idx){
    //base
    if(idx >= seq.size()) return 0;
    int & ret = cache[idx];
    if(ret) return ret;
    ret = INF;
    for(int stp = 3; stp <= 5; stp++){
        // printf("cost(%d, %d) %d \n", idx, stp, cost(idx,stp));
        ret = min(ret, cost(idx, stp) + dp(idx + stp));
    }
    return ret;
}

void solve(){
    cin>>seq;
    //reset
    fill(cache, cache+seq.size(), 0);
    cout<<dp(0)<<endl;
}

int main(){
    int c;
    cin>>c;
    while(c--) solve();
    return 0;
}