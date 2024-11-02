#include <iostream>
#include <cstring>

using namespace std;

string compressed;

string reversed(int & p){
	if (compressed[p] != 'x') 
		return string(1, compressed[p++]);
	p++;
	string ul = reversed(p);
	string ur = reversed(p);
	string dl = reversed(p);
	string dr = reversed(p);
	return string("x") + dl + dr + ul + ur;
}

void solve(){
	cin>>compressed;
	int p = 0;
	cout<<reversed(p)<<endl;
}

int main(){
	int C;
	cin>>C;
	while(C--){
		solve();
	}
	return 0;
}