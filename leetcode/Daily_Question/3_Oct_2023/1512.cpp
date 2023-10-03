#include <iostream>

using namespace std;

class Solution {
public:
    static int numIdenticalPairs(vector<int>& nums) {
        int nums_count[101] = {0};
        int res = 0; // number of good pairs
        for(int i=0 ;i < nums.size(); i++){
            res += nums_count[nums[i]];
            nums_count[nums[i]] += 1;
        }
        return res;
    }
};

int main() {
    vector<int> nums{1,2,3,1,1,3}; // change to desired value
    int answer =  Solution::numIdenticalPairs(nums);
    printf("output : %d",answer);
    return 0;
}