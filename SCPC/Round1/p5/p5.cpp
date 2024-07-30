#include <iostream>
#include <vector>
#include <map>

#define MAX_N 50'000
#define DEBUG_ST
#define DEBUG_Q1
#define DEBUG_Q2

using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
typedef map<ll,int> mli;

map<int,int> emptym;
struct SegTree{
public:
    vector< map<ll,int> > counts;
    vector<ll> squares;
    vector<bool> lazy;
    
    int n;
    SegTree(){};
    
    void reinit(const vector<ll> & array, int N){
        n = N;
        counts.resize(4*n);
        squares.resize(4*n, 0);
        lazy.resize(4*n, false);
        init(array, 1, 0, n-1);
    }
    
    map<ll,int>& init(const vector<ll> & array, int node, int nodeLeft, int nodeRight){
        if(nodeRight <= nodeLeft) {
            return counts[node] = map<ll,int> {{array[nodeLeft], 1}};
        }
        
        int mid = (nodeRight + nodeLeft) >> 1;
        auto l = init(array, node * 2    , nodeLeft, mid      );
        auto r = init(array, node * 2 + 1, mid+1   , nodeRight);
        
        // 여기서 정리를 해야돼!
        mli m(r);
        for(auto e : l){
            auto it = r.find(e.first);
            if(it == r.end()){
                m[e.first] = e.second;
            } else {
                m[e.first] = e.second + it->second;
            }
        }
        return counts[node] = m;
    }
    
    pair<mli&,ll> query(const int left, const int right, const int node, const int nodeLeft, const int nodeRight){
#ifdef DEBUG_Q1
cout<<"left, right, node, nodeLeft, nodeRight : "<<left<<", "<<right<<", "<<node<<", "<<nodeLeft<<", "<<nodeRight<<endl;
#endif
        if(right < nodeLeft || nodeRight < left) {
            mli emptymap;
			return {emptymap,-1};
        }
        
        if(left <= nodeLeft && nodeRight <= right) {
            if(!lazy[node]){
                for(auto & e : counts[node]){ // 자동으로 오름차순 되어 있다.
                    ll a = e.first; ll c = e.second;
#ifdef DEBUG_Q1
cout<<"a,c : "<<a<<", "<<c<<endl;
#endif
                    if(a == 1) continue; // 1은 제외한다
                    
                    int to_add_c = int(c/a);
                    if( to_add_c > 0){
                        squares[node] += to_add_c;
                        ll to_add_num = a*a;
                        auto it = counts[node].find(to_add_num);
                        if( it == counts[node].end()){
                            counts[node].insert({to_add_num,to_add_c});
                        } else {
                            it->second += to_add_c;
                        }
                        e.second -= to_add_c*a;
                        if(e.second <=0){}
                    }
                }
                lazy[node] = true;
            }
#ifdef DEBUG_Q1
cout<<"counts["<<node<<"] : ";
for(auto e : counts[node]){
    cout<<"{"<<e.first<<","<<e.second<<"} ";
}
cout<<"square : "<<squares[node]<<endl;
#endif
            return {counts[node], squares[node]};    
        } 
        
        int mid = (nodeLeft + nodeRight) >> 1;
        auto l = query(left, right, node*2, nodeLeft, mid);
        auto r = query(left, right, node*2 + 1, mid+1, nodeRight);
#ifdef DEBUG_Q2
cout<<"l.second , r.second"<<l.second<<","<<r.second<<endl;
#endif
		if(l.second == -1 && r.second != -1){
			mli m(r.first);
			ll square = r.second;
			for(auto& e : m){ // 자동으로 오름차순 되어 있다.
				ll a = e.first; ll c = e.second;

				if(a == 1) continue; // 1은 제외한다

				int to_add_c = int(c/a);
				if( to_add_c > 0){
					square += to_add_c;
					ll to_add_num = a*a;
					auto it = m.find(to_add_num);
					if( it == m.end()){
						m.insert({to_add_num,to_add_c});
					} else {
						it->second += to_add_c;
					}
					e.second -= to_add_c*a;
				}
			}
			return {m, square};

		} else if (r.second == -1 && l.second != -1){
			mli m(l.first);
			ll square = l.second;
			for(auto& e : m){ // 자동으로 오름차순 되어 있다.
				ll a = e.first; ll c = e.second;

				if(a == 1) continue; // 1은 제외한다

				int to_add_c = int(c/a);
				if( to_add_c > 0){
					square += to_add_c;
					ll to_add_num = a*a;
					auto it = m.find(to_add_num);
					if( it == m.end()){
						m.insert({to_add_num,to_add_c});
					} else {
						it->second += to_add_c;
					}
					e.second -= to_add_c*a;
				}
			}
			return {m, square};
		} else {
			ll square = (l.second + r.second);
			mli m(r.first);
#ifdef DEBUG_Q2
			for(auto e : m){
				    cout<<"{"<<e.first<<","<<e.second<<"} ";
			}
#endif
			for(auto e : l.first){
				if(e.second == 0 ) continue;
				auto it = m.find(e.first);
				if(it == m.end()){
					m[e.first] = e.second;
				} else {
					m[e.first] += e.second;
				}
			}

			for(auto& e : m){ // 자동으로 오름차순 되어 있다.
				ll a = e.first; ll c = e.second;

				if(a == 1) continue; // 1은 제외한다

				int to_add_c = int(c/a);
				if( to_add_c > 0){
					square += to_add_c;
					ll to_add_num = a*a;
					auto it = m.find(to_add_num);
					if( it == m.end()){
						m.insert({to_add_num,to_add_c});
					} else {
						it->second += to_add_c;
					}
					e.second -= to_add_c*a;
				}
			}
			#ifdef DEBUG_Q1
			for(auto e : m){
				cout<<"{"<<e.first<<","<<e.second<<"} ";
			}
			cout<<"square : "<<square<<endl;
			#endif
			return {m, square};	
		}
    }
    
    ll query(const int left, const int right){
        return query(left, right, 1, 0, n-1).second;
    }
    
} segtree;

int main(int argc, char** argv)
{
	int T, test_case;
	cin >> T;
	int N,Q;
	vector<ll> A(MAX_N);
	for(test_case = 0; test_case  < T; test_case++)
	{

		/////////////////////////////////////////////////////////////////////////////////////////////
		cin>>N;
		for(int i = 0 ; i < N; i++){
		    cin>>A[i];
		}
		
		//create segtree
		segtree.reinit(A, N);

#ifdef DEBUG_ST
for(int i = 0 ; i < segtree.counts.size(); i++){
    if(segtree.counts[i].empty()) continue;
    cout<<"counts["<<i<<"] : ";
    for(auto e : segtree.counts[i]){
        cout<<"{"<<e.first<<","<<e.second<<"} ";
    }
    cout<<endl;
}
#endif

		//query
		cin>>Q;
		int l,r;
		cout << "Case #" << test_case+1 << endl;
		for(int i = 0; i < Q; i++){
		    cin>>l>>r;
		    cout<<segtree.query(l-1,r-1)<<endl;
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////
	}

	return 0;//Your program should return 0 on normal termination.
}