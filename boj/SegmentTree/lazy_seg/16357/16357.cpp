#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 100'000
#define endl '\n'
// #define DEBUG_COMPRESS
// #define DEBUG_RMQ
// #define DEBUG_SCAN
using namespace std;


vector< pair<int,int> > intervals;
vector<int> intervals_all;
struct RMQ{ // range max query
public:
    int n;
    vector<int> rangeMax;
    vector<int> lazy;
    
    RMQ(int N){
        n = N;
        rangeMax = vector<int> (4*n, 0);
        lazy = vector<int> (4*n, 0);
    }
    
    //propagate
    void propagate(const int nn, const int nl, const int nr){
        if( lazy[nn] ){
            rangeMax[nn] += lazy[nn];
            if( nl < nr){
                lazy[nn*2] += lazy[nn];
                lazy[nn*2+1] += lazy[nn];
            }
        }
        lazy[nn] = 0;
    }
    
    
    //query
    int query(const int l, const int r, const int nn, const int nl, const int nr){
        //push
        propagate(nn, nl, nr);
        
        //out of range
        if( r < nl || nr < l) return -1;
        
        //inside range
        if( l <= nl && nr <= r){
            return rangeMax[nn];
        }
        
        int mid = (nl + nr) >> 1;
        return max( query(l, r, nn*2, nl, mid) , query(l, r, nn*2+1, mid+1, nr) );
    }
    
    //query - interface
    int query(const int l, const int r){
        return query(l,r,1,0,n-1);
    }
    
    //update 
    int update(const int l, const int r, const int w, const int nn, const int nl, const int nr){
        propagate(nn,nl,nr);
        
        //out of range
        if( r < nl || nr < l) return rangeMax[nn];
        
        //inside range
        if( l <= nl && nr <= r){
            rangeMax[nn] += w;
            if(nl < nr){
               lazy[nn*2] += w;
               lazy[nn*2 + 1] += w;
            }
            return rangeMax[nn];
        }
        int mid = (nl + nr) >> 1;
        return rangeMax[nn] = max(update(l, r, w, nn*2, nl, mid) , update(l, r, w, nn*2 + 1, mid+1, nr));
    }
    
    //update - interface
    void update(const int l, const int r, const int w){
        update(l,r,w,1,0,n-1);
    }
};

bool compare(const pair<int,int> & p1, const pair<int, int> & p2){
    if( p1.first == p2.first ) return p1.second < p2.second;
    return p1.first < p2.first;
}

int N;
//returns size of intervals_all after compression
int compressCoordinate(){
    sort(intervals_all.begin(), intervals_all.end());
	intervals_all.erase(unique( intervals_all.begin(), intervals_all.end()), intervals_all.end());
#ifdef DEBUG_COMPRESS
for(auto e : intervals_all){
	cout<<e<<" ";
}
	cout<<endl;
#endif
  
    
    sort(intervals.begin(), intervals.begin() + N, compare);
    for(auto & interval : intervals){
        interval.first  = lower_bound(intervals_all.begin(), intervals_all.end(), interval.first) - intervals_all.begin();
        interval.second = lower_bound(intervals_all.begin(), intervals_all.end(), interval.second) - intervals_all.begin();
    }
	return intervals_all.size();
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
    cin>>N;
    int ux,uy,vx,vy;
	intervals.resize(N);
    for(int i = 0 ; i < N; i++){
        cin>>ux>>uy>>vx>>vy;
        intervals[i] = {vy,uy};
        intervals_all.push_back(vy);
        intervals_all.push_back(uy);
    }

    //coordinate compression
	int total_coordinates_unique = compressCoordinate();
    RMQ rmq(total_coordinates_unique);
	RMQ rmql(total_coordinates_unique);
#ifdef DEBUG_COMPRESS
for(int i = 0 ; i < N; i++){
	auto p = intervals[i];
    printf("%d, %d \n", p.first, p.second);
}
#endif
	for(int i = 0 ; i < N; i++){
		auto p = intervals[i];
		//update rmq
		rmq.update(p.first, p.second, 1);
		rmql.update(p.first, p.second, 1);
	}

#ifdef DEBUG_RMQ
for(int i = 1 ; i < 23;i++){
	printf("rangeMAX[%d] : %d \n", i, rmq.rangeMax[i]);
}
#endif
	
    int res = 0;
    int lidx = 0; int n_left;
	vector<bool> removed (N, false);
	for(int leftp = intervals[0].first ; leftp <= intervals[N-1].first; leftp++){    
		// count number of recs including leftp
		// update segtree  at the same time
		n_left = rmql.query(leftp, leftp);
		// while( intervals[lidx1].second < leftp){
		// 	if( !removed[lidx1] ) 
		// 		rmq.update( intervals[lidx1].first, intervals[lidx1].second, -1);
		// 	removed[lidx1] = true;
		// 	lidx1++;
		// }
		
		while( lidx < N && intervals[lidx].first <= leftp ) {
			if( !removed[lidx] ) 
				rmq.update( intervals[lidx].first, intervals[lidx].second, -1);
			removed[lidx] = true;
			lidx++;
		}
		
		// printf("lidx1, lidx2 : %d, %d ", lidx1, lidx2);
		// n_left = lidx2 - lidx1;
		
		//query
		int n_right = rmq.query(0, total_coordinates_unique-1);
#ifdef DEBUG_SCAN
		printf("n_left, n_right : %d, %d \n", n_left, n_right);
#endif
		res = max(n_left + n_right, res);
	}

    cout<<res<<endl;
    return 0;
}