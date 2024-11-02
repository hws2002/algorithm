#include <iostream>
#include <vector>

#define ON_CROSS(i,j,x,y) (( (i)-(x) == (j)-(y) ) || ((i)-(x) == (y)-(j) ) )

//debug
// #define DEBUG_SOLVE
using namespace std;


int count = 0;	int N;
vector<int> Vector_column;
vector<int>::iterator iter;

#ifdef DEBUG_SOLVE
void printVector(vector< int > & Vector){
    cout<<"PRINTING OUT Vector : "<<endl;
    if(!Vector.empty()){
        for(iter = Vector.begin(); iter != Vector.end(); iter++){
            cout<<"("<<distance(Vector.begin(), iter)+1<<","<<(*iter)<<") ";
        }
    }
    cout<<endl;
}
#endif

bool isSafe(const int & row, const int & column){
	for(int i = 1 ; i <= Vector_column.size(); i++ ){
		if(row == i || 
		   column == Vector_column[i-1] || 
		   ON_CROSS(row, column, i, Vector_column[i-1])
		  ) return false;
	}
	return true;
}

void n_queen(const int row, const int num_queen){
	
#ifdef DEBUG_SOLVE
cout<<"n_queen("<<row<<","<<num_queen<<")"<<endl;
#endif
	if(num_queen >= N){
		count++;
		Vector_column.pop_back();
		return ;
	}
	
	for(int column = 1 ; column <= N; column++){
		if(isSafe(row,column)){
			Vector_column.push_back(column);
#ifdef DEBUG_SOLVE
printVector(Vector_column);
#endif
			n_queen(row+1, num_queen+1);
		}
	}
	
	// take a step back
#ifdef DEBUG_SOLVE
cout<<"taking a step back"<<endl;
#endif
	if(!Vector_column.empty()) Vector_column.pop_back();
}

int main(){
	//input

	cin>>N;
	
	//solve
	n_queen(1,0);
	
	//output
	cout<<count<<endl;
	return 0;
}