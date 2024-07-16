#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

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
        inspector = (inspector + num) % 3;
        digits[temp-'0'] +=1;
	}

    if(inspector || digits[0] <= 0){
        cout<<-1<<endl;
        return 0;
    }
    string res;
	int count;
    for(int i = 9; i >= 0; i--){
		count = 0;
		while(digits[i] > count++){
	        res += (i + '0');		
		}
    }
	//output
	cout<<res<<endl;
    return 0;
}