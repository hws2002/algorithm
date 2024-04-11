// 9663 - N-Queen
#include <iostream>
#include <vector>
#include <utility>
typedef long long ll;

#define endl '\n'
#define ON_CROSS(i,j,x,y) ( (((i)-(x)) ==  ((j) - (y))) || ( (i)-(x) ) == ( (y) - (j) ))

// debug
// #define DEBUG_SOLVE

using namespace std;

vector< pair<int, int> > Vector_Pair_i_j;
vector< pair<int, int> >::iterator iter;

#ifdef DEBUG_SOLVE
void printVector(vector< pair<int, int> > & Vector_Pair_i_j){
    cout<<"PRINTING OUT Vector_Pair_i_j : "<<endl;
    if(!Vector_Pair_i_j.empty()){
        for(iter = Vector_Pair_i_j.begin(); iter != Vector_Pair_i_j.end(); iter++){
            cout<<"("<<(*iter).first<<","<<(*iter).second<<") ";
        }
    }
    cout<<endl;
}
#endif


int main(){
    //input
    int N;
    cin>>N;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //solve
    ll count = 0; bool can_put;
    int x,y; int i = 0; int j = 0; 
    for( ; i < N; i++){
        for( ; j < N; j++){
#ifdef DEBUG_SOLVE
cout<<"i,j : "<<i<<","<<j<<endl;
#endif
            can_put = true;
            for(iter = Vector_Pair_i_j.begin(); iter != Vector_Pair_i_j.end(); iter++){
                x = (*iter).first; y = (*iter).second;
                if( i == x || j == y || ON_CROSS(i,j,x,y)){
                    can_put = false; break;
                }
            }
            
            if(can_put){
                Vector_Pair_i_j.push_back({i,j});
#ifdef DEBUG_SOLVE
cout<<"can_put true"<<endl;
printVector(Vector_Pair_i_j);
#endif
                if(Vector_Pair_i_j.size() == N){
                    count++;
                    Vector_Pair_i_j.pop_back();
                    x = Vector_Pair_i_j.back().first;
                    y = Vector_Pair_i_j.back().second;
                    Vector_Pair_i_j.pop_back();
                    i = x;
                    j = y;
					// now go over j-loop again
#ifdef DEBUG_SOLVE
cout<<"count : "<<count<<endl;
printVector(Vector_Pair_i_j);
cout<<"new i, j : "<<i<<","<<j<<endl;
#endif
                } else {
                    i++; // go to next row
					if(i >= N) {
						cout<<"sth went wrong"<<endl; break;
					}
					j = -1;
                }
            } else {
                //look for next possible position
                // but if we are on the end of board
                if( i == N-1 && j == N-1){
                    x = Vector_Pair_i_j.back().first;
                    y = Vector_Pair_i_j.back().second;
                    Vector_Pair_i_j.pop_back();
                    i = x;
                    j = y;
					// now go over j-loop again
#ifdef DEBUG_SOLVE
cout<<"at the end of board!"<<endl;
printVector(Vector_Pair_i_j);
cout<<"new i, j : "<<i<<","<<j<<endl;
#endif
                }
            }
        } // end j-loop
        // stopper
        if( N - Vector_Pair_i_j.size() > N - i - 1 ){
            x = Vector_Pair_i_j.back().first;
            y = Vector_Pair_i_j.back().second;
            Vector_Pair_i_j.pop_back();
            i = x-1;
            j = y+1;
#ifdef DEBUG_SOLVE
cout<<"stopper!"<<endl;
printVector(Vector_Pair_i_j);
cout<<"new i, j : "<<i<<","<<j<<endl;
#endif
			if(i == -1 && j >=N) break;
        } else {
            j = 0;
        } // end stopper
    } // end i
    
    cout<<count<<endl;
    return 0;
}