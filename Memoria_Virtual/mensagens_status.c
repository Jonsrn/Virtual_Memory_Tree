#include <stdio.h>
#include "Gerenciamento_Memoria.h"

void situacao_construcao_memoria(int situacao){
    if(situacao == 0){
        printf("A operação falhou, pois a Memória já foi construída.\n");
    }
    if(situacao == 1){
        printf("Memória alocada com sucesso!\n"); 
    }
    if(situacao == 2){
        printf("A operação falhou porque houve falha na alocação da Inserção\n"); 
    }
}

void situacao_alocacao_memoria(int situacao){
    if(situacao == 0){
        printf("A operação falhou porque não há dataset alocado na árvore\n"); 
    }
    if(situacao == 1){
        printf("Alocação da memória feita com sucesso\n"); 
    }
    if(situacao == 2){
        printf("A operação falhou, pois não foi possivel realizar a exclusão da Info desocupada\n"); 
    }
    if(situacao == 3){
        printf("A operação falhou, pois houve falha na criação de um novo bloco\n"); 
    }
    if(situacao == 4){
        printf("A operação falhou, pois não há espaço disponivel suficiente na memória\n"); 

    }
}

void situacao_desalocacao_memoria(int situacao){
    if(situacao == 0){
       printf("A operação falhou porque não há dataset alocado na árvore\n");  
    }
    if(situacao == 1){
        printf("Desalocação da memória feita com sucesso\n"); 
    }

} 
