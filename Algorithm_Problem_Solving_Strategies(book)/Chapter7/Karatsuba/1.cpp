#include <iostream>
#include <vector>

int main() {
    std::vector<int> a = {1, 2, 3, 4, 5}; // Example vector
    int k = 0; // Number of zeros to add

    // Create a vector with k zeros
    std::vector<int> zeros(k, 0);

    // Insert the zeros at the beginning of vector a
    a.insert(a.begin(), zeros.begin(), zeros.end());

    // Output the modified vector
    std::cout << "Modified vector: ";
    for (int num : a) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
