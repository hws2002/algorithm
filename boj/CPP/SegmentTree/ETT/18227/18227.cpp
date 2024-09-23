#include <iostream>
#include <vector>
#include <queue>

#define endl '\n'
#define MAX_N 200'000

// #define DEBUG_BFS
// #define DEBUG_DFS
using namespace std;

int N,C;

vector<int> edges[MAX_N];


//bfs - find level

vector<int> level(MAX_N,-1);
void bfs(){
    queue<int> q;
    int here = C;
    q.push(here);
    level[here] = 0;
    while(!q.empty()){
        here = q.front(); q.pop();
		// printf("here : %d \n", here);
        for(auto next : edges[here]){
            if( level[next] != -1) continue;
            level[next] = level[here] + 1;
            q.push(next);            
        }
    }
}

//dfs - find boundary
vector<pair<int,int>> boundary(MAX_N,{-1,-1});
int vcnt = 0;
void dfs(const int here){
	boundary[here].first = vcnt++;
	
	for(auto next : edges[here]){
		if( boundary[next].first != -1) continue;
		dfs(next);
	}
	
	boundary[here].second = vcnt-1;
	return ;
}

struct RSQ{
public:
	vector<int> rangeSum;
	int n;
	
	RSQ(const int N_){
		n = N_;
		rangeSum = vector<int>(4*n,0);
	}
	
	
	//add
	int add(int idx, int toadd, int nn, int nl, int nr){
		if( idx < nl || nr < idx) return rangeSum[nn];
		if( idx <= nl && nr <= idx) return rangeSum[nn] += toadd;
		int mid = (nl + nr) >>1;
		return rangeSum[nn] = add(idx, toadd, nn*2, nl, mid) + 
							add(idx, toadd, nn*2+1, mid+1, nr);
	}
		
	//add - interface
	void add(int idx, int toadd){ // assert(toadd==1)
		add(idx, toadd, 1, 0, n-1);
	}
	
	//query
	int query(int l, int r, int nn, int nl, int nr){
		if( r < nl || nr < l) return 0;
		if( l <= nl && nr <= r) return rangeSum[nn];
		int mid = (nl + nr) >> 1;
		return query(l,r,nn*2, nl, mid) + query(l, r,nn*2+1, mid+1, nr);
	}

	//query - interface
	int query(int l, int r){
		return query(l,r,1,0,n-1);
	}
};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    cin>>N>>C;
    C--;
    int x,y;
    for(int i = 0 ; i < N-1; i++){
        cin>>x>>y;
        x--;y--;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
    
    //find level
    bfs();
#ifdef DEBUG_BFS
cout<<"level "<<endl;
for(int i = 0; i < N; i++){
    cout<<i<<" ";
}
cout<<endl;
for(int i = 0 ; i < N; i++){
    cout<<level[i]<<" ";
}
cout<<endl;
#endif
    dfs(C);

#ifdef DEBUG_DFS
cout<<"dfs graph : "<<endl;
for(int i = 0 ; i < N; i++){
	cout<<boundary[i].first<<" ";
}
cout<<endl;
for(int i = 0 ; i < N; i++){	
	cout<<boundary[i].second<<" ";
}
cout<<endl;
#endif
	
	// range sum query segtree
	RSQ rsq(N);
	
    //query
    int Q;
    cin>>Q;
	int op;
    while(Q--){
    	cin>>op>>x;
		x--;
		if( op == 1){ // A도시에 '물이 채워진 횟수'를 추가한다.
			rsq.add(boundary[x].first,1);
		} else { // A도시에 얼마만큼의 물이 채워져 있는지 출력한다.
			cout << 1LL * rsq.query( boundary[x].first, boundary[x].second) * (level[x] + 1) << endl;
		}
    }
    return 0;
}