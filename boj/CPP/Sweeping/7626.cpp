#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 200'002
#define endl '\n'
using namespace std;
typedef long long ll;

struct Rec{
public:
    int x1,x2,y1,y2;
    Rec(int x1, int x2, int y1, int y2) : x1(x1), x2(x2), y1(y1), y2(y2){};
};

int N;
vector<Rec> rects;

struct Event{
public:
    int x;
    int delta;
    int idx;
    Event(int x, int delta, int idx) : x(x), delta(delta), idx(idx){};
};

vector<int> ys;

struct SegTree{
public:
    int n;
    vector<int> cnt;
    vector<int> rc; // rangecover in real coordiniate (coordinate before compression)
    
    SegTree(int n) : n(n){
        cnt.resize(4*n,0);
        rc.resize(4*n,0);
    };
    
    
    void add(int l ,int r, int val, int nn, int nl, int nr){
        // printf("l,r, nn, nl, nr : %d, %d, %d, %d , %d \n",l,r, nn, nl, nr);
        // out of range
        if( r <= nl || nr < l) return ;

        if( l <= nl && nr < r) {
            // inside of range
            cnt[nn] += val;
        } else {
            // the third case
            int mid = (nl + nr) >> 1;
            add(l,r,val, nn<<1, nl, mid); add(l,r,val, nn<<1|1, mid+1, nr);
        }

        if( cnt[nn] ) rc[nn] = ys[nr+1] - ys[nl];
        else {
            if(nr<=nl) rc[nn] = 0;
            else rc[nn] = rc[nn<<1] + rc[nn<<1|1];
        }
    }
    
    //add - interface
    void add(int l, int r, int val){ //add val to [l,r)
        add(l, r, val, 1, 0, n-1);
    }

    //query
    int query(){
        return rc[1];
    }
};

void compressCoordinate(){
    // compress coordinates of rects
    // and store result in ys
    for(auto & rec : rects){
        ys.push_back(rec.y1);
        ys.push_back(rec.y2);
    }
    
    sort(ys.begin(), ys.end());
    ys.erase( unique(ys.begin(), ys.end()), ys.end() );
    // for(auto y : ys){
    //     cout<<y<<" ";
    // }
    // cout<<endl;
    
    for(auto & rec : rects){
        rec.y1 = lower_bound(ys.begin(), ys.end(), rec.y1) - ys.begin();
        rec.y2 = lower_bound(ys.begin(), ys.end(), rec.y2) - ys.begin();
    }
}

ll unionArea(){
    // coordinate compression
    compressCoordinate();

    vector<Event> events;
    for(int i = 0; i < rects.size(); i++){
        events.push_back(Event(rects[i].x1,1,i));
        events.push_back(Event(rects[i].x2,-1,i));
    }

    sort(events.begin(), events.end(), [](const Event & e1, const Event & e2){
        return e1.x < e2.x;
    });

    SegTree t(ys.size()); // this value can be int(ys.size())+1
    // printf(" l, r, events[0].x : %d, %d ,%d \n", rects[events[0].idx].y1, rects[events[0].idx].y2, events[0].x);
    t.add(rects[events[0].idx].y1, rects[events[0].idx].y2, 1);
    ll ret = 0;
    for(int i = 1; i < events.size(); i++){
        ll diff_x = events[i].x - events[i-1].x;
        ret += diff_x * (1LL * t.query());
        // printf("t.query(), diff_x, toadd  :  %d, %lld, %lld \n", t.query(), diff_x, diff_x * 1LL * t.query());
        int l = rects[events[i].idx].y1;
        int r = rects[events[i].idx].y2;
        // printf("l,r, events[%d].x : %d, %d ,%d \n",i, l, r, events[i].x);
        t.add(l,r,events[i].delta);
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N;
    int x1,y1,x2,y2;
    for(int i = 0; i < N; i++){
        cin>>x1>>x2>>y1>>y2;
        rects.push_back(Rec(x1,x2,y1,y2));
    }
    
    cout<<unionArea()<<endl;
    
    return 0;
}