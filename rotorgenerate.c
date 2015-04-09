#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    srand(time(NULL));

    int i[94];
    int j[94];
    int k[94];

    int l = 0;

    for(l = 0; l < 94; l++){
        i[l] = ((rand()%94) + 32);
        j[l] = ((rand()%94) + 32);
        k[l] = ((rand()%94) + 32);
    }

    FILE *f = fopen("rotors.txt", "a+");
    for(l = 0; l < 94; l++){
        fwrite(&i[l], sizeof(char), 1, f);
        fwrite(" ", sizeof(char), 1, f);
    }
    fwrite("\n", sizeof(char), 1, f);
    for(l = 0; l < 94; l++){
        fwrite(&j[l], sizeof(char), 1, f);
        fwrite(" ", sizeof(char), 1, f);
    }
    fwrite("\n", sizeof(char), 1, f);
    for(l = 0; l < 94; l++){
        fwrite(&k[l], sizeof(char), 1, f);
        fwrite(" ", sizeof(char), 1, f);
    }

    fclose(f);

    return 0;
}
