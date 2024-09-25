#include <stdio.h>
 
int main(void) {
    char name[100];
 
    printf("이름을 입력해 주세요. ");
    scanf("%s", name);
 
    printf("당신의 이름은 %s입니다.\n", name);
 
    return 0;
}