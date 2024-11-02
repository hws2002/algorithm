#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

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
	while(num.size() > 1 && num.back() == 0) num.pop_back();
}

// a와 b를 곱한다
vector<int> bigIntMul(vector<int> & a, vector<int> & b){
	vector<int> res( a.size() + b.size() + 1, 0);
	for(int j = 0 ; j < b.size(); j++){
		for(int i = 0; i < a.size(); i++){
			res[i+j] += a[i] * b[j];
		}
	}
	
	normalize(res);
	return res;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
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
		cout<<e;
	}
	cout<<endl;
	for(auto e : b){
		cout<<e;
	}
	cout<<endl;
#endif
	
	auto res = bigIntMul(a,b);
	reverse(res.begin(), res.end());
	for(auto e : res){
		cout<<e;
	}
	
	cout<<endl;
	return 0;
}