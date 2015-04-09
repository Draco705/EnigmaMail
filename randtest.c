#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main(){
    srand(time(NULL));
    int random = 0;
    int i;
    for(i = 0; i < 10; i++){
       random = ((rand()%94) + 32);
       printf("Number = %c\n", (char)random);
    }

    return 0;
}
