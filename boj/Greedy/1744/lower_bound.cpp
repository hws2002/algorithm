#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {-5, -3, -2, -1};

    auto lower = std::lower_bound(vec.begin(), vec.end(), 0);

    if (lower == vec.end()) {
        std::cout << "Element not found." << std::endl;
    } else {
        std::cout << "Lower bound of 0 is at index: " << (lower - vec.begin()) << std::endl;
    }

    return 0;
}
