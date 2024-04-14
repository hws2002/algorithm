#include <iostream>
#include <vector>
using namespace std;

int MAP[11][11] = {0};
vector<int> Vector_Tofill;
bool FILLED[11][11] = {false};


bool is_determinedRow(const int & row, const int & column){
    bool OCCUPIED[10] = {false};
    int counter = 0;
    for(int c = 1; c <= 9; c++){
        // if(c == column) continue;
        if(MAP[row][c]) {
            OCCUPIED[MAP[row][c]] = true;
            counter++;
        }
    }
    if(counter == 8){
        for(int i = 1; i <= 9 ; i++){
            if(!OCCUPIED[i]){
                MAP[row][column] = i;
                break;
            }
        }
        FILLED[row][column] = true;
        return true;
    } else {
        return false;
    }
}

bool is_determinedColumn(const int & row, const int & column){
    bool OCCUPIED[10] = {false};
    int counter = 0;
    for(int r = 1; r <= 9; r++){
        // if(r == row) continue;
        if(MAP[r][column]) {
            OCCUPIED[MAP[r][column]] = true;
            counter++;
        }
    }
    
    if(counter == 8){
        for(int i = 1; i <=9 ; i++){
            if(!OCCUPIED[i]){
                MAP[row][column] = i;
                break;
            }
        }
        FILLED[row][column] = true;
        return true;
    } else {
        return false;
    }
}

bool is_determinedBox(const int & row, const int & column){
    //find out which box the blank is located
    // 0 1 2
    // 3 4 5
    // 6 7 8
    bool OCCUPIED[10] = {false};
    int counter = 0;
    int start_row = 3 * ( (row-1) / 3) + 1;
    int start_column =  3 * ( (column- 1) / 3) + 1;
    for(int r = start_row; r <= start_row + 2 ; r++){
        for(int c = start_column; c <= start_column + 2; c++){
            if(MAP[r][c]){
                OCCUPIED[MAP[r][c]] = true;
                counter++;
            }
        }
    }
    
    if(counter == 8){ // better >= 8
        for(int i = 1; i <= 9 ; i++){
            if(!OCCUPIED[i]){
                MAP[row][column] = i;
                break;
            }
        }
        FILLED[row][column] = true;
        return true;
    } else {
        return false;
    }
}

void printBoard(){
	cout<<endl;
    for(int i = 1; i <= 9; i++){
        for(int j = 1; j <= 9 ; j++){
            cout<<MAP[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

bool check_determined(const int & row, const int & column, const int & i){
        
        if(is_determinedRow(row, column)){
            Vector_Tofill.erase(Vector_Tofill.begin() + i);

            for(int j = 0; j < Vector_Tofill.size(); j++){
                // if( FILLED[ Vector_Tofill[j]/10 ][ Vector_Tofill[j]%10 ] ) continue;
                if( Vector_Tofill[j]%10 == column) {

                    check_determined( Vector_Tofill[j]/10 , column , j);
                    break ;
                }
            }
            return true;
        }
        
        if(is_determinedColumn(row,column)){
            Vector_Tofill.erase(Vector_Tofill.begin() + i);
            for(int j = 0 ; j < Vector_Tofill.size(); j++){
                // if( FILLED[ Vector_Tofill[j]/10 ][ Vector_Tofill[j]%10 ] ) continue;
                if( Vector_Tofill[j]/10 == row){
                    check_determined( row , Vector_Tofill[j]%10, j );
                    break;
                }
            }
            return true;
        }
        
        if(is_determinedBox(row,column)){
            Vector_Tofill.erase(Vector_Tofill.begin() + i);
            int count = 0;
            for(int j = 0; j < Vector_Tofill.size(); j++){
                // if( FILLED[ Vector_Tofill[j]/10 ][ Vector_Tofill[j]%10 ] ) continue;
                if( Vector_Tofill[j]/10 == row || Vector_Tofill[j]%10 == column){
                    check_determined(Vector_Tofill[j]/10, Vector_Tofill[j]%10, j); count++;
                    if(count >= 2) break;
                }
            }
            return true;
        }
	return false;
}

void fill_out_determined(){
	
    int row, column;
    for(int i = 0 ; i < Vector_Tofill.size(); i++){
        row = Vector_Tofill[i]/10;
        column = Vector_Tofill[i]%10;
        // if(FILLED[row][column] continue;
		if(check_determined(row, column,i))
			i = -1;
    }
	if(Vector_Tofill.empty()){ printBoard(); return;}
}


bool fillSuDoKu_DFS(const int & num_filled){
	if(num_filled >= Vector_Tofill.size()) return true;
	int row, column;
	for(int i = num_filled; i < Vector_Tofill.size(); i++){
		row = Vector_Tofill[i]/10; column = Vector_Tofill[i]%10;
		if( FILLED[row][column] ) continue;
		
		bool OCCUPIED[10] = {false};

		//check row
		for(int r = 1; r <= 9; r++){
			if( MAP[r][column] )
				OCCUPIED[MAP[r][column]] = true;
		}
		
		//check column
		for(int c = 1; c <= 9; c++){
			if( MAP[row][c] )
				OCCUPIED[MAP[row][c]] = true;
		}
		//check box
		int start_row = 3 * ( (row-1) / 3) + 1;
		int start_column =  3 * ( (column-1) / 3) + 1;
		for(int r = start_row; r <= start_row + 2 ; r++){
			for(int c = start_column; c <= start_column + 2; c++){
				if(MAP[r][c]){
					OCCUPIED[MAP[r][c]] = true;
				}
			}
		}
		bool can_fill = false;
		for(int num = 1 ; num <= 9 ; num++){
			if(!OCCUPIED[num]) {
				MAP[row][column] = num; FILLED[row][column] = true;
				can_fill = fillSuDoKu_DFS(i+1); if(can_fill) break;
				MAP[row][column] = 0; FILLED[row][column] = false;
			}
		}
		return can_fill;
	}
	return true;
}

int main(){
  	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //input
    for(int i = 1; i <= 9; i++){
        for(int j = 1 ; j <= 9; j++){
            cin>>MAP[i][j];
            if(MAP[i][j] == 0) Vector_Tofill.push_back(10*i + j);
        	FILLED[i][j] = MAP[i][j];
		}
    }
    //solve
    
    //first fill out already determined blanks
    fill_out_determined();

    //now fill out with back-tracking
    if(!Vector_Tofill.empty()){
        fillSuDoKu_DFS(0);
		printBoard();
    }
    return 0;
}