/*
모든 스위치들은 4번 이상 돌릴 필요가 없다
*/
#include <iostream>
#include <vector>
#include <limits.h>

#define OPTIMIZE
#define SWITCHES 10
#define NUM_CLOCK 16
#define MOD 4

// #define DEBUG_INPUT
// #define DEBUG_TRYALL
using namespace std;

vector<int> clock_status(NUM_CLOCK,0);
int res = 0;
// 메모리 사용량을 줄이고 싶다면 char을 사용하면 된다.
const bool link[SWITCHES][NUM_CLOCK] = {
  {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
  {1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0},
  {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
  {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
  {0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1},
  {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}
};

/*
idx번째 스위치부터 고려할때, 시계들을 모두 12시로 돌려놓기 위해 눌러야 할 스위치의 최소 수
*/

bool allSet(){
    for(auto c : clock_status){
        if(c != 0) return false;
    }
    return true;
}

void clickSwitch(int switchidx){
    for(int i = 0; i < NUM_CLOCK; i++){
        if(link[switchidx][i]){
            clock_status[i] = (clock_status[i] + 1) % 4;
        }
    }
}

void tryAll(const int idx, int num_click){
	if(num_click >= res) return ;
#ifdef DEBUG_TRYALL
printf("tryAll(%d, %d) \n", idx, num_click);
for(auto s : clock_status){
	cout<<s<<" ";
}
	cout<<endl;
#endif
    #ifdef OPTIMIZE // 만약 모든 시계가 이미 12시를 향하고 있다면, 더 이상 이 분기를 시도할 필요 없다.
    if(allSet()){
        res = min(res, num_click);
        return ;
    }
    #endif
    
    //base
    if(idx >= SWITCHES){ // 모든 스위치를 다 돌려봤다면
        if(allSet())
            res = min(res,num_click);
        return ;
    }

    for(int i = 0; i < 4; i++){
        tryAll(idx+1, num_click++);
        clickSwitch(idx);
    }
}

/*
0 1 2 3
*/
void solve(){
    //input
    for(int i = 0 ; i < NUM_CLOCK; i++){
        cin>>clock_status[i];
        clock_status[i] = (clock_status[i] / 3) % MOD;
    }
	
#ifdef DEBUG_INPUT
for(auto s : clock_status){
    cout<<s<<" ";
}
cout<<endl;
#endif
	
    //tryAll
    res = INT_MAX;
    tryAll(0,0);
	if(res == INT_MAX) cout<<-1<<endl;
    else cout<<res<<endl;
}

int main(){
    int C;
    cin>>C;
    while(C--){
        solve();
    }
    return 0;
}