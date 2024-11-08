#ifndef _GERENCIAMENTO_MEMORIA_H
#define _GERENCIAMENTO_MEMORIA_H

//Protótipo das Estruturas

typedef struct Info45MEM Inf45; //prototipo da informação presente em cada Info da 4-5
typedef struct Arvore45_Memoria Arv45Mem; //Prototipo da Estrutura da árvore 4-5

typedef struct Info45MEM{
    int bloco_inicio, bloco_fim, status;
}Inf45;

typedef struct Arvore45_Memoria{
    Inf45 info1, info2, info3, info4; 
    Arv45Mem *esq, *cent1, *cent2, *cent3, *dir; 
}Arv45Mem;

// Protótipos dos Menus

void menu_principal(); //Menu principal
void sobre();//O sobre
void funcionalidades(); //O submenu das Funcionalidades. 

//Protótipos das Funções da Árvore 4-5







//Protótipo das Funções Intermediarias

























#endif