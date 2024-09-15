#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

#define endl '\n'
using namespace std;

int N;
vector<string> v;

bool compare(const string & s1, const string & s2){
    if(s1.length() == s2.length()) return s1 < s2;
    return s1.length() < s2.length();
};

int main(){
    cin>>N;
    v.resize(N);
    for(int i = 0; i < N; i++){
        cin>>v[i];        
    }
    

    sort(v.begin(), v.end(), compare);

	v.erase(unique(v.begin(),v.end()), v.end());
    for(auto e : v){
        cout<<e<<endl;
    }
    return 0;
}