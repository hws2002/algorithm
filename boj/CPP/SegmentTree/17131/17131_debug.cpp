#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 200'000
#define MOD 1'000'000'007
#define endl '\n'
// #define DEBUG_INIT
// #define DEBUG_SORT
// #define DEBUG_LR
// #define DEBUG_FIND
using namespace std;
typedef long long ll;

int N,M;

template <typename T>
struct RSQ{
public:
    int n,sz;
    vector<T> rangeSum;
    vector<T> raw;
    RSQ(int n, T e) : n(n), sz(1<<log2ceil(n)), rangeSum(sz<<1, e), raw(n){};

    void init(){
        setLeaf();
        for(int i = sz-1; i>= 1; i--){
            rangeSum[i] = rangeSum[i<<1] + rangeSum[i<<1 | 1];
        }
    }
    
    void setLeaf(){
        for(int i = 0; i < n; i++){
            rangeSum[i | sz] = raw[i];
        }
    }

    T query(int l, int r){
		if( l >= r) return 0;
        T ret = 0;
        for(l += sz, r += sz; l < r; l>>=1, r>>=1){
            if(l&1) ret += rangeSum[l++];
            if(r&1) ret += rangeSum[--r];
        }
        return ret;
    }
    
    void update(int idx, T val){
        rangeSum[idx |= sz] = val;
		while( idx >>= 1){
            rangeSum[idx] = rangeSum[idx<<1] + rangeSum[idx<<1 | 1];			
        }
    }
private : 
    static int log2ceil(int n){
        int ret = 0;
        while( n > 1<<ret) ret++;
        return ret;
    }
};

struct Star{
public:
    int x,y;
	int oidx;
	int num;
    Star(int x, int y, int oi) : x(x), y(-y), oidx(oi), num(1){};
    
    bool operator==(const Star & rhs) const{
        return x == rhs.x && y == rhs.y;
    };
};

bool comp1(const Star & a, const Star & b){
    if( a.x == b.x ) return a.y < b.y;
    return a.x < b.x;
}

bool comp2(const Star & a, const Star & b){
    if( a.y == b.y ) return a.x < b.x;
    return a.y < b.y;
}

bool comp3(const Star & a, const Star & b){
    if( a.y == b.y ) return a.x > b.x;
    return a.y < b.y;
}

bool comp4(const Star & a, const Star & b){
    if( a.x == b.x) return a.y > b.y;
    return  a.x < b.x;
}

vector<Star> stars;
vector<ll> lft(MAX_N,0);
vector<ll> rgt(MAX_N,0);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>N;
    int x,y;    
    for(int i = 0;  i < N; i++){
        cin>>x>>y;
        stars.push_back(Star(x,y,i));
    }

    // x 기준으로 정렬, x가 같은 경우 y 역순 정렬
    sort(stars.begin(), stars.end(), comp1);
    
    //deduplicate
    vector<Star> stars_x_y;
	for(int i = 0 ; i < stars.size();){
        int num_of_same_stars = 0;
        auto star = stars[i];
        while( i+1 < stars.size()){
            if(i+1 < stars.size() && star == stars[i+1]) {
                num_of_same_stars++;
                i++;
            } else break;
        }
        num_of_same_stars++;
        i++;
        star.num = num_of_same_stars;
        stars_x_y.push_back(star);
    }
	int n_size = stars_x_y.size();
	for(int i = 0 ; i < n_size;i++){
		stars_x_y[i].oidx = i;
	}
	
    vector<Star> stars_x_inv_y = stars_x_y;
	vector<Star> stars_y_x = stars_x_y;
    vector<Star> stars_y_inv_x = stars_x_y;
	
    // x 기준으로 정렬, x가 같은 경우 y 순방향 정렬
    sort(stars_x_inv_y.begin(), stars_x_inv_y.end(), comp4);
    // y 역순으로 정렬, y가 같은 경우 x 순방향 정렬
    sort(stars_y_x.begin(), stars_y_x.end(), comp2);
    // y 역순으로 정렬, y가 같은 경우 x 역순 정렬
    sort(stars_y_inv_x.begin(), stars_y_inv_x.end(), comp3);
	
#ifdef DEBUG_SORT
	cout<<"v1  :";
for(auto s : stars_x_y){
    printf("(%d, %d) ", s.x, s.y);
}
cout<<endl;
cout<<"v2 : ";
for(auto s : stars_y_x){
	printf("(%d, %d) ", s.x, s.y);
}
cout<<endl<<"v3 : ";
for(auto s :stars_y_inv_x){
	printf("(%d, %d) ", s.x, s.y);
}
	cout<<endl;
#endif
	
	//create RSQ
	RSQ<ll> rsq(n_size,0);
	for(int i = 0; i < n_size; i++){
		rsq.raw[i] = stars_y_x[i].num;
	}
	rsq.init();

#ifdef DEBUG_INIT
for(int i = 0; i < n_size;i++){
	cout<<stars_x_y[i].num<<" ";
}
	cout<<endl;
for(int i = 0 ; i < rsq.sz<<1;i++){
	cout<<rsq.rangeSum[i]<<" ";
}
cout<<endl;
#endif
	
    //fill right
    for(int i = 0 ; i < n_size; i++){
        auto star = stars_x_y[i];
		auto start_= lower_bound(stars_y_x.begin(), stars_y_x.end(), star.y, [](const Star & s, int y){
                return s.y < y;
            });
    	auto end_ = upper_bound(stars_y_x.begin(), stars_y_x.end(), star, [](const Star & s, const Star & star){
    	return s.y < star.y; // Compare based on y
    		});
		
        int posi = lower_bound(
			start_, end_,
			star.x, 
			[]( const Star & s, int x){
				return s.x < x;
			}) - stars_y_x.begin();
#ifdef DEBUG_FIND
		printf(" star : (%d, %d), posi : %d , query : %lld \n", star.x, star.y, posi, rsq.query(0,posi));
#endif
        rgt[star.oidx] = rsq.query(0, posi);
        //remove
#ifdef DEBUG_FIND
		printf("%lld \n", rsq.rangeSum[posi + rsq.sz]);
#endif
        rsq.update(posi,0);
#ifdef DEBUG_FIND
		printf("%lld \n", rsq.rangeSum[posi + rsq.sz]);
#endif
    }
    
    //reset rsq
	for(int i = 0; i < n_size; i++){
		rsq.raw[i] = stars_y_inv_x[i].num;
	}
    rsq.init();
	
	// star 새로 정렬해주고, index 구해주기!
    //fill left
    for(int i = stars_x_inv_y.size()-1; i >= 0; i--){
        auto star = stars_x_inv_y[i];
		auto start_ = lower_bound(stars_y_inv_x.begin(), stars_y_inv_x.end(), star.y, [](const Star & s, int y){
			return s.y < y;
		});
		
		auto end_ = upper_bound(stars_y_inv_x.begin(), stars_y_inv_x.end(), star, [](const Star & s, const Star & st){
			return s.y < st.y;
		});

        int posi = lower_bound(
			start_, end_, star.x, [](const Star & s, int x){
                return -s.x < -x;
            }) - stars_y_inv_x.begin();
#ifdef DEBUG_FIND
		printf(" star : (%d, %d), posi : %d \n", star.x, star.y, posi);
#endif
        lft[star.oidx] = rsq.query(0,posi);
        //remove
        rsq.update(posi,0);
    }
	
#ifdef DEBUG_LR
	cout<<"right : ";
for(int i = 0 ; i < n_size; i++){
	cout<<rgt[i]<<" ";
}
	cout<<endl;
	cout<<"left : ";
for(int i = 0 ; i < n_size; i++){
	cout<<lft[i]<<" ";
}
cout<<endl;
#endif
	
    //output
    ll ret = 0;
    for(int i = 0; i < n_size; i++){
        ret = ( (stars_x_y[i].num * ((lft[i] * rgt[i]) % MOD) ) % MOD + ret) % MOD;
    }
    cout<<ret<<endl;
    return 0;
}