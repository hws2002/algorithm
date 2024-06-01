// 절단점 찾기 알고리즘
// 입력으로 주어지는 그래프가 연결 그래프가 아닐 수 도 있다는 점에 유의!

#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_V 10'000

using namespace std;

int V,E;
vector<int> adj[MAX_V];
vector<int> discovered;
vector<bool> isCutVertex;
vector<int> cutVertexes;
int cnt = 0;

int findCutVertex(const int here, const bool isRoot){
    discovered[here] = cnt++;
    int ret = discovered[here];
    int children = 0;
    for(auto there : adj[here]){
        if( discovered[there] == -1){ //트리 간선
            children++; // 이 코드가 왜 여기에 위치해야 하는지 알아야됨
            int subtree = findCutVertex(there,false);
            if( !isRoot && subtree >= discovered[here] ){
                if(isCutVertex[here] == false) cutVertexes.push_back(here);
                isCutVertex[here] = true;
                // 이 업데이트가 여러번 발생할 수 있다는 사실!
            }
            ret = min(ret, subtree);
        } else {
            ret = min(ret, discovered[there]);
        }
    }
    
    
    if(isRoot) {
        isCutVertex[here] = (children >= 2);
        if(isCutVertex[here]) cutVertexes.push_back(here);
    }
    return ret;
}

void findCutVertexAll(){
    //initialize
    discovered = vector<int> (V, -1);
    isCutVertex =  vector<bool> (V, false);
    cnt = 0;
    for(int i = 0 ; i < V; i++) if(discovered[i] == -1) findCutVertex(i,true);
}

int main(){
    cin>>V>>E;
    int A,B;
    while(E--){
        cin>>A>>B;
        adj[A-1].push_back(B-1);
        adj[B-1].push_back(A-1);
    }
    
    //find cutvertex
    findCutVertexAll();
    
    //output
    cout<<cutVertexes.size()<<endl;
    std::sort(cutVertexes.begin(), cutVertexes.end());
    for(auto cv : cutVertexes){
        cout<<cv+1<<" ";
    }
    cout<<endl;
    return 0;
}