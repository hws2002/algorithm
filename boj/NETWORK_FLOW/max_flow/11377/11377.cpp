// bipartite matching
// source - worker - work - sink
//   k|       |
// subsource -|
#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 2'003 // = MAX_M
#define INF 1'000'000'000
// #define DEBUG_INIT
// #define DEBUG_EK
using namespace std;

int N,M,K;

const int source = 0;
const int subsource = 1;
int sink;

int capacity[MAX_N][MAX_N] = {0};
int flow[MAX_N][MAX_N] = {0};

int res = 0;

void maxflow(){
    int here,amt;
    int V = N+M+3;
    
    while(true){
        amt = INF;
        vector<int> parent(V, -1);    
        queue<int> q;
		
		parent[source] = source;
        // source to subsource & workers
		for(int i = 1; i < N+2; i++){
			if( capacity[source][i] - flow[source][i] > 0){
				q.push(i);
				parent[i] = source;
			}
		}
        
        //source to worker
        while(!q.empty() && parent[sink] == -1){

            here = q.front(); q.pop();
#ifdef DEBUG_EK
printf("here : %d \n", here);
#endif
			if( here == subsource){ // here is subsource
				// only check worker
				for(int worker = 2; worker < N+2; worker++){
					if( parent[worker] == -1 && capacity[here][worker] - flow[here][worker] > 0){
						q.push(worker);
						parent[worker] = here;
					}
				}
			} else if( 2 <= here && here < N+2){ // here is worker
				// check work
                for(int work = N+2; work < N+2+M; work++){
                    if( parent[work] == -1 && capacity[here][work] - flow[here][work] > 0){
                        q.push(work);
                        parent[work] = here;
                    }
                }
				
				// check subsource
				if( parent[subsource] == -1 && capacity[here][subsource] - flow[here][subsource] > 0){
					q.push(subsource);
					parent[subsource] = here;
				}
				
            } else {  // here is work
				// check worker
                for(int worker = 2; worker < N+2; worker++){
                    if( parent[worker] == -1 && capacity[here][worker] - flow[here][worker] > 0){
                        q.push(worker);
                        parent[worker] = here;
                    }
                }
				
                // sink
                if( capacity[here][sink] - flow[here][sink] > 0){
                    q.push(sink);
                    parent[sink] = here;
                }
				
            }
        }
        
        if(parent[sink] == -1) break;

        // find amt
        here = sink;
#ifdef DEBUG_EK
cout<<"sink -> source : ";	
#endif
        while( here != source ){
#ifdef DEBUG_EK
cout<<here<<" ";
#endif
            amt = min(amt,  capacity[parent[here]][here] - flow[parent[here]][here]);
            here = parent[here];
        }
#ifdef DEBUG_EK
printf(" \namt : %d \n", amt);
#endif
        // add amt
        here = sink;
        while(here != source){
            flow[ parent[here] ][here] += amt;
            flow[ here ][ parent[here] ] -= amt;
            here = parent[here];
        }
        res += amt;
    }

}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    cin>>N>>M>>K;
    sink = N+M+2;
    int num_work, workidx;
    for(int i = 2; i < N + 2; i++){
        cin>>num_work;
        while(num_work--){
            cin>>workidx;
            workidx--;
            capacity[i][ N + 2 + workidx] = 1;
        }
    }
    
    
    // source to subsource
    capacity[source][subsource] = K;

	// source & subsource to worker
    for(int worker = 2; worker < N+2; worker++){
        capacity[source][worker] = 1;
		capacity[subsource][worker] = 1;
    }
    
    // work to sink
    for(int work = N+2; work < N+2+M; work++){
        capacity[work][sink] = 1;
    }
	
#ifdef DEBUG_INIT
for(int i = 0; i <= N+M+2; i++){
    for(int j = 0; j <= N + M +2; j++){ 
        cout<<capacity[i][j]<<" ";
    }
    cout<<endl;
}
#endif
    //maxflow
    maxflow();

    cout<<res<<endl;
    return 0;
}