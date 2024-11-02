#include <iostream>
#include <tuple>
#include <set>
#include <queue>

using namespace std;

int main(){
	queue< tuple<int,int,int> > Queue_state;
	
	Queue_state.push(make_tuple(1,1,2));
	
	int A,B,C;
	tuple<int,int,int> current_state;
	current_state = Queue_state.front();
	Queue_state.pop();
	tie(A,B,C) = current_state;
	
			cout<<"(A, B, C):("<<A<<","<<B<<","<<C<<")"<<endl;

	return 0;
}