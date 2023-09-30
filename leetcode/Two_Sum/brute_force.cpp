#include <iostream>
#include <vector>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target){
    for (int i = 0; i < nums.size(); i++ ){
        for (int j = i+1 ; j < nums.size(); j++){
            if(nums[i] + nums[j] == target){
                return {i,j};
            }
        }
    }
    return {};
}

int main() {
    // input
    vector<int> nums;
    int target;
    int n_nums;
    cin>>n_nums;
    for (int i=0 ; i< n_nums; i++){
        int num;
        cin>>num;
        nums.push_back(num);
    }
    cin>>target;
    vector<int> res = twoSum(nums,target);
    if (!res.empty()){
        for (int i = 0; i<res.size(); i++){
            cout<<res[i]<<" ";
        }
    } else{
        cout<<"trivial";
    }
    return 0;
}