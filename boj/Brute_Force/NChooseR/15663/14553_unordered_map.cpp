#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define endl '\n'
using namespace std;

// Custom hash function for vector<int>
struct VectorHash {
    size_t operator()(const std::vector<int>& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

int N,M;
vector<int> A;
unordered_map< vector<int>, bool, VectorHash> PRINTED; // Use custom hash function

void printVectorInt(vector<int> & picked){
    for(auto item : picked){
        cout<<item<<" ";
    }
    cout<<endl;
}

bool notPrinted(vector<int> & picked){
    return false;
}

void NchooseM9(vector<int> & picked, const int toChoose, bool visit[8]){
    if(toChoose <= 0){
        if( PRINTED.find(picked) == PRINTED.end() ) {
            printVectorInt(picked);
            PRINTED[picked] = true;
        }
        return ;
    }
    
    for(int next_idx = 0; next_idx < N; next_idx++){
        if( !visit[next_idx] ){
            picked.push_back(A[next_idx]);
            visit[next_idx] = true;
            NchooseM9(picked, toChoose-1, visit);
            visit[next_idx] = false;
            picked.pop_back();
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>M;
    for(int i = 0; i < N; i++){
        int temp;
        cin>>temp;
        A.push_back(temp);
    }
    
    std::sort(A.begin(), A.end());
    
    //solve
    vector<int> picked;
    bool visit[8] = {false};
    
    NchooseM9(picked,M,visit);
    
    return 0;
}
