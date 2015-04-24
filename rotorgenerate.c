#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

bool isThere(int rotor[], int size, int input);

int main(){
    srand(time(NULL));

    int i[94];
    int j[94];
    int k[94];

    int l = 0;

    int temp1, temp2, temp3;
    int size1, size2, size3;
    size1 = size2 = size3 = 0;

    for(l = 0; l < 94; l++){
        temp1 = ((rand()%94) + 32);
        size1++;
        if(isThere(i, size1, temp1)){
           while(isThere(i, size1, temp1)){
                temp1 = ((rand()%94)+32);
           }
        }
        i[l] = temp1;

        temp2 = ((rand()%94) + 32);
        size2++;
        if(isThere(j, size2, temp2)){
            while(isThere(j, size2, temp2)){
                temp2 = ((rand()%94)+32);
            }
        }
        j[l] = temp2;
        temp3 = ((rand()%94) + 32);
        if(isThere(k, size3, temp3)){
            while(isThere(k, size3, temp3)){
                temp3 = ((rand()%94)+35);
            }
        }
        k[l] = temp3;
    }

    FILE *f = fopen("rotors.txt", "a+");
    for(l = 0; l < 94; l++){
        fwrite(&i[l], sizeof(char), 1, f);
    }
    fwrite("\n", sizeof(char), 1, f);
    for(l = 0; l < 94; l++){
        fwrite(&j[l], sizeof(char), 1, f);
    }
    fwrite("\n", sizeof(char), 1, f);
    for(l = 0; l < 94; l++){
        fwrite(&k[l], sizeof(char), 1, f);
    }

    fclose(f);

    return 0;
}

bool isThere(int rotor[], int size, int input){
    bool isitThere = false;

    int i;

    for(i = 0; i < size; i++){
        if(input == rotor[i]){
            printf("%d\n", rotor[i]);
            isitThere = true;
            break;
        }
    }
    //printf("Is it there? %s\n", isitThere ? "true":"false");
    return isitThere;
}
