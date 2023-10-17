#include <iostream>
using namespace std;

class Solution {
public:
    int total_length;

    bool is_end(const int index){
        return (index == total_length/2) ? true : false;
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(); int n = nums2.size();
        int index1 = 0; int index2 = 0;
        total_length = m+n;
        if(total_length % 2){ // odd 
            while( !is_end(index1+index2) && index1 < m && index2 < n){
                nums1[index1] < nums2[index2] ? index1++ : index2++;
            }

            if( is_end(index1+index2) ){
                if (index1 == m){
                    return (double)nums2[index2];
                } else if (index2 == n){
                    return (double)nums1[index1];
                } else {
                    return nums1[index1] < nums2[index2] ? (double)nums1[index1] : (double)nums2[index2];
                }
            } else {
                if(index1 < m){
                    while (!is_end(index1+index2)){
                        index1++;
                    }
                    return (double)nums1[index1];
                } else {
                    while (!is_end(index1+index2)){
                        index2++;
                    }
                    return (double)nums2[index2];
                }
            }
        } else { //even
            double left = 0;
            while( !is_end(index1+index2) && index1 < m && index2 < n){
                if (nums1[index1] < nums2[index2]){
                    left = (double) nums1[index1];
                    index1++;
                } else {
                    left = (double) nums2[index2];
                    index2++;
                }
            }

            if(is_end(index1+index2)){
                if (index1 == m){
                    return ((double)nums2[index2] + left)/2;
                } else if (index2 == n){
                    return ((double)nums1[index1] + left)/2;
                } else {
                    return nums1[index1] < nums2[index2] ? ((double)nums1[index1] + left)/2 : ((double)nums2[index2] + left)/2;
                }
            } else {
                if(index1 < m ){
                    while (!is_end(index1+index2)){
                        left = nums1[index1];
                        index1++;
                    }
                    return ((double)nums1[index1] + left)/2;
                } else {
                    while( !is_end(index1+index2)){
                        left = nums2[index2];
                        index2++;
                    }
                    return ((double)nums2[index2] + left)/2;
                }
            }
        } 
    }
};

int main(){
    Solution solution1;
}