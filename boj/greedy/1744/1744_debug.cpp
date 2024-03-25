#include <iostream>
#include <vector>
#include <algorithm>

#define endl '\n'
// #define DEBUG_INPUT

using namespace std;

int N;
vector<int> Vector_num;

bool compare(const int & a, const int & b){
    return a < b; // ascending
}

int main(){
    //input
    cin>>N;
    Vector_num.resize(N,0);
    for(int i = 0; i < N; i++){
        cin>>Vector_num[i];
    }
    std::sort(Vector_num.begin(), Vector_num.end(), compare);
    int num_m = std::distance(Vector_num.begin(), std::lower_bound(Vector_num.begin(), Vector_num.end(), 0));
    int num_p = Vector_num.size() - std::distance(Vector_num.begin(), std::upper_bound(Vector_num.begin(), Vector_num.end(), 0));
    int num_0s = Vector_num.size() - num_p - num_m;
    int _index = num_m + num_0s;
    int num_1s = 0;
    while(_index < Vector_num.size() && Vector_num[_index] == 1){
        _index++;
        num_1s++;
    }
    int num_p_not1 = num_p - num_1s;
#ifdef DEBUG_INPUT
cout<<num_m<<" "<<num_0s<<" "<<num_1s<<" "<<num_p_not1;
#endif

    //solve
    
    int res = num_1s;
    
    // add positive numbers
    _index = Vector_num.size()-1;
    while(num_p_not1 > 1){
        res += Vector_num[_index] * Vector_num[_index-1];
        _index-=2;
        num_p_not1-=2;
    }
    if(num_p_not1) res+=Vector_num[_index];

    //add negative numbers
    _index = 0;
    while(num_m > 1){
        res += Vector_num[_index] * Vector_num[_index+1];
        _index+=2;
        num_m -=2;
    }
    
    if(num_m && !num_0s){
        res += Vector_num[_index];
    }
    cout<<res<<endl;
    return 0;
}