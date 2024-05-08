// Modifies the volume of an audio file
//foi pesquisado pela internet - NÃO
//teve algum problema de erro - eu apenas havia me esquecido de ter copiado os dados de cabeçalho do WAV para o outro arquivo.
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef uint8_t HEADER; //HEADER + FIRULAS * 2
typedef uint16_t VALUEWAV;//bytes

int main(int argc, char *argv[])
{
    VALUEWAV bufferwav;
    HEADER headerwav[44];
    //criando o cabeçalho
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    if (factor < 0) {
        printf("Error, fatores negativos não são permitidos.");
        return 1;
    }
    // TODO: Copy header from input file to output file
    fread(&headerwav,sizeof(HEADER),44,input);
    fwrite(&headerwav,sizeof(HEADER),44,output);

    // TODO: Read samples from input file and write updated data to output file
    while (fread(&bufferwav,sizeof(VALUEWAV),1,input)>0){
        bufferwav *= factor;
        fwrite(&bufferwav,sizeof(VALUEWAV),1,output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
