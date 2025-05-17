#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <crypt.h>

//Julia Evelyn Chaparro Ferreira


/**
* @brief Verifica se uma senha em texto é a mesma de uma senha criptografada.
*
* @param senhaTeste Senha em texto que queremos ver se corresponde à senha criptografada.
* @param senhaCriptografada Senha criptografada como no arquivo /etc/shadow.
* @return int Retorna 0 (zero) se as senhas forem iguais. Outro valor, caso contrário.
*/

int verificaSenha(char* senhaTeste, char* senhaCriptografada) {
    char *senhaTesteCriptografada = crypt(senhaTeste, senhaCriptografada);
    return strcmp(senhaTesteCriptografada, senhaCriptografada);
}


char *senhaCriptografada = "$6$l2xE4w9twgjtnZBz$9YK9krslZFraLffy5VNiahAfT.xZNvB54"
 "j91DMCMIoVFvj335ZKxb11qgVMn.KzU2GqVPPyS2FTBqPSciYq761"; //senha dos numeros de tamando 5

int tamanhoMaximo = 5;

char caracteres [] = {'a','b','c'};

int numeros [] = {'0','1','2','3','4','5','6','7','8','9'};

char letras [] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

int tamanho_carac = sizeof(caracteres)/sizeof(caracteres[0]);

int tamanho_nun = sizeof(numeros)/sizeof(numeros[0]);

int tamanho_letras = sizeof(letras)/sizeof(letras[0]);


bool gerenrateALLPassword(char pwd[],int pos, int siz){ 

    if(pos < siz){
        for(int i=0;i<tamanho_nun;i++){
            pwd[pos] = numeros[i];
            if (gerenrateALLPassword(pwd, pos+1,siz)){
                return true;
            }
        }
    }
    else{
        if(!verificaSenha(pwd,senhaCriptografada)){
            printf("%s -> sim! Senha encontrada! \n",pwd);
            return true;

        }else{
            printf("%s -> Nao \n",pwd);
            return false;
        }
            
        
    }
    return false;
}

void main() {
    char pwd[tamanhoMaximo+1]= {};
    for (int siz = 1; siz <= tamanhoMaximo; siz++) {
        gerenrateALLPassword(pwd, 0, siz);
    }
}





