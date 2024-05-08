#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//Objetivo - recuperar arquvios perdidos no cartão de memória
//resposta foi pega na internet - sim
//motivo do erro - eu pensei que as assinatura de um arquivo JPEG começava em qualquer lugar do bloco de 512 bytes
//mas na vdd todos eles começam nos primeiros 4 bytes de cada bloco de código lido do arquivo
typedef uint8_t BYTE;

int find_start(BYTE buffer[512]);

int main(int argc, char *argv[])//EOF end of file
{


    BYTE buffer[512];//coletar e analisar os bytes para encotrar os início de um JPEG
    BYTE jpgresp[] = {0xff,0xd8,0xff,0xe0};
    char jpgname[8];
    int jpgquant = 0;
    BYTE quatro[4];
    //abrindo os arquivos
    FILE *f = fopen("card.raw","r");
    FILE *outrof;
    int pos = 0;
    if (f == NULL){
        printf("Error ao abrir a imagem !!!");
        fclose(f);
        return 1;
    }
    while (fread(&buffer,sizeof(buffer),1,f) > 0){
            for (int j = 0; j <4;j++){
                quatro[j] = buffer[j];
            }

            //quatro[3] = (firstfour[3] >> 4) << 4;
            //se estiver encontrado
            if ((quatro[0] == jpgresp[0]) && (quatro[1] == jpgresp[1]) && (quatro[2] == jpgresp[2]) && ((quatro[3] & 0xf0) == jpgresp[3]))
            //if (memcmp(firstfour,jpgresp,sizeof(jpgresp))==0)
            {
                //arquivo encontrado !!!!
                //verificar se está aberto
                if (outrof == NULL)
                {//está fechado ? logo
                    sprintf(jpgname, "%03d.jpg", jpgquant);
                    outrof = fopen(jpgname, "a");
                    fwrite(&buffer, sizeof(buffer), 1, outrof);//escrever o que foi encontrado aqui
                }
                else//na vdd ele já está aberto
                {
                    fclose(outrof);
                    jpgquant++;
                    sprintf(jpgname,"%03d.jpg",jpgquant);
                    outrof = fopen(jpgname,"a");
                    fwrite(&buffer,sizeof(buffer),1,outrof);
                }
            }
            else
            {//caso não encontre
                if (outrof != NULL)
                {//já estiver aberto
                    fwrite(&buffer,sizeof(buffer),1,outrof);
                }

            }
        }

    //fechando os arquivos
    fclose(f);
    fclose(outrof);

    return 0;
}

int find_start(BYTE buffer[512]){
    for (int i = 0; i < buffer[512]; i++){
        if (buffer[i] != 0xff){//255
            continue;
        }
        if (buffer[i+1] != 0xd8){
        }
        if (buffer[i+2] != 0xff){
            continue;
        }
        if ((buffer[i+3] & 0xf0) != 0xe0){
            return i;
        }
    }
    return -1;
}
