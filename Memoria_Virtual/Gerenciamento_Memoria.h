#ifndef _GERENCIAMENTO_MEMORIA_H
#define _GERENCIAMENTO_MEMORIA_H

#define LIVRE 0
#define OCUPADO 1

//Protótipo das Estruturas

typedef struct Info45MEM Inf45; //prototipo da informação presente em cada Info da 4-5
typedef struct Arvore45_Memoria Arv45Mem; //Prototipo da Estrutura da árvore 4-5

typedef struct Info45MEM{
    int bloco_inicio, bloco_fim, intervalo, status;
}Inf45;

typedef struct Arvore45_Memoria{
    Inf45 info1, info2, info3, info4; 
    int N_infos; 
    Arv45Mem *esq, *cent1, *cent2, *cent3, *dir; 
}Arv45Mem;

// Protótipos dos Menus

void menu_principal(); //Menu principal
void sobre();//O sobre
void funcionalidades(); //O submenu das Funcionalidades. 

//Protótipos das Funções da Árvore 4-5

Arv45Mem *criar_no_Arv45(Inf45 Info, Arv45Mem *Filho_esq, Arv45Mem *Filho_cen1); 
int ehfolha(Arv45Mem *no); 
Arv45Mem *Adiciona_chave(Arv45Mem *no_atual, Inf45 Info, Arv45Mem *Maior_No); 
Arv45Mem *QuebraNo(Arv45Mem **No, Inf45 Info, Inf45 *Promove, Arv45Mem *Filho); 
Arv45Mem *insereArv45(Arv45Mem **no, Inf45 Info, Inf45 *promove, Arv45Mem **Pai, int *situacao); 

void imprimirArvore45(Arv45Mem *raiz); //Função de impressão



//Protótipo das Funções Intermediarias

void construir_memoria_do_sistema(Arv45Mem **Raiz); 
























#endif
