#include <iostream>
#include <queue>
#include <utility>

using namespace std;
#define DEBUG_INPUT
#define DEBUG_WHILE
#define DEBUG_MOVE
int N,M; // 1<= N, M <= 20
int BOARD[22][22] = {0}; // . : 1, # : 2, o : 1
bool VISIT[5153633] = {false};
struct Node {
public:
    int _step;
    int a_x,a_y,b_x,b_y;
    Node(const int & step, const int & ax, const int & ay,  const int & bx, const int & by) :
        _step(step),
        a_x(ax),
        a_y(ay),
        b_x(bx),
        b_y(by)
    {}
};

queue< Node * > Queue_Pair_a_b;

bool moveCoin(const int & ax, const int & ay,  const int & bx, const int & by, const int & res){
    int a_x, a_y, b_x, b_y;
    bool coin_a_out;
    bool coin_b_out;
    bool coin_overlap;
    //move left
    a_x = ax; a_y = ay; b_x = bx; b_y = by;
    coin_a_out = false; coin_b_out = false; coin_overlap = false;
    a_y--;
    if(BOARD[a_x][a_y] == 0){
        coin_a_out = true;
    } else if (BOARD[a_x][a_y] == 2){
        a_y++;
    }
    
    b_y--;
    if(BOARD[b_x][b_y] == 0){
        coin_b_out = true;
    } else if (BOARD[b_x][b_y] == 2){
        b_y++;
    }
    
    if ((a_x == b_x) && (a_y == b_y)){
        coin_overlap = true;
    }

    
    if(!coin_overlap && !VISIT[a_x*22*22*22 + a_y*22*22 + b_x*22 + b_y] ){
        if( coin_a_out ^ coin_b_out ) return true;
        else if ( !coin_a_out && !coin_b_out ) {
            Queue_Pair_a_b.push(new Node(res+1,a_x,a_y,b_x,b_y));
            VISIT[a_x*22*22*22 + a_y*22*22 + b_x*22 + b_y] = true;
#ifdef DEBUG_MOVE
cout<<"pushed ("<<a_x<<","<<a_y<<","<<b_x<<","<<b_y<<")"<<endl;
#endif
        }
    }
    
    //move up
    a_x = ax; a_y = ay; b_x = bx; b_y = by;
    coin_a_out = false; coin_b_out = false; coin_overlap = false;
    a_x--;
    if( BOARD[a_x][a_y] == 0){
        coin_a_out = true;      
    } else if (BOARD[a_x][a_y] == 2){
        a_x++;
    }
    
    b_x--;
    if(BOARD[b_x][b_y] == 0){
        coin_b_out = true;
    } else if (BOARD[b_x][b_y] == 2){
        b_x++;
    }
    
    if ((a_x == b_x) && (a_y == b_y)){
        // don't push to queue
        coin_overlap = true;
    }
    
    if(!coin_overlap && !VISIT[a_x*22*22*22 + a_y*22*22 + b_x*22 + b_y] ){
        if( coin_a_out ^ coin_b_out ) return true;
        else if ( !coin_a_out && !coin_b_out ) {
            Queue_Pair_a_b.push(new Node(res+1,a_x,a_y,b_x,b_y));
            VISIT[a_x*22*22*22 + a_y*22*22 + b_x*22 + b_y] = true;
#ifdef DEBUG_MOVE
cout<<"pushed ("<<a_x<<","<<a_y<<","<<b_x<<","<<b_y<<")"<<endl;
#endif
        }
    }
    //move right
    a_x = ax; a_y = ay; b_x = bx; b_y = by;
    coin_a_out = false; coin_b_out = false; coin_overlap = false;
    b_y++;
    if (BOARD[b_x][b_y] == 0){
        coin_b_out = true;      
    } else if (BOARD[b_x][b_y] == 2){
        b_y--;
    }

    a_y++;
    if (BOARD[a_x][a_y] == 0){
        coin_a_out = true;
    } else if (BOARD[a_x][a_y] == 2){
        a_y--;
    }
    
    if ((a_x == b_x) && (a_y == b_y)){
        // don't push to queue
        coin_overlap = true;
    }
    
    if(!coin_overlap && !VISIT[a_x*22*22*22 + a_y*22*22 + b_x*22 + b_y] ){
        if( coin_a_out ^ coin_b_out ) return true;
        else if ( !coin_a_out && !coin_b_out ) {
            Queue_Pair_a_b.push(new Node(res+1,a_x,a_y,b_x,b_y));
            VISIT[a_x*22*22*22 + a_y*22*22 + b_x*22 + b_y] = true;
#ifdef DEBUG_MOVE
cout<<"pushed ("<<a_x<<","<<a_y<<","<<b_x<<","<<b_y<<")"<<endl;
#endif
        }
    }
    //move down
    a_x = ax; a_y = ay; b_x = bx; b_y = by;
    coin_a_out = false; coin_b_out = false; coin_overlap = false;
    
    b_x++;
    if (BOARD[b_x][b_y] == 0){
        coin_b_out = true;      
    } else if (BOARD[b_x][b_y] == 2){
        b_x--;
    }

    a_x++;
    if (BOARD[a_x][a_y] == 0){
        coin_a_out = true;
    } else if (BOARD[a_x][a_y] == 2){
        a_x--;
    }
    
    if ((a_x == b_x) && (a_y == b_y)){
        // don't push to queue
        coin_overlap = true;
    }
    
    if(!coin_overlap && !VISIT[a_x*22*22*22 + a_y*22*22 + b_x*22 + b_y] ){
        if( coin_a_out ^ coin_b_out ) return true;
        else if ( !coin_a_out && !coin_b_out ) {
            Queue_Pair_a_b.push(new Node(res+1,a_x,a_y,b_x,b_y));
            VISIT[a_x*22*22*22 + a_y*22*22 + b_x*22 + b_y] = true;
#ifdef DEBUG_MOVE
cout<<"pushed ("<<a_x<<","<<a_y<<","<<b_x<<","<<b_y<<")"<<endl;
#endif
        }
    }
    
    return false;
}

int main(){
    //input
    cin>>N>>M; char temp; 
    int ax, ay,bx,by;
    for(int i = 1 ; i < N+1; i++){
        for(int j = 1; j < M+1; j++){
            cin>>temp;
            if(temp == '.'){
                BOARD[i][j] = 1;
            } else if(temp == '#'){
                BOARD[i][j] = 2;
            } else {
                BOARD[i][j] = 1;
                if( ax == 0) {
                    ax = i; ay = j;
                } else {
                    bx = i; by = j;
                }
            }
        }
    }
    
    if(ax*22 + ay > bx*22 + by) {
        // a is always ahead of b
        swap(ax,bx);
        swap(ay,by);
    }
    
    int res = 0;
    Queue_Pair_a_b.push(new Node(res,ax,ay,bx,by));
    VISIT[ax*22*22*22 + ay*22*22 + bx*22 + by] = true;
#ifdef DEBUG_INPUT
cout<<"PRINTING OUT BOARD : "<<endl;
for(int i = 0 ; i < N+2; i++){
    for(int j = 0; j < M+2; j++){
        cout<<BOARD[i][j];
    }
    cout<<endl;
}
#endif

    //solve

    Node * current_node; bool solved = false;
    while(!Queue_Pair_a_b.empty()){
        current_node = Queue_Pair_a_b.front(); Queue_Pair_a_b.pop();
        res = current_node->_step; if(res == 10) break;
        ax = current_node->a_x;
        ay = current_node->a_y;
        bx = current_node->b_x;
        by = current_node->b_y;
#ifdef DEBUG_WHILE
cout<<" res, ax, ay, bx, by : "<<res<<" "<<ax<<" "<<ay<<" "<<bx<<" "<<by<<" "<<endl;
#endif
        if(moveCoin(ax,ay,bx,by,res)) {
            solved = true;
            break;
        }
        delete current_node;
    }
    
    if(!solved){
        cout<<-1<<endl;
    } else {
        cout<<++res<<endl;
    }
    return 0;
}
