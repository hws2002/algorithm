#include <iostream>
#include <vector>

#define MAX_N 50
#define FOR(i,s,e) for(int i = s; i < e; i++)
using namespace std;

int N;
vector<int> aMatch;
vector<int> bMatch;
vector<bool> visited;

vector<int> adjAB[MAX_N];

struct stat{
    public:
    int s;
    int p;
    int t;
    // Default constrctor
    stat() : s(0), p(0), t(0){};
    
    stat(int s_, int p_, int t_) : s(s_), p(p_), t(t_){};
    
    bool operator <= (const stat & rhs) const {
        return s <= rhs.s && p <= rhs.p && t <= rhs.t;
    }
    
    bool operator < (const stat & rhs) const {
        return (s < rhs.s && p < rhs.p && t < rhs.t) ||
               (s <=rhs.s && p < rhs.p && t < rhs.t) ||
               (s < rhs.s && p <=rhs.p && t < rhs.t) ||
               (s < rhs.s && p < rhs.p && t <=rhs.t) ||
               (s <=rhs.s && p <=rhs.p && t < rhs.t) ||
               (s <=rhs.s && p < rhs.p && t <=rhs.t) ||
               (s < rhs.s && p <=rhs.p && t <=rhs.t) ;
    }
};

vector<stat> Stats(MAX_N);

int maxflow = 0;

bool dfs(const int here){
    if(visited[here]) return false;
    visited[here] = true;
    for(auto next : adjAB[here]){
        if( bMatch[next] == -1 || dfs(bMatch[next])) {
            aMatch[here] = next;
            bMatch[next] = here;
            return true;
        }
    }
    return false;
}


void bipartiteMatch(){
    //reset
    aMatch = vector<int> (N,-1);
    bMatch = vector<int> (N,-1);
    FOR(i,0,N){
        for(int j = 0; j < 2; j++){
            visited = vector<bool> (N,false);
            if( dfs(i) ) maxflow++;
        }
    }
}

int main(){
    cin>>N;
    int s,p,t;
    FOR(i,0,N){
        cin>>s>>p>>t;
        Stats[i] = stat(s,p,t);
    }
    
    //create edges
    FOR(i,0,N){
        FOR(j,i+1,N){
            if( Stats[j] <= Stats[i] ){
                adjAB[i].push_back(j);
            } else if( Stats[i] < Stats[j]){
                adjAB[j].push_back(i);
            } else {} // do nothing
        }
    }
    
    // 이분매칭
    bipartiteMatch();
    
    cout<<N - maxflow<<endl;
    return 0;
}