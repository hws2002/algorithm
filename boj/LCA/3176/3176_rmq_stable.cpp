// sparse table + rmq
#include <iostream>
#include <vector>
#include <limits.h>
#include <cmath>

#define MAX_N 100'000
#define MAX_LOG2N 17 // [log2(100,000)] + 1
#define endl '\n'
#define INF 1'000'000'000
// #define DEBUG_STABLE
// #define DEBUG_QUERY
using namespace std;
int N;
int K;
vector<int> trav; // 최대 2N
vector<int> pre2node(MAX_N);

vector<int> pow2d(MAX_LOG2N);
int parent[MAX_LOG2N][MAX_N] = {0}; // parent[k][i] : i번째 노드의 2^k번째 조상. 만약 i의 2^k번째 조상이 없다면, 루트를 가리킨다
int stablem[MAX_LOG2N][MAX_N] = {0}; // stable[k][i] : i번째 노드에서 2^k번째 조상까지의 거리들중 최소값. 만약 i의 2^k번째 조상이 없다면, 루트까지의 거리 중 최소값을 반환한다.
int stableM[MAX_LOG2N][MAX_N] = {0}; // stable[k][i] : i번째 노드에서 2^k번째 조상까지의 거리들중 최소값. 만약 i의 2^k번째 조상이 없다면, 루트까지의 거리 중 최대값을 반환한다.

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
        stablem[0][next] = cost;
        stableM[0][next] = cost;
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
    if(u > v) swap(u,v);
    int lca = rmq.query(u,v);
    return pre2node[lca];
}

// nodeIdx 기준 s의 dist번째 조상까지의 거리들 중 최소값과 최대값을 반환한다.
pair<int,int> fn(int s, int dist){
    if(dist <= 0) return {INF,-1};
	int k = log2(dist);
#ifdef DEBUG_QUERY
printf("fn(%d, %d, %d) \n", s, dist, k);
#endif
	auto pii = fn( parent[k][s], dist - pow2d[k]);
	return { min(stablem[k][s], pii.first), max(stableM[k][s], pii.second) };
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
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
    //create segtree
    RMQ rmq(trav);
    // cout<<"hello"<<endl;
    // create parent table & sparse table 
    stablem[0][0] = INF; 
	stableM[0][0] = -1;
	for(int k = 1; k < MAX_LOG2N; k++){
        for(int nodeIdx = 0; nodeIdx < N; nodeIdx++){
            // create parent table first
            parent[k][nodeIdx] = parent[k-1][ parent[k-1][nodeIdx] ];
			stablem[k][nodeIdx] = min(stablem[k-1][nodeIdx], stablem[k-1][parent[k-1][nodeIdx]]);
			stableM[k][nodeIdx] = max(stableM[k-1][nodeIdx], stableM[k-1][parent[k-1][nodeIdx]]);
        }
    }
#ifdef DEBUG_STABLE
cout<<"stablem : "<<endl;
	
for(int i = 0 ; i < N; i++){
	cout<<i+1<<" ";
}
cout<<endl;
	
for(int k = 0; k < 3; k++){
	printf("stablem[%d] : ",k);
	for(int i = 0; i < N; i++){
		cout<<stablem[k][i]<<" ";
	}
	cout<<endl;
}

cout<<"stableM : "<<endl;
for(int i = 0 ; i < N; i++){
	cout<<i+1<<" ";
}
cout<<endl;
	
for(int k = 0; k < 3; k++){
	printf("stableM[%d] : ",k);
	for(int i = 0; i < N; i++){
		cout<<stableM[k][i]<<" ";
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
printf("D, E, lca, d1, d2 : %d, %d, %d, %d, %d \n", D, E, lca, d1, d2);
#endif
		auto fnd1 = fn(D,d1);
		auto fnd2 = fn(E,d2);
		cout<<min(fnd1.first , fnd2.first)<<" ";
		cout<<max(fnd1.second, fnd2.second)<<endl;
    }
    return 0;
}