#include <iostream>
#include <vector>
using namespace std;

int main(){
	vector<int> v {0,1,2,3,4,5,6,7,8,9};
	cout<<v.size()<<endl;
	v.erase(v.begin() + 1);
	cout<<v.size()<<endl;
	for(auto num : v){
		cout<<num<<" ";
	}
	return 0;
}