#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){

    FILE *rotors = fopen("rotors.txt", "rb");
    FILE *eMessage = fopen("encryptedMessage.txt", "w");
    
    if(argc != 2){
        printf("Error! Not enough arguments!\n");
        return 1;
    }

    FILE *inMess = fopen(argv[1], "r"); //Open file for encryption

    char rotor1[94];
    char rotor2[94];
    char rotor3[94];

    int letter;

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

    char input[length];
    if(fread(input, sizeof(input) + 1, 1, inMess) < 0){
        printf("Read failed!\n");
    }

    int j = 0; //index for the rotors

    for(i = 0; i < (int)length; i++){
        if((int)input[i] < 32 || (int)input[i] > 126){
	  fputc(input[i], eMessage);
          i++;
        }

        letter = (int)input[i] + (int)rotor1[j];
	printf("R1: %d, ", letter);
        if(letter > 126){
            letter = (letter-126);
	    printf("Over 126, ");
	    if(letter < 32){
	        letter = letter + 32;
	    }
	}

        letter = letter + (int)rotor2[j];
	printf("R2: %d, ", letter);
        if(letter > 126){
            letter = (letter-126);
            printf("Over 126, ");
	    if(letter < 32){
	        letter = letter + 32;
	    }
        }

        letter = letter + (int)rotor3[j];
	printf("R3: %d, ", letter);
        if(letter > 126){
            letter = (letter - 126);
	    printf("Over 126, ");
            if(letter < 32){
	        letter = letter + 32;
	    }
       }

        printf("%c, ", (char)letter);
        printf("%d\n", letter);

        j++;
        if(j == 94){
            j = 0;
        }

        fputc(letter, eMessage);

    }

    fclose(eMessage);

    return 0;
}
