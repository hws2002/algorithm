// sparse table
#include <iostream>
#include <vector>
#include <limits.h>
#include <cmath>

#define MAX_N 100'000
#define MAX_LOG2N 17 // [log2(100'000) + 1
#define endl '\n'
#define INF 1'000'000'000

using namespace std;
typedef long long ll;

int N;
int M;
vector<int> trav; // 최대 2N
vector<int> pre2node(MAX_N);

vector<int> pow2d(MAX_LOG2N);
ll stable[MAX_LOG2N][MAX_N] = {0}; // stable[k][i] : i번째 노드에서 2^k번째 조상까지의 비용. 만약 i의 2^k번째 조상이 없다면, 루트까지의 거리를 반환한다.
int parent[MAX_LOG2N][MAX_N] = {0}; // parent[k][i] : i번째 노드의 2^k번째 조상. 만약 i의 2^k번째 조상이 없다면, 루트를 가리킨다

// 아래는 모두 nodeIdx 기준
vector<pair<int,ll>> children[MAX_N];
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
        ll cost = child.second;
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
    if(u > v) swap(u,v);
    int lca = rmq.query(u,v);
    return pre2node[lca];
}

// nodeIdx 기준 s의 dist번째 조상까지의 비용을 반환한다
ll costPath(int s, int dist){
	if(dist <= 0 ) return 0;
	int k = log2(dist);
	return stable[k][s] + costPath( parent[k][s], dist - pow2d[k]);
}

// nodeIdx 기준 s의 dist번째 조상을 반환한다.
int kthnode(int s, int dist){
	if(dist <= 0) return s;
	int k = log2(dist);
	return kthnode(parent[k][s],  dist - pow2d[k]);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N;
    int A,B; ll C;
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
    cin>>M;
    int q,u,v,k,lca;
    int d1,d2;
    while(M--){
        cin>>q>>u>>v;
		u--; v--;
		lca = findLCA(u,v, rmq); //lca (nodeIdx)
		d1 = depth[u] - depth[lca]; d2 = depth[v] - depth[lca];
		if(q == 1){
			cout<<costPath(u,d1) + costPath(v,d2)<<endl;
		} else {
			cin>>k;
			k--;
			if( k <= d1){
				cout<<kthnode(u, k)+1<<endl;
			} else {
				cout<<kthnode(v, d2 - (k-d1))+1<<endl;
			}
		}
    }
    return 0;
}
