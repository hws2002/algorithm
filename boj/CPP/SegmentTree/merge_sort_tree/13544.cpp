#include <iostream>
#include <vector>
#include <algorithm>

#define endl '\n'
// #define DEBUG_INPUT
#define all(v) v.begin(), v.end()
using namespace std;

template<typename dataType>
struct MergeTree{
public:
    using T = dataType;
    int n; 
    vector<T> raw;
    vector<vector<T>> rangeSort;
    
    MergeTree(int n) : n(n){
        raw.resize(n);
        rangeSort.resize(4*n);
    }
    
    void init(int nn, int nl, int nr){
        if( nr <= nl) {
            rangeSort[nn].push_back(raw[nl]);
            return;
        }
		
        int mid = (nl+nr)>>1;
		init(nn<<1, nl, mid); init(nn<<1 | 1, mid+1, nr);
		rangeSort[nn].resize(rangeSort[nn<<1].size() + rangeSort[nn<<1 | 1].size());
        merge( all(rangeSort[nn<<1]) , all(rangeSort[nn<<1 | 1]), rangeSort[nn].begin());
	}
	
	//query
	int query(int l, int r, int k, int nn, int nl, int nr){
		// printf("nn, nl, nr: %d, %d, %d \n", nn, nl, nr);
		if( r < nl || nr < l) return 0;
		
		if( l <= nl && nr <= r){
			return (rangeSort[nn].end() - upper_bound( all(rangeSort[nn]), k));
		}
		
		int mid = (nl + nr) >> 1;
		return query(l,r,k, nn<<1, nl, mid) + query(l,r,k, nn<<1 | 1, mid+1, nr);
	}
	
	int query(int i, int j, int k){
		// printf("i,j,k : %d, %d, %d \n", i,j,k);
		return query(--i, --j, k, 1, 0, n-1);
	}
};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    int N;
    cin>>N;
    MergeTree<int> mt(N);
    
    for(int i = 0 ; i < N; i++){
        cin>>mt.raw[i];
    }

    mt.init(1,0,mt.n-1);

#ifdef DEBUG_INPUT
for(auto sv : mt.rangeSort){
    for(auto e : sv){
        cout<<e<<" ";
    }
    cout<<endl;
}
cout<<endl;
#endif
	
	//query
	int M;
	int last_ans = 0;
	int a,b,c;
	cin>>M;
	while(M--){
		cin>>a>>b>>c;
		a ^= last_ans;
		b ^= last_ans;
		c ^= last_ans;
		last_ans = mt.query(a,b,c);
		cout<<last_ans<<endl;
	}
    return 0;
}