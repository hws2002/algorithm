// min cut max flow
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

#define MAX_N 100
// #define DEBUG_INPUT
// #define DEBUG_CON
// #define DEBUG_DINIC

using namespace std;

int N,M;
int MAP[MAX_N][MAX_N] = {0};
int vidx[MAX_N][MAX_N] = {0};

int source_x, source_y;
const int source = 0; //idx
int sink_x, sink_y;
int sink; //idx
struct edge{
public:
    int f,c,t;
    edge * inv;
    edge(): f(0), c(0), t(0), inv(nullptr){};
    edge(int f_, int c_, int t_) :
        f(f_),
        c(c_),
        t(t_),
        inv(nullptr){};
    int residual(){
        return c - f;
    }
};

vector<edge *> edges[MAX_N*MAX_N];

void addEdge(int u, int v, int c, bool bi = true){
    edge * uv = new edge(0,c,v);
    edge * vu;
    if (bi){
        vu = new edge(0,c,u);
    } else {
        vu = new edge(0,0,u);
    }
    uv->inv = vu;
    vu->inv = uv;
    edges[u].push_back(uv);
    edges[v].push_back(vu);
};

// create graph
bool connected[MAX_N*MAX_N][MAX_N*MAX_N] = {false};

int vcnt = 0;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = { 0, 1, 0,-1};
void bfs(){
    for(int i = 0 ; i < N; i++){
        fill(vidx[i], vidx[i] + M, -1);
    }
    vector<bool> once_pushed( N*M ,false);
    int here_x = source_x; int here_y = source_y;
    queue<pair<int,int>> q;
    q.push({here_x,here_y});
    vidx[here_x][here_y] = vcnt++;
    int hidx = vidx[here_x][here_y];
    once_pushed[hidx] = true;
    int nidx;
    while(!q.empty()){
        here_x = q.front().first; here_y = q.front().second; q.pop();
        hidx = vidx[here_x][here_y];
#ifdef DEBUG_CON
		printf("here_x, here_y, hidx : %d, %d ,%d \n",here_x, here_y, hidx);
#endif
        for(int i = 0; i < 4; i++){
            int nx = here_x + dx[i]; int ny = here_y + dy[i]; 

            if( 0 <= nx && nx < N && 0 <= ny && ny < M ){
				if (MAP[nx][ny] == 1) continue;
                // find nidx
                if( vidx[nx][ny] != -1) {
                    nidx = vidx[nx][ny];
                } else {
                    vidx[nx][ny] = vcnt++;
                    nidx = vidx[nx][ny];
                }

                if( !connected[hidx][nidx] ){
					if( hidx == 0 || MAP[nx][ny] == 3){
                        addEdge(hidx,nidx,1,false);                            
                    } else if ( MAP[nx][ny] == 0){
                        addEdge(hidx,nidx,1,true);
                    }
                }
				
                connected[hidx][nidx] = true;
                connected[nidx][hidx] = true;

				if(!once_pushed[nidx]){
                    q.push({nx,ny});
#ifdef DEBUG_CON
					printf("pushed nx, ny, nidx : %d, %d, %d \n",nx,ny,nidx);
#endif
                    once_pushed[nidx] = true;
                }
            }
        }
    }
}

/* DINIC */
int max_flow = 0;
vector<int> sidx(MAX_N*MAX_N,0);
vector<int> level(MAX_N*MAX_N,0);

#ifdef DEBUG_DINIC
int cnt = 0;
#endif

bool dinic_bfs(){
    queue<int> q;
    int hidx = source;
    q.push(hidx);
    fill(level.begin(), level.begin() + vcnt, -1);
    level[hidx] = 0;
    while(!q.empty()){
        hidx = q.front(); q.pop();
        if(hidx == sink) continue;
        for(auto ep : edges[hidx]){
            int nidx = ep->t;
            if( level[nidx] == -1 && ep->residual() > 0){
                level[nidx] = level[hidx] + 1;
                q.push(nidx);
            }
        }
    }
#ifdef DEBUG_DINIC
for(int i = 0; i < vcnt; i++)
	cout<<level[i]<<" ";
cout<<endl;
if (++cnt > 10) return false;
#endif
    return level[sink] != -1;
}

int dinic_dfs(int here, int flow){
    if( here == sink) return flow;
    for(int & i = sidx[here]; i < edges[here].size(); i++){
        auto ep = edges[here][i];
        int next = ep->t;
        if ( level[next] != level[here] + 1 || ep->residual() <= 0) continue;
        int amt = dinic_dfs(next, min(flow, ep->residual()));
        if( amt > 0){
            //push
            ep->f += amt;
            ep->inv->f -= amt;
            return amt;
        }
    }
    
    return 0;
}

void dinic(){
    sink = vidx[sink_x][sink_y];
#ifdef DEBUG_DINIC
printf("vcnt, sink : %d, %d \n", vcnt, sink);
#endif
	if (sink == -1) return ;
    while(dinic_bfs()){
        fill(sidx.begin(), sidx.begin() + vcnt, 0);
        while(true){
            int amt = dinic_dfs(0,numeric_limits<int>::max());
#ifdef DEBUG_DINIC
printf("amt : %d \n", amt);
#endif
            if( amt == 0) break;
            max_flow += amt;
        }
    }
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    cin>>N>>M;
    //input
    char city;
    for(int i = 0 ; i < N; i++){
        for(int j = 0 ; j < M; j++){
            cin>>city;
            if (city == '.'){
                //do nothing
            } else if (city == '#'){
                MAP[i][j] = 1;
            } else if (city == 'K'){
                MAP[i][j] = 2;
                source_x = i; source_y = j;
            } else { // H, school
                MAP[i][j] = 3;
                sink_x = i; sink_y = j;
            }
        }
    }
	
	// if adjacent
	for(int i = 0;  i < 4; i++){
		int nx = source_x + dx[i]; int ny = source_y + dy[i];
		if( 0 <= nx && nx < N && 0 <= ny && ny < M){
			if( nx == sink_x && ny == sink_y){
				cout<<-1<<endl;
				return 0;
			}
		}
	}
#ifdef DEBUG_INPUT
for(int i = 0; i < N; i++){
    for(int j = 0 ; j < M; j++){
        cout<<MAP[i][j]<<" ";
    }
    cout<<endl;
}
cout<<endl;
#endif
    //construct graph
    bfs();
#ifdef DEBUG_CON
for(int i = 0; i < N; i++){
    for(int j = 0 ; j < M; j++){
        cout<<vidx[i][j]<<" ";
    }
    cout<<endl;
}
cout<<endl;

for(int i = 0; i < vcnt; i++){
	printf("edges[%d] : ",i);
	for(auto ep : edges[i]){
		printf("(c,t : %d, %d) ", ep->c, ep->t);
	}
	cout<<endl;
}
cout<<endl;
#endif

    dinic();
    cout<<max_flow<<endl;
    return 0;
}