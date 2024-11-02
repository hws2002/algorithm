//without memoization
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>
// #define DEBUG_DEDUP
// #define DEBUG_SOLVE

using namespace std;

vector< pair<int,int> > Meetings;
vector< pair<int,int> > meetings;
unordered_map<int, int> cache;

bool compare( const pair<int,int> & a, const pair<int,int> & b){
    if(a.first == b.first) return a.second < b.second;
    return a.first < b.first;
}

bool compareFirst(const pair<int, int>& a, const pair<int, int>& b) {
    return a.first < b.first;
}

int solve(const int idx){
#ifdef DEBUG_SOLVE
cout<<"idx : "<<idx<<endl;
#endif
    if( idx >= meetings.size() ) return 0;
    if(cache.find(idx)!=cache.end()) return cache[idx];

    int complement = 0;
    int start = meetings[idx].first;
    while( idx + complement < meetings.size() && meetings[idx + complement].first == start && meetings[idx + complement].second == start) complement++;

#ifdef DEBUG_SOLVE
cout<<"idx + complement, meetings[idx + complement].first, meetings[idx + complement].second : "<<idx+complement<<" "<<meetings[idx + complement].first<<" "<<meetings[idx + complement].second<<endl;
#endif

    if( idx + complement >= meetings.size() ){
        cache[idx] = complement;
        return complement;
    }

    if( meetings[idx + complement].first == start){
        // meetings[idx+complement].second != start
        // 2 2
        // 2 3
        // 4 7
        int end = meetings[idx+complement].second;
        auto iter = lower_bound(meetings.begin(), meetings.end(), make_pair(end,-1), compareFirst);
        if( iter == meetings.end()) {
            int res = max(1 + complement, solve(idx + complement + 1));
            cache[idx] = res; 
            return res;
        }
        int res = max(1 + complement + solve(distance(meetings.begin(), iter)), solve(idx+complement+1));
        cache[idx] = res;
        return res;
    } else {
        // meetings[idx + complement].first != start
        // 2 2
        // 3 6 <- idx + complement
        
        int res = complement + solve(idx + complement);
        cache[idx] = res;
        return res;
    }
}

int main(){
    int N;
    cin>>N;
    int s,e;
    for(int i  = 0 ; i < N; i++){
        cin>>s>>e;
        Meetings.push_back({s,e});
    }

    //sort
    sort(Meetings.begin(), Meetings.end(), compare);

    //deduplicate
        
    for(int i = 0 ; i < Meetings.size(); ){
        int start = Meetings[i].first;
        while(i < Meetings.size() && Meetings[i].second == start) {
            meetings.push_back({ start, start});
            i++;
        }
        if( i >= Meetings.size()) break;
        if(Meetings[i].first == start){
            int end = Meetings[i].second;
            meetings.push_back( {start, end });
            while( i < Meetings.size() - 1 && Meetings[i+1].first == Meetings[i].first){
                i++;
            }
            if(i >= Meetings.size() - 1 && Meetings[i].first == start) break;
            i++;
        }
    }

#ifdef DEBUG_DEDUP
cout<<"printing out Meetings :"<<endl;
for(auto item :Meetings){
    cout<<item.first<<" ";
}
cout<<endl;

for(auto item :Meetings){
    cout<<item.second<<" ";
}
cout<<endl;

cout<<"printing out meetings :"<<endl;
for(auto item :meetings){
    cout<<item.first<<" ";
}
cout<<endl;

for(auto item :meetings){
    cout<<item.second<<" ";
}
cout<<endl;
#endif
    //solve
    cout<<solve(0)<<endl;

    return 0;
}