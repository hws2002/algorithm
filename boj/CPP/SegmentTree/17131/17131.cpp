#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 200'000
#define MOD 1'000'000'007
#define endl '\n'

using namespace std;
typedef long long ll;

int N;

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
	
	//create RSQ
	RSQ<ll> rsq_r(n_size,0);
	RSQ<ll> rsq_l(n_size,0);
	for(int i = 0; i < n_size; i++){
		rsq_r.raw[i] = stars_y_x[i].num;
		rsq_l.raw[i] = stars_y_inv_x[i].num;
	}
	rsq_r.init();
	rsq_l.init();
	
    //fill right
    for(int i = 0 ; i < n_size; i++){
        auto star_r = stars_x_y[i]; auto star_l = stars_x_inv_y[n_size-1-i];
		auto start_r= lower_bound(stars_y_x.begin(), stars_y_x.end(), star_r.y, [](const Star & s, int y){
                return s.y < y;
            });
		auto start_l = lower_bound(stars_y_inv_x.begin(), stars_y_inv_x.end(), star_l.y, [](const Star & s, int y){
				return s.y < y;
			});
    	auto end_r = upper_bound(stars_y_x.begin(), stars_y_x.end(), star_r, [](const Star & s, const Star & st){
    			return s.y < st.y; // Compare based on y
    		});
		auto end_l = upper_bound(stars_y_inv_x.begin(), stars_y_inv_x.end(), star_l, [](const Star & s, const Star & st){
				return s.y < st.y;
			});
		
        int posi_r = lower_bound(
			start_r, end_r,
			star_r.x, 
			[]( const Star & s, int x){
				return s.x < x;
			}) - stars_y_x.begin();

        int posi_l = lower_bound(
			start_l, end_l,
			star_l.x,
			[](const Star & s, int x){
				return -s.x < -x;	
			}) - stars_y_inv_x.begin();
		rgt[star_r.oidx] = rsq_r.query(0, posi_r);
		lft[star_l.oidx] = rsq_l.query(0, posi_l);
        
		//remove
        rsq_r.update(posi_r,0);
		rsq_l.update(posi_l,0);
    }
	
    //output
    ll ret = 0;
    for(int i = 0; i < n_size; i++){
        ret = ( (stars_x_y[i].num * ((lft[i] * rgt[i]) % MOD) ) % MOD + ret) % MOD;
    }
    cout<<ret<<endl;
    return 0;
}