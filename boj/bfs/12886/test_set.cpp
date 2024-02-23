#include <iostream>
#include <tuple>
#include <set>
#include <queue>

using namespace std;

int main(){
	queue< tuple<int,int,int> > Queue_state;
	
	Queue_state.push(make_tuple(1,1,2));
	set< tuple<int,int,int> > Set_State;

	int A,B,C;
	tuple<int,int,int> current_state;
	current_state = Queue_state.front();
	Queue_state.pop();
	tie(A,B,C) = current_state;
	cout<<"(A, B, C):("<<A<<","<<B<<","<<C<<")"<<endl;

	
	Set_State.insert(make_tuple(1,1,2));
	
	int a = 1;
	int b = 1;
	int c = 2;
	if(Set_State.find(tie(a,b,c))!= Set_State.end()){
		cout<<"tuple already exists";
	} else{
		cout<<"haha!"<<endl;
	}
	
	return 0;
}