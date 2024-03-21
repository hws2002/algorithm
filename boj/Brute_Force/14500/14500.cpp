#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;


typedef pair<int,int> p_ii;
int N,M;
int MAP[502][502] = {{0}};
bool VISIT[502][502];

struct Compare {
    bool operator()(const p_ii & a, const p_ii & b){
        return a.first < b.first;
    }
};


priority_queue< p_ii, vector< p_ii> , Compare > PQ_Pair_w_p; //weight_position

int dx[4] = {-1,1,0,0};          
int dy[4] = {0,0,-1,1};
int x_1,y_1, x_2, y_2;
int choose4blocks(const int weight, int posi, const int num_block2choose, bool VISIT[][502]){
    if( ( num_block2choose <= 0 || MAP[posi/(M+2)][posi%(M+2)] == 0 )) return weight;
    if( num_block2choose == 2 ) {
        x_2 = posi/(M+2);
        y_2 = posi%(M+2);
    }
    
    int res = -1;
    int new_posi;
    for(int i = 0 ; i < 4 ; i++){
        new_posi = posi + dx[i]*(M+2) + dy[i];
        if(VISIT[new_posi/(M+2)][new_posi%(M+2)]) continue;

        VISIT[new_posi/(M+2)][new_posi%(M+2)] = true;

        res = max(res, choose4blocks(weight + MAP[new_posi/(M+2)][new_posi%(M+2)], new_posi, num_block2choose-1, VISIT) );
        VISIT[new_posi/(M+2)][new_posi%(M+2)] = false;
    }

    if ( num_block2choose == 1){
        if(x_1 == x_2 && x_2 == posi/(M+2)){
            res = max(res, weight + MAP[x_2-1][y_2]);
            res = max(res, weight + MAP[x_2+1][y_2]);
        }
        if( y_1 == y_2 && (y_2 == (posi%(M+2)) ) ){
            res = max(res, weight + MAP[x_2][y_2-1]);
            res = max(res, weight + MAP[x_2][y_2+1]);

        }
    }
    return res;
}


int main(){
    //input
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>M;
    
    for(int i = 1 ; i < N+1; i++){
        for(int j = 1 ; j < M+1; j++){
            cin>>MAP[i][j];
            PQ_Pair_w_p.push({MAP[i][j],i*(M+2)+j});
        }
    }

    //solve
    int res = -1;
    int block_remaining = N*M;
    int possible_res, weight, posi;
    while(block_remaining >= 4){
        weight = PQ_Pair_w_p.top().first;
        posi = PQ_Pair_w_p.top().second;
        
        VISIT[posi/(M+2)][posi%(M+2)] = true;
        x_1 = posi/(M+2); y_1 = posi%(M+2);
        possible_res = choose4blocks(weight,posi,3, VISIT);
        VISIT[posi/(M+2)][posi%(M+2)] = false;
        PQ_Pair_w_p.pop();
        block_remaining--;
        res = max(res, possible_res);
    }
    
    cout<<res<<endl;
    return 0;
}