#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


// Aluna: Julia Evelyn Chaparro Ferreira - Laboratorio 3 - LPA


typedef struct no_rede no_rede;

typedef struct  lista_vizinhos_t  lista_vizinhos_t;
struct no_rede{
    int id;
    double pos_x;
    double pos_y;
    lista_vizinhos_t* lista_vizinhos;
};



struct lista_vizinhos_t{
    int no;
    lista_vizinhos_t* prox_vizinhos;
};


bool lista_vizinhos_adicionar(int vizinho, lista_vizinhos_t **lista){
    lista_vizinhos_t* vizinho_novo = malloc(sizeof(lista_vizinhos_t));
    if(vizinho_novo==NULL) return false;
    vizinho_novo->no = vizinho;
    vizinho_novo->prox_vizinhos = *lista;
    *lista = vizinho_novo;
    return true;
}

void imprimir_vizinho(int no){
    printf(" %d",no);
}

void lista_vizinhos_imprimir(lista_vizinhos_t *lista){
    lista_vizinhos_t* lista_nova = lista; 

    while(lista_nova !=NULL){
        imprimir_vizinho(lista_nova->no);
        lista_nova = lista_nova->prox_vizinhos;
    }
}

typedef no_rede* grafo_t;


grafo_t grafo_criar(int tam){
    grafo_t grafo = malloc(sizeof(no_rede)*tam);
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

void grafo_imprimir(int tam, grafo_t grafo){
    
    for(int i = 0; i< tam; i++){
        printf("NO %d:",i);
        lista_vizinhos_imprimir(grafo[i].lista_vizinhos);
        printf("\n");

    }

}

int main(int argc, char **argv){
    int quant_no;
    float raio;
    int i = 0; 
    FILE* entrada = fopen(argv[1],"r");

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
    grafo_imprimir(quant_no,grafo);

}

