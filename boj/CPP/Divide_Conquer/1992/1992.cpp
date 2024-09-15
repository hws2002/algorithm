#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int N,k;
int MAP[65][65] = {0};

string compress(int x, int y, int sizeN){
	// printf("compress(%d,%d,%d) \n",x,y,sizeN);
    if(sizeN <= 1) return string(to_string(MAP[x][y]));
    string ul = compress(x, y, sizeN/2);
    string ur = compress(x, y + sizeN/2, sizeN/2);
    string ll = compress(x + sizeN/2, y, sizeN/2);
    string lr = compress(x + sizeN/2, y + sizeN/2, sizeN/2);
	// printf("%s %s %s %s \n ",ul.c_str(),ur.c_str(),ll.c_str(),lr.c_str());
    if( ul == ur && ur == ll && ll == lr && lr == "0") return string("0");
    else if ( ul == ur && ur == ll && ll == lr && lr == "1") return string("1");
    else return string("(") + ul + ur + ll + lr + string(")");
}

int main(){
    cin>>N;
    k = log2(N);
    string s;
    for(int i = 0; i < N; i++){
        cin>>s;
        for(int j = 0; j < N; j++){
            MAP[i][j] = s[j] - '0';
        }
    }
    
    //compress
    cout<<compress(0,0,N)<<endl;
    
    return 0;
}