#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<int> Vector_nums;
vector<int>::iterator iter;

int N; //1 <= N <= 1000000

int main(){
    cin>>N;
    int temp;
    cin>>temp;

    Vector_nums.push_back(temp);
    for(int i = 1 ; i < N; i++){
        cin>>temp;
        if(temp > Vector_nums.back()) Vector_nums.push_back(temp);
        else if (temp < Vector_nums.front()) Vector_nums[0] = temp;
        else{
            iter = lower_bound(Vector_nums.begin(), Vector_nums.end(), temp);
            *iter = temp;
        }
    }
    
    //output
    cout<<Vector_nums.size()<<endl;
    return 0;    
}