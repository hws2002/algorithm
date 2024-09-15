#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int N,M;
vector< vector<int> > MAP;
int * HEIGHT;
queue<int> Queue_height_index;
bool * VISIT;

int height = 0;
int getHeightBFS(const int & root){
    //reset VISIT;
    memset(VISIT, false, (N+1) * sizeof(bool));
    int parent,child;
    height = 1;
    Queue_height_index.push(root);
    VISIT[root] = true;
    
    while(!Queue_height_index.empty()){
        parent = Queue_height_index.front(); Queue_height_index.pop();
        for(int i = 0; i < MAP[parent].size(); i++){
            child = MAP[parent][i];
            if(!VISIT[child]){
                    height++;
                    Queue_height_index.push(child);
                    VISIT[child] = true;
            }
        }
    }
    HEIGHT[root] = height;
    return height;
}


int main(){
    //input
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin>>N>>M; int A,B;
    MAP.resize(N+1); VISIT = new bool[N+1]; HEIGHT = new int[N+1];
    for(int i =  0; i < M;i++){
        cin>>A>>B;
        MAP[B].push_back(A);
    }

    //solve
    int res = 0;
    for(int i = 1; i <=N; i++){
        res = max(res, getHeightBFS(i));
    }
    for(int i = 1; i <=N; i++){
        if(HEIGHT[i] == res) cout<<i<<" ";
    }
    cout<<endl;
    delete [] VISIT, HEIGHT;
    return 0;
}