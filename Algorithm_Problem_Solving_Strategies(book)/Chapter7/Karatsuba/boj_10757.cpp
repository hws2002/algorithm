#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

#define MAX_LEN 300'000
// #define DEBUG_INPUT
using namespace std;

vector<int> a;
vector<int> b;

vector<int> addTo(vector<int> & a, vector<int> & b){
	int len = max(a.size(),b.size()) + 1;
	vector<int> res(len, 0);
	int carry = 0;
	a.resize(len,0); b.resize(len,0);
	for(int i = 0 ; i < res.size(); i++){
		res[i] = (a[i] + b[i] + carry) % 10;
		carry = (a[i] + b[i] + carry) / 10;
	}
	
	while(!res.empty() && res.back() == 0){
		res.pop_back();
	}
	
	return res;
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
	
	auto res = addTo(a,b);
	reverse(res.begin(), res.end());
	for(auto e : res){
		cout<<e;
	}
	
	cout<<endl;
	return 0;
}