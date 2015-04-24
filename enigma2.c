#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){

    FILE *rotors = fopen("rotors.txt", "rb");
    FILE *decrypt = fopen("decrypt.txt", "w"); //Opens the decryption file for writing the actual message
    FILE *adjust = fopen("adjust.txt", "r");

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
    int adjuster[length];
    for (i = 0; i < length; ++i)
    {
        adjuster[i] = 0;
    }

    while(i < (int)length){
        fscanf(adjust, "%d ", &adjuster[i]);
        //printf("%d, ", adjuster[i]);
        //printf("i is: %d", i);
        ++i;
    }

    printf("len is %zd", length);

    for(i = 0; i < length; ++i){
        printf("%d, ", adjuster[i]);
    }

    fclose(adjust);

    char letter;

    if(fread(input, sizeof(input) + 1, 1, encMess) < 0){
        printf("Read failed!\n");
    }

    int j = 0; //index for the rotors
    int orig;
    for(i = 0; i < (int)length; i++){
        if((int)input[i] < 32 || (int)input[i] > 126){ //ignore any characters not inside the ASCII alphabet range
	      fputc(input[i], decrypt);
          i++;
          continue;
        }

        printf("Before first shift: %d, ", adjuster[i]);
        orig = adjuster[i];
        adjuster[i] = adjuster[i] >> 1;
        printf("%u, ", adjuster[i]);
        
        printf("Orig: %c     ", input[i]);
        letter = (int)input[i] - (int)rotor3[j];
	    printf("R3: %d,    ", letter);
        if((adjuster[i] % 2) == 1){
            letter = letter - 32;
            adjuster[i] = adjuster[i] >> 1;
            printf("Adjust 6: %u", adjuster[i]);
        }
        else{adjuster[i] = adjuster[i] >> 1;}
	    if((adjuster[i] % 2) == 1){
            letter = letter + 126;
            printf("Adjust 5: %u", adjuster[i]);
	    }
        else{adjuster[i] = adjuster[i] >> 1;}

        letter = letter - (int)rotor2[j];
	printf("R2: %d,    ", letter);
        if((adjuster[i] % 2) == 1){
            letter = letter - 32;
            adjuster[i] = adjuster[i] >> 1;
            printf("Adjust 4: %u", adjuster[i]);
        }
        else{adjuster[i] = adjuster[i] >> 1;}
	    if((adjuster[i] % 2) == 1){
            letter = letter + 126;
            adjuster[i] = adjuster[i] >> 1;
            printf("Adjust 3: %u", adjuster[i]);
	    }
        else{adjuster[i] = adjuster[i] >> 1;}
        

        letter = letter - (int)rotor1[j];
	printf("R1: %d,    ", letter);
        if((adjuster[i] % 2) == 1){
            letter = letter - 32;
	        adjuster[i] = adjuster[i] >> 1;
            printf("Adjust 2: %u", adjuster[i]);
        }
        else{adjuster[i] = adjuster[i] >> 1;}
	    if((adjuster[i] % 2) == 1){
	        letter = letter + 126;
            adjuster[i] = adjuster[i] >> 1;
            printf("Adjust 1: %u", adjuster[i]);
	    }
        else{adjuster[i] = adjuster[i] >> 1;}
        

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
