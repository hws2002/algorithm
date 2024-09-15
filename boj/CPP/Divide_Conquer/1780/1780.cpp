#include <iostream>
#include <vector>
   
using namespace std;
int N;
int total_count_m1 = 0;
int total_count_0 = 0;
int total_count_p1 = 0;
vector< vector<int> > MAP;

	
void count_paper(){
	if(N <= 1) return;
	int st_x, st_y, end_x, end_y;
	int count_m1 = 0;
	int count_0 = 0;
	int count_p1 = 0;
	int count_2 = 0;
	for(int st_x = 0; st_x < N / 3 ; st_x++){
		for(int st_y = 0; st_y < N/ 3 ; st_y++){
			count_m1 = 0;
			count_0 = 0;
			count_p1 = 0;
			count_2 = 0;
			for(int row = 3*st_x ; row < 3+3*st_x; row++){
				for(int column = 3*st_y; column < 3+3*st_y; column++){
					if ( MAP[row][column] == -1){
						count_m1++;
					} else if (MAP[row][column] == 0){
						count_0++;
					} else if (MAP[row][column] == 1){
						count_p1++;
					} else { // do nothing
						count_2++;
					}
				}
			}
			if ( (count_m1 && !count_0 && !count_p1 && !count_2) ||
				(!count_m1 && count_0 && !count_p1 && !count_2) ||
				(!count_m1 && !count_0 && count_p1 && !count_2)
			) {
				if(count_m1){
					MAP[st_x][st_y] = -1;
					total_count_m1 -= 8;
				}
				if(count_0){
					MAP[st_x][st_y] = 0;
					total_count_0 -= 8;
				} 
				if (count_p1) {
					MAP[st_x][st_y] = 1;
					total_count_p1 -= 8;
				}
			} else {
				MAP[st_x][st_y] = 2;
			}

		}
	}
	N/=3;
	count_paper();
}

int main(){
	//input
	cin>>N;
	MAP.resize(N , vector<int> (N,0));
	for(int i = 0 ; i < N; i++){
		for(int j  = 0 ; j < N; j++){
			cin>>MAP[i][j];
			if( MAP[i][j] == -1){
				total_count_m1++;
			} else if( MAP[i][j] == 0){
				total_count_0++;
			} else {
				total_count_p1++;
			}
		}
	}
	//solve
	
	count_paper();
	
	cout<<total_count_m1<<endl<<total_count_0<<endl<<total_count_p1<<endl;
	return 0;
}
