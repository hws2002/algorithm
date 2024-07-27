#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
bool MAP[20][20] = {false};
vector< vector<int> > Vector_Vector_selections;
vector< vector<int> >::iterator iter;

//version1
void generateSelections(){
    for(int i = 0 ; i < (1<<N); i++){
        vector<int> Vector_selections;
        int pos = 0; int j = i;
        while(j > 0){
            if(j % 2) {
                Vector_selections.push_back(pos);
            }
            j>>=1;
            pos++;
        }
        Vector_Vector_selections.push_back(Vector_selections);
    }
}

/*
0 <= row_n < N
*/

void flip_row(const int & row_n){
    for(int i = 0; i < N; i ++){
        MAP[row_n][i] = !MAP[row_n][i];
    }
}

int main(){
    //input
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N; char temp;
    for(int i = 0 ; i < N; i++){
        for(int j = 0 ; j < N; j++){
            cin>>temp;
            if(temp == 'H'){
                MAP[i][j] = 1;
            }
        }
    }    
    //solve
    int res = N*N;
    generateSelections();
    //outer loop - flip rows
    vector<int> Vector_selections;
    vector<int>::iterator inner_iter;
    for(iter = Vector_Vector_selections.begin() ; iter != Vector_Vector_selections.end(); iter++){
        Vector_selections = *iter;
        //flip rows
        for(inner_iter = Vector_selections.begin(); inner_iter != Vector_selections.end(); inner_iter++){
            flip_row(*inner_iter);
        }
        //inner loop - flip columns
        int total_t = 0; int num_t = 0;
        for(int j = 0 ; j < N; j++){
            num_t = 0;
            for(int i = 0; i < N; i++){
                if(MAP[i][j] == 0) num_t++;
            }
            num_t = min(num_t, N - num_t);
            total_t += num_t;
        }
        //restore rows
        for(inner_iter = Vector_selections.begin(); inner_iter != Vector_selections.end(); inner_iter++){
            flip_row(*inner_iter);
        }
        res = min(res,total_t);
    }
    
    //output
    cout<<res<<endl;
    
    return 0;
}