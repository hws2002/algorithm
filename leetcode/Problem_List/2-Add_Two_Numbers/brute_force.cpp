#include <iostream>
using namespace std;

#define DEBUG
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode * next) : val(x), next(next) {}

};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* res = new ListNode();
    ListNode* res_head = res;
    int carry = 0;
    while( l1 != nullptr || l2 != nullptr){
        // add digits
        int add;
            
        if(l1 == nullptr){
            //for the following digits, we only need l2
            while(l2 != nullptr){
                    #ifdef DEBUG
                        printf("l2[i] : %d \n", l2->val);
                    #endif
                add = l2->val + carry;
                if(add >= 10){
                    carry = 1;
                    add -= 10;
                } else {
                    carry = 0;
                }
                res->next = new ListNode(add);
                res = res->next;
                l2 = l2->next;
            }
            return res_head;
        } else if( l2 == nullptr){
            // for the following digits, we only need l1
            while(l1 != nullptr){
                    #ifdef DEBUG
                        printf("l1[i] : %d \n", l1->val);
                    #endif
                add = l1->val + carry;
                if(add >= 10){
                    carry = 1;
                    add -= 10;
                } else {
                    carry = 0;
                }
                res->next = new ListNode(add);
                res = res->next;
                l1 = l1->next;
            }
            return res_head;
        } else {
            // we have l1 and l2
            #ifdef DEBUG
                printf("l1[i] : %d, l2[i] : %d \n", l1->val, l2->val);
            #endif
            add = l1->val + l2->val + carry;
        }

        // calculate carry
        if(add >= 10){
            carry = 1;
            add -= 10;
        } else {
            carry = 0;
        }
        // assign value and move pointers
        res->next = new ListNode(add);
        res = res->next;
        l1 = l1->next;
        l2 = l2->next;
    }
    return res_head;
}

void deleteList(ListNode * head){
    while(head!= nullptr){
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main(){

    int l1_length; int l2_length;
    ListNode * l1 = new ListNode(); 
    ListNode * l2 = new ListNode(); 
    ListNode * l1_head; ListNode * l2_head;
    l1_head = l1; l2_head = l2;
        #ifdef DEBUG
            printf("pointer l1 : %p", l1);
            printf("pointer l1_head : %p", l1_head);
            printf("pointer l2 : %p", l2);
            printf("pointer l2_head : %p \n", l2_head);
        #endif
    // INPUT : l1
        #ifdef DEBUG
            cout<<"RECEIVING L1"<<endl;
        #endif
    cin>>l1_length;
    for(int i = 0; i< l1_length; i++){
        int digit;
        cin>>digit;
        l1->val = digit;
        l1->next = new ListNode();
        l1 = l1->next;
    }
    l1 = l1_head;
        #ifdef DEBUG
            cout<<"L1 is as follows"<<endl;
            cout<<"[";
            while(l1 != nullptr){
                printf("pointer : %p, val : ", l1);
                cout<<l1->val<<",";
                l1 = l1->next;
            }
            cout<<"]"<<endl;
        #endif
    
    // INPUT : l2
        #ifdef DEBUG
            cout<<"RECEIVING L2"<<endl;
        #endif
    cin>>l2_length;
    for(int i = 0; i < l2_length; i++){
        int digit;
        cin>>digit;
        l2->val = digit;
        l2->next = new ListNode();
        l2 = l2->next;
    }
    l2 = l2_head;
        #ifdef DEBUG
            cout<<"L2 is as follows"<<endl;
            cout<<"[";
            while(l2 != nullptr){
                printf("pointer : %p, val : ", l2);
                cout<<l2->val<<",";
                l2 = l2->next;
            }
            cout<<"]"<<endl;
        #endif
    // // SOLVE

    ListNode * res = addTwoNumbers(l1_head, l2_head);

    // OUTPUT
    vector<int> res_digits;
    while(res != nullptr){
        // cout<<res->val;
        res_digits.push_back(res->val);
        res = res->next;
    }
    for (int i=1; i < res_digits.size(); i++){
        cout<<res_digits[i];
    }

    // free memory
    deleteList(l1_head);
    deleteList(l2_head);
    if (res!= nullptr) deleteList(res);
    return 0;
}