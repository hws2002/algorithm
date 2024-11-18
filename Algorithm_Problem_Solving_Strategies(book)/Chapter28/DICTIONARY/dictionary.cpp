#include <iostream>
#include <cstring>
#include <vector>

#define MAX_V 26

#define endl '\n'
// #define DEBUG_CE
// #define DEBUG_DFS
using namespace std;

int N;

bool edge[MAX_V][MAX_V] = {{0}};

void createEdge(const string & s1, const string & s2){
    for(int i = 0; i < min<int>(s1.size(), s2.size()); i++){
        if(s1[i] != s2[i]){
            edge[ s1[i] - 'a' ][ s2[i] - 'a' ] = true;
#ifdef DEBUG_CE
            printf("added edge %d -> %d \n", s1[i] - 'a', s2[i] - 'a');
#endif
            return ;
        }
    }
}

vector<int> discovered(MAX_V, 0);
vector<int> finished(MAX_V, false);
int Vcnt = 1;

vector<int> ret;

int dfs(int h){
#ifdef DEBUG_DFS
    printf("dfs(%d) \n", h);
#endif
    discovered[h] = Vcnt++;
    
    for(int nxt = 0; nxt < MAX_V; nxt++){
        if( edge[h][nxt] ){
            if(!discovered[nxt]){ // tree 간선
                if(!dfs(nxt)) return false;
            } else {
                if( discovered[nxt] < discovered[h]){
                    if( finished[nxt]){ //교차 간선
                        //do nothing
                    } else { // 역방향 간선
                        return false;
                    }
                } else { // 순방향 간선
                    //do nothing
                }
            }
        }
    }
#ifdef DEBUG_DFS
    printf("dfs(%d) end \n", h);
#endif
	ret.push_back(h);
    return finished[h] = true;
}

void solve(){
    cin>>N;
    
    //reset
    for(int i = 0; i < MAX_V; i++)
        fill(edge[i], edge[i] + MAX_V, 0);
    
    discovered = vector<int> (MAX_V,0);
    finished = vector<int> (MAX_V, false);
    ret.clear();
	
    string s1,s2;
    cin>>s1;
    for(int i = 1 ; i < N; i++){
        cin>>s2;
        //create edges from (s1 -> s2)
        createEdge(s1,s2);
        s1 = s2;
    }
    
    for(int i = 0; i < MAX_V; i++){
        if(!discovered[i]) {
            if(!dfs(i)){
				printf("INVALID HYPOTHESIS\n");
                return ;
            }
        }
    }
    
    // RECON
	for(int i = ret.size()-1; i>= 0; i--){
		printf("%c", ret[i] + 'a');
	}
	printf("\n");
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    int c;
    cin>>c;
    while(c--) solve();
    return 0;
}