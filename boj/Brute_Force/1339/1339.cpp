#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

// #define DEBUG_INPUT

using namespace std;

bool compare(const int & a , const int & b){
	return a > b;
}

//custom compare function
int main(){
	
	//init
	vector< int > WEIGHT_ALPHABET(26,0);
	
	//input
	int N;
	cin>>N;
	for(int i = 0 ; i < N ; i++){
		string input;
		cin>>input;
		int length = input.size();
		for(int _char = 0 ; _char < length; _char++){
			WEIGHT_ALPHABET[input[_char]-'A'] += pow(10,length - 1 -_char);
		}
	}
	
	// arrange in order of weight
	sort(WEIGHT_ALPHABET.begin(), WEIGHT_ALPHABET.end(), compare);
	
	//extract valid weights (exclude 0)
	//end gonna be less than 10
	int end = 0;
	while(WEIGHT_ALPHABET[end] != 0)
		end++;
	vector< int > VALID_WEIGHT_ALPHABET(WEIGHT_ALPHABET.begin(), WEIGHT_ALPHABET.begin() + end);
	
	//output
	int res = 0;
	int largest = 9;
	for(int i = 0; i < end; i++){
		res += largest * VALID_WEIGHT_ALPHABET[i];
		largest--;
	}
	cout<<res;
}