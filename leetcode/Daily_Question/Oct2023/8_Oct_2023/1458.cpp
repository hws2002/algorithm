#include <iostream>
using namespace std;
class Solution {
public:

    int memoization[501][501];
    bool calculated[501][501] = {false};
    vector<int> _nums1;
    vector<int> _nums2;
    int length1;
    int length2;
    bool isAnswerNegative = true;
    int MaxNegativeAnswer = INT_MIN;
    int dp(int i, int j){
        // printf("start caluclate dp[%d][%d] \n",i,j);
        if(i>=length1 || j >= length2) {
            // printf("index out of range \n");
            return -1000001;
        }
        if(calculated[i][j]) {
            // printf("already calculated! memozation[%d][%d] = %d \n", i,j,memoization[i][j]);
            return memoization[i][j];
        }
        if(isAnswerNegative && _nums1[i] * _nums2[j] >= 0) isAnswerNegative = false;
        else MaxNegativeAnswer = max(_nums1[i] * _nums2[j], MaxNegativeAnswer);
        int choice1 = dp(i+1,j+1) == -1000001 ? (_nums1[i]*_nums2[j]) : (max(0,(_nums1[i]*_nums2[j])) + max(0,dp(i+1,j+1)));
        int choice2 = dp(i,j+1);
        int choice3 = dp(i+1,j);
        bool end2 = choice2 == -1000001 ? true : false;
        bool end3 = choice3 == -1000001 ? true: false;
        // printf("choice1, choice2, choice3 = %d, %d ,%d \n",choice1,choice2,choice3);
        if(!end2&&!end3) memoization[i][j] = max({choice1,choice2,choice3});
        else if(!end2&&end3) memoization[i][j] = max(choice1, choice2);
        else if(end2&&!end3) memoization[i][j] = max(choice1, choice3);
        else memoization[i][j] = choice1; // (end2&&end3)
        calculated[i][j] = true;
        // printf("i : %d, j : %d, memoization[i][j] = %d \n",i,j,memoization[i][j]);
        return memoization[i][j];
    }
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        length1 = nums1.size(); length2 = nums2.size();
        _nums1 = nums1;
        _nums2 = nums2;
        int i = 0; int j = 0;
        int res = dp(i,j);
        if(isAnswerNegative) return MaxNegativeAnswer;
        else return res;
    }
};

int main(){
    Solution solution;
    vector<int> nums1 = {666,-66,194,-454,174,-861,123,242,217,537,420,-338,-938,-507,-11,834,964,837,71,950,467,-330,139,151,962,-22,259,-698,-529,874,503,471,268,168,-557,-305,-220,131,-692,-933,-399,-432,-985,346,-633,943,476,-895,602,637,-787,-553,448,-458,851,-464,844,110,-925,-263,-135,-769,-997,-423,658,234,-930,538,-250,641,-587,702,-577,-278,79,68,858,383,48,-690,-730,320,-337,44,698,741,-611,-414,22,-577,773,608,-38,909,-681,-348,622,-851,84,430,-109,-839,262,922,853,217,-81,-550,-344,957,501,907,96,963,947,-877,-928,314,-577,945,-977,-404,739,749,-799,872,-535,72,-801,16,461,835,-459,136,-284,766,-139,922,-202,-527,-144,398,-466,261,604,-46,32,112,-535,367,-746,-169,976,858,855,971,834,-106,-971,609,-842,410,561,-483,-172,-373,-439,-177,687,-541,632,-107,-693,-406,208,-475,218,-531};
    vector<int> nums2 = {997,278,620,-390,479,-413,852,443,-481,-363,655,393,-364,-591,-499,-606,-621,-928,-729,800,923,-495,-319,368,854,-674,-703,-223,-516,239,615,-444,-860,919,418,-918,-740,358,-551,-178,-602,879,610,-929,631,112,-111,-96,518,902,583,94,247,-92,-953,10,-40,-509,166,-779,-16,-385,250,-628,-495,233,-234,20,311,-896,233,-251,852,-725,-688,-688,658,161,946,-593,73,771,824,737,495,-449,-517,340,-323,-204,-556,378,-934,113,-829,835,-753,371,907,344,-581,822,540,979,-731,-241,601,-58,-613,-182,370,874,54,-714,-174,-54,645,-371,172,95,139,-479,190,-932,-914,-487,-955,-443,485,-949,143,-587,375,-805,-882,114,-135,-505,-676,-453,-410,692,-901,959,-281,-559,-482,-214,-954,-189,-307,931,-465,652,64,59,-354,310,737,-582,-301,527,-708,494,966,47,-938,-577,-288,192,-394,-513,914,-746,-59,17,-100,-40,665,-851,335,-65,-155,-580,395,193,671,-952,-505,-495,-943,-2,937,-42,-918,-501,-218,-642,477,987};
    int res = solution.maxDotProduct(nums1,nums2);
    printf("Output : %d",res);
    return 0;
}