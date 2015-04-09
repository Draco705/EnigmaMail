#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){

    FILE *rotors = fopen("rotors.txt", "rb");
    FILE *eMessage = fopen("enigma.txt", "w");
    
    if(argc != 3){
        printf("Error! Not enough arguments!\n");
        return 1;
    }

    FILE *inMess = fopen(argv[1], "r");

    char rotor1[94];
    char rotor2[94];
    char rotor3[94];

    char letter;
    char* input;

    int opt = atoi(argv[2]);

    int i;

    for(i = 0; i < 282; i++){ //Rotor setup
        if(i < 94){
           fscanf(rotors, "%c ", &rotor1[i]);
        }
        if(i >= 94 && i < 188){
            fscanf(rotors, "%c ", &rotor2[i-94]);
        }
        if(i >= 188){
            fscanf(rotors, "%c ", &rotor3[i-188]);
        }
     }
        
    fclose(rotors); //Done with the rotor file at this point
    
    size_t start = ftell(inMess); //Get start of file and file size then reset filepointer to start
    fseek(inMess, 0, SEEK_END);
    size_t length = ftell(inMess);
    fseek(inMess, start, SEEK_SET);

    input = malloc(length);
    if(fgets(input, sizeof(input), inMess) == NULL){
        printf("Read failed!\n");
    }

    int place = 0;

    

    

    return 0;
}
