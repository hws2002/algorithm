#include <iostream>
#include <map>
#include <cstring>
#include <vector>

using namespace std;

int n;

int comb(vector<int> v){
	if(v.empty()) return 0;
	if(v.size()==1) return v.back();
	return v.back() + (v.back() + 1) * comb( vector<int>(v.begin(), v.end()-1) );
}

void solve(){
	map<string, int> m;
	vector<int> v;
	cin>>n;
	string name, cate;
	for(int i = 0; i < n; i++){
		cin>>name>>cate;
		m[cate]+=1;
	}
	
	for(const auto & pair : m){
		v.push_back(pair.second);
	}
	cout<<comb(v)<<endl;
}

int main(){
	int T;
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}