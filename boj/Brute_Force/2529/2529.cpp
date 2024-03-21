#include <iostream> 
#include <vector>

using namespace std;

int K;
vector<int> Vector_sign;

int main(){
    
    //input
    cin>>K;
    char inequality_sign;
    for(int i = 0 ; i < K; i++){
        cin>>inequality_sign;
        if(inequality_sign == '>') {
            Vector_sign.push_back(0);
        } else { // '<'
            Vector_sign.push_back(1);
        }
    }
    
    
    //solve
    
    //max
    int largest = 9;
    
    int Vector_index_main = 0;
    int Vector_index_sub = 0;
    int lt_count = 0; // 'less than' count. actually this value is one more than the count
    while(Vector_index_main < K){
        if(Vector_sign[Vector_index_main]){ // <
            //count how many consequtive '<' they have
            Vector_index_sub = Vector_index_main;
            while(Vector_sign[Vector_index_main] && Vector_index_main < Vector_sign.size() ){
                Vector_index_main++;
            }
            lt_count = Vector_index_main - Vector_index_sub + 1 ;
            while(lt_count--){
                cout<<largest - lt_count;
            }
            largest -=  (Vector_index_main - Vector_index_sub + 1) ;
        } else { // >
            cout<<largest--;
        }
        Vector_index_main++;
    }    
    if( !Vector_sign[K-1] ) cout<<largest;
    
    cout<<endl;
    //min
    int smallest = 0;
    
    Vector_index_main = 0;
    Vector_index_sub = 0;
    int gt_count = 0; //'greater than' count.  actually this value is one more than the count
    while(Vector_index_main < K){
        if(Vector_sign[Vector_index_main]){ // <
            cout<<smallest++;
        } else { // >
            Vector_index_sub = Vector_index_main;
            while( !Vector_sign[Vector_index_main] && Vector_index_main < Vector_sign.size() ){
                Vector_index_main++;
            }
            gt_count = Vector_index_main - Vector_index_sub + 1; 
            while(gt_count--){
                cout<<smallest + gt_count;
            }
            smallest += Vector_index_main - Vector_index_sub + 1;
        }
        Vector_index_main++;
    }
    if( Vector_sign[K-1] ) cout<<smallest;
    cout<<endl;
    return 0;
}





