#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// Aluna: Julia Evelyn Chaparro Ferreira - Laboratorio 2 - LPA

int tabela_hash_tam;

struct pessoa_t{
    char nome[51];
    long long int cpf;
    int idade;
};
typedef struct pessoa_t pessoa_t;

typedef struct lista_pessoas_t lista_pessoas_t;

struct lista_pessoas_t{
    pessoa_t* pessoa;
   lista_pessoas_t* prox_pessoa;
};

// Esta funcao vai adicionar uma pessoa, para saber se  foi adicionado ela vai retonat true caso contrario vai retonar false
bool lista_pessoas_adicionar(pessoa_t *pessoa, lista_pessoas_t **lista){
    lista_pessoas_t* pessoa_nova = malloc(sizeof(lista_pessoas_t));
    if(pessoa_nova == NULL) return false;
    pessoa_nova->pessoa = pessoa;
    pessoa_nova->prox_pessoa = *lista;
    *lista = pessoa_nova;
    return true;

}

//esta funcao vao imprimir de forma correta para o terminnal
void imprimir_pessoa(pessoa_t* pessoa){
    assert(pessoa != NULL);
    printf("-%s\t%lld\t%d\n",pessoa->nome,pessoa->cpf,pessoa->idade);
}

//esta funao vai colocar na tela todos as pessoas listadas na lista no terminal
void lista_pessoas_listar(lista_pessoas_t *lista){
    while(lista != NULL){
        imprimir_pessoa(lista->pessoa);
        lista = lista->prox_pessoa;
    }
}

typedef lista_pessoas_t** tabela_hash_t;

tabela_hash_t tabela_hash_pessoas_criar(){
    tabela_hash_t lista_hash = malloc(sizeof(lista_pessoas_t*)*tabela_hash_tam);
    for(int i=0; i < tabela_hash_tam;i++){
        lista_hash[i] = NULL;
    }
    return lista_hash;
}

// esta funcao vai calcular a funcao hash
int tabela_hash_pessoas_funcao(pessoa_t *pessoa){
    int calculo = pessoa->cpf % tabela_hash_tam;
    return calculo;
}

//esta funcao vai adicionar na tabala hash e retonar true se foi colocado entro da tabela 
bool tabela_hash_pessoas_adicionar(pessoa_t *pessoa, tabela_hash_t tabela_hash){
    int pos = tabela_hash_pessoas_funcao(pessoa);
    return lista_pessoas_adicionar(pessoa,&tabela_hash[pos]);
}


//esta funcao vai imprimir de forma organizada a tabela hash e os item que estarem dentro dela
void tabela_hash_pessoas_listar(tabela_hash_t tabela_hash){
    int i = 0;
    for(i =0; i< tabela_hash_tam; i++){
        printf("POSIÇÃO %d DA TABELA HASH:\n",i);
        lista_pessoas_listar(tabela_hash[i]);
    }
}


int main(int argc, char **argv){

    sscanf(argv[1],"%d",&tabela_hash_tam); // vai pegar o primiro argumento que passar pelo terminal que seria o tamanho da tabela

    tabela_hash_t tab = tabela_hash_pessoas_criar();//vai criar a tabela 

    FILE* arquivo_de_entrada = fopen(argv[2],"r");// vai abrir o arquivo e ler o que estiver dentro

    while(!feof(arquivo_de_entrada)){
        pessoa_t* p = malloc(sizeof(pessoa_t));
        fscanf(arquivo_de_entrada, "%50[^\t]\t%lld\t%d\n", p->nome, &p->cpf, &p->idade);
        tabela_hash_pessoas_adicionar(p,tab);
    }

    tabela_hash_pessoas_listar(tab);// vai imprirmir os itens da tabela hash
}


