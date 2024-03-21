#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>

// #define DEBUG_INPUT
// #define DEBUG_SOLVE

using namespace std;

bool compare( const pair<int,int> & a, const pair<int,int> & b){
    // descending order by d
    return a.second > b.second;
}

int n;
vector< pair<int,int> > Vector_Pair_p_d;
vector< pair<int,int> >::iterator iter;
priority_queue<int> PQ_p;

int main(){
    //input
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>n; int p,d;
    for(int i = 0 ; i < n ; i++){
        cin>>p>>d;
        Vector_Pair_p_d.push_back({p,d});
    }

    //sort
    std::sort(Vector_Pair_p_d.begin(), Vector_Pair_p_d.end(), compare);

#ifdef DEBUG_INPUT
cout<<"PRINTING SORTED Vector_Pair_p_d : "<<endl;
for(iter = Vector_Pair_p_d.begin(); iter != Vector_Pair_p_d.end(); iter++){
    cout<<iter->first<<" ";
}
cout<<endl;

for(iter = Vector_Pair_p_d.begin(); iter != Vector_Pair_p_d.end(); iter++){
    cout<<iter->second<<" ";
}
cout<<endl;
#endif
            
    //solve
    int res = 0;
    // iter = Vector_Pair_p_d.begin();
    int index_pair = 0;
    for(d =  Vector_Pair_p_d.begin()->second; d >= 1; d--){
        while(index_pair < Vector_Pair_p_d.size() && Vector_Pair_p_d[index_pair].second >= d){
#ifdef DEBUG_SOLVE
cout<<"pushing : "<<Vector_Pair_p_d[index_pair].first<<endl;
#endif
            PQ_p.push( Vector_Pair_p_d[index_pair++].first);
        }
        if(!PQ_p.empty()){
#ifdef DEBUG_SOLVE
cout<<"top : "<<PQ_p.top()<<endl;
#endif
            res+=PQ_p.top(); PQ_p.pop();
        }
    }
    cout<<res<<endl;
    return 0;
}