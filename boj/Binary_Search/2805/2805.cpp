// 구간합

#include <iostream>
#include <vector>
#include <algorithm>
// #define DEBUG_INPUT
typedef long long ll;
using namespace std;

int N,M;
vector<ll> trees;
vector<ll> prevsum;

int main(){
	cin>>N>>M;
	int temp;
	for(int i = 0; i < N; i++){
		cin>>temp;
		trees.push_back(temp);
	}
	
	//sort
	std::sort(trees.begin(), trees.end());
	prevsum = vector<ll> (N+1);
	prevsum[0] = 0;
	prevsum[1] = trees[0];
	for(int i = 1 ; i < trees.size(); i++)
		prevsum[i+1] = trees[i] + prevsum[i];
	
#ifdef DEBUG_INPUT
cout<<"print out trees: ";
for(auto item : trees){
	cout<<item<<" ";
}
cout<<endl<<"print out prevsum: ";
for(auto item : prevsum){
	cout<<item<<" ";
}
cout<<endl;
#endif
	//solve - parametric search
	int lo = 0;
	int hi = trees.size();
	int mid = 0;
	ll h = 0;
	
	// get largest lower bound of h as long as we can get at this step
	// * definition of lower bound follows that of among mathmetics
	ll taken = 0;
	while(lo < hi){
		mid = (lo + hi)>>1;
		h = trees[mid];
		taken = prevsum.back() - prevsum[mid+1] - h * (N - mid - 1);
		if( taken == M ){
			break;
		} else if (taken > M){
			lo = mid + 1;
		} else {//taken < M
			hi = mid;
		}
	}
	
	// now lengthen h as we get taken == M
	while(taken > M){
		h++;
		taken = prevsum.back() - prevsum[mid+1] - h * (N - mid - 1);
	}
	
	cout<<h<<endl;
	return 0;
}