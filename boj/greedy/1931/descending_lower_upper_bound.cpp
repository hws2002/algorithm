#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>

using namespace std;

int main()
{
    vector<int> vec = {45,40,40,35,12,6,3};

    auto itr3 = lower_bound(vec.begin(),vec.end(),40,std::greater<int>());
    auto itr4 = upper_bound(vec.begin(),vec.end(),40,std::greater<int>());

    if(itr3 == vec.end() && itr4 == vec.end())
        cout<<"Lower & Upper Bound not Found\n";
    else
    {
        cout <<"lower Bound of 40 :"<<*itr3<<endl;
        cout <<"Upper Bound of 40 :"<<*itr4<<endl;
		cout <<"distance(begin, iter3) :"<<distance(vec.begin(), itr3)<<endl;
    }
	
	auto iter5 = upper_bound(vec.begin(), vec.end(), 45, std::greater<int>());
	cout<<*iter5<<endl;
	
	if(iter5 == vec.begin()){
		cout<<"iter5 == vec.begin()"<<endl;
	}
	if(iter5 == vec.end()){
		cout<<"iter5 == vec.end()"<<endl;
	}
    return 0;
}