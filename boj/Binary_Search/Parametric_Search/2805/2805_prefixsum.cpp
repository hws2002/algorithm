// 구간합

#include <iostream>
#include <vector>
#include <algorithm>
#define endl '\n'
// #define DEBUG_INPUT
typedef long long ll;
using namespace std;

ll N;
ll M;
vector<ll> trees;
vector<ll> prevsum;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
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
	ll lo = 0;
	ll hi = trees.size();
	ll mid = 0;
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
		    if(lo == mid) break;
			lo = mid;
		} else {//taken < M
			hi = mid;
		}
	}
	
	if(lo == hi && hi == 0){
	    h = 0;
	    while(prevsum.back() - 0 - (h+1) * N >= M){
	        h++;
	    }
	} else {
    	// now lengthen h till we get taken == M
    	while(prevsum.back() - prevsum[mid+1] - (h+1) * (N - mid - 1) >= M){
    		h++;
    	}
	}
	
	cout<<h<<endl;
	return 0;
}