#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 300001
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

struct SegTree{
public:
    int n;
    vector<int> cnt;
    vector<int> rc; // rangecover
    
    SegTree(int n) : n(n){
        cnt.resize(4*n,0);
        rc.resize(4*n,0);
    };
    
    
    void add(int l ,int r, int val, int nn, int nl, int nr){

        // printf("l,r, nn, nl, nr : %d, %d, %d, %d , %d \n",l,r, nn, nl, nr);
        // out of range
        if( r < nl || nr < l) return ;
        
        if( l <= nl && nr <= r) {
            // inside of range
            cnt[nn] += val;
        } else {
            // the third case
            int mid = (nl + nr) >> 1;
            add(l,r,val, nn<<1, nl, mid); add(l,r,val, nn<<1|1, mid+1, nr);
        }
        
        if( cnt[nn] ) rc[nn] = nr - nl + 1;
        else {
            if(nr<=nl) rc[nn] = 0;
            else rc[nn] = rc[nn<<1] + rc[nn<<1|1];
        }
    }
    
    //add - interface
    void add(int l, int r, int val){ //add val to [l,r]
        add(l, r, val, 1, 0, n-1);
    }
    
    //query
    int query(){
        return rc[1];
    }
};

int unionArea(){
    
    vector<Event> events;
    for(int i = 0; i < rects.size(); i++){
        events.push_back(Event(rects[i].x1,1,i));
        events.push_back(Event(rects[i].x2,-1,i));
    }
    
    sort(events.begin(), events.end(), [](const Event & e1, const Event & e2){
        return e1.x < e2.x;
    });
    
    SegTree t(MAX_N);
    // printf(" l, r, events[0].x : %d, %d ,%d \n", rects[events[0].idx].y1, rects[events[0].idx].y2, events[0].x);
    t.add(rects[events[0].idx].y1, rects[events[0].idx].y2 - 1 , 1);
    int ret = 0;
    for(int i = 1; i < events.size(); i++){
        int diff_x = events[i].x - events[i-1].x;
        ret += diff_x * (t.query());
        // printf("t.query(), diff_x, toadd  :  %d, %d, %d \n", t.query(), diff_x, diff_x * t.query());
        int l = rects[events[i].idx].y1;
        int r = rects[events[i].idx].y2;
        // printf("l,r, events[%d].x : %d, %d ,%d \n",i, l, r, events[i].x);
        t.add(l,r-1,events[i].delta);
    }
    return ret;
}

int main(){
    cin>>N;
    int x1,y1,x2,y2;
    for(int i = 0; i < N; i++){
        cin>>x1>>y1>>x2>>y2;
        rects.push_back(Rec(x1,x2,y1,y2));
    }
    
    cout<<unionArea()<<endl;
    
    return 0;
}