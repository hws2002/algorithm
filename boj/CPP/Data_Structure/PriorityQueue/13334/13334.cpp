#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define MAX_N 100'000
#define MAX_D 200'000'000

// #define DEBUG_SORT
// #define DEBUG_Q
using namespace std;
typedef pair<int,int> pii;

#ifdef DEBUG_Q
void printQueue(priority_queue<int, vector<int>, greater<> > q){
    while(!q.empty()){
        // cout<<"("<<q.front().first<<","<<q.front().second<<") ";
        cout<<q.top()<<" ";
        q.pop();
    }
    cout<<endl;
}
#endif
int n,d;
vector<pii> ho;
bool compare(const pii & a, const pii & b){
    if( a.second == b.second ) return a.first < b.first;
    return a.second < b.second;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin>>n;
    int h,o;
    for(int i = 0; i < n; i++){
        cin>>h>>o;
        if(h > o) swap(h,o);
        ho.push_back({h,o});
    }
    
    //sort
    std::sort(ho.begin(), ho.end(), compare);
#ifdef DEBUG_SORT
for(auto p : ho){
    cout<<"("<<p.first<<","<<p.second<<") ";
}
cout<<endl;
#endif
    cin>>d;
    
    // pq
    
    int res = 0;
    priority_queue<int, vector<int>, greater<> > pq;
    int co = -100'000'005;
    for(int i = 0; i < ho.size();){
        co = ho[i].second;
        int s = co-d;
#ifdef DEBUG_Q
cout<<"co : "<<co<<endl;
printQueue(pq);
#endif
        while(!pq.empty() && pq.top() < s){
            pq.pop();
        }
        int j;
        for(j = i; j < ho.size(); j++){
            if( ho[j].second != co) break;
            if( ho[j].first >= s){
                pq.push(ho[j].first);
            }
        }
        i = j;
        res = max(res, (int)pq.size());
    }
    
    //output
    cout<<res<<endl;
    return 0;
}