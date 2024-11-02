//brute force
#include <iostream>
#include <vector>

using namespace std;

int N,M;

void printVector(vector<int> & chosen){
    for(auto item: chosen){
        cout<<item<<" ";
    }
    cout<<endl;
}
void n_choose_r(vector<int> & chosen, const int last, const int toChoose){
    if(toChoose <= 0) {
        printVector(chosen);
        return ;
    }
    
    for(int next = last + 1; next <= N; next++){
        chosen.push_back(next);
        n_choose_r(chosen, next, toChoose-1);
        chosen.pop_back();
    }
}

int main(){
    //input
    cin>>N>>M;
    
    //solve
    vector<int> chosen;
    n_choose_r(chosen, 0 ,M);
    return 0;
}