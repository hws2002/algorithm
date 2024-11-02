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

// a에 b를 더한다
void addTo(vector<int> & a, vector<int> & b){
	int carry = 0;
	int len = max(a.size(),b.size()) + 1;
	a.resize(len,0); b.resize(len,0);
	int temp;
	for(int i = 0 ; i < len; i++){
		temp = a[i];
		a[i] = (a[i] + b[i] + carry) % 10;
		carry = (temp + b[i] + carry) / 10;
	}
	
	while(!a.empty() && a.back() == 0) a.pop_back();
}

//a에서 b를 뺸다. assert a > b
void subFrom(vector<int> & a, vector<int> & b){
	for(int i = 0 ; i < b.size(); i++){
		a[i] -= b[i];
	}
	normalize(a);
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

// a에 10^k를 곱한다 assert k>=0
void mul10(vector<int> & a, int k){
	vector<int> zeros(k,0);
	a.insert(a.begin(), zeros.begin(), zeros.end());
}

vector<int> karatsuba(vector<int> & a, vector<int> & b){
	if( a.empty() || b.empty()) return vector<int> ();
	if( a.size() < b.size()) return karatsuba(b,a);
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
for(auto e : a){
	cout<<e;
}
cout<<" ";
for(auto e : b){
	cout<<e;
}
cout<<endl;
		reverse(a.begin(),a.end());
		reverse(b.begin(),b.end());
	if( a.size() <= 5) return bigIntMul(a,b);

	int half = a.size() / 2;
	vector<int> a1(a.begin(), a.begin() + half);
	vector<int> a2(a.begin() + half, a.end());
	vector<int> b1(b.begin(), b.begin() + min<int>(b.size(), half) );
	vector<int> b2(b.begin() + min<int>(b.size(), half), b.end());
	// if ( b.size() > half){		
		// b2 = vector<int>(b.begin() + half, b.end());
	// }
	
	// a1*b1
	cout<<"calling karatsuba(a1,b1)"<<endl;
	vector<int> a1_b1 = karatsuba(a1,b1);
	
	// a2*b2
	cout<<"calling karatsuba(a2,b2)"<<endl;
	vector<int> a2_b2 = karatsuba(a2,b2);

	// mid = (a1 + a2) * (b1 + b2) - a1*b1 - a2*b2
	addTo(a1,a2); addTo(b1,b2);
	vector<int> mid = karatsuba(a1,b1);
	subFrom(mid,a1_b1);
	subFrom(mid,a2_b2);
	// a1*b1 * 10^{2*half} + mid * 10^{half} + a2*b2
	mul10(a1_b1, 2*half);
reverse(a1_b1.begin(), a1_b1.end());
for(auto e :a1_b1){
	cout<<e;
}
cout<<endl;
	
reverse(a1_b1.begin(), a1_b1.end());
	
	mul10(mid,half);
reverse(mid.begin(), mid.end());
for(auto e :mid){
	cout<<e;
}
cout<<endl;
reverse(mid.begin(), mid.end());
	
	addTo(a1_b1,mid);
	addTo(a1_b1,a2_b2);
cout<<"half : "<<half<<endl;

reverse(a1_b1.begin(), a1_b1.end());
for(auto e :a1_b1){
	cout<<e;
}
cout<<endl;
reverse(a1_b1.begin(), a1_b1.end());
	return a1_b1;
};

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
	
	auto res = karatsuba(a,b);
	if(res.empty()) {
		cout<<0<<endl;
		return 0;
	}
	
	reverse(res.begin(), res.end());
	for(auto e : res){
		cout<<e;
	}
	
	cout<<endl;
	return 0;
}