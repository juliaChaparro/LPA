#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Aluna: Julia Evelyn Chaparro Ferreira - Laboratorio 4 - LPA


struct evento_t {
    double tempo;
    int alvo;
    int tipo;
};
typedef struct evento_t evento_t;

typedef struct  lista_vizinhos_t  lista_vizinhos_t;
typedef struct lista_eventos_t lista_eventos_t;

typedef struct no_t no_t;

struct no_t{
    int id;
    double pos_x;
    double pos_y;
    bool pacote_enviado;
    lista_vizinhos_t* lista_vizinhos;
};


struct lista_eventos_t{
    evento_t* evento;
    lista_eventos_t* prox_evento;
};

struct lista_vizinhos_t{
    int no;
    lista_vizinhos_t* prox_vizinhos;
};

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

bool lista_vizinhos_adicionar(int vizinho, lista_vizinhos_t **lista){
    lista_vizinhos_t* vizinho_novo = malloc(sizeof(lista_vizinhos_t));
    if(vizinho_novo==NULL) return false;
    vizinho_novo->no = vizinho;
    vizinho_novo->prox_vizinhos = *lista;
    *lista = vizinho_novo;
    return true;
}


typedef no_t* grafo_t;

grafo_t grafo_criar(int tam){
    grafo_t grafo = malloc(sizeof(no_t)*tam);
    return grafo;
}

void grafo_atualizar_vizinhos(int tam, double raio_comunicacao, grafo_t grafo){
    for(int i=0; i< tam;i++){
        for(int j = 0;j<tam;j++){
            int dist = sqrt(pow(grafo[i].pos_x - grafo[j].pos_x, 2) + pow(grafo[i].pos_y - grafo[j].pos_y, 2));
            if((j!= i) && (dist < raio_comunicacao)){
                lista_vizinhos_adicionar(grafo[j].id,&grafo[i].lista_vizinhos);
            }
        }
    }
}

//verificar esta funçao....provalmente ta errado
void remover_item_lista_eventos(lista_eventos_t** lista, evento_t* evento){
    lista_eventos_t* aux = *lista;
    if((*lista)->evento == evento){
        (*lista) = (*lista)->prox_evento;
        free(aux);
    }
}

void simulacao_iniciar(lista_eventos_t **lista, grafo_t grafo){

    lista_eventos_t* listas_eventos = *lista;
    evento_t* prim_atual;
    
    while (*lista!=NULL){
        prim_atual = (*lista)->evento;
        *lista = (*lista)->prox_evento;
        no_t* no = &grafo[prim_atual->alvo];
        printf("[%3.6f] Nó %d recebeu pacote.\n",prim_atual->tempo,prim_atual->alvo);
        if(no->pacote_enviado == false){
            lista_vizinhos_t* aux = no->lista_vizinhos;
            while(aux != NULL){
                evento_t* evento_criado =  malloc(sizeof(evento_t));
                
                evento_criado->alvo = aux->no;
                evento_criado->tipo = 1;
                evento_criado->tempo = (prim_atual->tempo+(0.1 + (grafo[aux->no].id * 0.01)));
                lista_eventos_adicionar_ordenado(evento_criado,lista);

                printf("\t--> Repassando pacote para o nó %d ...\n",grafo[aux->no].id);
                aux = aux->prox_vizinhos;
                
            }

            no->pacote_enviado = true;   
        }
    }
}


int main(int argc, char **argv){
    int quant_no;
    float raio;
    int i = 0; 
    FILE* entrada = fopen(argv[1],"r");

    lista_eventos_t* lista= NULL;

    fscanf(entrada,"%d\t%f\n",&quant_no,&raio);

    grafo_t grafo =  grafo_criar(quant_no);
    int id;
    double x;
    double y;

    while(!feof(entrada)){
        fscanf(entrada,"%d\t%lf\t%lf\n",&id, &x,&y);
        grafo[i].id = id;
        grafo[i].pos_x = x;
        grafo[i].pos_y = y;
        i++;

    }
    grafo_atualizar_vizinhos (quant_no,raio,grafo);

    evento_t* evento_novo = malloc(sizeof(evento_t));

    evento_novo->alvo = 0;
    evento_novo->tipo = 1;
    evento_novo->tempo = 1;
    lista_eventos_adicionar_ordenado(evento_novo,&lista);
    simulacao_iniciar(&lista,grafo);
}