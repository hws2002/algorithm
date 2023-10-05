#include <cstdio>
#include "hashtable.h"

int main(){
    int type;
    char buffer[1000];int data;
    hashtable table(10000,new naive_hashing(),new linear_probe());
    while(true){
        scanf("%d", &type);
        if(type == 0){
            scanf("%s", buffer);scanf("%d",&data);
            table.insert(hash_entry(buffer, data));
        }else if(type == 1){
            scanf("%s",buffer);
            printf("%d\n", table.query(buffer));
        }else break;
    }
    return 0;
}
/*
#include<cstdio>
int main(){
    freopen("a.txt","w",stdout);
    freopen("b.txt","r",stdin);
    //接下来，cin/cout/printf/scanf都会从b.txt尝试读取数据，并将输出打印到a.txt
    return 0;
}

#include<ctime>
//...
double t1=clock();
myfunc(); //要测时间的代码段
double t2=clock();
double result = (t2-t1)/CLOCKS_PER_SEC;//result里存的就是要测时间的代码段的运行时间，单位秒
*/