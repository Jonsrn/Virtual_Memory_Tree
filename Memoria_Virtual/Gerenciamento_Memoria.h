#ifndef _GERENCIAMENTO_MEMORIA_H
#define _GERENCIAMENTO_MEMORIA_H

#define LIVRE 0
#define OCUPADO 1
#define APAGAR 2
#define MANTER 3

//Protótipo das Estruturas

typedef struct Info45MEM Inf45; //prototipo da informação presente em cada Info da 4-5
typedef struct Arvore45_Memoria Arv45Mem; //Prototipo da Estrutura da árvore 4-5

typedef struct Info45MEM{
    int bloco_inicio, bloco_fim, intervalo, status, status_apagar;
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

//Protótipo das funções de exibição de status

void situacao_construcao_memoria(int situacao); 
void situacao_alocacao_memoria(int situacao);





//Protótipos das Funções da Árvore 4-5

Arv45Mem *criar_no_Arv45(Inf45 Info, Arv45Mem *Filho_esq, Arv45Mem *Filho_cen1); 
int ehfolha(Arv45Mem *no); 
Arv45Mem *Adiciona_chave(Arv45Mem *no_atual, Inf45 Info, Arv45Mem *Maior_No); 
Arv45Mem *QuebraNo(Arv45Mem **No, Inf45 Info, Inf45 *Promove, Arv45Mem *Filho); 
Arv45Mem *insereArv45(Arv45Mem **no, Inf45 Info, Inf45 *promove, Arv45Mem **Pai, int *situacao); 

void imprimirArvore45(Arv45Mem *raiz); //Função de impressão



//Protótipo das Funções Intermediarias

void construir_memoria_do_sistema(Arv45Mem **Raiz); //Função que monta o dataset
void alocar_memoria_para_programa(Arv45Mem **Raiz); //Função auxiliar que cuida de alocar memória para uma "aplicação", se tiver espaço disponivel
int alocar_memoria(Arv45Mem *Raiz, int qtd_blocos); //Função de alocação de memória
Arv45Mem *atualizar_bloco(Arv45Mem *Raiz, int qtd_blocos, int operacao, int localizacao_info, int *situacao); //Função que atualiza os blocos, seja inserção ou remoção;
int ajustando_os_intervalos(Arv45Mem *Raiz, Inf45 **bloco_anterior, int opcao); 

























#endif
