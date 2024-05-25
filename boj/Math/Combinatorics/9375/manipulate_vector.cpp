#include <iostream>
#include <vector>


using namespace std;

int main(){
	vector<int> v{1,2,3,4,5,6,7,8};
	for(auto item : vector<int>(v.begin(), v.end()-1))
		cout<<item<<endl;

	return 0;
}