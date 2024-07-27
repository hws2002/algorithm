#include <iostream>
#include <vector>
#include <algorithm>


// #define DEBUG_INPUT
// #define DEBUG_SOLVE

using namespace std;

int N,C;
vector<int> Vector_X;
/*
Given number `to_find`, find the lower bound from Vector_X
lower_bound : greater than or equal to 
return index
*/

int binSearch_LB(const int & to_find){
    int mid,lo = 0;
    int hi = Vector_X.size();
    
    while(lo < hi){
        mid = (lo + hi) >> 1;
        if(Vector_X[mid] > to_find){
            hi = mid;        
        } else if (Vector_X[mid] < to_find){
            lo = mid + 1;
        } else {
            return mid;
        }
    }
    if(Vector_X[lo] == to_find){
        return lo;
    } else {
        return lo++;
    }
    return lo;
}

bool solve(const int & res){
    int c = 1; 
    int x = Vector_X.front();
    // int _index;
#ifdef DEBUG_SOLVE
cout<<"res : "<<res<<endl;
#endif
    while(true){
        auto _index = binSearch_LB(x + res);
        // auto _index = std::lower_bound(Vector_X.begin(), Vector_X.end(), x+res);
        
        if(_index < Vector_X.size() ) {        
        // if(_index != Vector_X.end() ){
#ifdef DEBUG_SOLVE
cout<<"Found a lower bound of "<<x+res<<" in Vector_X , x : "<<Vector_X[_index]<<endl;
// cout<<"Found a lower bound of "<<x+res<<" in Vector_X , x : "<<*_index<<endl;
#endif
            x = Vector_X[_index];
            // x = *_index;
            if(++c >= C){
                return true;
            }
        } else{
            return false;
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    //input
    cin>>N>>C;
    int temp;
    for(int i = 0 ; i < N ;i ++){
        cin>>temp;
        Vector_X.push_back(temp);
    }
    
    
    //sort
    std::sort(Vector_X.begin(), Vector_X.end());

#ifdef DEBUG_INPUT
cout<<"PRINTING OUT Vector_X : "<<endl;
for(auto iter = Vector_X.begin(); iter != Vector_X.end(); iter++){
    cout<< *iter <<" ";
}    
cout<<endl;
#endif
    //solve
    int res_max = ( Vector_X.back() - Vector_X.front() )/ (C-1) ; 
    int res_min = 1; int res = 1;
    while(res_min <= res_max){
        res = (res_max + res_min) >> 1;   
        if( solve(res) ){
            res_min = res + 1;
        } else {
            if(res_max == res) break;
            res_max = res;
        }
    }
    
    //output
    cout<<res_min-1<<endl;
    
    return 0;
}