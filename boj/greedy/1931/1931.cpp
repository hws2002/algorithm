//dp
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include<functional>

typedef long long ll;

// #define DEBUG_SORT
// #define DEBUG_SOLVE

using namespace std;


int N; // 1<= N <= 100000
vector< pair<int,int> > Vector_s_e;

bool compare( const pair<int,int> & a, const pair<int,int> & b){
    if(a.first == b.first) return a.second < b.second;
    return a.first < b.first;
}

void printVectorPair(vector< pair<int,int> > Vector_s_e){
    cout<<"printing out Vector_s_e"<<endl;
    for(vector< pair<int,int> >::iterator iter = Vector_s_e.begin(); iter != Vector_s_e.end(); iter++){
        cout<<(*iter).first<<" "<<(*iter).second<<endl;
    }
}

void printVector(vector<int> & v){
    for(vector<int>::iterator iter = v.begin(); iter != v.end(); iter++){
        cout<<(*iter)<<" ";
    }
    cout<<endl;
}
int main(){
    //input
    cin>>N;
    int s,e;
    for(int i = 0 ; i < N; i++){
        cin>>s>>e;
        Vector_s_e.push_back({s,e});
    }
    
    //solve
    //sort
    std::sort(Vector_s_e.begin(), Vector_s_e.end(), compare);
#ifdef DEBUG_SORT
printVectorPair(Vector_s_e);
#endif
    
    
    //upper_bound
    vector<int> Start;
    vector<int> dp;
    int i = Vector_s_e.size() - 1;
    int start = Vector_s_e[i].first;
    while(i>=0 && start == Vector_s_e[i].first) i--;
	int complement = 0;
	i++;
	int end = Vector_s_e[i].second;;
	while( i+complement + 1 < Vector_s_e.size()  && Vector_s_e[i + complement+ 1].first == start && Vector_s_e[i + complement + 1].second == end) {
		complement++;
	}
	
	if( i + complement + 1< Vector_s_e.size() && Vector_s_e[i + complement].second == start && Vector_s_e[i + complement+1].first == start){
		end = Vector_s_e[i + complement +1].second;
		complement++;
	}
	
	i--;
    dp.push_back(1 + complement);
    Start.push_back(start);
#ifdef DEBUG_SOLVE
cout<<"printing out dp : "<<endl;
printVector(dp);
cout<<"printing out start : "<<endl;
printVector(Start);
#endif
    int to_push, left_compare;
	int c_complement; // concatenated complement
    for(; i >= 0 ; i--){
        start = Vector_s_e[i].first;
        while(i>=0 && start == Vector_s_e[i].first) i--;
		i++;
		end = Vector_s_e[i].second;
#ifdef DEBUG_SOLVE
cout<<"i,start, end : "<<i<<","<<start<<","<<end<<endl;
#endif
		complement = 0;
		while( i+complement + 1 < Vector_s_e.size()  && Vector_s_e[i + complement+ 1].first == start && Vector_s_e[i + complement + 1].second == end) {
			complement++;
		}
		
		if( i + complement + 1< Vector_s_e.size() && Vector_s_e[i + complement].second == start && Vector_s_e[i + complement+1].first == start){
			end = Vector_s_e[i + complement +1].second;
			complement++;
		}
		
		if( upper_bound(Start.begin() , Start.end() , end, std::greater<int>())  <= Start.begin() ){
            to_push = dp.back();
        } else{
            to_push = max(1 + complement + dp[std::distance( Start.begin(), upper_bound(Start.begin() , Start.end() , end ,std::greater<int>()) ) -1], dp.back());
        }
        dp.push_back(to_push);
        Start.push_back(start);
#ifdef DEBUG_SOLVE
cout<<"printing out dp : "<<endl;
printVector(dp);
cout<<"printing out start : "<<endl;
printVector(Start);
#endif
    }
    cout<<dp.back()<<endl;
    return 0;
}

