# 557. Reverse Words in a String III
[LeetCode - 557. Reverse Words in a String III](https://leetcode.com/problems/reverse-words-in-a-string-iii/?envType=daily-question&envId=2023-10-01)

## Intuition

문장을 whitespace를 기준으로 split해서 단어들로 나눈다음에, 각각의 단어들을 reverse 시키면 된다.

## Approach

split을 효율적으로 할 수 있는 library가 있는데, `sstream`이다. 

sstream 을 활용하여 split 시키는 함수는 다음과 같이 구현할수 있고,

```cpp
vector<string> split(const string& s){
	istringstream iss(s);
	vector<string> tokens;
	string token;
	while( iss >> token) {
		tokens.push_back(token);
	}
	return tokens;
}
```

! iss 관련해서는 [여기](https://www.notion.so/cbd8c3d4a66342ae9c12d4fee090ba0c?pvs=21)를 참고하자

단어 reverse함수는 이미 구현되어있다.

```cpp
#include <iostream>
#include <algorithm>
#include <string>

int main() {
    std::string word = "hello";
    std::reverse(word.begin(), word.end());
    std::cout << word << std::endl; // Output: "olleh"
    return 0;
}
```

최종적으로 다음과 같이 구현할 수 있겠다.

```cpp
class Solution {
public:

    vector<string> split(const string& s){
        istringstream iss(s);
        vector<string> tokens;
        string token;
        while(iss >> token){
            tokens.push_back(token);
        }
        return tokens;
    };

    string reverseWords(string s) {
        vector<string> tokens = split(s);
        for(int i = 0; i < tokens.size(); i++){
            reverse(tokens[i].begin(), tokens[i].end());
        }
        string res;
        for (int i=0; i< tokens.size(); i++){
            res += tokens[i];
            if( i < tokens.size() -1){
                res += " ";
            }
        }
        return res;
    };
};
```

### Follow-up

<aside>
🤔 굳이 split 하고 reverse하고 다시 string으로 바꿔야 해? 한번에 해봐

</aside>

```cpp
class Solution {
public:
    string reverseWords(string s) {
		string res;
		istringstream iss(s);
        string token;
        while( iss >> token){
            reverse(token.begin(), token.end());
            res += token + " ";
        }
        res.pop_back();
        return res;
    };
};
```