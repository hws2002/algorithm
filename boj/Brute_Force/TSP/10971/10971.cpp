//10971
//brute - force
#include <iostream>
#include <vector>
#include <limits.h>
typedef long long ll;
// #define DEBUG_SOLVE

using namespace std;
void printPath(vector<int> & path){
    for(vector<int>::iterator iter = path.begin(); iter != path.end(); iter++){
        cout<<*iter<<" ";
    }
    cout<<endl;
}


int N; // 2 <= N <= 10
int W[11][11] = {0};


ll shortestPath(vector<int> & path, vector<bool> & visited, ll currentLength){
#ifdef DEBUG_SOLVE
printPath(path);
if(path.size() == 4)
cout<<currentLength<<endl;
#endif
    //base 
    if(path.size() == N){
        return currentLength + W[path.back()][path[0]];
    }
    ll ret = LLONG_MAX;

    // look for next city
    int here = path.back();
    for(int next = 1; next <= N; next++){
        if(visited[next] || W[here][next] == 0) continue;
        path.push_back(next); visited[next] = true;
        ll cand = shortestPath(path, visited, currentLength + W[here][next]);
        ret = min(cand, ret);
        if(!path.empty()) path.pop_back(); visited[next] = false;
    }
    return ret;
}

int main(){
    //input
    cin>>N;
    
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cin>>W[i][j];
        }
    }
    
    
    //solve
    vector<int> path;
    vector<bool> visited(N+1,false);
    path.push_back(1);
    visited[1] = true;
    cout<<shortestPath( path, visited, 0)<<endl;
    return 0;
}