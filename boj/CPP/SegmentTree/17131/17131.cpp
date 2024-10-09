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
    Star(int x, int y, int oi) : x(x), y(y), oidx(oi), num(1){};
    
    bool operator==(const Star & rhs) const{
        return x == rhs.x && y == rhs.y;
    };
};

// x순, y순
bool comp1(const Star & a, const Star & b){
    if( a.x == b.x ) return a.y < b.y;
    return a.x < b.x;
}

// x순, y역
bool comp2(const Star & a, const Star & b){
    if( a.x == b.x) return a.y > b.y;
    return  a.x < b.x;
}

// y순, x역
bool comp3(const Star & a, const Star & b){
    if( a.y == b.y ) return a.x > b.x;
    return a.y < b.y;
}

// y순, x순
bool comp4(const Star & a, const Star & b){
    if( a.y == b.y ) return a.x < b.x;
    return a.y < b.y;
}




vector<Star> stars;
vector<ll> lft(MAX_N,0);
vector<ll> rgt(MAX_N,0);

int getPosi_r(vector<Star>::iterator b, vector<Star>::iterator e, int f, vector<Star> & v){
	return lower_bound(b,e,f,[](const Star & s, int x){
			return s.x < x;
	}) - v.begin();
};


int getPosi_l(vector<Star>::iterator b, vector<Star>::iterator e, int f, vector<Star> & v){
	return lower_bound(b,e,f,[](const Star & s, int x){
			return -s.x < -x;
	}) - v.begin();
};

vector<Star>::iterator getStart(vector<Star>::iterator b, vector<Star>::iterator e, const Star & f){
	return lower_bound(b,e, f, [](const Star & s, const Star & st){
		return s.y < st.y;
	});
}

vector<Star>::iterator getEnd(vector<Star>::iterator b, vector<Star>::iterator e, const Star & f){
	return upper_bound(b, e, f, [](const Star & s, const Star & st){
		return s.y < st.y;
	});
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>N;
    int x,y;
    for(int i = 0;  i < N; i++){
        cin>>x>>y;
        stars.push_back(Star(x,-y,i)); // y값은 거꾸로 담는다
    }

    //x순, y순
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
	
	// x순, y역
    sort(stars_x_inv_y.begin(), stars_x_inv_y.end(), comp2);
	// y순, x역
    sort(stars_y_inv_x.begin(), stars_y_inv_x.end(), comp3);
    // y순, x순
    sort(stars_y_x.begin(), stars_y_x.end(), comp4);

	
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
		
		auto start_r = getStart(stars_y_x.begin(), stars_y_x.end(), star_r);
		auto start_l = getStart(stars_y_inv_x.begin(), stars_y_inv_x.end(), star_l);
		
		auto end_r = getEnd(stars_y_x.begin(), stars_y_x.end(), star_r);
		auto end_l = getEnd(stars_y_inv_x.begin(), stars_y_inv_x.end(), star_l);	
		
		int posi_r = getPosi_r(start_r, end_r, star_r.x, stars_y_x);
		int posi_l = getPosi_l(start_l, end_l, star_l.x, stars_y_inv_x);

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