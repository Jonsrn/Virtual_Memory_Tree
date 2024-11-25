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
    int bloco_inicio, bloco_fim, intervalo, status, status_apagar, tam_total;
}Inf45;

typedef struct Arvore45_Memoria{
    Inf45 info1, info2, info3, info4; 
    int N_infos; 
    Arv45Mem *esq, *cent1, *cent2, *cent3, *dir; 
}Arv45Mem;

// Protótipos dos Menus

void menu_principal(); //Menu principal
void sobre();//O sobre, o criador do trabalho basicamente. kkkk
void funcionalidades(); //O submenu das Funcionalidades. 

//Protótipo das funções de exibição de status

void situacao_construcao_memoria(int situacao); //informa o status final da operação de construção da memória
void situacao_alocacao_memoria(int situacao); //Informa o status final da operação da "alocação" da memória
void situacao_desalocacao_memoria(int situacao); //Informa o status final da operação de "liberação" da memória





//Protótipos das Funções da Árvore 4-5

Arv45Mem *criar_no_Arv45(Inf45 Info, Arv45Mem *Filho_esq, Arv45Mem *Filho_cen1); //função base de  criação do Nó
int ehfolha(Arv45Mem *no); //Função auxiliar que identifica que estou em uma folha
Arv45Mem *Adiciona_chave(Arv45Mem *no_atual, Inf45 Info, Arv45Mem *Maior_No); //função que adiciona novas infos em um nó que não está totalmente cheio 
Arv45Mem *QuebraNo(Arv45Mem **No, Inf45 Info, Inf45 *Promove, Arv45Mem *Filho); //Função que Quebra o Nó e separa as infos, promovendo o meio
Arv45Mem *insereArv45(Arv45Mem **no, Inf45 Info, Inf45 *promove, Arv45Mem **Pai, int *situacao); //Função base de inserção na árvore 4-5
void imprimirArvore45(Arv45Mem *raiz); //Função base de impressão
void imprimirInfo(Inf45 info); //imprime informações detalhadas de cada Info
int percorrer_recuperar_Infos(Arv45Mem *Raiz, Inf45 ***vetor_recuperado, int *numero_infos); //Essa função percorre a árvore original, e faz uma cópia, excluindo as INFOS com a TAG APAGAR
void liberarArvore45(Arv45Mem **Raiz); //Libera a arvore 4-5
int eh_ultimo(Arv45Mem *Raiz, int localizacao_info); //Função pra saber se estou no ultimo bloco









//Protótipo das Funções Intermediarias

void construir_memoria_do_sistema(Arv45Mem **Raiz); //Função que monta o dataset
void alocar_memoria_para_programa(Arv45Mem **Raiz); //Função auxiliar que cuida de alocar memória para uma "aplicação", se tiver espaço disponivel
void desalocar_memoria_sistema(Arv45Mem **Raiz); //Função auxiliar que cuida de liberar a memória
int alocar_memoria(Arv45Mem *Raiz, int qtd_blocos); //Função de alocação de memória
int desalocar_memoria(Arv45Mem *Raiz, int qtd_blocos); //Função de desalocação de memória
Arv45Mem *atualizar_bloco(Arv45Mem *Raiz, int qtd_blocos, int operacao, int localizacao_info, int *situacao); //Função que atualiza os blocos, seja inserção ou remoção;
int ajustando_os_intervalos(Arv45Mem *Raiz, Inf45 **bloco_anterior, int opcao); //função que passa um "pente-fino" garantindo que não tenha espaços em branco entre os intervalos após as operações. 
int agrupar_infos(Arv45Mem *Raiz, Inf45 **info_anterior); //Passa verificando se há blocos adjacentes iguais (desconsiderando os que estão na pendencia de serem apagados)























#endif
