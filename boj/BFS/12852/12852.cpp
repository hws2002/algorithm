#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 1'000'000
using namespace std;


int main(){
    int N;
    cin>>N;
    
    vector<int> visited(MAX_N+1, 0);
    vector<int> choice(MAX_N+1, -1);
    
    queue<int> q;
    int here = N;
    q.push(here);
    visited[here] = 1;
    
    
    while(!q.empty()){
        here = q.front(); q.pop();
        
        if( here == 1) break;
        
        // /3
        if(!(here%3) && !visited[here/3]){
            q.push(here/3);
            visited[here/3] = visited[here] + 1;
            choice[here/3] = here;
        }
        
        // /2
        if( !(here & 1) && !visited[here/2]){
            q.push(here/2);
            visited[here/2] = visited[here] + 1;
            choice[here/2] = here;
        }
        
        // -1
        if( 1 <= here && !visited[here-1]){
            q.push(here-1);
            visited[here-1] = visited[here] + 1;
            choice[here-1] = here;
        }
    }
    
    
    //output
    cout<<visited[1]-1<<endl;
    
    vector<int> res;
    while( here != N){
        res.push_back(here);
        here = choice[here];
    }

    cout<<N<<" ";    
    for(int i = res.size()-1; i >= 0; i--){
        cout<<res[i]<<" ";
    }
    return 0;
}