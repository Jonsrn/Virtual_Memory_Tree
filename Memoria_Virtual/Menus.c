#include <stdio.h> 
#include <stdlib.h> 
#include "Gerenciamento_Memoria.h"


void menu_principal(){
    printf("Bem vindo ao Gerenciamento da Memória\n"); 
    printf("[1]-Preencher a Memória\n"); 
    printf("[2]-Funcionalidades\n"); 
    printf("[3]-Sobre\n"); 
    printf("[0]-Sair\n"); 
}

void sobre(){
    printf("Trabalho desenvolvido por: Jonathan dos Santos Barbosa\n"); 
}

void funcionalidades(){
    printf("Bem vindo ao Menu de Funcionalidades\n");
    printf("[1]-Alocar Espaço na memória para uma aplicação\n"); 
    printf("[2]-Liberar Espaço Alocado na Memória\n"); 
    printf("[0]-Sair\n"); 
}


