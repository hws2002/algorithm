#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

// #define DEBUG_BFS
// #define DEBUG_INPUT
// #define DEBUG_VISIT
using namespace std;

int N,M;
vector< vector<int> > MAP;
int HEIGHT[10001] = {0};
queue<int> Queue_height_index;
bool * VISIT;

int height = 0;
int getHeightBFS(const int & root){
#ifdef DEBUG_BFS
cout<<"starts bfs with : "<<root<<endl;
#endif
    //reset VISIT;
    memset(VISIT, false, (N+1) * sizeof(bool));
#ifdef DEBUG_VISIT
for(int i = 1; i <= N; i++){
    cout<<i<<" ";
}
cout<<endl;
for(int i = 1; i <= N; i++){
    cout<<VISIT[i]<<" ";
}
cout<<endl;
#endif
    int parent,child;
    height = 1;
    Queue_height_index.push(root);
    VISIT[root] = true;
    
    while(!Queue_height_index.empty()){
        parent = Queue_height_index.front(); Queue_height_index.pop();
        for(int i = 0; i < MAP[parent].size(); i++){
            child = MAP[parent][i];
#ifdef DEBUG_BFS
cout<<"child : "<<child<<endl;
#endif
            if(!VISIT[child]){
                    height++;
                    Queue_height_index.push(child);
#ifdef DEBUG_BFS
cout<<"pushed : "<<child<<endl;
#endif
                    VISIT[child] = true;
            }
        }
    }
    
    HEIGHT[root] = height;
#ifdef DEBUG_BFS
cout<<"height : "<<height<<endl;
#endif
    return height;
}


int main(){
    //input
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin>>N>>M; int A,B;
    MAP.resize(N+1); VISIT = new bool[N+1];
    for(int i =  0; i < M;i++){
        cin>>A>>B;
        MAP[B].push_back(A);
    }
    
#ifdef DEBUG_INPUT
for(int i = 1; i <=N; i++){
    cout<<"CHILDREN of "<<i<<endl;
    for(int j = 0 ; j < MAP[i].size(); j++){
        cout<<MAP[i][j]<<" ";
    }
    cout<<endl;
}
#endif

    //solve
    int res = 0;
    for(int i = 1; i <=N; i++){
        res = max(res, getHeightBFS(i));
    }
    for(int i = 1; i <=N; i++){
        if(HEIGHT[i] == res) cout<<i<<" ";
    }
    cout<<endl;
    delete [] VISIT;
    return 0;
}