#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#define DEBUG_INPUT
#define DEBUG_ASSIGN

using namespace std;



bool compare(const std::pair<int, int> & a, const std::pair<int, int> & b){
	//sort by value in descending order
	if (a.first != b.first){
		return a.first > b.first;
	}
	//if values are equal, sort by original index in ascending order
	return a.second < b.second;
}

int DIGIT_ALPHABET[8][10] = {0};
int ALPHABET_NUMBER[10] = {0};
bool assigned[10] = {false};
int largest = 9;



void assign_number_to_alphabet(vector<pair<int,int>> & AppearanceIndex,int digit){
	#ifdef DEBUG_ASSIGN
		cout<<"digit : "<<digit<<endl;
	#endif
	sort(AppearanceIndex.begin(), AppearanceIndex.end(), compare);
	
	#ifdef DEBUG_ASSIGN
		for(const auto& pair : AppearanceIndex){
			cout<<"Appearance : "<<pair.first<<", Index : "<<pair.second<<endl;
		}
	#endif
	
	if(digit == 0){
		for(int i = 0 ; i < AppearanceIndex.size(); i++){
			int _index = AppearanceIndex[i].second;
			#ifdef DEBUG_ASSIGN
				cout<<"Assigned "<<largest<<" to "<<_index<<" !"<<endl;
			#endif
			ALPHABET_NUMBER[_index] = largest;
			assigned[_index] = true;
			largest--;
		}
	} else {

		for(int i = 0; i < AppearanceIndex.size(); i++){
			//find a segment where AppearanceIndex[i].first are same
			int appearance = AppearanceIndex[i].first;
			int _index = AppearanceIndex[i].second;
			int j = i+1;

			while( j < AppearanceIndex.size() && AppearanceIndex[j].first == appearance){
				j++;
			}

			#ifdef DEBUG_ASSIGN
				cout<<"i,j : "<<i<<","<<j<<endl;
			#endif
			if ( j > i+1) {
				for(int k = i; k < j ; k++){
					_index = AppearanceIndex[k].second;

					AppearanceIndex[k].first = DIGIT_ALPHABET[digit-1][_index];
					#ifdef DEBUG_ASSIGN
						cout<<"Assigned new appearance "<<DIGIT_ALPHABET[digit-1][_index]<<" to alphabet "<<_index<<endl;
					#endif
				}
				vector<pair<int, int>> new_AppearanceIndex(AppearanceIndex.begin()+i, AppearanceIndex.begin() + j);
				assign_number_to_alphabet(new_AppearanceIndex, digit-1);
				i = j-1;
			} else {
				#ifdef DEBUG_ASSIGN
					cout<<"Assigned "<<largest<<" to "<<_index<<" !"<<endl;
				#endif
				ALPHABET_NUMBER[_index] = largest;
				assigned[_index] = true;
				largest--;
			}
		}
	}
}

int main(int argc, char * argv []){
	int N;
	cin>>N;
	for(int i = 0; i < N ; i++){
		string input;
		cin>>input;
		int length = input.size();
		for(int j = 0; j < length ; j++){
			DIGIT_ALPHABET[length - j - 1][input[j] - 'A'] += 1;			
		}
	}
	
	#ifdef DEBUG_INPUT
		cout<<"  ABCDEFGHIJ"<<endl;
		for(int i = 0 ; i < 8 ; i++){
			cout<<i<<" ";
			for(int j = 0; j < 10; j++){
				cout<<DIGIT_ALPHABET[i][j];
			}
			cout<<endl;
		}
	#endif
	
	// assign number to each alphabet
	for(int i = 7 ; i >= 0 ; i--){
		vector< pair<int, int> > AppearanceIndex;
		for(int j = 0; j < 10; j++){
			if(assigned[j] || DIGIT_ALPHABET[i][j]==0) continue;
			AppearanceIndex.push_back({DIGIT_ALPHABET[i][j],j});
		}
		if(AppearanceIndex.empty()) continue;
		#ifdef DEBUG_ASSIGN
			cout<<"Sort & Assign numbers to 10 to the "<<i<<"th digit"<<endl;
		#endif
		assign_number_to_alphabet(AppearanceIndex,i);
	}
	
	//output
	int res = 0;
	for(int i = 0 ; i < 8 ; i++){
		int to_sum = 0;
		for(int j = 0; j < 10 ; j++){
			to_sum += DIGIT_ALPHABET[i][j] * ALPHABET_NUMBER[j];
		}
		res += to_sum * pow(10,i);
	}
	
	cout<<res;
	return 0;
}