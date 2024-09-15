#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N,M;
vector<int> Vector_Ni;


int binSearch(const int & to_find){
    int lo = 0, hi = N-1;
    int mid;
    while(lo <= hi){
        mid = (lo + hi) >> 1;
        if( lo == hi ) {
            if(Vector_Ni[mid] == to_find) return 1;
            else return 0;
        }
        if( Vector_Ni[mid] > to_find ){
            hi = mid;
        } else if( Vector_Ni[mid] < to_find){
            lo = mid + 1;
        } else{
            return 1;
        }
    }
    return 0;
}

int main(){
    //input
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 
    cout.tie(NULL);
    
    cin>>N; int temp;
    for(int i = 0; i < N; i++){
        cin>>temp; Vector_Ni.push_back(temp);
    }
    
    //sort
    std::sort( Vector_Ni.begin(), Vector_Ni.end() );
    
    cin>>M;
    for(int i = 0 ; i < M; i++){
        cin>>temp;
        cout<<binSearch(temp)<<" ";
    }
    cout<<endl;
    return 0;
}