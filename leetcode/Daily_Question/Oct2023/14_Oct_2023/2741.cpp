#include <iostream>
using namespace std;

class Solution {
public:

    vector<int> _cost;
    vector<int> _time;
    int threshold;
    long long memoization[500][501] = {0};

    long long dp(int index, int remaining){
        if(remaining <= 0 ) return 0;
        if(index >= threshold) return INT_MAX;
        if(memoization[index][remaining]) return memoization[index][remaining];
        long long paint = _cost[index] + dp(index+1, remaining-1-_time[index]);
        long long skip = dp(index+1, remaining);
        memoization[index][remaining] = std::min(paint,skip);
        return memoization[index][remaining];
    }

    int paintWalls(vector<int>& cost, vector<int>& time) {
        _cost = cost;
        _time = time;
        threshold = cost.size();
        int res = (int) dp(0,threshold);
        return res;
    }
};

int main(){
    vector<int> cost{2,3,4,2};
    vector<int> time{1,1,1,1};
    Solution solution;
    int result = solution.paintWalls(cost,time);
    printf("output : %d ", result);
    return 0;
}