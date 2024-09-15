#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int N,M;
int num_0 = 0;
int num_1 = 0;
int num_2 = 0;
/*
find out the area of secure region given walls(copied LAB) and virus
*/

int pervade( int (&lab)[9][9] , queue<int> queue_virus ){
	int infected = 0;
	while( !queue_virus.empty() ){
		int virus = queue_virus.front();
		queue_virus.pop();
		//pervade to 4 directions
		int virus_x = virus/M;
		int virus_y = virus%M;
		
		if( virus_x+1 < N && lab[virus_x+1][virus_y] == 0 ){
			lab[virus_x+1][virus_y] = 2;
			queue_virus.push(virus+M);
			infected++;
		}
		
		if( virus_x-1 > -1 && lab[virus_x-1][virus_y] == 0 ){
			lab[virus_x-1][virus_y] = 2;
			queue_virus.push(virus-M);
			infected++;

		}
		
		if( virus_y+1 < M && lab[virus_x][virus_y+1] == 0 ){
			lab[virus_x][virus_y+1] = 2;
			queue_virus.push(virus+1);
			infected++;

		}
		
		if( virus_y-1 > -1 && lab[virus_x][virus_y-1] == 0 ){
			lab[virus_x][virus_y-1] = 2;
			queue_virus.push(virus-1);
			infected++;
		}
	}
	return num_0 - infected;
}

int main( int argc , char * argv [] ){
	//input
	queue<int> Queue_virus;
	int LAB[9][9] = {0};

	cin>>N>>M;
	for( int i = 0 ; i < N ; i++ ){
		for( int j = 0 ; j < M ; j++ ){
			cin>>LAB[i][j];
			if ( LAB[i][j] == 1)
				num_1++;
			else if ( LAB[i][j] == 2 ){
				num_2++;
				Queue_virus.push(M*i+j);
			}
		}
	}

	#ifdef DEBUG_INPUT
		for( int i = 0 ; i < N ; i++ ){
			for( int j = 0 ; j < M ; j++ ){
				cout<<LAB[i][j]<<" ";
			}
			cout<<endl;
		}
	#endif
	
	//find largest area
	int wall_1st = 0;
	while( LAB[wall_1st/M][wall_1st%M] != 0 ) wall_1st++;
	int wall_2nd = wall_1st + 1 ;
	while( LAB[wall_2nd/M][wall_2nd&M] != 0 ) wall_2nd++;
	int wall_3rd = wall_2nd + 1 ;
	while( LAB[wall_3rd/M][wall_3rd&M] != 0 ) wall_3rd++;
	
	int largest_area = 0;
	
	while( wall_1st < N*M - 2 ){
		//copy lab
		int copiedLAB[9][9] = {0};
		for (int i = 0; i < N; i++){
			copy( std::begin( LAB[i] ), std::end( LAB[i] ), std::begin( copiedLAB[i] ) );
		}
		

		// locate walls
		copiedLAB[wall_1st/M][wall_1st%M] = 1;
		copiedLAB[wall_2nd/M][wall_2nd%M] = 1;
		copiedLAB[wall_3rd/M][wall_3rd%M] = 1;
	
		num_0 = N*M - num_1 - num_2 - 3;
		// pervade
		largest_area = max( largest_area, pervade( copiedLAB, Queue_virus) );
		
		wall_3rd++;
		while( LAB[wall_3rd/M][wall_3rd%M] != 0 ) wall_3rd++;
		if( wall_3rd > N*M - 1 ){
			wall_2nd++;
			while( LAB[wall_2nd/M][wall_2nd%M] != 0 ) wall_2nd++;
			
			wall_3rd = wall_2nd + 1;
			while( LAB[wall_3rd/M][wall_3rd%M] != 0 ) wall_3rd++;
			if( wall_3rd > N*M - 1){
				wall_1st++;
				while( LAB[wall_1st/M][wall_1st%M] != 0 ) wall_1st++;
				wall_2nd = wall_1st + 1;
				while( LAB[wall_2nd/M][wall_2nd%M] != 0 ) wall_2nd++;

				wall_3rd = wall_2nd + 1;
				while( LAB[wall_3rd/M][wall_3rd%M] != 0 ) wall_3rd++;
				if( wall_3rd > N*M - 1){
					break;
				}
			}
		}
	}
	
	//output
	cout<<largest_area;
	return 0;
}
