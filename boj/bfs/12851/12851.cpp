#include <iostream>
#include <queue>
#include <limits.h>

using namespace std;

struct Node{
public : 
    int _height;
    int _x;
    Node(const int & height, const int x):
        _height(height),
        _x(x){};
};

queue<Node> Queue_Node;
int N,K;
int FASTEST_VISIT[100001] = {0};
int WAYS[100001] = {0};

int main(){
    //input
    cin>>N>>K;
    std::fill(FASTEST_VISIT, FASTEST_VISIT + 100001, -1);
    Queue_Node.push(Node(0,N));
    FASTEST_VISIT[N] = 0;
    WAYS[N] = 1;
    int height, x;
    while(!Queue_Node.empty()){
        height = Queue_Node.front()._height; 
        x = Queue_Node.front()._x;
        Queue_Node.pop();
        
        if( FASTEST_VISIT[K] != -1 && height >= FASTEST_VISIT[K]) continue;
        
        if ( x < K){
            if( x + 1 <= 100000){
                if(FASTEST_VISIT[x+1] < 0){
                    Queue_Node.push(Node(height+1, x+1));
                    FASTEST_VISIT[x+1] = height + 1;
                    WAYS[x+1] += WAYS[x];
                } else if (FASTEST_VISIT[x+1] >= height + 1){
                    WAYS[x+1] += WAYS[x];
                }
            }
            
            if( 2 * x <= 100000){
                if(FASTEST_VISIT[2*x] < 0){
                    Queue_Node.push(Node(height+1, 2*x));
                    FASTEST_VISIT[2*x] = height + 1;
                    WAYS[2*x] += WAYS[x];
                } else if (FASTEST_VISIT[2*x] >= height + 1){
                    WAYS[2*x] += WAYS[x];
                }
            }
            
            if( x - 1 >= 0 ){
                if(FASTEST_VISIT[x-1] < 0 ){
                    Queue_Node.push(Node(height+1, x-1));
                    FASTEST_VISIT[x-1] = height + 1;
                    WAYS[x-1] += WAYS[x];
                } else if (FASTEST_VISIT[x-1] >= height + 1){
                    WAYS[x-1] += WAYS[x];
                }
            }
        }
        
        if ( x > K && x - 1 >= 0){
            if(FASTEST_VISIT[x-1] < 0 ){
                Queue_Node.push(Node(height+1, x-1));
                FASTEST_VISIT[x-1] = height + 1;
                WAYS[x-1] += WAYS[x];
            } else if (FASTEST_VISIT[x-1] >= height + 1){
                WAYS[x-1] += WAYS[x];
            }
        }
    }
    
    
    
    //output
    cout<<FASTEST_VISIT[K]<<endl<<WAYS[K]<<endl;
    return 0;
}