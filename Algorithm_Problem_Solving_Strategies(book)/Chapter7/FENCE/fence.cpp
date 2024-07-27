//divide and conquer

#include <iostream>
#include <vector>

#define MAX_N 20000
using namespace std;

int N;
vector<int> Fence(MAX_N);

// dnq(left, right) : Fence의 [left right] 판자들만 고려했을때, 잘라낼 수 있는 최대 직사각형의 크기를 반환한다.
int dnq(const int left, const int right){
	//base
	if(right <= left) return Fence[left];

	int half = (right + left) >> 1;
	int ret =  max( dnq(left, half), dnq(half+1,right) );
	int width = 2; int height = min(Fence[half], Fence[half+1]);
	int midMax = width * height;
	int l = half; int r = half+1;
	while(true){
		if( l <= left && r >= right) break;
		if( r < right && (l == left || Fence[r+1] > Fence[l-1])){
			height = min(height, Fence[r+1]);
			r++;
		} else if ( l > left && (r == right || Fence[l-1] >= Fence[r+1])){
			height = min(height, Fence[l-1]);
			l--;
		}
		midMax = max(midMax, ++width * height);
	}
	
	return max(ret, midMax);
}

void solve(){
	cin>>N;
	for(int i = 0; i < N; i++){
		cin>>Fence[i];
	}
	
	//dnq
	cout<<dnq(0,N-1)<<endl;
}

int main(){
	int C;
	cin>>C;
	while(C--){
		solve();
	}
	return 0;
}