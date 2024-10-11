#include <iostream>
#include <vector>
#include <algorithm>


#define MAX_COOR 1'000'000'000
using namespace std;
typedef long long ll;

template <typename T>
struct Rectangle{
    // x1 < x2, y1 < y2
    T x1, y1, x2, y2;
    Rectangle(T x1, T y1, T x2, T y2) : x1(x1), y1(y1), x2(x2), y2(y2){};
};

template <typename T>
struct SegTree{
	int n;
	vector<ll> rangeCover;
	vector<int> count;
	vector<int> lazy;
	
	SegTree(int n) : n(n){
		rangeCover.resize(4*n,0);
		rangeSum.resize(4*n,0);
		lazy.resize(4*n,0);
	}
	
	void propagate(int nn, int nl, int nr){
		if( lazy[nn] ){
			
			if( nl < nr){
				lazy[nn<<1] += lazy[nn];
				lazy[nn<<1|1] += lazy[nn];
			}
			lazy[nn] = 0;
		}
	}
	
	int update(int l, int r, int toadd, int nn, int nl, int nr){
		propagate(nn,nl,nr);
		if( r < nl || nr < l) return rangeCover[nn];
		
	}
	
	//update
	void update(int l, int r, int toadd){
		update(l,r,toadd,1,0,n-1);
	}
	
	//query
	ll query(int l, int r, int nn, int nl, int nr){
		// push
		propagate(nn,nl,nr);
		
		if( r < nl || nr < l) return 0;
		
		if( l <= nl && nr <= r) {
			return rangeCover[nn];
		}
		
		int mid = (nl + nr) >> 1;
		return query(l,r, nn<<1, nl, mid) + query(l,r, nn<<1 | 1, mid+1, nr);
	}

	//query
	ll query(int l, int r){ // [l,r]
		return query(l, r, 1, 0, n-1);
	}
	
};

//직사각형들의 면적을 계산한다
template <typename T>
T unionArea(const vector< Rectangle<T>> & rects){
    if(rects.empty()) return 0;
    
    // 이벤트 정보 : (x 좌표, 왼쪽인가 오른쪽인가, 사각형의 번호)
    typedef pair<T, pair<int,int> > Event;
    vector<Event> events;
    vector<T> ys;
    // 각 사각형을 순회하면서 y좌표의 모음과 이벤트의 집합을 찾는다
    for(int i = 0; i < rects.size(); i++){
        ys.push_back(rects[i].y1);
        ys.push_back(rects[i].y2);
        events.push_back( Event(rects[i].x1, {1,i}) );
        events.push_back( Event(rects[i].x2, {-1,i}) );
    }
    
    // y 좌표의 집합을 정렬하고 중복을 제거
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());    
    
    // 이벤트 목록을 정렬
    sort(events.begin(), events.end());    
    T ret = 0;
    
    //count[i] = ys[i] ~ ys[i+1] 구간에 겹쳐진 사각형의 수
    vector<int> count(ys.size()-1, 0);
    for(int i = 0 ; i < events.size(); i++){
        T x = events[i].first;
        int delta = events[i].second.first;
        int rectangle = events[i].second.second;
        //count[]를 갱신
        T y1 = rects[rectangle].y1; T y2 = rects[rectangle].y2;
        for(int j = 0; j < ys.size(); j++){
            if (y1 <= ys[j] && ys[j] < y2){
                count[j] += delta;
            }
        }
        
        //cutLength 값을 계산한다
        T cutLength = 0;
        for(int j = 0; j < ys.size()-1; j++){
            if(count[j] > 0)
                cutLength += ys[j+1] - ys[j];
        }
        // 다음 이벤트까지의 거리에 cutLength를 곱한 값을 리턴한다
        if(i + 1 < events.size())
            ret += cutLength * (events[i+1].first - x);
    }
    return ret;
};

int main(){
    int N;
    cin>>N;
    vector<Rectangle<ll>> rects;
    ll x1,x2,y1,y2;
    while(N--){
        cin>>x1>>x2>>y1>>y2;
        rects.push_back(Rectangle<ll>(x1,y1,x2,y2));
    }

	cout<<unionArea<ll>(rects)<<endl;
    return 0;
}

