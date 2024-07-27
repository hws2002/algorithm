//brute force

#include <iostream>
#include <vector>

#define MAX_N 1'001
#define MAX_K 51
using namespace std;

int N;

vector<int> course2time[MAX_N];
vector<int> time2course[MAX_K];

int main(){
    cin>>N;
    for(int i = 1; i <= N; i++){
        int k,coursetime;
        cin>>k;
        for(int j = 0 ; j < k ; j++){
			cin>>coursetime;
            course2time[i].push_back(coursetime);
            time2course[coursetime].push_back(i);
        }
    }
    
    int M;
    cin>>M;
    
    for(int i = 0 ; i < M; i++){
        
        vector<int> available;
        bool availableArray[MAX_K] = {0};
        int p,temp;
        int res = 0;
        cin>>p;
        for(int j = 0 ; j < p; j++){
            cin>>temp;
            available.push_back(temp);
            availableArray[temp] = true;
        }
        
        bool visit[MAX_N] = {false};
        for(auto t : available){
            for(auto c : time2course[t]){
                if(!visit[c]){
                    //check whether the course can be taken
                    bool cantake = true;
                    for(int j = 0 ; j < course2time[c].size(); j++){
                        if(!availableArray[course2time[c][j]]){
                            cantake = false;
                            break;
                        }
                    }
                    if(cantake){
                        res++;
                    }
                    visit[c] = true;
                }
            }
            
        }
        cout<<res<<endl;
    }   
    
    return 0;
}