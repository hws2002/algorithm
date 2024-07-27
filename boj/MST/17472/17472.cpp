#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define MAX_N 10
#define NUM_ISLAND 6
// #define DEBUG_CREATE
// #define DEBUG_EDGE
using namespace std;

int N,M;
int MAP[MAX_N][MAX_N] = {0};
bool visit[MAX_N][MAX_N] = {false};
int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};

vector< pair<int,int> > Boundary[NUM_ISLAND];
vector<pair<int, pair<int,int> > > Edges;

int getDistance(int is1, int is2){
	int dist = 100;

	for(auto p1 : Boundary[is1]){
		for(auto p2 : Boundary[is2]){
			if(p1.first == p2.first ){
				int p1s = p1.second; int p2s = p2.second;
				if (p1s > p2s) swap(p1s, p2s);
				if (p2s - p1s <= 2) continue;
				bool openroad = true;
				for(int c = p1s + 1; c < p2s; c++){
					// cout<<"imgoing"<<endl;
					if(MAP[p1.first][c]) {openroad = false; break;}
				}
				if(openroad)
					dist = min(dist, p2s - p1s);
			} else if (p1.second == p2.second){
				int p1f = p1.first; int p2f = p2.first;
				if (p1f > p2f) swap(p1f,p2f);
				if (p2f - p1f <= 2) continue;
				bool openroad = true;
				for(int r = p1f+1; r < p2f; r++){
					if(MAP[r][p1.second]) {openroad = false; break;}
				}
				if(openroad)
					dist = min(dist, p2f - p1f);
			}
		}
	}
	
	return dist-1;
}


struct DisjointSet{
public:
    vector<int> parent;
    vector<int> rank;
    
    DisjointSet(const int n){
        rank.resize(n,0);
        parent.resize(n);
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }
    }
    
    //find
    int find(int u){
        if(parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }
    
    //merge
    bool merge(int u, int v){
        u = find(u); v = find(v);    
        if( u == v ) return false;
        if(rank[u] > rank[v]) swap(u,v);
        parent[u] = v;
        if( rank[u] == rank[v]) rank[v]++;
        return true;
    }
};


int kruskal(int gsize, DisjointSet& set){
	int cnt = 0;
	int res = 0;
	int w,u,v;
	bool foundmst = false;
	for(auto e : Edges){
		w = e.first; u = e.second.first; v= e.second.second;
		if( set.find(u) == set.find(v)) continue;
		set.merge(u,v);
		res += w;
		cnt++;
		if(cnt >= gsize-1) {
			foundmst = true;
			break;
		}
	}
	if(foundmst) return res;
	return -1;
}

int main(){
	cin>>N>>M;
	for(int i = 0; i < N; i++){
		for(int j =0; j < M; j++){
			cin>>MAP[i][j];
		}
	}
	
	//create graph
	int islandIdx = 0;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			if(!visit[i][j] && MAP[i][j]){
				queue<int> q;
				q.push(i*11 + j);
				Boundary[islandIdx].push_back({i,j});
				visit[i][j] = true;
				int x,y,nx,ny;
				while(!q.empty()){
					x = q.front()/11; y = q.front() % 11;
					q.pop();
					for(int i = 0; i < 4; i++){
						nx = x + dx[i]; ny = y + dy[i];
						if(!(0<= nx && nx < N && 0 <= ny && ny < M)) continue;
						if(!visit[nx][ny] && MAP[nx][ny]){
							q.push( nx * 11 + ny );
							visit[nx][ny] = true;
							Boundary[islandIdx].push_back({nx,ny});
						}	
					}
					
				}
				islandIdx++;
			}
		}
	}
#ifdef DEBUG_CREATE
for(int i = 0; i < islandIdx;i++){
	for(auto b : Boundary[i]){
		printf("(%d,%d) ",b.first, b.second);
	}
	cout<<endl;
}
#endif
	
	//init edges
	for(int i = 0; i < islandIdx; i++){
		for(int j = i+1; j < islandIdx; j++){
			//get min dist between i and j
			int distij = getDistance(i,j);
			if(distij < 99) Edges.push_back({distij,{i,j}});
		}
	}
	std::sort(Edges.begin(), Edges.end());
#ifdef DEBUG_EDGE
for(auto e : Edges){
	printf("(%d,%d,%d) ", e.first, e.second.first, e.second.second);
}
#endif
	
	//kruskal
	DisjointSet set(islandIdx);
	cout<<kruskal(islandIdx, set)<<endl;
	
	return 0;
}