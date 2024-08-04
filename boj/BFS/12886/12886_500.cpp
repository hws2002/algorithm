
#include <iostream>
#include <queue>
#include <algorithm>


#define DEBUG_VISIT
#define DEBUG_TOTAL
#define DEBUG_QUEUE

using namespace std;

/*
input
1 <= A, B, C <= 500
*/
#ifdef DEBUG_QUEUE
void printQueue(queue<int> Queue){
	int total;
	int A,B,C;
	cout<<"Current Queue: ";
	while(!Queue.empty()){
		total = Queue.front();
		Queue.pop();
		A = total / (501*501);
		total %= (501*501);
		B = total / 501;
		total %=501;
		C = total;
		cout<<"("<<A<<","<<B<<","<<C<<")"<<" ";
	}
	cout<<endl;
}
#endif

void MarkVisited(bool * visit, const int & a, const int & b, const int & c){
	int total;
	visit[a*501*501 + b*501 + c] = true;
	visit[a*501*501 + c*501 + b] = true;
	visit[b*501*501 + a*501 + c] = true;
	visit[b*501*501 + c*501 + a] = true;
	visit[c*501*501 + a*501 + b] = true;
	visit[c*501*501 + b*501 + a] = true;
}
				 
int main(){
	//input
	int A;
	int B;
	int C;
	cin>>A>>B>>C;
	
	//solve - bfs
	bool * VISIT = new bool[501*501*501];
	std::fill_n(VISIT, 501*501*501, false);
	queue<int> Queue_states;
	int total = A*501*501 + B*501 + C;
	Queue_states.push(total);
	MarkVisited(VISIT,A,B,C);
	int a;
	int b;
	int c;
	while(!Queue_states.empty()){
		#ifdef DEBUG_QUEUE
			printQueue(Queue_states);
		#endif
		total = Queue_states.front();
		Queue_states.pop();
		A = total / (501*501);
		total %= (501*501);
		B = total / 501;
		total %=501;
		C = total;
		a = A; b = B; c = C;
		#ifdef DEBUG_TOTAL
			cout<<"A,B,C : "<<a<<" "<<b<<" "<<c<<endl;
		#endif
		// a<->b
		if(a > b){
			a -=b;
			b *=2;
			if(a==b && b==c){
				cout<<1<<endl;
				return 0;
			}
			total = a*501*501 + b*501 + c;
			if(!VISIT[total]){
				Queue_states.push(total);
				MarkVisited(VISIT, a, b, c);
			}
		} else if (a < b) {
			b -=a;
			a *=2;
			if(a==b && b==c){
				cout<<1<<endl;
				return 0;
			}
			total = a*501*501 + b*501 + c;
			if(!VISIT[total]){
				Queue_states.push(total);
				MarkVisited(VISIT, a, b, c);
			}
		} else{
			//do nothing for a==b (skip)
		}
		a = A; b = B; c = C;
		// a<->c
		if(a > c){
			a -=c;
			c *=2;
			if(a==b && b==c){
				cout<<1<<endl;
				return 0;
			}
			total = a*501*501 + b*501 + c;
			if(!VISIT[total]){
				Queue_states.push(total);
				MarkVisited(VISIT, a, b, c);
			}			
		} else if (a < c) {
			c -=a;
			a *=2;
			if(a==b && b==c){
				cout<<1<<endl;
				return 0;
			}
			total = a*501*501 + b*501 + c;
			if(!VISIT[total]){
				Queue_states.push(total);
				MarkVisited(VISIT, a, b, c);
			}
		} else{
			//do nothing for a==c (skip)
		}
		a = A; b = B; c = C;
		// c<->b
		if(c > b){
			c -=b;
			b *=2;
			if(a==b && b==c){
				cout<<1<<endl;
				return 0;
			}
			total = a*501*501 + b*501 + c;
			if(!VISIT[total]){
				Queue_states.push(total);
				MarkVisited(VISIT, a, b, c);
			}
		} else if (c < b) {
			b -=c;
			c *=2;
			if(a==b && b==c){
				cout<<1<<endl;
				return 0;
			}
			total = a*501*501 + b*501 + c;
			if(!VISIT[total]){
				Queue_states.push(total);
				MarkVisited(VISIT, a, b, c);
			}
		} else{
			//do nothing for c==b (skip)
		}
		
	}
	
	delete[] VISIT;
	cout<<0<<endl;
	return 0;
}
