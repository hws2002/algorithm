#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
// #define DEBUG
class Solution {
public:

    static bool Inres(const vector<int>& res, int valueToFind){
        #ifdef DEBUG
            for(int i = 0 ; i< res.size(); i++){
                printf("%dth element : %d \n", i+1, res[i]);
            }
        #endif
        if (res.empty()) return false;
        return find(res.begin(), res.end(), valueToFind) != res.end() ? true : false ; 
    }
    static vector<int> majorityElement(vector<int>& nums) {
        vector<int> res;
        if(nums.size() == 1){
            res = nums;
            return res;
        }
        if(nums.size() == 2 ){
            if (nums[0] == nums[1]){
                res.push_back(nums[0]);
            } else {
                res.push_back(nums[0]);
                res.push_back(nums[1]);
            }
            return res;
        }
        unordered_map<int, int> element2count;
        int threshold = static_cast<int>(nums.size()) / 3;
        #ifdef DEBUG
            printf("threshold : %d \n", threshold);
        #endif
        for(int i =0; i < nums.size(); i++){
            auto it = element2count.find(nums[i]);
            if( it != element2count.end()){
                // already in hashmap
                #ifdef DEBUG
                    printf("(i=%d) num, count : %d, %d \n",i, nums[i], it->second);
                #endif
                it->second += 1;
                if (it->second > threshold && (!Inres(res,it->first))) {
                    #ifdef DEBUG
                        printf("(i=%d) pushing element %d to res \n",i,it->first);
                    #endif
                    res.push_back(it->first);
                    if (res.size() >= 2) break;
                }
            } else {
                #ifdef DEBUG
                    printf("(i=%d) adding new element : %d \n", i,nums[i]);
                #endif
                element2count[nums[i]] = 1;
            }
        }
        return res;
    }
};

int main(){
    vector<int> nums{3,2,3};
    vector<int> res = Solution::majorityElement(nums);
    std::cout<<"[";
    for (std::vector<int>::iterator it = res.begin(); it != res.end(); ++it) {
        std::cout << *it <<",";
    }
    std::cout<<"]";
    return 0;
}