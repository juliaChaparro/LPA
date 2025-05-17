#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Julia Evelyn Chaparro Ferreira 

struct zip_file_hdr
{
    int signature;
    short version;
    short flags;
    short compression;
    short mod_time;
    short mod_date;
    int crc;
    int compressed_size;
    int uncompressed_size;
    short name_length;
    short extra_field_length;

} __attribute__((packed));

int main(int argc, char *argv[]){
    int cont = 0;
    FILE *zip_file = fopen(argv[1], "rb");
    struct zip_file_hdr *file_hdr = malloc(sizeof(struct zip_file_hdr));
    
    while (!feof(zip_file)){

        fread(file_hdr, sizeof(struct zip_file_hdr), 1, zip_file);
        
        if(file_hdr->signature == 0x04034b50){

            char* nome_arq = malloc(file_hdr->name_length+1);

            fread(nome_arq,file_hdr->name_length,1,zip_file);
            
            nome_arq[file_hdr->name_length] = '\0';
            printf("Arquivo %d\n",cont);

            printf(" --> Nome do Arquivo: %s\n", nome_arq);
            printf(" --> Assinatura: %.8x\n", file_hdr->signature); // Imprime hexadecimal
            printf(" --> Tamanho Compactado: %d\n", file_hdr->compressed_size);
            printf(" --> Tamanho Nao Compactado: %d\n", file_hdr->uncompressed_size);
            cont++;
            free(nome_arq);
            fseek(zip_file, file_hdr->extra_field_length + file_hdr->compressed_size, SEEK_CUR);
        }
        else{
            exit(1);
        }
    }
    free(file_hdr);
    fclose(zip_file);
}