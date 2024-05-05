#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

int N,M;
bool BUTTONS[10] = {false};

int main(){
    
    cin>>N>>M; int button = 0;
    std::fill(BUTTONS, BUTTONS + 10, true);
    for(int i = 0 ; i < M; i++){
        cin>>button;
        BUTTONS[button] = false;
    }

    int ret = abs(N - 100);

    // up
    string upperN = to_string(N);
    

    // down

    cout<<res<<endl;
    return 0;
}