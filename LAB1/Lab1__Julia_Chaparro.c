#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// Aluna: Julia Evelyn Chaparro Ferreira - Laboratorio 1 - LPA 

struct evento_t {
    double tempo;
    int alvo;
    int tipo;
};
typedef struct evento_t evento_t;

typedef struct lista_eventos_t lista_eventos_t;

struct lista_eventos_t{
    evento_t* evento;
    lista_eventos_t* prox_evento;
};



bool lista_eventos_adicionar_inicio(evento_t *evento, lista_eventos_t **lista){
    lista_eventos_t *item_novo = malloc(sizeof(lista_eventos_t)); 
    if (item_novo == NULL) return false; 
    item_novo->evento = evento; 
    item_novo->prox_evento = *lista; 
    *lista = item_novo;
    return true;
}


bool lista_eventos_adicionar_fim(evento_t *evento, lista_eventos_t **lista){
    if(evento == NULL) return false;
    lista_eventos_t* item = malloc(sizeof(lista_eventos_t));
    item->evento = evento;
    if (*lista==NULL){
        *lista = item;
        item->prox_evento = NULL;
    }
    else{
        lista_eventos_t* atual = *lista;
        while(atual->prox_evento != NULL){
            atual = atual->prox_evento;
        }
        atual->prox_evento = item;
        item->prox_evento = NULL;
    }
    return true;
}

bool lista_eventos_adicionar_ordenado(evento_t *evento, lista_eventos_t **lista){
    if(evento == NULL) return false;
    lista_eventos_t* item_novo = malloc(sizeof(lista_eventos_t));
    item_novo->evento = evento;
    lista_eventos_t* atual = *lista;
    
    if(atual == NULL){
        *lista = item_novo;
        item_novo->prox_evento = NULL;
        return true;
    }
    if(evento->tempo < atual->evento->tempo){
        item_novo->prox_evento = atual;
        *lista = item_novo;
    }else{
        while(atual->prox_evento != NULL && atual->prox_evento->evento->tempo < evento->tempo){
            atual=atual->prox_evento;
        }
        lista_eventos_t* aux = atual->prox_evento;        
        atual->prox_evento = item_novo;
        item_novo->prox_evento = aux;   
    }
    return true;
}

//funcao que vai deixar de uma formar correta quando for mostrar para o usuaria.
void imprimir_evento(evento_t* evento){
    assert(evento != NULL);
    printf("Tempo do evento: %3.6f\nAlvo do evento: %d\nTipo do evento: %d\n",evento->tempo,evento->alvo,evento->tipo);
}

void lista_eventos_listar(lista_eventos_t *lista){
    assert(lista != NULL); 
    while(lista != NULL){
        imprimir_evento(lista->evento);
        lista = lista->prox_evento;
    }
}

int main(int argc,char *argv[]){
    FILE* arquivo_de_entrada = fopen(argv[1],"r");
    lista_eventos_t* lista;
    while(!feof(arquivo_de_entrada)){
        evento_t* evento_novo = malloc(sizeof(evento_t));
        fscanf(arquivo_de_entrada,"%lf\t%d\t%d\n",&evento_novo->tempo,&evento_novo->alvo,&evento_novo->tipo);
        lista_eventos_adicionar_ordenado(evento_novo,&lista);
    }
    lista_eventos_listar(lista);
}