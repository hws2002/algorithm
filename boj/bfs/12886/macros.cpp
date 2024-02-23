#include <iostream>

using namespace std;

#define SORT_ASCENDING(a,b,c) \
	do { \
		if ((a) > (b)) swap((a),(b)); \
		if ((b) > (c)) swap((b),(c)); \
		if ((a) > (b)) swap((a),(b)); \
	} while (false)
	

#define IS_TARGET_STATE(a,b,c) (a == b && b == c)

#define RESET_VALUE(a,b,c,A,B,C) \
	(a) = (A), \
	(b) = (B), \
	(c) = (C)


int main(){
	int A = 101;
	int B = 114;
	int C = 110;
	int a = 1;
	int b = 14;
	int c = 10;
	
	SORT_ASCENDING(a,b,c);
	cout<<"RESULT OF SORT_ASCENDING : "<<a<<" "<<b<<" "<<c<<endl;
	
	RESET_VALUE(a,b,c,A,B,C);
	cout<<"RESULT OF RESET_VALUE: "<<a<<" "<<b<<" "<<c<<endl;
	
	if(IS_TARGET_STATE(a,b,c)){
		cout<<"TARGET STATE achieved!"<<endl;
	} else{
		cout<<"Not a TARGET STATE."<<endl;
	}
	return 0;
}