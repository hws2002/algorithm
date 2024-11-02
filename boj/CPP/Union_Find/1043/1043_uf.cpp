// union find

#include <iostream>
#include <vector>

using namespace std;

bool MAP[51][51] = {0};
bool know_truth[51] = {false};
bool VISIT[51] = {false};
vector< vector<int> > party_people;
vector<int> people_who_know;
int N,M;

int main(){
    //input
    cin>>N>>M;
    party_people = vector< vector<int> > (M+1);
    int r,temp;
    cin>>r; 
    for(int i = 0; i < r ; i++){
        cin>>temp;
        know_truth[temp] = true;
        people_who_know.push_back(temp);
    }
    
    for(int i = 1; i <= M; i++){
        cin>>r;
        int v1,v2;
        cin>>v1;
        v2 = v1;
        party_people[i].push_back(v1);
        for(int j = 0 ; j < r-1; j++){
            v1 = v2;
            cin>>v2;
            party_people[i].push_back(v2);
            MAP[v1][v2] = true;
            MAP[v2][v1] = true;
        }
    }
    
    
    //union find
    while( !people_who_know.empty()){
        int start = people_who_know.back();
        people_who_know.pop_back();
        for(int next = 1; next <= N; next++){
            if(MAP[start][next] && !VISIT[next]){
                people_who_know.push_back(next);
                know_truth[next] = true;
                VISIT[next] = true;
            }
        }
        VISIT[start] = true;
    }
    
    //output
    int res = M;
    for(int party = 1; party <= M; party++){
        for(auto person : party_people[party]){
            if( know_truth[person] ) {
                res--;
                break;
            }
        }
    }
    cout<<res<<endl;
    return 0;
}