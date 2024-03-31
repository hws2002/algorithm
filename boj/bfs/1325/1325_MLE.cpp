#include <iostream>
#include <vector>

// #define DEBUG_TREE
// #define DEBUG_UPDATE

using namespace std;

int N,M;
struct Node{
public:
    vector<Node *> _parents;
    int _height;
    Node(const int height) : _height(height){
        
    };
};

vector< Node * > Vector_Node_Posi;
int largest_height = 0;

void update_height(const Node * posi){
#ifdef DEBUG_UPDATE
    cout<<"updating height of posi address : "<< posi<<endl;
#endif
    if(!posi->_parents.empty()){
        for(int i = 0 ; i < posi->_parents.size(); i++){
            if( posi->_height + 1 > posi->_parents[i]->_height ){
                posi->_parents[i]->_height = posi->_height + 1;
#ifdef DEBUG_UPDATE
    cout<<"height updated to :" <<  posi->_parents[i]->_height <<" start updating parent node!"<<endl;
#endif
                update_height(posi->_parents[i]);
            }
        }
    } else {
        largest_height = max(largest_height, posi->_height);
#ifdef DEBUG_UPDATE
    cout<<"largest_height : "<< largest_height<<endl;
#endif
    }
}

#ifdef DEBUG_TREE
void printParentsPosi(const Node * posi){
    if(posi->_parents.empty()){
        cout<<"_parents vector empty!"<<endl;
        return;
    }
    for(int i = 0 ; i < posi->_parents.size(); i++){
        cout<<posi->_parents[i]<<endl;
    }
    cout<<endl;
}
#endif


int main(){
    //input
    cin>>N>>M; int A,B;
    Node * child_posi;
    Node * parent_posi;
    for(int i = 0; i < N+1; i++){
        Vector_Node_Posi.push_back(new Node(0));
        // height == 0 indicates the Node hasn't been created yet
    }
    
    for(int i = 0 ; i < M; i++){
        cin>>A>>B;
        child_posi = Vector_Node_Posi[A];
        parent_posi = Vector_Node_Posi[B];
        if(child_posi->_height == 0) child_posi->_height = 1;
        if(parent_posi ->_height == 0) parent_posi->_height = 1;
        child_posi->_parents.push_back(parent_posi);
#ifdef DEBUG_TREE
cout<<"child_posi---------------- "<<endl;
cout<<"address : "<<child_posi<<endl;
cout<<"computer number : "<<A<<endl;
cout<<"parents : "<<endl;
printParentsPosi(child_posi);
cout<<"height : "<<child_posi->_height<<endl;

cout<<"parent_posi---------------- "<<endl;
cout<<"address : "<<parent_posi<<endl;
cout<<"computer number : "<<B<<endl;
cout<<"parents : "<<endl;
printParentsPosi(parent_posi);
cout<<"height : "<<parent_posi->_height<<endl;
#endif
        //update height
        if(child_posi->_height + 1 > parent_posi->_height) {
            parent_posi->_height = child_posi->_height + 1;
#ifdef DEBUG_UPDATE
cout<<"parent height updated to :" <<  child_posi->_height + 1<<" start updating!"<<endl;
#endif
            update_height(parent_posi);
        }
    }
    
    //output
    for(int i = 1; i <= N; i++){
        if(Vector_Node_Posi[i]->_height == largest_height){
            cout<<i<<" ";
        }
    }
    cout<<endl;
    return 0;
}