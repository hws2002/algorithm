#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    int N, operand;
    string operation;
    stack<int> stack;

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> operation;
        if (operation == "push") {
            cin >> operand;
            stack.push(operand);
        } else if (operation == "top") {
            if (!stack.empty())
                cout << stack.top() << endl;
            else
                cout << -1 << endl;
        } else if (operation == "size") {
            cout << stack.size() << endl;
        } else if (operation == "empty") {
			if(stack.empty()) cout<<1<<endl;
			else cout<<0<<endl;
        } else if (operation == "pop") {
            if (!stack.empty()) {
                stack.pop();
            } else {
                cout << -1 << endl;
            }
        }
    }

    return 0;
}
