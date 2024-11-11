// 연결 그래프
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

#define MAX_N 100'000
#define endl '\n'
// #define DEBUG_DFS

using namespace std;

vector<int> edges[MAX_N];
int N,M;

vector<int> discovered(MAX_N, 0);
vector<bool> inCicle(MAX_N, false);
// stack<int> st;
vector<int> st;
int Vcnt = 1;

bool dfs(int h, int p){
#ifdef DEBUG_DFS
printf("dfs(%d,%d) \n", h, p);
#endif 
    discovered[h] = Vcnt++;
    // st.push(h);
    st.push_back(h);

#ifdef DEBUG_DFS
for(int i = 0 ; i < st.size(); i++){
    cout<<i<<" ";
}
cout<<endl;
for(auto s : st){
    cout<<s<<" ";
}
cout<<endl;

for(int i = 0; i < N; i++){
    cout<<inCicle[i]<<" ";
}

cout<<endl;
#endif

    for(auto nxt : edges[h]){
#ifdef DEBUG_DFS
        printf("nxt : %d \n", nxt);
#endif
        if(nxt == p) continue;
        if(discovered[nxt] == 0){
            if(dfs(nxt,h)) return true;
        } else {
            if( discovered[nxt] < discovered[h]){ // found cycle
                for(int i = st.size()-1; i >= 0 && st[i] != nxt; i--){
                    if(inCicle[st[i]]) return true;
                    inCicle[st[i]] = true;
                }
                
                if(inCicle[nxt]) return true;
                inCicle[nxt] = true;
            } 
        }
    }
    // st.pop();
    st.pop_back();
#ifdef DEBUG_DFS
printf("return dfs(%d, %d) \n",h,p);
#endif
    return false;
}

int main(){
    cin>>N>>M;
    
    int x,y;
    for(int i = 0 ; i < M; i++){
        cin>>x>>y; x--;y--;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
    
	for(int i = 0 ; i < N; i++){
		st.clear();
		if(discovered[i] == 0)
		if(dfs(i,-1)) {
			cout<<"Not cactus"<<endl;
			return 0;
		}
	}

	cout<<"Cactus"<<endl;
	
    return 0;
}