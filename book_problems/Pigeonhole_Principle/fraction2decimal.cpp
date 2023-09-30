#include <iostream>
using namespace std;

/***
 * @brief print a/b in decimal format
 * @remark a >=0, b>=0 이라고 가정
 * @remark a/b 가 무한 소수인지 아닌지는 pigeonhole principle 을 써서 판단한다.
 * @remark a%b가 취할 수 있는 수는 [0,b), 즉 b가지이다. 그렇다면, 밑의 while문이 b번 이상 반복되면, a/b는 무한소수라고 판단 할 수 있다.
 * @remark a/b가 무한 소수일 경우, ...을 출력한다.
 * @details a/b의 몫의 길이(ex. xxx.yyy에서 xxx의 길이)는 a를 b진법을 나타냈을때의 길이이다.
 * @details 무한(순환) 소수의 경우, 
*/

void printDecimal(int a, int b){
    // to get the length of quotient
    int a_=a, q=0;
    vector<int> quotients;
    int iter = 0;
    while(a>0){
        if(iter >=b){
            printf("a/b is infinite decimal\n a/b :");
            for(int i =0; i < quotients.size(); ++i)
                printf("%d",quotients[i]);
            printf("...");
            return;
        }
        quotients.push_back(a/b);
        q = q*10 + a/b;
        if(q*b + q > a_) quotients.push_back(-1);
        a = (a % b) * 10;
        iter++;
    }
    
    // FINITE decimal
    printf("a/b is finite decimal\n a/b :");
    for(int i=0; i<quotients.size(); ++i){
        if(quotients[i] == -1) printf(".");
        else printf("%d",quotients[i]);
    }
}

int main(){
    printDecimal(1,3);
    printDecimal(1,7);    
    return 0;
}