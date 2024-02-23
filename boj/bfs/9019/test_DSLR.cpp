#include <iostream>
using namespace std;

int D(int num){
//operation 0
	num <<= 1;
	num %= 10000;
	return num;
}

int S(int num){
//operation 1
	num -=1;
	num %= 10000;
	if(num < 0) num += 10000;
	return num;
}

int L(int num){
//operation 2
	int leftmost = num / 1000;
	num *= 1e1;
	num += leftmost;
	num %= 10000;
	return num;
}

int R(int num){
//operation 3
	int rightmost = num % 10;
	num /= 10;
	num += (rightmost * 1000);
	return num;
}

int main(){
	int num = 1;
	//D
	cout<<"D : "<<D(num)<<endl;
	//S
		cout<<"S : "<<S(num)<<endl;
	//L
	cout<<"L : "<<L(num)<<endl;
	//R
		cout<<"R : "<<R(num)<<endl;
	return 0;
}