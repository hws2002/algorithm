#include <iostream>
#include <vector>
#include <bitset>

// #define DEBUG_SCAN
#define MAX_N 200'000

using namespace std;

int maxLengthEqual[MAX_N] = {0};
int maxLength[MAX_N] = {0};
int Set[MAX_N] = {0};

int res = 1;
int N; // 1 <= N <= 200'000
vector<int> S;

// bool inSet(const int val, const int set){
//     return ( set & (1<<val) );
// }

void scan(const int idx){
    
    //if S[idx] in Set[idx+1]
    //update maxLength and Set
    if( Set[idx+1] & (1<<S[idx]) ){
        maxLength[idx] = 1 + maxLength[idx+1];
        Set[idx] = Set[idx + 1];
    } else { 
        maxLength[idx] = 1 + maxLengthEqual[idx+1];
        Set[idx] = (1<<S[idx]) + (1<<S[idx+1]);
    }
    
    // update maxLengthEqual
    if( S[idx] == S[idx+1]) {
        maxLengthEqual[idx] = maxLengthEqual[idx+1] + 1;
    } else {
        maxLengthEqual[idx] = 1;
    }
    res = max(res, maxLength[idx]);
    return ;
}



int main(){
    cin>>N;
    int Si;
    for(int i = 0; i < N; i++){
        cin>>Si;
        S.push_back(Si);
    }
    
    //solve - dp
    maxLength[N-1] = 1;
    Set[N-1] = 1<<(S.back());
    maxLengthEqual[N-1] = 1;
    
    for(int i = N-2; i>=0; i--){
        scan(i);
#ifdef DEBUG_SCAN
cout<<"printing out maxLengthEqual : ";
for(int j = N-1; j >= i ; j--){
	cout<<maxLengthEqual[j]<<" ";
}
cout<<endl;
cout<<"printing out maxLength : ";
for(int j = N-1; j >= i ; j--){
	cout<<maxLength[j]<<" ";
}	
cout<<endl;
cout<<"printing out Set : ";
for(int j = N-1; j >= i ; j--){
	bitset<10> x(Set[j]);
	cout<<x<<" ";
}
		cout<<endl;
#endif
	}
    
    cout<<res<<endl;
    return 0;
}