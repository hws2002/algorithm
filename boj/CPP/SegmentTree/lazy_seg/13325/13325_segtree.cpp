#include <iostream>
#include <vector>
#include <cmath>

#define MAX_K 20
// #define DEBUG_INPUT
// #define DEBUG_DFS
// #define DEBUG_ST
#define endl '\n'
#define INF 2'000'000'000

using namespace std;
typedef long long ll;

int k;
vector<int> weights((1<<(MAX_K+1)), 0);

ll ret = 0;


int num_leaf;

struct SegTree{
public:
	vector<int> rangeMin;
	vector<int> lz;
	int n;
	
	void initSegTree(vector<int> & arr){
		n = arr.size();
		rangeMin.resize(4*n);
		lz.resize(4*n);
		init(arr,1,0,n-1);
	}
	
	int init(vector<int> & arr ,int nn, int nl, int nr){
		if( nr <= nl ) return rangeMin[nn] = arr[nl];
		int mid = (nl + nr ) >> 1;
		return rangeMin[nn] = min(init(arr, nn<<1, nl, mid) , init(arr, nn<<1 | 1, mid+1, nr));
	}
	
	//propagate
	void push(int nn, int nl, int nr){
		if(lz[nn]){
			rangeMin[nn] += lz[nn];
			if( nl < nr){
				lz[nn<<1] += lz[nn];
				lz[nn<<1|1] += lz[nn];
			}
		}
		lz[nn] = 0;
	}
	
	int update(int l, int r, int toadd, int nn, int nl, int nr){
		//propagate
		push(nn,nl,nr);
		
		if( r < nl || nr < l) return INF;
		if(l <= nl && nr <= r){
			rangeMin[nn] += toadd;
			if( nl < nr){
				lz[nn<<1] += toadd;
				lz[nn<<1|1] += toadd;
			}
			return rangeMin[nn];
		}
		int mid = (nl + nr) >> 1;
		return rangeMin[nn] = min(
			update(l, r, toadd, nn<<1, nl , mid),
			update(l, r, toadd, nn<<1 | 1, mid+1, nr)
		);
	}

	void update(int l, int r, int toadd){
		update(l, r, toadd, 1, 0, n-1);	
	}
	
	int query(int l, int r, int nn, int nl, int nr){
		//propagate
		push(nn,nl,nr);
		if( r < nl || nr < l) return INF;
		if( l <= nl && nr <= r) return rangeMin[nn];
		int mid = (nl + nr) >> 1;
		return  min( query(l , r, nn<<1, nl, mid), query(l ,r, nn<<1 | 1, mid+1, nr) );
	}
	//query
	int query(int l, int r){
		return query(l, r, 1, 0, n-1);
	}
};

SegTree t;

void dfs(int h){
#ifdef DEBUG_DFS
	printf("dfs(%d) \n" ,h);
#endif
    //find range
	int height = log2(h);
	int rl = h;
	int rr = h;
	for(int i = 0 ; i < k - height; i++){
		rl = rl<<1;
		rr = rr<<1 | 1;
	}
	if( h == rl) { // leaf
		ret += 1LL*t.query(h - num_leaf,h - num_leaf);
		return ;
	}
#ifdef DEBUG_DFS
	printf("rl, rr : %d, %d \n",rl ,rr);
#endif

    // find min 
	int toadd = t.query(rl - num_leaf,rr - num_leaf);
#ifdef DEBUG_ST
	printf("toadd : %d \n", toadd);
#endif
	ret += 1LL*toadd;
	
	t.update(rl-num_leaf,rr-num_leaf,-toadd);
    if( h<<1 | 1 < 1<<k+1 ){
        dfs(h<<1); dfs( h<<1 | 1);
    }
    return ;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    cin>>k;
	int mdist = -1; num_leaf = 1<<k;
	
	
    for(int i = 1 + 1 ; i < (1<<(k+1)) - 1 + 1; i++){
        cin>>weights[i];
        ret += 1LL * weights[i];
        weights[i] += weights[i>>1];
		if( 1<<k <= i){
			mdist = max(mdist, weights[i]);
		}
    }
	
	for(int i = 1<<k; i< 1<<k+1; i++){
		weights[i] = mdist - weights[i];
	}
#ifdef DEBUG_INPUT
printf("ret : %lld \n", ret);
for(int i = 1<<k; i < 1<<(k+1); i++){
    printf("wegiths[%d] : %d \n", i, weights[i]);
}
cout<<endl;
#endif
    // init segtree
	vector<int> leaf_w(weights.begin() + (1<<k), weights.begin() + (1<<k) + (1<<k));
    t.initSegTree(leaf_w);

#ifdef DEBUG_ST
for(int i = 1; i < 1<<k; i++){
	cout<<t.rangeMin[i]<<" ";
}
	cout<<endl;
#endif
    dfs(1);

    cout<<ret<<endl;
    return 0;
}