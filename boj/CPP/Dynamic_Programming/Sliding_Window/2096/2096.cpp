// 슬라이딩 윈도우 
/*
maxScore = max(
    prevP0 + p0 + dp(r,0) ,
    prevP1 + p1 + dp(r,1) ,
    prevP2 + p2 + dp(r,2) ,
) 
----- intput new p's -----

*/
#include <iostream>
#include <limits.h>

using namespace std;

int maxScore = 0;
int minScore = INT_MAX;
int N;

int main(){
    cin>>N;
    int maxPrevP0 = 0; int maxPrevP1 = 0; int maxPrevP2 = 0;
    int minPrevP0 = 0; int minPrevP1 = 0; int minPrevP2 = 0;
    int p0 = 0; int p1 = 0; int p2 = 0;
    int temp0, temp1, temp2;
    for(int i = 1; i <= N; i++){
        cin>>p0>>p1>>p2;
        maxScore = max( maxPrevP0 + p0 , max( maxPrevP1 + p1, maxPrevP2 + p2));
        minScore = min( minPrevP0 + p0 , min( minPrevP1 + p1, minPrevP2 + p2));
        
        temp0 = maxPrevP0; temp1 = maxPrevP1; temp2 = maxPrevP2;
        maxPrevP0 = max(temp0 + p0, temp1 + p1);
        maxPrevP1 = max(temp0 + p0, max( temp1 + p1, temp2 + p2) );
        maxPrevP2 = max(temp1 + p1, temp2 + p2);
        
        temp0 = minPrevP0; temp1 = minPrevP1; temp2 = minPrevP2;
        minPrevP0 = min(temp0 + p0, temp1 + p1);
        minPrevP1 = min(temp0 + p0, min( temp1 + p1, temp2 + p2) );
        minPrevP2 = min(temp1 + p1, temp2 + p2);
    }
    
    cout<<maxScore<<" "<<minScore<<endl;
    return 0;
}
