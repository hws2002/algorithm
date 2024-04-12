// 9663 - N-Queen
#include <iostream>
#include <vector>
#include <utility>

#define endl '\n'
#define ON_CROSS(i,j,x,y) ( (((i)-(x)) ==  ((j) - (y))) || ( (i)-(x) ) == ( (y) - (j) ))
using namespace std;

vector< pair<int, int> > Vector_Pair_i_j;
vector< pair<int, int> >::iterator iter;



int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //input
    int N;
    cin>>N;
    //solve
    int count = 0; bool can_put;
    int x,y; int i = 0; int j = 0; 
    for( ; i < N; i++){
        for( ; j < N; j++){
            can_put = true;
            for(iter = Vector_Pair_i_j.begin(); iter != Vector_Pair_i_j.end(); iter++){
                x = (*iter).first; y = (*iter).second;
                if( i == x || j == y || ON_CROSS(i,j,x,y)){
                    can_put = false; break;
                }
            }
            if(can_put){
                Vector_Pair_i_j.push_back({i,j});
                if(Vector_Pair_i_j.size() == N){
                    count++;
                    Vector_Pair_i_j.pop_back();
                    i = Vector_Pair_i_j.back().first;
                    j = Vector_Pair_i_j.back().second;
                    Vector_Pair_i_j.pop_back();
					// now go over j-loop again
                } else {
                    i++; // go to next row
					j = -1;
                }
            } else {
                // look for next possible position
                // but if we are on the end of board
                if( i == N-1 && j == N-1){
                    i = Vector_Pair_i_j.back().first;
                    j = Vector_Pair_i_j.back().second;
                    Vector_Pair_i_j.pop_back();
					// now go over j-loop again
                }
            }
        } // end j-loop
		
        // stopper - optimizer
        if( N - Vector_Pair_i_j.size() > N - i - 1 ){
            i = Vector_Pair_i_j.back().first - 1;
            j = Vector_Pair_i_j.back().second + 1;
            Vector_Pair_i_j.pop_back();
			if(i == -1 && j >=N) break;
        } else {
            j = 0;
        } // end stopper
		
    } // end i
    
    cout<<count<<endl;
    return 0;
}