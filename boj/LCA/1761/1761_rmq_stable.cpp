// sparse table
#include <iostream>
#include <vector>
#include <limits.h>
#include <cmath>

#define MAX_N 40'000
#define MAX_LOG2N 16 // [log2(40000)
#define endl '\n'
#define INF 1'000'000'000
// #define DEBUG_TRAV
// #define DEBUG_RMQ
// #define DEBUG_STABLE
// #define DEBUG_QUERY

using namespace std;

int N;
int K;
vector<int> trav; // 최대 2N
vector<int> pre2node(MAX_N);

vector<int> pow2d(MAX_LOG2N);
int stable[MAX_LOG2N][MAX_N] = {0}; // stable[k][i] : i번째 노드에서 2^k번째 조상까지의 거리. 만약 i의 2^k번째 조상이 없다면, 루트까지의 거리를 반환한다.
int parent[MAX_LOG2N][MAX_N] = {0}; // parent[k][i] : i번째 노드의 2^k번째 조상. 만약 i의 2^k번째 조상이 없다면, 루트를 가리킨다

// 아래는 모두 nodeIdx 기준
vector<pair<int,int>> children[MAX_N];
vector<int> flocintrav(MAX_N);
vector<int> node2pre(MAX_N);
vector<int> depth(MAX_N);

int preIdx = 0;

void travPre(const int here, const int d, const int p){
    node2pre[here] = preIdx;
    depth[here] = d;
    pre2node[preIdx] = here;
    flocintrav[here] = trav.size();
    trav.push_back(node2pre[here]);
    preIdx++;
    for(auto child : children[here]){
        int next = child.first;
        int cost = child.second;
        if(next == p) continue;
        parent[0][next] = here;
        stable[0][next] = cost;
        travPre(next, d+1, here);
        trav.push_back(node2pre[here]);
    }
}

struct RMQ{ // range min query
  int n;
  vector<int> rangeMin;
  
  RMQ(const vector<int> & array){
      n = array.size();
      rangeMin.resize(4*n);
      init(array, 1, 0, n-1);
  }
  
  int init(const vector<int> & array, const int nodeNum, int nodeLeft, int nodeRight){
    if(nodeRight <= nodeLeft) return rangeMin[nodeNum] = array[nodeRight];
    int mid = (nodeLeft + nodeRight) >> 1;
    return rangeMin[nodeNum] = min( init(array, nodeNum<<1, nodeLeft, mid) , init(array, (nodeNum<<1)+1, mid+1, nodeRight));
  }
  
  
  //query
  int query(int left, int right,int nodeNum, int nodeLeft, int nodeRight){
    if( right < nodeLeft || nodeRight < left) return INF;
    if( left <= nodeLeft && nodeRight <= right) return rangeMin[nodeNum];
    
    int mid = (nodeLeft + nodeRight) >> 1;
    return min( query(left, right, nodeNum<<1, nodeLeft, mid), query(left, right, (nodeNum<<1) + 1, mid+1, nodeRight));
  }
  
  int query(const int left, const int right){
    return query(left,right, 1, 0, n-1);
  }
};

// nodeIdx 기준 u와 v의 LCA(nodeIdx)를 반환한다
int findLCA(int u, int v, RMQ & rmq){
    u = flocintrav[u]; v = flocintrav[v];
#ifdef DEBUG_QUERY
printf("u : %d, v : %d, ", u, v);
#endif
    if(u > v) swap(u,v);
    int lca = rmq.query(u,v);
#ifdef DEBUG_QUERY
printf("lca : %d \n", pre2node[lca]);
#endif
    return pre2node[lca];
}

// nodeIdx 기준 s의 dist번째 조상까지의 거리를 반환한다
int fn(int s, int dist){
#ifdef DEBUG_QUERY
	printf("fn(%d, %d) \n", s, dist);
#endif
    if(dist <= 0) return 0;
    int ret = 0;
    for(int d = MAX_LOG2N-1; d >= 0; d--){
        if(!dist) break;
        if(dist / pow2d[d]){
            ret += stable[d][s];
#ifdef DEBUG_QUERY
printf("dist, pow2d[%d], ret : %d, %d, %d \n", d, dist, pow2d[d], ret);
#endif
            s = parent[d][s];
            dist -= pow2d[d];
        }
    }
    
    return ret;
}

int main(){
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);
    cin>>N;
    int A,B,C;
    for(int i = 0; i < N-1; i++){
        cin>>A>>B>>C;
        A--;B--;
        children[A].push_back({B,C});
        children[B].push_back({A,C});
    }
    
    //pre
    for(int i = 0; i < MAX_LOG2N; i++){
        pow2d[i] = pow(2,i);
    }
    
    // travpre
    // root 아무거나 잡고 시작
    travPre(0,0,-1);
#ifdef DEBUG_TRAV
for(int i = 0; i < N; i++){
    cout<<i+1<<" ";
}
cout<<endl;
cout<<"node2pre : "<<endl;
for(int i = 0; i < N; i++){
    cout<<node2pre[i]<<" ";
}    
cout<<endl;

cout<<"trav : "<<endl;
for(auto e : trav){
    cout<<e<<" ";
}
cout<<endl;
cout<<"depth : "<<endl;
for(int i = 0; i < N; i++){
    cout<<depth[i]<<" ";
}
cout<<endl;

#endif
    //create segtree
    RMQ rmq(trav);
    
    // create parent table & sparse table 
    for(int k = 1; k < MAX_LOG2N; k++){
        for(int nodeIdx = 0; nodeIdx < N; nodeIdx++){
            // create parent table first
            parent[k][nodeIdx] = parent[k-1][ parent[k-1][nodeIdx] ];
            stable[k][nodeIdx] = stable[k-1][nodeIdx] + stable[k-1][parent[k-1][nodeIdx]];
        }
    }
#ifdef DEBUG_STABLE
for(int i = 0; i < N; i++){
    cout<<i+1<<" ";
}
cout<<endl;
for(int k = 0; k < 4; k++){
    cout<<"parent["<<k<<"]  : ";
    for(int i = 0; i < N; i++){
        cout<<parent[k][i]+1<<" ";
    }
    cout<<endl;
}

for(int k = 0; k < 4; k++){
    cout<<"stable["<<k<<"]  : ";
    for(int i = 0 ; i < N; i++){
        cout<<stable[k][i]<<" ";
    }
    cout<<endl;
}
#endif

    //query
    cin>>K;
    int D,E,lca;
    int d1,d2;
    while(K--){
        cin>>D>>E;
        D--; E--;
        lca = findLCA(D,E, rmq); //lca (nodeIdx)
        d1 = depth[D] - depth[lca]; d2 = depth[E] - depth[lca];
#ifdef DEBUG_QUERY
printf("d1 : %d, d2 : %d \n", d1,d2);
#endif
        cout<<fn(D,d1) + fn(E,d2)<<endl;
    }
    return 0;
}