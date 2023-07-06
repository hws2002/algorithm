#include <iostream>
#include <string>
#include <algorithm>

std::string format_with_thousand_commas(unsigned int num) {
    std::string str = std::to_string(num);
    int n = str.length() - 3;
    while (n > 0) {
        str.insert(n, ",");
        n -= 3;
    }
    return str;
}
