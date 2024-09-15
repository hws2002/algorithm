#include <iostream>
#include <vector>
#include <algorithm>
#define endl '\n'
using namespace std;

int N,M;
vector<int> Arr;

void printVector(vector<int> & v){
    for(auto item : v){
        cout<<item<<" ";
    }
    cout<<endl;
}

void NChooseM5(vector<int> & picked, const int toChoose, bool visit[9]){
    //base
    if(toChoose <= 0){
        //printOutPicked
        printVector(picked);
        return ;
    }
    
    for(int idx = 0; idx < N; idx++){
        if( !visit[idx] ){
            picked.push_back(Arr[idx]);
            visit[idx] = true;
            NChooseM5(picked, toChoose-1, visit);
            picked.pop_back();
            visit[idx] = false;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //input
    cin>>N>>M;
    int temp;
    for(int i = 0 ; i < N; i++){
        cin>>temp;
        Arr.push_back(temp);
    }
    //sort
    std::sort(Arr.begin(), Arr.end());

    bool visit[9] = {false};
    vector<int> picked;
    NChooseM5(picked,M,visit);
    return 0;
}