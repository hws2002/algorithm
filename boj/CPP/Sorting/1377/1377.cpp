#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <limits.h>


using namespace std;

bool compare( const pair<int, int> & a ,const pair<int, int> & b){
    if(a.first == b.first) return a.second < b.second;
    return a.first < b.first;
}

int main(){
    //input
    int N, temp;
    vector< pair<int, int> > Vector_pair_num_index;
    cin>>N;
    for(int i = 0; i < N; i++){
        cin>>temp;
        Vector_pair_num_index.push_back({temp, i});
    }
    
    std::sort(Vector_pair_num_index.begin(), Vector_pair_num_index.end(), compare);
    
    int res = INT_MIN;
    for(int i = 0 ; i < N; i++){
        res = max(Vector_pair_num_index[i].second - i, res);
    }
    res++;
    cout<<res<<endl;
    return 0;
}