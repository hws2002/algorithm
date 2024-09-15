//sparse table
#include <iostream>
#include <vector>
#include <cmath>

#define MAX_N 100'000
#define MAX_M 100'000
#define MAX_LOG2N 18
#define INF 10'000'000

// #define DEBUG_TRAV
// #define DEBUG_STABLE
// #define DEBUG_LCA
#define endl '\n'
using namespace std;

int N,M;
int pow2d[MAX_LOG2N];

vector<int> children[MAX_N]; // nodeIdx 기준
vector<int> trav;
vector<int> node2pre(MAX_N,-1);
vector<int> pre2node(MAX_N,-1);
vector<int> floctrav(MAX_N,-1); // nodeIdx 기준
// vector<int> depth; // nodeIdx 기준 - unnecessary

int stable[MAX_LOG2N][MAX_N<<1]; // floctrav 기준
// stable[k][i] : trav[i,i+2^k-1] 중 가장 작은 수를 반환한다. (반환 값은 preIdx)

int preIdx = 0;

void travPre(const int here, const int parent){
    node2pre[here] = preIdx;
    pre2node[preIdx] = here;
    preIdx++;
    floctrav[here] = trav.size();
    trav.push_back(node2pre[here]);
    for(auto child : children[here]){
        if(child == parent) continue;
        travPre(child, here);
        //돌아올때도 trav에 넣어준다
        trav.push_back(node2pre[here]);
    }
}

// trav[s, s+dist] 중 가장 작은 숫자를 반환한다 (반환 값은 preIdx)
int fn(int s, int dist){
    if(dist < 0) return INF;
    int k1 = (int)log2(dist+1);
    return min( stable[k1][s] , fn(s + pow2d[k1], dist - pow2d[k1]));
}


// nodeIdx기준 u와 v 의 LCA를 반환한다.
int findLCA(int u, int v){
    u = floctrav[u]; v = floctrav[v];
    if( u > v ) swap(u,v);
    int dist = v - u;
    return fn(u,dist);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    cin>>N;
    int u,v;
    for(int i = 0; i < N-1; i++){
        cin>>u>>v;
        u--; v--;
        children[u].push_back(v);
        children[v].push_back(u);
    }
    
    //pre
    for(int i = 0 ; i < MAX_LOG2N; i++){
        pow2d[i] = pow(2,i);
    }
    
    //travPre
    travPre(0,-1); // root = 0
#ifdef DEBUG_TRAV
cout<<"node2pre : "<<endl;
for(int i = 0; i < N; i++){
    cout<<i+1<<" ";    
}
cout<<endl;

for(int i = 0; i < N; i++){
    cout<<node2pre[i]<<" ";
}
cout<<endl;

cout<<"trav : "<<endl;
for(auto e : trav){
	cout<<e<<" ";
}
cout<<endl;
#endif

    //create sparse table
    for(int i = 0; i < trav.size(); i++){
        stable[0][i] = trav[i];
    }
    
    for(int k = 1; k < MAX_LOG2N; k++){
        for(int i = 0; i + pow2d[k-1] < trav.size(); i++){
            stable[k][i] = min(stable[k-1][i] , stable[k-1][i+ pow2d[k-1]]);
        }
        for(int i = trav.size() - pow2d[k-1]; i < trav.size(); i++){
            stable[k][i] = stable[k-1][i];
        }
    }
#ifdef DEBUG_STABLE
cout<<"stable : "<<endl;
for(int k = 0; k < MAX_LOG2N; k++){
	printf("stable[%d] : ",k);
	for(int i = 0; i < trav.size(); i++){
		cout<<stable[k][i]<<" ";
	}
	cout<<endl;
}
#endif
    //query
    cin>>M;
    while(M--){
        cin>>u>>v;
        u--;v--;
        cout<<pre2node[findLCA(u,v)]+1<<endl;
    }
    
    return 0;
}

