#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

// #define DEBUG_INPUT

int N,M;
int VISIT[20000001] = {0};
int ANSWER[20000001] = {0};

vector< pair<int, int> > Vector_Pair_num_appear;
vector< pair<int, int> >::iterator iter;

bool compare(const pair<int,int> & a, const pair<int,int> & b){
    return a.first < b.first;
}

int main(){
    cin.tie(NULL); ios_base::sync_with_stdio(false);

    //input
    cin>>N;
    int temp;
    int _index = 1;
    cin>>temp; Vector_Pair_num_appear.push_back({temp,1});
    VISIT[temp+10000000] = _index++;
    for(int i = 2; i <=N; i++){
        cin>>temp;
        if(!VISIT[temp + 10000000]){
            Vector_Pair_num_appear.push_back({temp,1});
            VISIT[temp + 10000000] = _index++;
        } else {
            Vector_Pair_num_appear[VISIT[temp + 10000000]-1].second++;
        }
    }


    //
    std::sort(Vector_Pair_num_appear.begin(), Vector_Pair_num_appear.end(), compare);

#ifdef DEBUG_INPUT
cout<<"PRINTINGO UT Vector_Pair_num_appear: "<<"\n";
for(iter = Vector_Pair_num_appear.begin(); iter != Vector_Pair_num_appear.end(); iter++){
    cout<<"("<<(*iter).first <<","<<(*iter).second<<") ";
}
cout<<"\n";
#endif
    //solve
    cin>>M;
    int lo , hi, mid; bool found = false;
    for(int i = 0 ; i < M; i++){
        cin>>temp;
        if(ANSWER[temp+10000000]) { cout<<ANSWER[temp+10000000]-1<<" "; continue;}
        lo = 0; hi = Vector_Pair_num_appear.size()-1; found = false;
        while(lo < hi){
            mid = (lo+hi) >> 1;
            if(Vector_Pair_num_appear[mid].first > temp){
                hi = mid;
            } else if(Vector_Pair_num_appear[mid].first < temp){
                lo = mid + 1;
            } else {
                cout<<Vector_Pair_num_appear[mid].second<<" ";
                ANSWER[temp+10000000] = Vector_Pair_num_appear[mid].second+1;
                found = true;
                break;
            }
        }

        if(!found){
            if(Vector_Pair_num_appear[lo].first == temp) {
                cout<<Vector_Pair_num_appear[lo].second<<" ";
                ANSWER[temp+10000000] = Vector_Pair_num_appear[lo].second + 1;
            } else {cout<<0<<" "; ANSWER[temp+10000000] = 1;}
        }
    }
    cout<<"\n";
    return 0;
}