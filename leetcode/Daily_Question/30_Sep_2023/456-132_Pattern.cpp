#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

bool find132pattern(vector<int>& nums){
        int n = nums.size();
        stack< pair<int,int> > mono_s;
        mono_s.push({nums[0],nums[0]});

        for(int i = 1 ; i < nums.size(); i++){
            int to_compare = mono_s.top().first;
            int leftMin = mono_s.top().second;
            while(!mono_s.empty() && mono_s.top().first <= nums[i]){
                mono_s.pop();
            }
            if(!mono_s.empty() && mono_s.top().second < nums[i]) return true;
            mono_s.push({nums[i], min(leftMin,nums[i])});
        }
        return false;
}

int main() {
    vector<int> nums = {3,1,4,2};
    string answer = find132pattern(nums) ? "true" : "false";
    printf("Output : %s", answer.c_str());
    return 0;
}