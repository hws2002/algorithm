#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>

#define DEBUG_INPUT
#define DEBUG_CHOOSE
#define DEBUG_OUTERLOOP

using namespace std;


typedef pair<int,int> p_ii;
int N,M;
int MAP[502][502] = {0};
bool VISIT[502][502];
struct Compare {
    bool operator()(const p_ii & a, const p_ii & b){
        return a.first < b.first;
    }
};

#ifdef DEBUG_INPUT 
void printPQ(priority_queue< p_ii, vector< p_ii >, Compare> pq){
     int count = 0;
     while(!pq.empty() && count++ < 10){
        cout<<pq.top().first<<" at ("<<pq.top().second/(M+2)<<","<<pq.top().second%(M+2)<<")"<<endl;
        pq.pop();
     }
     cout<<endl;
}

#endif
priority_queue< p_ii, vector< p_ii> , Compare > PQ_Pair_w_p; //weight_position

int dx[4] = {-1,1,0,0};          
int dy[4] = {0,0,-1,1};

int choose4blocks(const int weight, int posi, const int num_block2choose, bool VISIT[][502]){
    if( ( num_block2choose <= 0 || MAP[posi/(M+2)][posi%(M+2)] == 0 )) return weight;
    int res = -1;
    int new_posi;
    for(int i = 0 ; i < 4 ; i++){
        // if( ((dx[i] < 0) && (posi/(M+1) == 1)) ||
        //     ((dx[i] > 0) && (posi/M+1) == N)) ||
        //     ((dy[i] < 0) && (posi%(M+1) == 1) ||
        //     ((dy[i] > 0) && (posi%(M+1) == M)
        // ) continue; 
        new_posi = posi + dx[i]*(M+2) + dy[i];
        if(VISIT[new_posi/(M+2)][new_posi%(M+2)]) continue;
#ifdef DEBUG_CHOOSE
cout<<"wegith : "<<weight<<" and still remains "<<num_block2choose<<" blocks to choose"<<endl; 
cout<<"MAP["<<new_posi/(M+2)<<"]["<<new_posi%(M+2)<<"] ="<<MAP[new_posi/(M+2)][new_posi%(M+2)]<<endl;
#endif
        VISIT[new_posi/(M+2)][new_posi%(M+2)] = true;
        res = max(res, choose4blocks(weight + MAP[new_posi/(M+2)][new_posi%(M+2)], new_posi, num_block2choose-1, VISIT) );
        VISIT[new_posi/(M+2)][new_posi%(M+2)] = false;
    }
    
    return res;
}


int main(){
    //input
    cin>>N>>M;
    
    for(int i = 1 ; i < N+1; i++){
        for(int j = 1 ; j < M+1; j++){
            cin>>MAP[i][j];
            PQ_Pair_w_p.push({MAP[i][j],i*(M+2)+j});
        }
    }
#ifdef DEBUG_INPUT
cout<<"PRINTING OUT MAP : " <<endl;
for(int i = 0 ; i < N+2; i++){
    for(int j = 0 ; j < M+2; j++){
        cout<<MAP[i][j];
    }
    cout<<endl;
}

printPQ(PQ_Pair_w_p);
#endif

    //solve
    int res = -1;
    int block_remaining = N*M;
    int possible_res, weight, posi;
    while(block_remaining >= 4){
        //choose 4 blocks that add up to largest
        for(int i = 0 ; i < N+2; i++){
            for(int j = 0 ; j < M+2; j++){
                VISIT[i][j] = false;
            }
        }
        weight = PQ_Pair_w_p.top().first;
        posi = PQ_Pair_w_p.top().second;
        
#ifdef DEBUG_OUTERLOOP
cout<<"weight = "<<weight<<", posi : ("<<posi/(M+2)<<","<<posi%(M+2)<<")"<<endl;
#endif
        VISIT[posi/(M+2)][posi%(M+2)] = true;
        possible_res = choose4blocks(weight,posi,3, VISIT);
        MAP[posi/(M+2)][posi%(M+2)] = 0;
        PQ_Pair_w_p.pop();
        block_remaining--;
        res = max(res, possible_res);
    }
    
    cout<<res<<endl;
    return 0;
}