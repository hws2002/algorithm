// 가장 긴 바이토닉 수열까지 출력하기
#include <iostream>
#include <algorithm>

using namespace std;

int N;
int A[1002] = {0};
int choice[1002] = {0};
int cache[1002][2] = {0};

typedef enum{
	GOINGUP,
	GOINGDOWN
} State;

int bitonic1(const int here, const State state){
	
	int& ret = cache[here][state];
	if(ret) return ret;
	ret = 1;
	if(state == GOINGUP){
		int& ret2 = cache[here][GOINGDOWN];
		ret2 = 1;
		int choice2 = -1;
		
		for(int next = here + 1; next <= N; next++){
			if(here == 0 || A[here] < A[next]){
				if( ret < bitonic1(next, state) + 1 ){
					ret = bitonic1(next, state) + 1;
					choice[here] = next;
				}
			}
			
			if(here == 0 || A[here] > A[next]){
				if( ret2 < bitonic1(next, GOINGDOWN) + 1){
					ret2 = bitonic1(next, GOINGDOWN) + 1;
					choice2 = next;
				}
			}
			
		}
		
		if( ret < ret2){
			ret = ret2;
			choice[here] = choice2;
		}
	} else {
		for(int next = here + 1; next <= N; next++){
			if(here == 0 || A[here] > A[next]){
				if( ret < bitonic1(next, state) + 1){
					ret = bitonic1(next, state) + 1;
					choice[here] = next;
				}
			}
		}
	}
	
	return ret;
}

int main(){
	cin>>N;
	std::fill(choice, choice + N, -1);
	
	for(int i = 1; i <= N; i++){
		cin>>A[i];
	}
	
	int res = bitonic1(0,GOINGUP)-1;
	cout<<res<<endl;

	cout<<"choice : ";
for(int i = 0; i < N; i++){
	cout<<choice[i]<<" ";
}
cout<<endl;
	
	//reconstruct
	int i = 0;
	while(res--){
		cout<<A[choice[i]]<<" ";
		i = choice[i];
	}
	
	cout<<endl;
	return 0;
}