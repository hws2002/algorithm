#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
#define DEBUG_INPUT
#define DEBUG_SOLVE
int N,K;


vector< pair<int,int> > Vector_Pair_M_V;
vector<int> Vector_C;
vector<pair<int,int>>::iterator iter_p;
vector<int>::iterator iter_c; 

bool TAKEN[300001] = {false};


bool compare(const pair<int, int> & a, const pair<int, int> & b){
    if(a.second == b.second) return a.first < b.first;
    return a.second > b.second;
}


// bool cmp(const int & to_find,  pair<int, int> const & p){
//     return (p.first > to_find);
// }


int main(){
    //input
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>N>>K;
    int m,v;
    for(int i = 1; i <= N; i++){
        // jewels
        cin>>m>>v;
        Vector_Pair_M_V.push_back({m,v});
    }
    
    int temp;
    for(int i = 0 ; i < K; i++){
        cin>>temp;
        Vector_C.push_back(temp);
    }
    
    //sort
    std::sort(Vector_Pair_M_V.begin(), Vector_Pair_M_V.end(), compare);
    std::sort(Vector_C.begin(), Vector_C.end());
#ifdef DEBUG_INPUT
cout<<"Vector_Pair_M_V :"<<endl;
cout<<"M : ";
for(iter_p = Vector_Pair_M_V.begin(); iter_p != Vector_Pair_M_V.end(); iter_p++){
    cout<<iter_p->first<<" ";
}
cout<<endl<<"V : ";
for(iter_p = Vector_Pair_M_V.begin(); iter_p != Vector_Pair_M_V.end(); iter_p++){
    cout<<iter_p->second<<" ";  
}
cout<<endl;

cout<<"Vector_C : "<<endl;
for(iter_c = Vector_C.begin(); iter_c != Vector_C.end(); iter_c++){
    cout<<*iter_c<<" ";
}
cout<<endl;
#endif
    //solve
    long res = 0;
    int bag_spent = 0; int index_c = 0;
    for(iter_p = Vector_Pair_M_V.begin(); bag_spent < K && iter_p != Vector_Pair_M_V.end(); iter_p++){
        iter_c = std::lower_bound(Vector_C.begin(), Vector_C.end(), iter_p->first);
        index_c = distance(Vector_C.begin(), iter_c);
        while(index_c < K && TAKEN[index_c]){
            index_c++;
        }
        if(index_c == K) continue;

#ifdef DEBUG_SOLVE
    cout<<"Jewel to steal (M,V) : ("<<iter_p->first <<","<<iter_p->second <<")"<<endl;
    cout<<"Bag to use = "<<index_c<<"th bag, C : "<<Vector_C[index_c]<<endl;
#endif
        res += iter_p->second; 
        TAKEN[index_c] = true;
        bag_spent++;
    }
    
    cout<<res<<endl;
    return 0;
}