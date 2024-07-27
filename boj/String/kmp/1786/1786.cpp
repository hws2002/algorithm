#include <iostream>
#include <vector>

#define endl '\n'
#define MAX_N 1'000'005
// #define DEBUG_LENGTH
// #define DEBUG_PI
using namespace std;

vector<int> res;

void getPartialMatch(char P[], int pi[], int m){
    int begin = 1;
    int matched= 0;
    while(begin + matched < m){
        if(P[begin + matched] == P[matched]){
            matched++;
            pi[begin+matched-1] = matched;
        } else {
            if( matched == 0){
                begin++;
            } else {
                begin += matched - pi[matched-1];
                matched = pi[matched - 1];
            }
        }
    }
}

void kmp(char H[], char P[]){
    //get length
    int n = 0; int m = 0;
    while( H[n] != '\n') n++;
    while( P[m] != '\n') m++;
#ifdef DEBUG_LENGTH
for(int i = 0 ; i < n; i++){
    cout<<H[i];
}
cout<<endl;
for(int i = 0 ; i < m; i++){
    cout<<P[i];
}
cout<<endl;
#endif
    // create pi
    int pi[MAX_N] = {0};
    getPartialMatch(P, pi, m);
#ifdef DEBUG_PI
for(int i = 0; i < m; i++){
    cout<<pi[i]<<" ";
}
cout<<endl;
#endif
    //run kmp
    int begin = 0;
    int matched = 0;
    while( begin <= n - m){
        if( H[begin + matched] == P[matched]){
            matched++;
            if( matched == m) res.push_back(begin);
        } else {
            if(matched == 0)
                begin++;
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
}

int main(){
    char T[MAX_N];
    char P[MAX_N];
    fgets(T, MAX_N, stdin);
    fgets(P, MAX_N, stdin);
    kmp(T,P);
    cout<<res.size()<<endl;
    for(auto r : res){
        cout<<r+1<<" ";
    }
    return 0;
}