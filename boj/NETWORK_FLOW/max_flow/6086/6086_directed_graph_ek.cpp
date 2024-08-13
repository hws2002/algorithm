#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 700
#define MAX_V 52
#define INF 100'000'000
// #define DEBUG_INPUT
// #define DEBUG_EK
using namespace std;

int N;
const int source = 26;  // A
const int sink = MAX_V-1; // Z

int capacity[MAX_V][MAX_V] = {0}; // symmetric matrix
int flow[MAX_V][MAX_V] = {0};

int cnt = 0;
void maxflow(){
    int here;
    int amt;
    while(true){
        cnt++;
#ifdef DEBUG_EK
printf("iter : %d \n", here);
#endif
        vector<int> parent(MAX_V,-1);
        queue<int> q;
        here = source;
        q.push(here);
        parent[here] = here; // source의 parent는 source
        while(!q.empty() && parent[sink] == -1){
            here = q.front(); q.pop();
#ifdef DEBUG_EK
// printf("here : %d \n", here);
#endif
            for(int next = 0; next < MAX_V; next++){
                if( parent[next] == -1 && capacity[here][next] + flow[next][here] - flow[here][next] > 0){
                    q.push(next);
                    parent[next] = here;
                }
            }
        }
        
        if(parent[sink] == -1) break;
        
        // find amt
        here = sink;
        amt = INF;
#ifdef DEBUG_EK
printf("sink to source\n");
#endif
        while( here != source ){
#ifdef DEBUG_EK
printf("%c ", here+'A');
#endif
            amt = min(amt, capacity[ parent[here] ][here] + flow[ here ][ parent[here] ] - flow[ parent[here] ][ here ]); // TODO
            here = parent[here];
        }
#ifdef DEBUG_EK
printf("amt : %d \n", amt);
#endif
        // add amt
        here = sink;
        while( here != source ){
            flow[ parent[here] ][here] += amt;
            if( flow[ parent[here] ][here] > flow[here][parent[here]]){
                flow[ parent[here] ][here] -= flow[here][ parent[here] ];
                flow[here][parent[here]] = 0;
            } else {
                flow[here][parent[here]] -= flow[parent[here]][here];
                flow[parent[here]][here] = 0;
            }
            here = parent[here];
        }
        // res += amt;
    }
}

int char2idx(char u){
    if( 'a' <= u && u <= 'z'){
        return u - 'a';
    }
    if( 'A' <= u && u <= 'Z'){
        return u - 'A' + 26;
    }
}

int main(){
    cin>>N;
    char U,V; int u,v,f;
    for(int i = 0; i < N; i++){
        cin>>U>>V>>f;
        u = char2idx(U); v = char2idx(V);
        capacity[u][v] += f;
        capacity[v][u] += f;
    }
#ifdef DEBUG_INPUT
cout<<" ";
    for(char c = 'A'; c <= 'Z'; c++){
        cout<<c<<" ";
    }
cout<<endl;

for(char c = 'A'; c<='Z'; c++){
    cout<<c;
    for(int j = 0; j < MAX_V; j++){
        cout<<capacity[c-'A'][j]<<" ";
    }
    cout<<endl;
}
cout<<endl;
#endif
    //maxflow
    maxflow();
    int res = 0;
    for(int i = 0; i < MAX_V; i++){
        res += flow[i][sink];
    }
    cout<<res<<endl;
    return 0;
}