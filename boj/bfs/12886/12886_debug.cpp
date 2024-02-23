#include <iostream>
#include <queue>
#include <tuple>
#include <set>
#include <algorithm>

using namespace std;

// #define DEBUG_TUPLE
// #define DEBUG_SET
// #define DEBUG_QUEUE


#ifdef DEBUG_SET
	void printSet(const std::set<std::tuple<int, int, int>>& Set) {
		std::cout << "Set elements: ";
		for(const auto& tuple : Set) {
			std::cout << "(" << std::get<0>(tuple) << ", " << std::get<1>(tuple) << ", " << std::get<2>(tuple) << ") ";
		}
		std::cout << std::endl;
	}
#endif

#ifdef DEBUG_QUEUE
	void printQueue(queue< tuple<int,int,int> > Queue){
		cout<<"Queue : ";
		tuple<int,int,int> state;
		while(!Queue.empty()){
			state = Queue.front();
			std::cout << "(" << std::get<0>(state) << ", " << std::get<1>(state) << ", " << std::get<2>(state) << ") ";
			Queue.pop();
		}
		cout<<endl;
	}
#endif

#define SORT_ASCENDING(a,b,c) \
	do { \
		if ((a) > (b)) swap((a),(b)); \
		if ((b) > (c)) swap((b),(c)); \
		if ((a) > (b)) swap((a),(b)); \
	} while (false)
	

#define IS_TARGET_STATE(a,b,c) (a == b && b == c)

#define RESET_VALUE(a,b,c,A,B,C) \
	(a) = (A), \
	(b) = (B), \
	(c) = (C)

/*
maintain order of element in single state as a ascending order!
*/

int main(int argc, char * argv[]){
	//input
	int A,B,C;
	cin>>A>>B>>C;
	if(A==B && B==C) {
		cout<<1<<endl;
		return 0;
	}
	set< tuple<int,int,int> > Set_State;
	queue< tuple<int,int,int> > Queue_State;
	
	SORT_ASCENDING(A,B,C);
	
	Queue_State.push(make_tuple(A,B,C));
	Set_State.insert(make_tuple(A,B,C));
	
	tuple<int,int,int> current_state;
	int a,b,c;
	// int count  = 0;
	while(!Queue_State.empty()){
		#ifdef DEBUG_SET
			printSet(Set_State);
		#endif
		#ifdef DEBUG_QUEUE
			printQueue(Queue_State);
		#endif
		// count++; if(count >= 10) break;
		current_state = Queue_State.front();
		Queue_State.pop();
		A = get<0>(current_state);
		B = get<1>(current_state);
		C = get<2>(current_state);
		
		// #ifdef DEBUG_QUEUE
		// 	cout<<"After pop, ";
		// 	printQueue(Queue_State);
		// #endif
		#ifdef DEBUG_TUPLE
			cout<<"(A, B, C):("<<A<<","<<B<<","<<C<<")"<<endl;
		#endif
		RESET_VALUE(a,b,c,A,B,C);
	//a <-> b
		if(a > b){
			a -=b;
			b *=2;
			if(IS_TARGET_STATE(a,b,c)){
				cout<<1<<endl;
				return 0;
			}
			SORT_ASCENDING(a,b,c);
			if(Set_State.find(make_tuple(a,b,c)) == Set_State.end()){
				Queue_State.push(make_tuple(a,b,c));
				Set_State.insert(make_tuple(a,b,c));
			}
		} else if( a < b){
			b -=a;
			a *=2;
			if(IS_TARGET_STATE(a,b,c)){
				cout<<1<<endl;

				return 0;
			}
			SORT_ASCENDING(a,b,c);
			if(Set_State.find(make_tuple(a,b,c)) == Set_State.end()){
				Queue_State.push(make_tuple(a,b,c));
				Set_State.insert(make_tuple(a,b,c));
			}
		} else {}
		RESET_VALUE(a,b,c,A,B,C);
	// a<->c
		if(a > c){
			a -=c;
			c *=2;
			if(IS_TARGET_STATE(a,b,c)){
				cout<<1<<endl;

				return 0;
			}
			SORT_ASCENDING(a,b,c);
			if(Set_State.find(make_tuple(a,b,c)) == Set_State.end()){
				Queue_State.push(make_tuple(a,b,c));
				Set_State.insert(make_tuple(a,b,c));
			}
		} else if( a < c){
			c -=a;
			a *=2;
			if(IS_TARGET_STATE(a,b,c)){
				cout<<1<<endl;

				return 0;
			}
			SORT_ASCENDING(a,b,c);
			if(Set_State.find(make_tuple(a,b,c)) == Set_State.end()){
				Queue_State.push(make_tuple(a,b,c));
				Set_State.insert(make_tuple(a,b,c));
			}
		} else {}
		RESET_VALUE(a,b,c,A,B,C);
	// b<->c
		if(c > b){
			c -=b;
			b *=2;
			if(IS_TARGET_STATE(a,b,c)){
				cout<<1<<endl;
				return 0;
			}
			SORT_ASCENDING(a,b,c);
			if(Set_State.find(make_tuple(a,b,c)) == Set_State.end()){
				Queue_State.push(make_tuple(a,b,c));
				Set_State.insert(make_tuple(a,b,c));
			}
		} else if( c < b){
			b -=c;
			c *=2;
			if(IS_TARGET_STATE(a,b,c)){
				cout<<1<<endl;
				return 0;
			}
			SORT_ASCENDING(a,b,c);
			if(Set_State.find(make_tuple(a,b,c)) == Set_State.end()){
				Queue_State.push(make_tuple(a,b,c));
				Set_State.insert(make_tuple(a,b,c));
			}
		} else {}
	}
	
	//failed to find a route to target_state
	cout<<0<<endl;
	return 0;
}