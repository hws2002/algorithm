#include <iostream>
using namespace std;
int main(){
    unsigned char a = 17;
    short b = -18;
    int c =2;
    unsigned int d = 0;
    cout<< (a+b) * c + d<< endl;
    // we presume that the output would be 4294967294
    // because originally the output should be -2, but as it would be formatted to unsigned int, 
    // its value would be 2^32 -2 = 4294967294
    std::cout << "Max unsigned int: " << std::numeric_limits<unsigned int>::max() << std::endl;
    std::cout << "Max unsigned int: " << std::numeric_limits<unsigned int>::max() +1 -2 << std::endl;
    return 0;
}