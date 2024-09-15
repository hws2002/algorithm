#include <iostream>
#include <algorithm>
#include <queue>
#include <set>

// #define DEBUG_QUEUE
// #define DEBUG_VISIT
using namespace std;
#ifdef DEBUG_QUEUE
void printQueue(queue< set<int> > Queue){
	int A,B,C;
	set<int> current_state;
	cout<<"Current Queue: ";
	while(!Queue.empty()){
		current_state = Queue.front();
		Queue.pop();
		auto it = current_state.begin();
		A = *it++;
		B = *it++;
		C = *it;
		cout<<"("<<A<<","<<B<<","<<C<<")"<<" ";
	}
	cout<<endl;
}
#endif

#ifdef DEBUG_VISIT
void printSet(std::set<std::set<int>> Set) {
    std::cout << "Current VISITED: ";
    for (const auto& item : Set) {
        std::cout << "(";
        for (int value : item) {
            std::cout << value << ",";
        }
        std::cout << ")";
    }
    std::cout << std::endl;
}
#endif

int main(){
	//input
	
	int A;
	int B;
	int C;
	cin>>A>>B>>C;
	std::set< set<int> > Set_States;
	queue< set<int> > Queue_States;
	
	Set_States.insert({A,B,C});
	Queue_States.push({A,B,C});
	int a, b, c;
	while(!Queue_States.empty()){
		#ifdef DEBUG_QUEUE
			printQueue(Queue_States);
		#endif
		#ifdef DEBUG_VISIT
			printSet(Set_States);
		#endif
		set<int> current_state = Queue_States.front();
		Queue_States.pop();
		auto it = current_state.begin();
		A = *it++;
		B = *it++;
		C = *it;
		a = A; b = B; c = C;

		#ifdef DEBUG_QUEUE
			cout<<"A,B,C : "<<a<<" "<<b<<" "<<c<<endl;
		#endif
		if( a > b ){
			a -= b;
			b *= 2;
			if(a==b && b==c){
				cout<<1;
				return 0;
			}
			if(Set_States.find({a,b,c}) == Set_States.end()){
				Queue_States.push({a,b,c});
				Set_States.insert({a,b,c});
			}
		} else if (a < b){
			b -= a;
			a *= 2;
			if(a==b && b==c){
				cout<<1;
				return 0;
			}
			if(Set_States.find({a,b,c}) == Set_States.end()){
				Queue_States.push({a,b,c});
				Set_States.insert({a,b,c});
			}
		} else {
			//do nothing
		}
		
		a = A; b = B; c = C;

		if(a < c){
			c -= a;
			a *= 2;
			if(a==b && b==c){
				cout<<1;
				return 0;
			}
			if(Set_States.find({a,b,c}) == Set_States.end()){
				Queue_States.push({a,b,c});
				Set_States.insert({a,b,c});
			}
		} else if( a > c){
			a -= c;
			c *= 2;
			if(a==b && b==c){
				cout<<1;
				return 0;
			}
			if(Set_States.find({a,b,c}) == Set_States.end()){
				Queue_States.push({a,b,c});
				Set_States.insert({a,b,c});
			}
		} else {
			
		}
		
		a = A; b = B; c = C;

		if (b > c){
			b -= c;
			c *= 2;
			if(a==b && b==c){
				cout<<1;
				return 0;
			}
			if(Set_States.find({a,b,c}) == Set_States.end()){
				Queue_States.push({a,b,c});
				Set_States.insert({a,b,c});
			}
		} else if(b < c){
			c -= b;
			b *= 2;
			if(a==b && b==c){
				cout<<1;
				return 0;
			}
			if(Set_States.find({a,b,c}) == Set_States.end()){
				Queue_States.push({a,b,c});
				Set_States.insert({a,b,c});
			}
		} else {
			
		}
	}
		
	cout<<0<<endl;
	return 0;
	
}