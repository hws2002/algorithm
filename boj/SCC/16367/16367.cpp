// Red : false, Blue : true
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>

#define MAX_K 5'000
#define MAX_N 10'000
#define FOR(i,s,e) for(int i = s; i < e; i++)
// #define DEBUG_CREATE
// #define DEBUG_ADJ
// #define DEBUG_TJ
using namespace std;

int k, n;

vector<int> adj[MAX_K<<1];

void createAdj(const int l1,  char c1, const int l2,  char c2){
#ifdef DEBUG_CREATE
	printf("l1, c1, l2, c2 : %d, %c, %d, %c \n", l1, c1, l2, c2);
#endif  
	c1 -= 'B'; c2 -= 'B';
    if( c1 && c2 ){ // R R
#ifdef DEBUG_CREATE
		printf("R R \n");
#endif
		adj[l2*2].push_back(l1*2+1);
        adj[l1*2].push_back(l2*2+1);
    } else if ( c1 && !c2){ // R B
#ifdef DEBUG_CREATE
		printf("R B \n");
#endif
		adj[l2*2 + 1].push_back(l1*2 + 1);
        adj[l1*2].push_back(l2*2);
    } else if ( !c1 && c2){ // B R
#ifdef DEBUG_CREATE

		printf("B R \n");
#endif
		adj[l2*2].push_back(l1*2);
        adj[l1*2+1].push_back(l2*2 + 1);
    } else { // B B
#ifdef DEBUG_CREATE
		printf("B B\n");
#endif
        adj[l2*2 + 1].push_back(l1*2);
        adj[l1*2 + 1].push_back(l2*2);
    }
}

vector<int> discovered(MAX_K<<1, 0);
vector<int> sccId(MAX_K<<1, 0);

int vCnt = 1; int sCnt = 1;

stack<int> st;

int tarjan(const int here){
#ifdef DEBUG_TJ
	printf("tarjan(%d) \n",here);
#endif
    discovered[here] = vCnt++;
    int lowest_node = discovered[here];
	st.push(here);
    for(auto next : adj[here]){
        if(!discovered[next]) lowest_node = min(lowest_node, tarjan(next));
        else {
            if(!sccId[next]) lowest_node = min(lowest_node, discovered[next]);
        }
    }
    
    if(lowest_node == discovered[here]){ // found scc!
        while(true){
            int t = st.top();
            sccId[t] = sCnt;
            st.pop();
            if( t == here) break;
        }
        sCnt++;
    }
	
    return lowest_node;
}

void tarjanAll(){
    FOR(i,0, k<<1){
        if(!discovered[i]) {
#ifdef DEBUG_TJ
			printf("hello tarjan %d \n", i);
#endif
			tarjan(i);
		}
    }
}

int main(){
    cin>>k>>n;
    int l1,l2,l3;
	char c1,c2,c3;
    
    FOR(i,0,n){ // creat adj
        cin>>l1>>c1>>l2>>c2>>l3>>c3;
        l1--; l2--; l3--;
        // l1 <-> l2
        createAdj(l1,c1,l2,c2);
        // l2 <-> l3
        createAdj(l2,c2,l3,c3);
        // l3 <-> l1
        createAdj(l3,c3,l1,c1);
    }
#ifdef DEBUG_ADJ
for(int i = 0; i < k<<1; i++){
	printf("adj[%d] : ",i);
	for(auto next : adj[i]){
		cout<<next<<" ";
	}
	cout<<endl;
}
#endif
    // tarjan
    tarjanAll();
#ifdef DEBUG_TJ
for(int i = 0; i < k<<1;i++){
	printf("sccId[%d] : %d \n", i, sccId[i]);
}
#endif
    //output
    bool conflict = false;
    for(int i = 0; i < k<<1; i+=2){
        if(sccId[i] == sccId[i+1]){
            conflict = true;
            break;
        }
    }
    
    if(conflict){
        cout<<-1<<endl;
    } else {
        vector<pair<int,int>> order;
        for(int i = 0; i < k<<1; i++){
            order.push_back({-sccId[i],i});
        }
        vector<int> values(k, -1);
        std::sort(order.begin(), order.end());
#ifdef DEBUG_TJ
cout<<"(sccid, vi)"<<endl;
for(auto psi : order){
	printf("(%d, %d) \n", psi.first, psi.second);
}
#endif
        for(auto psi : order){
            int vidx = psi.second;
            // int sccid = psi.first; 
            int lidx = vidx>>1; bool isvnot = (vidx % 2 == 1);
			
            // assign false to the scc
            int lshouldb = isvnot ? 1 : 0;
            if( values[lidx] == -1) values[lidx] = lshouldb;
            // else if( values[lidx] != lshouldb) {
                // cout<<-1<<endl;
                // return 0;
            // }
        }
        
        for(auto lv : values){
            if(lv) cout<<"B";
            else cout<<"R";
        }
    }
    return 0;
}

