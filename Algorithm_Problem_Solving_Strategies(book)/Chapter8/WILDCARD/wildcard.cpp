#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

string file_name;
string W;

bool match(int i, int j){
	while(i < W.size() && j < file_name.size() && W[i] == file_name[j]){
		i++; j++;
	}
	
	if( i >= W.size() ){ // W의 끝에 다다랐다면
		return j>=file_name.size();
	}
	
	if( W[i] == '?'){ // W의 끝이 ?라면
		if( j >= file_name.size()) return false;
		return match(i+1, j);
	}
	
	// if (W[i] == '*'){ // W의 끝이 *라면
		
	// }
	return match(i,j+1) || match(i+1,j);
}

void solve(){
	cin>>W;
	int N;
	cin>>N;
	vector<string> res;
	while(N--){
		cin>>file_name;
		if(match(0,0)) res.push_back(file_name);
	}
	sort(res.begin(), res.end());
	for(auto e : res){
		cout<<e<<endl;
	}
}

int main(){
	int C;
	cin>>C;
	while(C--){
		solve();
	}
	return 0;
}