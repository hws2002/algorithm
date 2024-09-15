#include <iostream>
#include <queue>

using namespace std;

int N,M,V;
bool MAP[1001][1001] = {false};
bool VISIT[1001] = {false};
queue<int> Queue_BFS;

void DFS(const int & current){
    for(int end = 1; end <= N; end++){
        if( MAP[current][end] && !VISIT[end]){
            cout<<end<<" ";
            VISIT[end] = true;
            DFS(end);
        }
    }
}

int main(){
    //input
    cin>>N>>M>>V;
    int start,end;
    for(int i = 0 ; i < M; i++){
        cin>>start>>end;
        MAP[start][end] = true; MAP[end][start] = true;
    }

    //DFS
    int current = V;
    VISIT[current] = true;
    cout<<current<<" ";
    DFS(current);
    cout<<endl;
    //BFS
    std::fill(VISIT, VISIT + N + 1, false);
    current = V;
    Queue_BFS.push(current);
    VISIT[current] = true;
    while(!Queue_BFS.empty()){
        current = Queue_BFS.front(); Queue_BFS.pop();
        cout<<current<<" ";
        for(int end = 1; end <= N; end++){
            if( MAP[current][end] && !VISIT[end]){
                VISIT[end] = true;
                Queue_BFS.push(end);
            }
        }
    }

    cout<<endl;
    return 0;
}