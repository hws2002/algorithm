#include <iostream>
#include <vector>
#define endl '\n'
#define MAX_N 100'000
// #define DEBUG_INPUT
// #define DEBUG_CONSTRUCT
using namespace std;

vector<int> adj[MAX_N];
vector<int> subTreeSize(MAX_N, 0);

int N,R,Q;


// root를 루로 하는 서브트리의 사이즈를 반환한다.
int constructTree(int root, int parent){
    subTreeSize[root] = 0;
    for(int i = 0 ; i < adj[root].size(); i++){
        int child = adj[root][i];
        if( child == parent) continue;
        subTreeSize[root] += constructTree(child,root);
    }
    subTreeSize[root]++;
#ifdef DEBUG_CONSTRUCT
cout<<"subTreesize["<<root<<"] = "<<subTreeSize[root]<<endl;
#endif
    return subTreeSize[root];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //input
    cin>>N>>R>>Q;
    int U,V;
    for(int i = 0 ; i < N-1 ; i++){
        cin>>U>>V;
        adj[U-1].push_back(V-1);
        adj[V-1].push_back(U-1);
    }
#ifdef DEBUG_INPUT
for(int i = 0 ; i < N; i++){
    cout<<"adj["<<i<<"] :";
    for(auto w : adj[i]){
        cout<<w<<" ";
    }
    cout<<endl;
}
#endif
    // make tree and construct size table simultaneously
    constructTree(R-1,-1);
    
    //query
    for(int i = 0; i < Q; i++){
        cin>>U;
        cout<<subTreeSize[U-1]<<endl;
    }
    return 0;
}



