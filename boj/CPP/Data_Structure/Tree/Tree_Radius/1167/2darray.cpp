#include <iostream>
using namespace std;

int main(int argc, char * argv[]){
	int n = 0;
	cin>>n;
	cout<<n<<endl;
	
	int** array = new int*[n];
	for(int i =0; i< n; i++){
		array[i] = new int [n];
	}
	
	for (int i =0; i< n; i++){
		delete[] array[i];
	}
	delete[] array;
	return 0;
}