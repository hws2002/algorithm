#include <iostream>
#include <vector>

#define MAX_N 1'000'001
// #define DEBUG_LIS5
using namespace std;

int N;
vector<int> A;
vector<int> res;
vector<int> resIdx;
vector<int> prevChoice;

#ifdef DEBUG_LIS5
void printVector(vector<int> & v){
    for(auto item : v){
        cout<<item<<" ";
    }
    cout<<endl;
}
#endif

void lis5(){
    for(int idx = 0 ; idx < A.size(); idx++){
        if(res.empty() || res.back() < A[idx]){
            res.push_back(A[idx]);
            if(prevChoice.empty()) prevChoice.push_back(-1);
            else prevChoice.push_back(resIdx.back());
            resIdx.push_back(idx);
        } else {
            auto iter = std::lower_bound(res.begin(), res.end(), A[idx]);
            if( *iter == A[idx] ) {prevChoice.push_back(-1); continue;}
            *iter = A[idx];
            resIdx[std::distance(res.begin(), iter)] = idx;
            if( std::distance(res.begin(), iter) == 0) prevChoice.push_back(-1);
            else prevChoice.push_back(resIdx[std::distance(res.begin(), iter)-1]);
        }
#ifdef DEBUG_LIS5
cout<<"prevChoice : ";
printVector(prevChoice);
cout<<"res : ";
printVector(res);
cout<<"resIdx : ";
printVector(resIdx);
#endif
    }
}

int main(){
    cin>>N;
    
    int temp;
    for(int i = 0 ; i < N; i++){
        cin>>temp;
        A.push_back(temp);
    }
    
    //lis
    lis5();
    
    //output
    cout<<res.size()<<endl;
    vector<int> ans;
    int idx = resIdx.back();
    while(idx != -1){
        ans.push_back(A[idx]);
        idx = prevChoice[idx];
    }
    for(int i = ans.size()-1; i >= 0; i--){
        cout<<ans[i]<<" ";
    }
    return 0;
}
