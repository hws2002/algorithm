#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    static int countOverlappingPattern(
        const string& colors,
        const string& pattern
    ){
        int count = 0;
        for (size_t i = 0; i <= colors.size() - pattern.size(); i++) {
            if (colors.substr(i, pattern.size()) == pattern) {
                count++;
            }
        }
        return count;
    };

    static bool winnerOfGame(string colors) {
        if(colors.size() <= 2) return false;
        string A_pattern = "AAA";
        string B_pattern = "BBB";
        int A_count = countOverlappingPattern(colors,A_pattern);
        int B_count = countOverlappingPattern(colors,B_pattern);
        return A_count > B_count ? true : false;
    };
};


int main() {
    string colors ="AA";
    string output = Solution::winnerOfGame(colors) ? "true" : "false";
    printf("Output : %s", output.c_str());
    return 0;
}