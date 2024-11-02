#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>


// #define DEBUG_INPUT

using namespace std;



//custom compare function

bool compare(const std::pair<int, int> & a, const std::pair<int ,int > & b){
	
	if(a.first != b.first){
		return a.first > b.first;
	}
	return a.second < b.second;
}

int main(){
	
	//init
	vector< pair<int,int> > WEIGHT_ALPHABET(10);
	
	for(int i = 0 ; i < 10 ; i++){
		WEIGHT_ALPHABET[i].second = i;
	}
	
	//input
	int N;
	cin>>N;
	for(int i = 0 ; i < N ; i++){
		string input;
		cin>>input;
		int length = input.size();
		for(int _char = 0 ; _char < length; _char++){
			WEIGHT_ALPHABET[input[_char]-'A'].first += pow(10,length - 1 -_char);
		}
	}
	
	// arrange in order of weight
	sort(WEIGHT_ALPHABET.begin(), WEIGHT_ALPHABET.end(),compare);
	
	#ifdef DEBUG_INPUT
	cout<<"DEBUG_INPUT : WEIGHT_ALPHABET"<<endl;
		for(int i = 0 ; i < 10 ; i++){
			cout<<WEIGHT_ALPHABET[i].first<<" ";
		}
		cout<<endl;
		for(int i = 0 ; i < 10 ; i++){
			cout<<WEIGHT_ALPHABET[i].second<<" ";
		}
		cout<<endl;
	#endif
	
	//output
	int res = 0;
	for(int i = 9 ; i >= 0; i--){
		res += i * WEIGHT_ALPHABET[9-i].first;
	}
	cout<<res<<endl;
}