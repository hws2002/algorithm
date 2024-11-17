#include <iostream>
#include <cstring>
#include <vector>

#define endl '\n'
using namespace std;

int N,M;

struct DisjointSet{

public:
    vector<int> parent;
    vector<int> rank;
    vector<int> op;
	vector<int> gsize;
    DisjointSet(int n){
        parent.resize(n); rank.resize(n,0);
        op.resize(n,-1); gsize.resize(n,1);
        for(int i = 0 ; i < n ;i++){
            parent[i] = i;
        }
    }
    
    int find(int u){
        if( u == parent[u]) return u;
        return parent[u] = find(parent[u]);
    }
    
    int merge(int u, int v){
        u = find(u); v = find(v);
        if( u == v) return u;
        if( rank[u] < rank[v]) swap(u,v);
        parent[v] = u;
        if( rank[u] == rank[v]) rank[u]++;
		gsize[u] += gsize[v];
        return u;
    }
};

void solve(){
    cin>>N>>M;
    string tmp; int u,v;
    DisjointSet set(N);
	bool contra = false;
	int i;
    for( i = 1; i <= M; i++){
        cin>>tmp>>u>>v;
        u = set.find(u); v = set.find(v);
        int op1 = set.op[u]; int op2 = set.op[v];
        if( op1 > -1) op1 = set.find(op1);
        if( op2 > -1) op2 = set.find(op2);
        if( tmp == "ACK" ){    
            if( op1 == v || op2 == u) { cout<<"CONTRADICTION AT "<<i<<endl;contra = true; break;}
            int p = set.merge(u,v);
            int op_ = -1;
            if(op1 > -1 && op2 > -1) op_ = set.merge( op1, op2 );
            else {
                if( op1 > -1) op_ = op1;
                else op_ = op2;
            }
            set.op[p] = op_;
            if(op_ > -1) set.op[op_] = p;
        } else {
            if( u == v ) { cout<<"CONTRADICTION AT "<<i<<endl;contra = true; break;}
            else if ( op1 != -1 && op1 == op2) { cout<<"CONTRADICTION AT "<<i<<endl; contra = true; break;}
            else if ( op1 != -1 && set.op[v] == op1) { cout<<"CONTRADICTION AT "<<i<<endl; contra = true; break;}
            else if ( op2 != -1 && set.op[u] == op2) { cout<<"CONTRADICTION AT "<<i<<endl; contra = true; break;}
            int p1 = u;
            if(op2 > -1) p1 = set.merge(u, op2); 
            int p2 = v;
            if(op1 > -1) p2 = set.merge(v, op1);
            set.op[p1] = p2; set.op[p2] = p1;
        }
    }
	
	if (contra) {
		while( i++ < M){
			cin>>tmp>>u>>v;
		}
	} else{
		int group_1 = N;
		int ret = 0;
		vector<bool> added(N,false);
		
		for(int j = 0; j < N; j++){
			int k = set.find(j);
			if( k > -1) {
				if(added[k] == false){
					int p = set.op[k];
					if( p > -1){
						ret += max(set.gsize[k], set.gsize[p]);
						added[p] = true;
						group_1 -= set.gsize[p];
					} else {
						ret += set.gsize[k];
					}
					group_1 -= set.gsize[k];
					added[k] = true;
				}
			}
		}
    	cout<<"MAX PARTY SIZE IS "<<ret+group_1<<endl;
	}
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