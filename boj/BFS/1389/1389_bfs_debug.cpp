#include <iostream>
#include <queue>
#include <limits.h>

// #define DEBUG_SOLVE
// #define DEBUG_QUEUE

using namespace std;



struct Node{
public:
    int _height;
    int _value;
    Node(const int & height, const int value):
        _height(height),
        _value(value){};
};

void printQueue( queue<Node *> Queue){
    cout<<"PRINTING OUT QUEUE"<<endl;
    while(!Queue.empty()){
        cout<<Queue.front()->_value<<" "; Queue.pop();
    }
    cout<<endl;
}

int N, M;
bool MAP[101][101] = {false};
int RES[101] = {0};
// int RES2[101][101] = {0};

int min_kevin_bacon = INT_MAX;
void kevin_baconBFS(const int & start){
#ifdef DEBUG_SOLVE
cout<<"start kevin_baconBFS("<<start<<")"<<endl;
#endif
    queue<Node *> Queue_friends;
    bool VISIT[101] = {false};
    Queue_friends.push(new Node(0, start));
    VISIT[start] = true;
    int kevin_bacon = 0;
    Node * NodePosi; int height, value;
    while(!Queue_friends.empty()){
#ifdef DEBUG_QUEUE
printQueue(Queue_friends);
#endif
        NodePosi = Queue_friends.front(); Queue_friends.pop();
        height = NodePosi->_height;
        value = NodePosi->_value;
        kevin_bacon+= height;
        for(int end = 1; end <= N; end++){
            if(!VISIT[end] && MAP[value][end]){
                Queue_friends.push(new Node(height+1, end));
                VISIT[end] = true;
            }
        }
        delete NodePosi;
    }
    
    min_kevin_bacon = min( min_kevin_bacon, kevin_bacon);
    RES[start] = kevin_bacon;
    return ;
}

int main(){
    //input
    cin>>N>>M;int A,B;
    for(int i = 0; i < M; i++){
        cin>>A>>B;
        MAP[A][B] = true;
        MAP[B][A] = true;
    }
    
    //solve
    for(int start = 1; start <=N; start++){
        kevin_baconBFS(start);
    }
#ifdef DEBUG_SOLVE
for(int i = 1; i <= N; i++){
    cout<<RES[i]<<" ";
}
cout<<endl;
#endif
    //output
    for(int i = 1; i <= N; i++){
        if(RES[i] == min_kevin_bacon) {
            cout<<i<<endl;
            break;
        }
    }
    return 0;
}