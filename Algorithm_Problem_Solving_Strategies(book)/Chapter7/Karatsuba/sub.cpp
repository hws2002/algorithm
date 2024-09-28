#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
// #include "karatsuba.h"

#define MAX_LEN 300'000
// #define DEBUG_INPUT
using namespace std;

vector<int> a;
vector<int> b;

void normalize(vector<int> & num){
	num.push_back(0);
	for(int i = 0 ; i+1 < num.size(); i++){
		if(num[i] < 0){
			int borrow = (abs(num[i]) + 9) / 10;
			num[i+1] -= borrow;
			num[i] += borrow*10;
		} else {
			num[i+1] += num[i] / 10;
			num[i] %= 10;
		}
	}
	while(!num.empty() && num.back() == 0) num.pop_back();
}

//a에서 b를 뺸다. assert a > b
void subFrom(vector<int> & a, vector<int> & b){
	for(int i = 0 ; i < b.size(); i++){
		a[i] -= b[i];
	}
	normalize(a);
}


int main(){
	string num1, num2;
	cin>>num1>>num2;
	a.resize(num1.size());
	b.resize(num2.size());
	for(int i = 0; i < num1.size(); i++){
		a[i] = num1[i] - '0';
	}
	reverse(a.begin(), a.end());
	for(int i = 0 ; i < num2.size(); i++){
		b[i] = num2[i] - '0';
	}
	reverse(b.begin(), b.end());

#ifdef DEBUG_INPUT
	for(auto e : a){
		cout<<e<<" ";
	}
	cout<<endl;
	for(auto e : b){
		cout<<e<<" ";
	}
	cout<<endl;
#endif
	
	subFrom(a,b);
	reverse(a.begin(), a.end());
	for(auto e : a){
		cout<<e;
	}
	
	cout<<endl;
	return 0;
}