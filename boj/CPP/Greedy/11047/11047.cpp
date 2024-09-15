#include <iostream>
#include <vector>

#define INF 20
using namespace std;

int N,K;


int main(){
	cin>>N>>K;
	vector<int> A;
	int temp;
	for(int i = 0 ; i < N; i++){
		cin>>temp;
		A.push_back(temp);
	}
	
	//solve - binary search
	int remaining = K;
	int num = 0;
	vector<int>::iterator lb_iter = A.end();
	while(remaining){
		lb_iter = lower_bound(A.begin(), lb_iter, remaining);
		if(lb_iter == A.end() || *lb_iter > remaining){
			int upper_min = *(lb_iter-1);
			int to_add = remaining / upper_min;
			num += to_add;
			remaining -= upper_min * to_add;
		} else if(*lb_iter == remaining) {
			num += remaining / (*lb_iter) ;
			remaining -= (*lb_iter);
		} else{
			cout<<"sth went wrong!"<<endl;
			break;
		}
	}
	//output
	cout<<num<<endl;
	return 0;
}
