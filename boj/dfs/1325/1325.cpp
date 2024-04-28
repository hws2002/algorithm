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

void getHeightDFS(const int & root){
    int child;
    VISIT[root] = true;
    for(int i = 0 ; i < MAP[root].size(); i++){
        child = MAP[root][i];
        if(!VISIT[child]){
            height++;
            VISIT[child] = true;
            getHeightDFS(child);
        }
    }
    
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
        //dfs - recursion
        //reset height
        height = 1;
        //reset VISIT
        memset( VISIT, 0 ,(N+1) * sizeof(bool) );
        getHeightDFS(i);
        HEIGHT[i] = height;
        res = max(res, height);
    }
    for(int i = 1; i <=N; i++){
        if(HEIGHT[i] == res) cout<<i<<" ";
    }
    cout<<endl;
    delete [] VISIT, HEIGHT;
    return 0;
}