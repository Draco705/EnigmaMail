#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){

    FILE *rotors = fopen("rotors.txt", "rb");
    FILE *decrypt = fopen("decrypt.txt", "w"); //Opens the decryption file for writing the actual message

    if(argc != 2){
        printf("Error! Not enough arguments!\n");
        return 1;
    }

    FILE *encMess = fopen(argv[1], "r");

    char rotor1[94], rotor2[94], rotor3[94];

    int i;

    for(i = 0; i < 282; i++){
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

    fclose(rotors);

    size_t start = ftell(encMess);
    fseek(encMess, 0, SEEK_END);
    size_t length = ftell(encMess);
    fseek(encMess, start, SEEK_SET);

    char input[length];
    char letter;

    if(fread(input, sizeof(input) + 1, 1, encMess) < 0){
        printf("Read failed!\n");
    }

       int j = 0; //index for the rotors

    for(i = 0; i < (int)length; i++){
        if((int)input[i] < 32 || (int)input[i] > 126){
	  fputc(input[i], decrypt);
          i++;
        }

        letter = (int)input[i] - (int)rotor1[j];
	printf("R1: %d, ", letter);
        if(letter < 32){
            letter = letter + 126;
	    printf("Under 32, ");
	    if(letter > 126){
		letter = letter - 32;
	    }
	}

        letter = letter - (int)rotor2[j];
	printf("R2: %d, ", letter);
        if(letter < 32){
            letter = letter + 126;
	    printf("Under 32, ");
	    if(letter > 126){
		letter = letter - 32;
	    }
        }

        letter = letter - (int)rotor3[j];
	printf("R3: %d, ", letter);
        if(letter < 32){
            letter = letter +126;
	    printf("Under 32, ");
	    if(letter > 126){
		letter = letter - 32;
	    }
        }

        printf("%c, ", (char)letter);
        printf("%d\n", letter);

        j++;
        if(j == 94){
            j = 0;
        }

        fputc(letter, decrypt);

    }

    fclose(decrypt);

    return 0;
}
