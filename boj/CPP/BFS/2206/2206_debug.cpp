#include <iostream>
#include <queue>

// #define DEBUG_INPUT
// #define DEBUG_BFS
using namespace std;


int N, M;
int MAP[1002][1002] = {{0}};
bool VISIT[1002][1002] = {{false}};
vector<int> Vector_walls;
vector<int>::iterator iter;
struct Node {
public:
    int _height;
    int _x;
    int _y;
    Node(const int & height,const int & x, const int & y) :
        _height(height),
        _x(x),
        _y(y){};
    
};
queue< Node *> Queue_Node;

int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};


int main(){
    //input
    cin>>N>>M; char temp;
    
    //trivial case
    if(N==1 && N==M) {
        cout<<1<<endl;
        return 0;
    }
    for(int i = 1; i < N+1; i++){
        for(int j = 1 ; j < M+1; j++){
            cin>>temp;
            MAP[i][j] = temp - '0';
            MAP[i][j] = !MAP[i][j];
        }
    }
#ifdef DEBUG_INPUT
for(int i = 0 ; i < N+2;i++){
    for(int j = 0; j < M+2; j++){
        printf("%d",MAP[i][j]);
    }
    cout<<endl;
}
#endif
        
    //solve - bfs
    int res = 1000002;
    //bfs(1,1,N,M);
    for(int j = 0; j < M+2;j++) {
        VISIT[0][j] = true;
        VISIT[N+1][j] = true;
    }
    for(int i = 1; i < N+1; i++){
        VISIT[i][0] = true;
        VISIT[i][M+1] = true;
    }
    Queue_Node.push(new Node(1,1,1)); VISIT[1][1] = true; 
    int height, x, y; Node * current_node;
    bool found_route = false;
    while(!Queue_Node.empty()){
        current_node = Queue_Node.front(); Queue_Node.pop();
        height = current_node->_height; x = current_node->_x; y = current_node->_y;
        delete current_node;
        for(int i = 0 ; i < 4; i ++){
            if( !found_route && (x + dx[i]) == N && (y + dy[i]) == M  ){
                //reached (N,M)
                res = height+1; 
                found_route = true;
            }
            if(!VISIT[x+dx[i]][y+dy[i]] && MAP[x+dx[i]][y+dy[i]] == 0){
                //encountered a wall (except fence)
                MAP[x+dx[i]][y+dy[i]] = (height+1);
                VISIT[x+dx[i]][y+dy[i]] = true;
            }
            if(!VISIT[x+dx[i]][y+dy[i]] && MAP[x + dx[i]][y+dy[i]] == 1){
                //common road
                Queue_Node.push(new Node(height+1, x+dx[i], y+dy[i]));
                VISIT[x+dx[i]][y+dy[i]] = true;
            }
        }
    }
    
    for(int i = 1 ; i < N+1; i++){
        for(int j = 1 ; j < M+1; j++){
            VISIT[i][j] = false;
        }
    }
    //bfs(N,M,1,1);
    Queue_Node.push(new Node(1,N,M)); VISIT[N][M] = true;
    while(!Queue_Node.empty()){
        current_node = Queue_Node.front(); Queue_Node.pop();
        height = current_node->_height; x = current_node->_x; y = current_node->_y;
        delete current_node;
        for(int i = 0 ; i < 4; i ++){
            if(!VISIT[x+dx[i]][y+dy[i]] && MAP[x+dx[i]][y+dy[i]] > 1){
                //encountered a wall that can be reached from (1,1)
                res = min(res, MAP[x+dx[i]][y+dy[i]] + height);
                VISIT[x+dx[i]][y+dy[i]] = true;
            }
            if(!VISIT[x+dx[i]][y+dy[i]] && MAP[x + dx[i]][y+dy[i]] == 1){
                //common road
                Queue_Node.push(new Node(height+1, x+dx[i], y+dy[i]));
                VISIT[x+dx[i]][y+dy[i]] = true;
            }a
        }
    }

    
    //output
    if(res == 1000002) cout<<-1<<endl;
    else cout<<res<<endl;
    return 0;
}
