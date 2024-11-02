#include <iostream>
#include <queue>

#define MAX_N 100'000
#define MAX_POSI 200'000
#define MAX_K 100'000
using namespace std;

int N,K;

int main(){
    cin>>N>>K;
    vector<int> visited(MAX_POSI, 0);
    vector<int> choice(MAX_POSI, -1);
    int here = N;
    queue<int> q;
    q.push(here);
    visited[here] = 0;
    choice[here] = here;
    
    while(!q.empty()){
        here = q.front(); q.pop();
        if(here == K) break;
        // X - 1
        if( 0 <= here-1 && !visited[here-1]){
            q.push(here-1);
            visited[here-1] = visited[here] + 1;
            choice[here-1] = here;
        }
        
        // X + 1
        if( here + 1 < MAX_POSI && !visited[here+1]){
            q.push(here+1);
            visited[here+1] = visited[here] + 1;
            choice[here+1] = here;
        }
    
        // 2*X
        if( (here<<1) < MAX_POSI && !visited[here<<1]){
            q.push(here<<1);
            visited[here<<1] = visited[here] + 1;
            choice[here<<1] = here;
        }
    }
    
    cout<<visited[K]<<endl;
    vector<int> res;
    while(here != N){
        res.push_back(here);
        here = choice[here];
    }
    res.push_back(here);

    for(int i = res.size()-1; i>=0; i--){
        cout<<res[i]<<" ";
    }
    return 0;
}
