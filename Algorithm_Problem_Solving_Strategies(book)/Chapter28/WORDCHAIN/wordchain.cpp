#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

#define all(v) v.begin(), v.end()
#define MAX_V 26
#define MAX_N 100

#define endl '\n'
// #define DEBUG_INPUT
// #define DEBUG_EC
using namespace std;

int n;
string s;

vector<string> words;

vector< int > adj[MAX_V];
int sidx[26] = {0};
vector<pair<int, int> > degree(MAX_V); // {in,out}
vector<int> edges[26][26];

void ecDfs(int here, vector<int> & path){
#ifdef DEBUG_EC
    printf("here : %d %c \n", here, here + 'a');
#endif
    while(sidx[here] < adj[here].size()){
        int there = adj[here][ sidx[here] ];
        sidx[here]++;
        ecDfs(there, path);
    }
#ifdef DEBUG_EC
printf("pushed %c \n", here+'a');
#endif
    path.push_back(here);
}

vector<int> getEulerCircuit(int src){
    vector<int> ret;
    fill(sidx, sidx + 26, 0);
    ecDfs(src, ret);
    return ret;
}

void solve(){
    cin>>n;
    words.resize(n);
    for(int i = 0 ; i < 26; i++) {
		adj[i].clear();
		degree[i] = {0,0};
	}
    
    for(int i = 0 ; i < n; i++){
        cin>>words[i];
		int s = words[i][0] - 'a'; int e = words[i].back() - 'a';
        adj[s].push_back(e);
		edges[s][e].push_back(i);
		degree[s].second++; // out
		degree[e].first++; // in
    }

#ifdef DEBUG_INPUT
for(int i = 0 ; i< 26; i++){
	if( adj[i].size() > 0){
		printf("%d %c : ", i, i+'a');
		for(const auto & p : adj[i]){
			cout<<"{"<<p.first<<","<< words[p.second]<<"} ";
		}
		cout<<endl;
	}
}
#endif
	
	
	// check whether euler circuit exists
	int s = -1; int e = -1; int src = -1;
	for(int i = 0; i < 26; i++){
		if( degree[i].first != -0 || degree[i].second != 0) src = i;
		
		if( abs(degree[i].first - degree[i].second) >= 2) {
			cout<<"IMPOSSIBLE"<<endl;
			return ;
		}
		
		if( degree[i].first == degree[i].second+1){ // in > out
			// set end node
			if(e != -1){
				cout<<"IMPOSSIBLE"<<endl;
				return;
			}
			e = i;
		}
		
		if( degree[i].first + 1 == degree[i].second){
			if( s != -1){
				cout<<"IMPOSSIBLE"<<endl;
				return ;
			}
			s = i;
		}
	}
	
	if( s == -1 && e == -1){ // euler circuit
#ifdef DEBUG_EC
        printf("src : %d %c ", src, src+ 'a');
#endif
        vector<int> ec_vertex = getEulerCircuit(src);
        if( ec_vertex.size() == n+1){
            reverse( all(ec_vertex) );
			for(int i = 1 ; i <= n; i++){
				int v = ec_vertex[i]; int u = ec_vertex[i-1];
				cout<< words[edges[u][v].back()]<<" ";
				edges[u][v].pop_back();
			}
            cout<<endl; 
			return ;
		}
	} else if ( s!= -1 && e != -1){ // euler trail
        vector<int> ec_vertex = getEulerCircuit(s);
        if( ec_vertex.size() == n+1){
            reverse( all(ec_vertex) );
			for(int i = 1 ; i <= n; i++){
				int v = ec_vertex[i]; int u = ec_vertex[i-1];
				cout<< words[edges[u][v].back()]<<" ";
				edges[u][v].pop_back();
			}
            cout<<endl; 
			return ;
		}
	} 
	cout<<"IMPOSSIBLE"<<endl;
}

int main(){
    int c; cin>>c; while(c--) solve();
    return 0;
}