#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <arpa/inet.h>

typedef struct {
    uint8_t daddr[6]; // Endereco MAC de destino
    uint8_t saddr[6]; // Endereco MAC de origem (source)
    uint16_t protocol; // Protocolo da próxima camada (IP!)
} ethernet_hdr_t;


typedef struct {
    uint8_t hdr_len:4, // Tamanho do Cabeçalho,
    version:4; // Versão do IP
    uint8_t tos; // Tipo de serviço
    uint16_t tot_len; // Tamanho total do IP
    uint16_t id; // Id do pacote
    uint16_t frag_off; // Fragmentado?
    uint8_t ttl; // Tempo de vida
    uint8_t protocol; // Protocolo próxima camada (TCP!)
    uint16_t check; // Checksum
    uint8_t saddr[4]; // Endereço IP de origem
    uint8_t daddr[4]; // Endereço IP de destino
} ip_hdr_t;


typedef struct {
    uint16_t sport; // Porta TCP de origem
    uint16_t dport; // Porta TCP de destino
    uint32_t seq; // Sequência
    uint32_t ack_seq; // Acknowledgement
    uint8_t reservado:4, // Não usado
    hdr_len:4; // Tamanho do cabecalho
    uint8_t flags; // Flags do TCP
    uint16_t window; // Tamanho da janela
    uint16_t check; // Checksum
    uint16_t urg_ptr; // Urgente
} tcp_hdr_t;


int main(int argc, char *argv[] ){

    ethernet_hdr_t* mac = malloc(sizeof(ethernet_hdr_t));
    ip_hdr_t* ip = malloc(sizeof(ip_hdr_t));
    tcp_hdr_t* tcp = malloc(sizeof(tcp_hdr_t));

    FILE *arquivo_aberto = fopen(argv[1], "rb");

    while(!feof(arquivo_aberto)){

        fread(mac, sizeof(ethernet_hdr_t), 1, arquivo_aberto);
        printf("Lendo Ethernet ..\n");

        printf("--> MAC de Origem: ");
        for(int i = 0; i<6;i++){
            printf("%02x ", mac->saddr[i]);
        }
        printf("\n");
        printf("--> MAC de Destino: ");
        for(int j = 0; j<6;j++){
            printf("%02x ",mac->daddr[j]);
        }
        printf("\n");

        fread(ip, sizeof(ip_hdr_t), 1, arquivo_aberto);

        printf("Lendo IP ..\n");

        int tamando_Cabesalho_ip = ip->hdr_len * 4;

        printf("--> Versão do IP: %d\n", ip->version); 
        printf("--> Tamanho do cabeçalho: %d bytes\n", tamando_Cabesalho_ip);
        printf("--> Tamanho do pacote: %d bytes\n", ntohs(ip->tot_len));

        printf("--> Endereço IP de Origem: ");
        for(int k=0;k<4;k++){
            printf("%u ", ip->saddr[k]);
        }

        printf("\n");

        printf("--> Endereço IP de Destino: ");
        for(int k=0;k<4;k++){
            printf("%u ", ip->daddr[k]);
        }
        printf("\n");

        int passou = tamando_Cabesalho_ip - sizeof(ip_hdr_t);
        fseek(arquivo_aberto,passou,SEEK_CUR);
        
        fread(tcp, sizeof(tcp_hdr_t), 1, arquivo_aberto);
        printf("Lendo TCP .. \n");

        printf("--> Porta de Origem: %u\n",ntohs(tcp->sport));
        printf("--> Porta de Destino: %u\n",ntohs(tcp->dport));

        int tamando_Cabesalho_tcp = tcp->hdr_len * 4;  
        printf("--> Tamanho do cabeçalho: %d bytes\n",tamando_Cabesalho_tcp);

        int passou_tcp = tamando_Cabesalho_tcp - sizeof(tcp_hdr_t);
        fseek(arquivo_aberto,passou_tcp,SEEK_CUR);


        int tam_dados = ntohs(ip->tot_len) - (ip->hdr_len*4) - (tcp->hdr_len*4);

        printf("Lendo Dados (HTTP) ..\n");

        printf("--> Tamanho dos dados: %d bytes\n",tam_dados);

        int caractere;
        while ((caractere = fgetc(arquivo_aberto)) != EOF) {
            printf("%c", caractere);
        }
    
    }

    free(mac);
    free(tcp);
    free(ip);

    fclose(arquivo_aberto);

}