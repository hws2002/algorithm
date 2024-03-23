#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

// #define DEBUG_INPUT
// #define DEBUG_SS
// #define DEBUG_CAL

#define endl '\n'
typedef long long ll;
using namespace std;

int digits[10] = {0};
int main(){
    string N;
    cin>>N;
    int inspector = 0; int num; 
    char temp;
    stringstream ss(N);
    while(ss >> temp){
        num = temp - '0';
#ifdef DEBUG_INPUT
cout<<num<<" ";
#endif
        inspector = (inspector + num) % 3;
        digits[temp-'0'] +=1;
	}
#ifdef DEBUG_INPUT
	cout<<endl;
#endif
    if(inspector || digits[0] <= 0){
        cout<<-1<<endl;
        return 0;
    }
#ifdef DEBUG_SS
	for(int i = 9; i>=0; i--){
		cout<<i<<":"<<digits[i]<<endl;
	}
#endif
    string res;
	int count;
    for(int i = 9; i >= 0; i--){
		count = 0;
		while(digits[i] > count++){
	        res += (i + '0');		
#ifdef DEBUG_CAL
cout<<"res : " <<res<<endl;
#endif
		}
    }
	//output
	cout<<res<<endl;
    return 0;
}