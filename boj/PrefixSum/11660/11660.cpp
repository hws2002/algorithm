#include <iostream>

using namespace std;

int N,M;
int MAP[1024][1024] = {0};
int PrefixSum[1024][1024] = {0};

int main(){
    cin>>N>>M;
    cin>>MAP[0][0];
    PrefixSum[0][0] = MAP[0][0];
    
    // initial row
    for(int j = 1; j < N; j++){
        cin>>MAP[0][j];
        PrefixSum[0][j] = PrefixSum[0][j-1] + MAP[0][j];
    }

    //initial column
    for(int i = 1; i < N; i++){
        cin>>MAP[i][0];
        PrefixSum[i][0] = PrefixSum[i-1][0] + MAP[i][0];
    }

    for(int i = 1 ; i < N; i++){
        for(int j = 1 ; j < N; j++){
            cin>>MAP[i][j];
            PrefixSum[i][j] = PrefixSum[i-1][j] + PrefixSum[i][j-1] - PrefixSum[i-1][j-1] + MAP[i][j];
        }
    }

    //solve
    int x1,y1,x2,y2;
    while(M--){
        cin>>x1>>y1>>x2>>y2;
        cout<<PrefixSum[x2-1][y2-1] - PrefixSum[x2-1][y1-2] - PrefixSum[x1-2][y2-1] + PrefixSum[x1-2][y1-2]<<endl;
    }

    return 0;
}