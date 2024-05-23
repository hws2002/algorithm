
// '+' 와 '-' 사이에서는 먼저 출현한 operator 먼저 계산
// '*' 와 '/' 사이에서는 먼저 출현한 operator 먼저 계산

#include <iostream>
#include <cstring>
#include <stack>
// #include <string.h>

#define OPTR_N 7
// #define DEBUG_SOLVE
using namespace std;

typedef enum {
    ADD,
    SUB,
    MUL,
    DIV,
    L_P,
    R_P,
    EOL
} Operator;

const char pri[OPTR_N][OPTR_N] = {
    {'>','>','<','<','<','>','>'}, // '+' 와 '-' 사이에서는 먼저 출현한 operator 먼저 계산한다
    {'>','>','<','<','<','>','>'},
    {'>','>','>','>','<','>','>'}, // '*' 와 '/' 사이에서는 먼저 출현한 operator 먼저 계산
    {'>','>','>','>','<','>','>'},
    {'<','<','<','<','<','=',' '},//스택안의 ( 와 infix표현식의 )가 만날경우, 아무것도 출력하지 않고 끝낸다.
    {' ',' ',' ',' ',' ',' ',' '},//애초에 )는 스택에 있을 수 없음
    {' ',' ',' ',' ',' ',' ',' '} //애초에 EOL도 스택에 있을 수 없음
};

// < : push to stack
// > : pop till meet '<'

Operator optr2rank(const char op){
    switch(op){
        case '+': return ADD;
        case '-': return SUB;
        case '*': return MUL;
        case '/': return DIV;
        case '(': return L_P;
        case ')': return R_P;
        case '\0': return EOL;
        default : return EOL;
    }
}

const char priority(const char op1, const char op2){
    return pri[optr2rank(op1)][optr2rank(op2)];
}

#ifdef DEBUG_SOLVE
void printStack(stack<char> st){
    while(!st.empty()){
        cout<<st.top()<<" ";
        st.pop();
    }
    cout<<endl;
}
#endif
void infix2postfix(char infix[102], string & RPN){
    stack<char> optr;
    int idx = 0;
    while(infix[idx] != '\0'){
#ifdef DEBUG_SOLVE
cout<<infix[idx]<<endl;
cout<<"stack status : ";
printStack(optr);
#endif
        if( 'A' <= infix[idx] && infix[idx] <= 'Z'){
            RPN.push_back(infix[idx++]);
        } else {
            if(optr.empty()){
                optr.push(infix[idx++]);    
            } else {
                char op1 = optr.top();
                char op2 = infix[idx];
                if(priority(op1,op2) == '>'){
                    
                    while( !optr.empty() && priority(optr.top(), op2) == '>' ){
                        RPN.push_back(optr.top());
                        optr.pop();
                    }
                    
                } else if (priority(op1,op2) == '<'){
                    optr.push(op2);
                    idx++;
                } else if (priority(op1,op2) == '='){
                    // ( )
                    optr.pop();
                    idx++;
                } else {
                    cout<<"sth went wrong"<<endl;
                    return;
                }
            }
        }
    }

    while(!optr.empty()){
        RPN.push_back(optr.top());
        optr.pop();
    }
    return ;
}

int main(){
    char infix[102];
    fgets(infix, sizeof(infix), stdin);
    string RPN; //revese polish notation
    infix2postfix(infix, RPN);
    cout<<RPN<<endl;
    return 0;
}