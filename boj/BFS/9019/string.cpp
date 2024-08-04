#include <iostream>
#include <string>
#include <algorithm>


using namespace std;

char num2char(int num){
	if(num == 0)
		return 'D';
	else if (num == 1)
		return 'S';
	else if (num==2)
		return 'L';
	else 
		return 'R';
}

int main(int argc, char * argv []){
	string res;
	res +='A';
	cout<<res<<endl;
	
	res+=num2char(2);

	std::reverse(res.begin(), res.end());
	
	cout<<res<<endl;
	return 0;
}