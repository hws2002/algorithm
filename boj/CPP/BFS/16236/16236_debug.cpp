//16236
#include <iostream>
#include <queue>
#include <vector>


using namespace std;

#define DEBUG_INPUT
#define DEBUG_VECTOR_SIZE
#define DEBUG_OUTER_LOOP
#define DEBUG_FIND_DISTANCE

int N;
int MAP[22][22] = {0};
int shark_posi;
int shark_size = 2; 
int fish2eat_togetbig = shark_size;
vector<int> Vector_1size;
vector<int> Vector_2size;
vector<int> Vector_3size;
vector<int> Vector_4size;
vector<int> Vector_5size;
vector<int> Vector_6size;

vector< vector<int> * > Vector_VNSPosi = {
                                        & Vector_1size,
                                        & Vector_2size,
                                        & Vector_3size,
                                        & Vector_4size,
                                        & Vector_5size,
                                        & Vector_6size
};

vector< vector<int> * >::iterator iter1;

vector<int>::iterator iter2;
struct Node{
public:
    int _distance;
    int _posi;
    //constructor
    Node(const int & distance,const int & posi):
        _distance(distance),
        _posi(posi){};
};

void tryout(bool ** visit,queue<Node *> & Queue ,const int & distance, const int & posi){
    if( (!visit[posi/22][posi%22]) && (MAP[posi/22][posi%22] <= shark_size )){
        Queue.push(new Node(distance+1,posi));
        visit[posi/22][posi%22] = true;
    }
}

#ifdef DEBUG_FIND_DISTANCE
void printQueue(queue<Node *> Queue){
    Node * nodeposi;
    while(!Queue.empty()){
        nodeposi = Queue.front();
        Queue.pop();
        cout<<"("<<(nodeposi->_posi)/22 <<","<<(nodeposi->_posi)%22<<")";
    }
}
#endif

int distance_shark2fish(const int & shark, const int & fish){
#ifdef DEBUG_FIND_DISTANCE
    cout<<"Finding distance from ("<<shark/22<<","<<shark%22<<") to ("<<fish/22<<","<<fish%22<<")"<<endl;
#endif
    Node * current_node = new Node(0,shark);
    queue<Node *> Queue_node;
    bool ** VISIT = new bool*[N+2];
    for(int i = 0 ; i < N + 2; i++) {
        VISIT[i] = new bool[N+2];
        std::fill(VISIT[i], VISIT[i] + N+2, false);
        VISIT[i][0] = true ; VISIT[i][N+1] = true;
    }
    fill(VISIT[0],VISIT[0] + N + 2, true);
    fill(VISIT[N+1],VISIT[N+1] + N + 2, true);

    Queue_node.push(current_node);
    VISIT[shark/22][shark%22] = true;
    int distance = 401;
    int posi;
    while(!Queue_node.empty()){
#ifdef DEBUG_FIND_DISTANCE
cout<<"Status of Queue_node : ";
    printQueue(Queue_node);
cout<<endl;
#endif
        current_node = Queue_node.front(); Queue_node.pop();
        distance = current_node->_distance;
        posi = current_node -> _posi;
        if(posi == fish) return distance;
        //try out 4 neighborhoods
        tryout(VISIT, Queue_node, distance, posi+1);
        tryout(VISIT, Queue_node, distance, posi-1);
        tryout(VISIT, Queue_node, distance, posi+22);
        tryout(VISIT, Queue_node, distance, posi-22);
    }
    
    //delete memory
    for(int i = 0 ; i < N+2 ; i++){
        delete VISIT[i];
    }
    delete [] VISIT;
    return distance;
}

int main()
{
    //input
    cin>>N;
    for(int i  = 1 ; i <= N ; i++){
        for(int j = 1; j <= N; j++){
            cin>>MAP[i][j];
            if(MAP[i][j] == 1){
                Vector_1size.push_back(i*22 + j);
            } else if (MAP[i][j] == 2) {
                Vector_2size.push_back(i*22 + j);    
            } else if (MAP[i][j] == 3) {
                Vector_3size.push_back(i*22 + j);    
            } else if (MAP[i][j] == 4) {
                Vector_4size.push_back(i*22 + j);    
            } else if (MAP[i][j] == 5) {
                Vector_5size.push_back(i*22 + j);    
            } else if (MAP[i][j] == 6) {
                Vector_6size.push_back(i*22 + j);    
            } else if(MAP[i][j] == 9){
                shark_posi = i*22 + j;
                MAP[i][j] = 0;
            } else {
            }   
        }
    }
#ifdef DEBUG_INPUT
cout<<"------------DEBUG_INPUT------------"<<endl;
for(int i = 0 ; i < N + 2; i++){
    for(int j = 0 ; j < N+2 ; j++){
        cout<<MAP[i][j];
    }
    cout<<endl;
}
cout<<"-----------------------------------"<<endl;
#endif

#ifdef DEBUG_VECTOR_SIZE
int DEBUG_fish_size = 1;
cout<<"---------DEBUG_VECTOR_SIZE---------"<<endl;
for(iter1 = Vector_VNSPosi.begin(); iter1 != Vector_VNSPosi.end(); iter1++){
    cout<<"fish size : "<<DEBUG_fish_size<<endl;
    for(iter2 = (*iter1)->begin(); iter2 != (*iter1)->end(); iter2++){
        cout<<"("<<*iter2/22<<","<<*iter2%22<<") ";
    }
    cout<<endl;
    DEBUG_fish_size++;
}
cout<<"-----------------------------------"<<endl;
#endif
    //solve
    bool help = false;
    int total_distance = 0;
    while(!help){
        //look for any fish that is available
        int fish2eat = -1;
        int fish2eat_size = 1;
        int distance = 401;
        for(iter1 = Vector_VNSPosi.begin() ; fish2eat_size++ < shark_size && (iter1 != Vector_VNSPosi.end()) ; iter1++){
#ifdef DEBUG_OUTER_LOOP
cout<<"fish to eat size , shark_size : "<<fish2eat_size-1<<","<<shark_size<<endl;
cout<<"MAP : "<<endl;
for(int i = 1; i <= N ;i++){
    for(int j = 1; j <= N; j++){
        cout<<MAP[i][j]<<" ";
    }
    cout<<endl;
}
#endif
            for(iter2 = (*iter1)->begin(); iter2 != (*iter1)->end(); iter2++){
                if(MAP[*iter2/22][*iter2%22] <= 0) continue;
                //find a distance from shark_posi to fish2eat_posi
                int distance2compare = distance_shark2fish(shark_posi,*iter2);
#ifdef DEBUG_OUTER_LOOP
cout<<"distance , distance2compare : "<<distance<<","<<distance2compare<<endl;
#endif
                if (distance > distance2compare ){
                    distance = distance2compare;
                    fish2eat = *iter2;
                } else if (distance == distance2compare){
                    if(fish2eat > *iter2){
                        distance = distance2compare;
                        fish2eat = *iter2;
                    }
                }
            }
        }
        
        //if there's no fish available
        if(distance == 401) break;
        
        //if so eat the fish
        MAP[fish2eat/22][fish2eat%22] = 0; // place where once been a fish, but already eaten
        shark_posi = fish2eat; // replace shark position
        total_distance += distance;
        if(--fish2eat_togetbig <=0 ){
            fish2eat_togetbig = ++shark_size;
        }
#ifdef DEBUG_OUTER_LOOP
cout<<"ate fish on ("<<fish2eat/22<<","<<fish2eat%22<<")"<<endl;
cout<<"fish to eat to get big , shark_size, total distance : "<<fish2eat_togetbig<<","<<shark_size<<","<<total_distance<<endl;
#endif
    }
    
    //output
    cout<<total_distance<<endl;
    return 0;
}