//dfs - Euler Circuit
#include <iostream>
#include <vector>

// #define DEBUG_INPUT
#define MAX_N 1'000
using namespace std;

int ADJ[MAX_N][MAX_N] = {0};
vector<int> adj[MAX_N];
vector<int> degrees(MAX_N, 0);
vector<int> start(MAX_N, 0);
int Vcnt = 0;
vector<bool> discovered(MAX_N, false);

void dfs(const int here){

	discovered[here] = true; Vcnt++;
	
	for(auto next : adj[here]){
		if( discovered[next] ) continue;
		dfs(next);
	}
	return;
}


int N;
vector<int> res;
void EulerCircuit(const int here){

    for(int & i = start[here]; i < adj[here].size(); i++){
        int next = adj[here][i];
        while( ADJ[here][next] > 0){
            ADJ[here][next]--;
            ADJ[next][here]--;
            EulerCircuit(next);
        }
    }
	
    res.push_back(here);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
    cin>>N;
	// if( N == 1) { cout<<1<<endl; return 0;}
    
    bool possible = true;
	int w;
    for(int i = 0; i < N; i++){
        for(int j = 0 ; j < N; j++){
           	cin>>ADJ[i][j];
			if( ADJ[i][j] ){
				adj[i].push_back(j);
				degrees[i] += ADJ[i][j];
			}
        }
		
        if(degrees[i] % 2 == 1 || degrees[i] == 0){
            possible = false;
            break;
        }
    }

#ifdef DEBUG_INPUT
for(int i = 0 ; i < N ;i++){
	cout<<"adj["<<i<<"] ";
	for(auto e : adj[i]){
		cout<<e<<" ";
	}
	cout<<endl;
}
#endif

    
    if(!possible) {
        cout<<-1<<endl;
        return 0;
    }
    
	
	// run scc
	dfs(0);
	
	if(Vcnt < N) {
		cout<<-1<<endl;
		return 0;
	}
	
    //find EulerCircuit
    EulerCircuit(0);
    
    for(int i = res.size()-1; i >= 0; i--){
        cout<<res[i]+1<<" ";
    }
    cout<<endl;
    return 0;
}
    