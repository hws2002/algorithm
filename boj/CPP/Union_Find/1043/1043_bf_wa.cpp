//brute force

#include <iostream>
#include <vector>
using namespace std;

int N,M;
bool KNOW_TRUTH[51] = {false};
int PARTIES[51] = {false};
vector< vector<int> > people_party;

int main(){
    //input
    cin>>N>>M;
    people_party = vector< vector<int> > (N+1);
    int r;
    cin>>r;
    int temp;
    for(int i = 0 ; i < r; i++){
        cin>>temp;
        KNOW_TRUTH[temp] = true;
    }
    
    for(int i = 1 ; i <= M; i++){
        int partyCapacity;
        cin>>partyCapacity;
        bool cantSay = false;
        vector<int> party_people;
        for(int j = 0; j < partyCapacity; j++){
            cin>>temp;
            party_people.push_back(temp);
            people_party[temp].push_back(i);
            if(cantSay){
                KNOW_TRUTH[temp] = true;
            } else {
                if( KNOW_TRUTH[temp] ){
                    cantSay = true;
                    for(int k = 0 ; k < party_people.size(); k++){
                        KNOW_TRUTH[party_people[k]] = true;
                    }
                }
            }
        }
    }
    
    // mark can't
    for(int i = 1; i <= N; i++){
        if(KNOW_TRUTH[i]){
            for(auto party : people_party[i]){
                PARTIES[party] = true;
            }
        }
    }
    
    //output
    int res = 0;
    for(int i = 1; i <= M; i++){
        if(!PARTIES[i]) res++;    
    }
    cout<<res<<endl;
    return 0;
}