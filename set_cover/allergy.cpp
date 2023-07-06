#include <iostream>
#include <vector>
using namespace std;
// #define DEBUG
const int INF = 987654321;
int n_members = 4;
int n_menu = 6;

/***
 * @brief : chosen[i] = i번째 친구가 선택한 음식의 종류 
*/
const string Menus[] = { "갈비찜","피자","잡채","떡볶이","탕수육","닭강정"};
const string Students[] = {"Kyle","Gray","Ariel","Emma"};
const int chosen[4][6] = {
    {0,1,1,1,0,0},
    {0,0,0,0,1,1},
    {1,0,1,0,1,0},
    {1,1,0,0,0,1}
};
vector<int> chosen_menu(n_menu+1,-1);
/***
 * @brief : printing all the selected menus
 * @desc : for debugging
*/
#ifdef DEBUG
void print_menu(const vector<int> & menu_){
    for(int i=0; i<menu_.size(); i++){
        cout<<Menus[menu_[i]]<<" ";
    }
}
#endif
/***
 * @brief : 모든 친구들이 음식을 먹을 수 있는지 여부를 반환한다.
 * 
*/
bool canEverybodyEat(const vector<int> & menu){
    for(int i=0; i<n_members; ++i){
        bool canEat = false;
        for(int j=0; j < menu.size();j++){
            if(chosen[i][menu[j]]){
                canEat = true;
                break;
            }
        }
        if(!canEat)
            return false;
    }
        #ifdef DEBUG
            printf("canEveryBodyEat : ");
            print_menu(menu);
            printf("\n");
        #endif
    if(chosen_menu.size() > menu.size()){
        chosen_menu = menu;
    }
    return true;
}

/***
 * @brief : 
*/
int selectMenu(vector<int> & menu, int food){
    #ifdef DEBUG
        cout<<"Current selected menus: ";
        print_menu(menu);
        cout<<" Current Depth : "<<food<<endl;
    #endif
    //base
    if (food == n_menu){
        if (canEverybodyEat(menu))
            return menu.size();
        return INF;
    }
    //recursive
    int ret = selectMenu(menu, food+1); // 이 음식을 만들지 않는 경우의 답을 계산
    menu.push_back(food);
    ret = min(ret, selectMenu(menu,food+1));// 이 음식을 만드는 경우의 답을 계산
    menu.pop_back();
    return ret;
}


int main(){
    vector<int> menu;
    #ifdef DEBUG
        printf("Members : ");
        for(int i=0; i<n_members;i++){
            cout<<Students[i]<<" ";
        }
        printf("\nMenus : ");
        for(int i=0; i<n_menu;i++){
            cout<<Menus[i]<<" ";
        }
        printf("\n");
    #endif
    int ret = selectMenu(menu,0);
    if(ret== INF){
        cout<<"Failed"<<endl;
    } else {
        #ifdef DEBUG
            printf("ret:%d ",ret);
        #endif
        cout<<"Selected Menus : ";
        for (int i = 0; i<chosen_menu.size(); ++i){
            cout<<Menus[chosen_menu[i]]<<" ";
        }
        cout<<endl;
    }
    return 0;
}