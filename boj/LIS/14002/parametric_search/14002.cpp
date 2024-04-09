#include <iostream>
#include <vector>

// #define DEBUG_VECTOR

using namespace std;
vector< vector<int> * > Vector_LIS;

int upper_bound(const int & Ai){
    int lo = 0;
    int hi = Vector_LIS.size(); int mid;
    while( lo <= hi && lo < Vector_LIS.size()){
        mid = (lo + hi) >> 1;
        if(Vector_LIS[mid]->back() > Ai){
            hi = mid - 1;
        } else if (Vector_LIS[mid]->back() < Ai){
            lo = mid + 1;
        } else {
            return mid + 1;
        }
    }
    return lo;
}

int main(){
    int N, Ai;
    cin>>N;
    cin>>Ai;
    Vector_LIS.push_back( new vector<int>(1,Ai));
    int ub = 0;
    for(int i = 1; i < N; i++){
        cin>>Ai;
        ub = upper_bound(Ai);
        
        if(ub == 0){
            if(Vector_LIS[0]->size() == 1) Vector_LIS[0]->front() = Ai;
            else{// create new vector
                Vector_LIS.insert(Vector_LIS.begin(),new vector<int> (1,Ai));
            }
        } else if(ub == Vector_LIS.size()){
            if( Vector_LIS[ub-1]->back() == Ai) continue;
            else{
                Vector_LIS.push_back(new vector<int>( *(Vector_LIS[ub-1]) ) );
                Vector_LIS.back()->push_back(Ai);
            }
        } else {
            if( Vector_LIS[ub-1]->back() == Ai) continue;
            else { // Vector_LIS[ub-1]->back() < Ai
                if( Vector_LIS[ub]-> size() == Vector_LIS[ub-1] ->size() + 1){
                   delete Vector_LIS[ub];
                   Vector_LIS[ub] = new vector<int> ( *(Vector_LIS[ub-1]) );
                } else{
                    Vector_LIS.insert( Vector_LIS.begin() + ub, new vector<int>( *(Vector_LIS[ub-1]) ) );
                }
                Vector_LIS[ub]->push_back(Ai);
            }
        }
    }
    //output
    cout<<Vector_LIS.back()->size()<<endl;
    for(int value : *( Vector_LIS.back() )){
        cout<<value<<" ";
    }
    //delete 
    for (auto vecPtr : Vector_LIS) {
        delete vecPtr;
    }
    Vector_LIS.clear();
    return 0;
}