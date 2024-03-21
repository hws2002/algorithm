#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;
int N,K;


vector< pair<int,int> > Vector_Pair_M_V;
vector<int> Vector_C;
vector<pair<int,int>>::iterator iter_p;
vector<int>::iterator iter_c; 
std::priority_queue<int> PQ_V;

bool compare(const pair<int, int> & a, const pair<int, int> & b){
    // if(a.first == b.first) return a.second < b.second;
    return a.first < b.first;
}


int main(){
    //input
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
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
    
    //solve
    long long res = 0; int index_p=0;
    for(int i = 0; i < K ; i++){
        while( index_p < N && Vector_Pair_M_V[index_p].first <= Vector_C[i] ){
            PQ_V.push(Vector_Pair_M_V[index_p].second);
            index_p++;
        }
        
        if(!PQ_V.empty()){
            res += PQ_V.top(); 
            PQ_V.pop();
        }
    }
    
    cout<<res<<endl;
    return 0;
}