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
    char inchar;
    int i;

    for(i = 0; i < 282; i++){ //Rotor setup
        if(i < 94){
           inchar = fgetc(rotors);
           rotor1[i] = inchar;
        }
        if(i >= 94 && i < 188){
            inchar = fgetc(rotors);
            if(inchar == '\n'){
                inchar = fgetc(rotors); //step one more character if fgetc grabs a newline
            }
            rotor2[i-94] = inchar;

        }
        if(i >= 188){
            inchar = fgetc(rotors);
            if(inchar == '\n'){
                inchar = fgetc(rotors); //step one more character if fgetc grabs a newline
            }
            rotor3[i-188] = inchar;
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
        if((int)input[i] < 32 || (int)input[i] > 126){ //ignore any characters not inside the ASCII alphabet range
	      fputc(input[i], decrypt);
          i++;
          continue;
        }
        
        printf("Orig: %c     ", input[i]);
        letter = (int)input[i] - (int)rotor3[j];
	printf("R3: %d,    ", letter);
        if(letter < 32){
            letter = letter + 126;
	    printf("Under 32, ");
	    if(letter > 126){
		letter = letter - 32;
	    }
	}

        letter = letter - (int)rotor2[j];
	printf("R2: %d,    ", letter);
        if(letter < 32){
            letter = letter + 126;
	    printf("Under 32, ");
	    if(letter > 126){
		letter = letter - 32;
	    }
        }

        letter = letter - (int)rotor1[j];
	printf("R1: %d,    ", letter);
        if(letter < 32){
            letter = letter +126;
	    printf("Under 32, ");
	    if(letter > 126){
		letter = letter - 32;
	    }
        }

        printf("Final: %c,    ", (char)letter);
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
