#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

//Julia Evelyn Chaparro Ferreira
//Matricula: 22351229

typedef struct  chunk{
    int tamanho;
    char tipo[4];
}chunk;

struct  chunk_IHDR{
    
    int width;
    int height;
    char bit_depth;
    char colour_type;
    char compression_methord;
    char filter_method;
    char interlace_method;

}__attribute__((packed));

typedef struct chunk_IHDR chunk_IHDR;

int main(int argc, char *argv[]){
    int cont = 1;
    struct chunk *chunk_1 = malloc(sizeof(struct chunk));
    chunk_IHDR *chunk_ihdr = malloc(sizeof(chunk_IHDR));

    FILE *arquivo_png = fopen(argv[1], "rb");


    fseek(arquivo_png,8,SEEK_CUR);

    while (!feof(arquivo_png)){

        printf("Lendo chunk %d\n",cont);

        fread(chunk_1, sizeof(struct  chunk), 1, arquivo_png);
        printf(" --> Tamanho: %d\n", ntohl(chunk_1->tamanho));
        printf(" --> Tipo: %.4s\n",chunk_1->tipo);
        
        
        if(strcmp(chunk_1->tipo,"IHDR") == 0){

            fread(chunk_ihdr, sizeof(chunk_IHDR), 1, arquivo_png); 
            printf("    --> Largura: %d\n", ntohl(chunk_ihdr->width)); 
            printf("    --> Altura: %d\n", ntohl(chunk_ihdr->height)); 
            fseek(arquivo_png,4,SEEK_CUR);
        }

        else if(strcmp(chunk_1->tipo,"IEND") == 0){
            break;
        }
        else{
            fseek(arquivo_png, ntohl(chunk_1->tamanho)+4,SEEK_CUR);
        }
        cont++;
    }

    free(chunk_1);
    free(chunk_ihdr);

    fclose(arquivo_png);

}


