#include <iostream>
#include <bitset>
#include <memory.h>

#define MAX_SEM 10
#define MAX_CLASS 12
#define INF 10000

#define endl '\n'
using namespace std;

int cache[MAX_SEM][1<<MAX_CLASS] = {{0}};

int N,K,M,L;

int prerequisite[MAX_CLASS] = {0};
int semester[MAX_SEM] = {0};

int bitCount(int n){
    int ret = 0;
    while(n){
        ret += (n&1);
        n >>= 1;
    }
    return ret;
}

int dp(int sem, int taken){
    // printf("%d, %d \n", sem, taken);
    if( bitCount(taken) >= K) return 0;
    if( sem >= M) return INF;
    int & ret = cache[sem][taken];
    if(ret > -1) return ret;
    
    ret = INF;
    int open = (semester[sem] & ~taken);
    //  cout<<"open : "<<open<<endl;   
    
    // 고를 수 있는 수업만 (이미 prerequisite을 들은 수업만) 남긴다
    for(int i = 0; i < N; i++){
        if(  (open & (1<<i)) &&
             ((taken & prerequisite[i]) != prerequisite[i])
            )
            open = open & ~(1<<i);
    }
    // cout<<"open : "<<open<<endl;
    for(int take = open; take ; take = ((take-1) & open)){
        if( bitCount(take) > L) continue;
        ret = min(ret, 1 + dp(sem+1, take | taken));
    }
    ret = min(ret, dp(sem+1, taken));
    // printf("ret : %d \n", sem);
    return ret;
}

void solve(){
    cin>>N>>K>>M>>L;
    
    for(int i = 0; i < M; i++){
        fill(cache[i], cache[i] + (1<<MAX_CLASS), -1);    
    }
    
    memset(prerequisite, 0 , sizeof(prerequisite));
    memset(semester, 0 , sizeof(semester));
    
    // get info of course
    for(int i = 0 ; i < N; i++){
        int num_pre;
        cin>>num_pre;
        while(num_pre--){
            int pre;
            cin>>pre;
            prerequisite[i] |= (1<<pre);
        }
    }
    
    // info of semester
    for(int i = 0; i < M; i++){
        int num_class;
        cin>>num_class;
        while(num_class--){
            int class_num;
            cin>>class_num;
            semester[i] |= (1<<class_num);
        }
    }
// for(int i = 0; i < N; i++){
//     cout<<prerequisite[i]<<" ";
// }    
// cout<<endl;

// for(int i = 0; i < M; i++){
//     cout<<semester[i]<<" ";
// }
// cout<<endl;
    int res = dp(0,0);
    if(res >= INF) cout<<"IMPOSSIBLE"<<endl;
    else cout<<res<<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int C;
    cin>>C;
    while(C--) solve();
    return 0;
}
