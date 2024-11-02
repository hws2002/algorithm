#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 100'000
using namespace std;

int Answer;

int main(int argc, char** argv)
{
	int T, test_case;

	freopen("input.txt", "r", stdin);

	cin >> T;
	int N,L;
	int A[MAX_N];
	int B[MAX_N];
	for(test_case = 0; test_case  < T; test_case++)
	{
	    
		Answer = 0;
		/////////////////////////////////////////////////////////////////////////////////////////////
        
		//input
		cin>>N>>L;
		for(int i = 0 ; i < N; i++){
            cin>>A[i];
        }
		for(int i = 0 ; i < N; i++){
			cin>>B[i];
		}
		
		std::sort(A, A + N);
		std::sort(B, B + N);
		
		//solve
		for(int i = 0 ; i < N; i++){
			Anbswer = max(Answer , abs(A[i] - B[i]));
		}
		
		if( Answer > L) Answer = -1;
		else if(Answer < L) {
			int & v1; int & v2;
			int aidx = 0; int bidx = 0;
			
		} else {} // do nothing
		
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}