#include <iostream>
#define DEBUG_PRE
#define endl '\n'
using namespace std;

int N,M;
int MAP[1025][1025] = {0};
int PrefixSum[1025][1025] = {0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N>>M;

    for(int i = 1 ; i <= N; i++){
        for(int j = 1 ; j <= N; j++){
            cin>>MAP[i][j];
            PrefixSum[i][j] = PrefixSum[i-1][j] + PrefixSum[i][j-1] - PrefixSum[i-1][j-1] + MAP[i][j];
        }
    }

#ifdef DEBUG_PRE

#endif
    //solve
    int x1,y1,x2,y2;
    while(M--){
        cin>>x1>>y1>>x2>>y2;
        cout<<PrefixSum[x2][y2] - PrefixSum[x2][y1-1] - PrefixSum[x1-1][y2] + PrefixSum[x1-1][y1-1]<<endl;
    }

    return 0;
}