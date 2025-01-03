#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define endl '\n'
#define MAX_N 12

using namespace std;

int N;

int sgn(int x){
    if(x == 0) return 0;
    return x > 0 ? 1 : -1;
}

int incr(int x){
    return x >= 0 ? x + 1 : x - 1;
}

int get(int state, int idx){
    return (state>>(idx*2)) & 3;
}

// value번째 기둥에 index번 원반을 꼽는다
// index번 원반을 value번쨰 기둥에 꼽는다
int movePlate(int state, int index, int value){
    // 먼저 state의 index에 해당하는 위치를 비우고(set 0)
    // value로 넣는다
    return (state & ~(3<<(index*2))) | (value<<(index*2));
}

void solve(){
    cin>>N;

    int src = 0;
    int num_plates;
    int plate_num;
    for(int i = 0; i < 4; i++){
        cin>>num_plates;
        while(num_plates--){
            cin>>plate_num;
            plate_num--;
            src |= i<<(plate_num*2);
        }
    }
    
    int tgt = (1<<(N*2))-1;
    
    vector<int> dist(1<<(N*2), 0);
    
    queue<int> q;
    q.push(src);
    q.push(tgt);
    dist[src] = 1;
    dist[tgt] = -1;
    
    while(!q.empty()){
        int h = q.front(); q.pop();
        int c = dist[h];
        //find smallest plate for each column
        int top[4] = {-1,-1,-1,-1};
        for(int i = N-1; i>=0; i--){
            top[get(h,i)] = i;
        }
        
        // 0 2 3 1
        
        for(int i = 0; i < 4; i++){
            if(top[i] == -1) continue;
            for(int j = 0; j < 4; j++){
                if( j == i) continue;
                if( top[j] == -1 || top[j] > top[i]){
                    int next = movePlate(h, top[i], j);
                    
                    if( dist[next] == 0 ) {
                        dist[next] = incr(c);
                        q.push(next);
                    } else if ( sgn(dist[next]) != sgn(c)){
                        cout<< abs(dist[next]) + abs(c) - 1<<endl;
                        return ;
                    }
                }
            }
        }
    }
}

int main(){
    int C;
    cin>>C;
    while(C--) solve();
    return 0;
}