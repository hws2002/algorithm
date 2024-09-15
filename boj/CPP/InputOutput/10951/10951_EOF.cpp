#include <stdio.h>
#include <string.h>

int main()
{
    int A,B;
    while(scanf("%d %d", &A, &B) != EOF){
        getchar();
        printf("%d\n",A+B);
    }
    return 0;
}