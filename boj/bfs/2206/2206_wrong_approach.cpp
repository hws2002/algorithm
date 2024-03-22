#include <iostream>
#include <vector>
#include <queue>

#define DEBUG_INPUT
#define DEBUG_BFS
using namespace std;


int N, M;
bool MAP[1002][1002] = {{false}};
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

#ifdef DEBUG_BFS
void printQueue(queue< Node *> Queue_Node){
    cout<<"printing out current Queue_Node"<<endl;
    while(!Queue_Node.empty()){
        cout<<"("<<Queue_Node.front()->_height<<","<<Queue_Node.front()->_x<<","<<Queue_Node.front()->_y<<") ";
        Queue_Node.pop();
    }
    cout<<endl;
}
#endif

int main(){
    //input
    cin>>N>>M; char temp;
    for(int i = 1; i < N+1; i++){
        for(int j = 1 ; j < M+1; j++){
            cin>>temp;
            MAP[i][j] = temp - '0';
            MAP[i][j] = !MAP[i][j];
        }
    }
    Vector_walls.push_back(1003);
    for(int i = 1; i < N+1; i++){
        for(int j = 1; j < M+1; j++){
            if(!MAP[i][j]){
                int zeros = 0;
                for(int l = 0 ; l < 4; l++){
                    if(!MAP[i + dx[l]][j + dy[l]]){
                        zeros++;
                    }
                }
                if(zeros<=2) Vector_walls.push_back(i * 1002 + j);
            }
        }
    }
#ifdef DEBUG_INPUT
for(int i = 0 ; i < N+2;i++){
    for(int j = 0; j < M+2; j++){
        printf("%d",MAP[i][j]);
    }
    cout<<endl;
}
cout<<"printing out Vector_walls : "<<endl;
for(iter = Vector_walls.begin(); iter!= Vector_walls.end(); iter++){
    cout<<(*iter)/1002<<" "<<(*iter)%1002<<endl;
}
cout<<endl;
#endif
    //solve - bfs
    int res = 1000002;
    for(iter = Vector_walls.begin(); iter!= Vector_walls.end(); iter++){
        for(int i = 1 ; i < N+1; i++){
            for(int j = 1 ; j < M+1; j++){
                VISIT[i][j] = false;
            }
        }
        MAP[(*iter)/1002][(*iter)%1002] = true;
        Queue_Node.push(new Node(1,1,1));
        VISIT[1][1] = true; int height, x, y; Node * current_node;
        int possible_res = 1000002; bool found_route = false;
#ifdef DEBUG_BFS
cout<<"start searching route with destroying wall : "<<(*iter)/1002<<","<<(*iter)%1002<<endl;
#endif
        while(!Queue_Node.empty()){
#ifdef DEBUG_BFS
printQueue(Queue_Node);
#endif
            current_node = Queue_Node.front(); Queue_Node.pop();
            height = current_node->_height; x = current_node->_x; y = current_node->_y;
            if(height >= res-1) break;
            delete current_node;
            for(int i = 0 ; i < 4; i ++){
                if( (x + dx[i]) == N && (y + dy[i]) == M){
                    possible_res = height+1;
                    found_route = true;
                }
                if(!VISIT[x+dx[i]][y+dy[i]] && MAP[x + dx[i]][y+dy[i]]){
                    Queue_Node.push(new Node(height+1, x+dx[i], y+dy[i]));
                    VISIT[x+dx[i]][y+dy[i]] = true;
                }
            }
            if(found_route) break;
        }
        res = min(res, possible_res);
        MAP[(*iter)/1002][(*iter)%1002] = false;
    }
    
    //output
    if(res == 1000002) cout<<-1<<endl;
    else cout<<res<<endl;
    return 0;
}
