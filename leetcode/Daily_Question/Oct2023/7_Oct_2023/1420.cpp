#include <iostream>
using namespace std;

static const long long MOD = 1000000007;
int my_map[51][101][51] = {0};
class Solution {
public:


    static long long mod_pow(long long a, long long b, long long MOD) {
        long long result = 1;
        while (b > 0) {
            if (b & 1) {
                result = (result * a) % MOD;
            }
            a = (a * a) % MOD;
            b >>= 1;
        }
        return result;
    }


    static int numOfArrays(int n, int m, int k) {
        if ( k > m || k == 0) return 0;
        if (n ==1 && k ==1 ) return m;
        if (k==1) {
            long long res = 0; 
            for(int i = 1; i <= m; i++){
                res = (res + mod_pow(i, n-1, MOD)) % MOD;
            }
            // int index = 100000 * n + 100 * m  + k;
            my_map[n][m][k] = (int)(res % MOD);
            return my_map[n][m][k];
        }
        long long res = 0;
        for(int i = k; i <= m; i++){
            for(int j = k-1; j <=n-1; j++){
                // int index = 100000 * j + 100 * (i-1) + k-1;
                res += 
                    my_map[j][i-1][k-1] ? 
                    (my_map[j][i-1][k-1] * (mod_pow(i, n-j-1,MOD))) % MOD 
                    : ((static_cast<long long>(numOfArrays(j, i-1, k-1))) * (mod_pow(i, n-j-1,MOD))) % MOD;
            }
        }
        // int index = 100000 * n + 100 * m  + k;
        my_map[n][m][k] = (int) (res%MOD);
        return my_map[n][m][k];
    }
};

int main(){
    int n = 50;
    int m = 100;
    int k = 25;
    int res = Solution::numOfArrays(n,m,k);
    printf("Output : %d", res);
    return 0;
}