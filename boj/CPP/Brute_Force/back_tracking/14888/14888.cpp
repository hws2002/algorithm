#include <iostream>
#include <limits.h>

#define MAX_N 11
// #define DEBUG_BF
using namespace std;

int N;
int A[MAX_N];
int operators[4] = {0};

int resMax = INT_MIN;
int resMin = INT_MAX;

int calValue(int value, int op_num, int idx){
    if(op_num == 0){
        return value + A[idx+1]; 
    } else if (op_num == 1){
        return value - A[idx+1];
    } else if (op_num == 2){
        return value * A[idx+1];
    } else {
        return value / A[idx+1];
    }
}

void tryAll(int idx, int value){
#ifdef DEBUG_BF
printf("tryAll(%d, %d) \n",idx,value);
#endif
    if(idx >= N-1) {
        resMax = max(value, resMax);
        resMin = min(value, resMin);
        return ;
    }
    
    int i = 0;
    for(int i = 0 ; i < 4; i++){
        if(operators[i]){
            operators[i]--;
            tryAll(idx+1, calValue(value, i, idx));
            operators[i]++;
        }
    }
}

int main(){
    
    cin>>N;
    
    for(int i = 0; i < N; i++){
        cin>>A[i];
    }
    
    for(int i = 0; i < 4; i++){
        cin>>operators[i];
    }
    
    tryAll(0,A[0]);
    cout<<resMax<<endl<<resMin<<endl;
    return 0;
}
