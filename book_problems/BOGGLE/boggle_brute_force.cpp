#include <iostream>
// #define DEBUG
using namespace std;
string BOARD[5][5];
int n_words;
string * WORDS;
int *x_;
int *y_;

/***
 * @brief 단어가 존재하는지 확인한다.
 * @param int y : y좌표
 * @param int x : x좌표
 * 
*/

const int dx[8] = {-1,-1,-1,1,1,1,0,0};
const int dy[8] = {-1,0,1,-1,0,1,-1,1};
bool hasWord(int y, int x, const string& word){
    // BASE CASE
    if(y<0 || y>=5 || x<0 || x>=5) return false;
    if(BOARD[x][y] != std::string(1, word[0])) return false;
    if(word.size() == 1) return true;
    for(int direction = 0; direction < 8 ; direction++){
        if(hasWord(y+dy[direction],x+dx[direction],word.substr(1)))
            return true;
    }
    return false;
}

int main(){
    // INPUT
    for(int i=0; i<5; ++i){
        for(int j=0; j<5; ++j){
            cin >> BOARD[i][j];
        }
    }
    cin>>n_words;
    WORDS = new string[n_words];
    x_ = new int[n_words];
    y_ = new int[n_words];
    for(int i=0; i<n_words; ++i){
        cin>>WORDS[i];
    }
    for(int i=0; i<n_words; ++i){
        cin>>x_[i]>>y_[i];
    }
    // ALGORITHM
    #ifdef DEBUG
        for(int i=0; i<5; ++i){
            for(int j=0; j<5; ++j){
                cout<<BOARD[i][j]<<" ";
            }
            cout<<endl;
        }

        for(int i=0; i<n_words;++i){
            cout<<WORDS[i]<<" x : "<<x_[i]<<" y : "<<y_[i]<<endl;
        }
    #endif
    for (int i=0; i<n_words;i++){
        if(hasWord(x_[i],y_[i],WORDS[i]))
            printf("%s EXISTS\n",WORDS[i].c_str());
        else 
            printf("%s DOENS'T EXIST\n",WORDS[i].c_str());
    }
    // CLEAR
    delete[] WORDS;
    delete[] x_;
    delete[] y_;
    return 0;
}