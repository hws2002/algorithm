#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

// #define DEBUG_INPUT1
// #define DEBUG_INPUT2

vector< pair<int,int> > Vector_Pair_num_app;
vector< pair<int,int> >::iterator iter;

int N,M;
    int lo = 0;
    int hi = Vector_Pair_num_app.size()-1;
    int mid = 0;
    bool found = false;
    

bool compare(const pair<int,int> & a, const pair<int,int> & b){
    return a.first < b.first;
}



int main(){
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    //input
    cin>>N;
    
    int num; cin>>num; Vector_Pair_num_app.push_back({num,1});
    for(int i = 1 ; i < N; i++){
        cin>>num;
#ifdef DEBUG_INPUT1
cout<<"Printing out Vector_Pair_num_app"<<endl;
for(iter = Vector_Pair_num_app.begin(); iter != Vector_Pair_num_app.end(); iter++){
    cout<<"("<<(*iter).first<<","<<(*iter).second<<")"<<" ";
}
cout<<endl;
#endif
        //bin search num
        lo = 0; hi = Vector_Pair_num_app.size()-1; found = false;
        if( (Vector_Pair_num_app.back()).first < num) {
            Vector_Pair_num_app.push_back({num,1});
            continue;
        }
        
        while(lo < hi){
            mid = (lo + hi) >> 1;
            if( Vector_Pair_num_app[mid].first < num){
                lo = mid + 1;
            } else if (Vector_Pair_num_app[mid].first > num){
                hi = mid;
            } else {
                found = true;
                Vector_Pair_num_app[mid].second +=1;
                break;
            }
        }
        
        if(!found){//lo==hi
            if(Vector_Pair_num_app[lo].first == num){
                Vector_Pair_num_app[lo].second +=1;
            } else {
                Vector_Pair_num_app.insert(Vector_Pair_num_app.begin() + lo, {num,1});
            }
        }
    }
#ifdef DEBUG_INPUT2
cout<<"Printing out Vector_Pair_num_app"<<endl;
for(iter = Vector_Pair_num_app.begin(); iter != Vector_Pair_num_app.end(); iter++){
    cout<<"("<<(*iter).first<<","<<(*iter).second<<")"<<" ";
}
cout<<endl;
#endif

    
//arrange in ascending order (based on second value)
// std::sort(Vector_Pair_num_app.begin(), Vector_Pair_num_app.end(), compare);
    
    //solve
    cin>>M;
    int to_find;
    for(int i = 0; i < M; i++){
        cin>>to_find;
        if( (Vector_Pair_num_app.back()).first < to_find) {
            cout<<0<<" ";
            continue;
        }
        lo = 0; hi = Vector_Pair_num_app.size()-1; found = false;
        // TODO : binsearch(to_find)
        while(lo < hi){
            mid = (lo + hi) >> 1;
            if(Vector_Pair_num_app[mid].first > to_find){
                hi = mid;
            } else if (Vector_Pair_num_app[mid].first < to_find){
                lo = mid + 1;
            } else {
                cout<<Vector_Pair_num_app[mid].second<<" ";
                found = true;
                break;
            }
        }

        if(!found){
            if(Vector_Pair_num_app[lo].first == to_find){
                cout<<Vector_Pair_num_app[lo].second<<" ";
            } else {
                cout<<0<<" ";
            }
        }
    }
    cout<<endl;
    return 0;
}