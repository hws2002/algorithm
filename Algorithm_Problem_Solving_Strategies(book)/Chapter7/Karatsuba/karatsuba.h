#ifndef KARATSUBA_H
#define KARATSUBA_H

using namespace std;

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
	
	while(!a.empty() && a.back() == 0){
		a.pop_back();
	}
}

//a에서 b를 뺸다. assert a > b
void subFrom(vector<int> & a, vector<int> & b){
	int carrry = 0;
	
	int temp;
	for(int i = 0; i < b.size(); i++){
		if( a[i] - b[i] < 0){
			a[i+1] = (a[i+1] - 1 + 10) % 10;
			a[i] = 10 + a[i] - b[i];
		} else {
			a[i] = a[i] - b[i];
		}
	}
	
	while(!a.empty() && a.back() == 0){
		a.pop_back();
	}
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
#endif