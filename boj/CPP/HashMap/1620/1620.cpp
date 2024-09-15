#include <iostream>
#include <unordered_map>
#include <cstring>
#include <vector>
#define endl '\n'
using namespace std;
unordered_map<string, int> Encyclopedia;
vector<string> Enclyclopedia_v;
void answer(){
    string query;
    cin>>query;
    if('0'<= query[0] && query[0] <= '9'){
        //integer query
        int queryIndex = stoi(query);
        cout<<Enclyclopedia_v[queryIndex-1]<<endl;
    } else {
        cout<<Encyclopedia.at(query)<<endl;
    }
}

int main(){
    //input
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N,M; // 1<= N,M <= 100000
    cin>>N>>M;
    

    string temp;
    
    for(int i = 0 ; i < N; i++){
        cin>>temp;
        Encyclopedia.insert(make_pair(temp, i+1)); 
        Enclyclopedia_v.push_back(temp);
    }
    
    //solve
    while(M-- > 0){
        answer();
    }
    //output
    
    return 0;
}