#include <iostream>
#include <cstring>
#include <stack>

using namespace std;

string s;
void solve(){
	cin>>s;
	stack<char> st;
	for(int i = 0 ; i < s.size(); i++){
		if( s[i] == '(' || s[i] == '{' || s[i] == '[')
			st.push(s[i]);
		else {
			
		}
	}
}

int main(){
	int c; cin>>c; while(c--) solve();
	return 0;
}