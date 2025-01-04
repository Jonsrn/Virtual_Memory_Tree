#ifndef _GERENCIAMENTO_MEMORIA_H
#define _GERENCIAMENTO_MEMORIA_H

#define LIVRE 0
#define OCUPADO 1
#define APAGAR 2
#define MANTER 3

//Protótipo das Estruturas

typedef struct Info23MEM Inf23; //prototipo da informação presente em cada Info da 2-3
typedef struct Arvore23_Memoria Arv23Mem; //Prototipo da Estrutura da árvore 2-3

typedef struct Info23MEM{
    int bloco_inicio, bloco_fim, intervalo, status, status_apagar, tam_total;
}Inf23;

typedef struct Arvore23_Memoria{
    Inf23 info1, info2; 
    int N_infos; 
    Arv23Mem *esq, *cent, *dir; 
}Arv23Mem;

// Protótipos dos Menus

void menu_principal(); //Menu principal
void sobre();//O sobre, o criador do trabalho basicamente. kkkk
void funcionalidades(); //O submenu das Funcionalidades. 

//Protótipo das funções de exibição de status

void situacao_construcao_memoria(int situacao); //informa o status final da operação de construção da memória
void situacao_alocacao_memoria(int situacao); //Informa o status final da operação da "alocação" da memória
void situacao_desalocacao_memoria(int situacao); //Informa o status final da operação de "liberação" da memória





//Protótipos das Funções da Árvore 2-3

Arv23Mem *criar_no_Arv23(Inf23 Info, Arv23Mem *Filho_esq, Arv23Mem *Filho_cen); //função base de  criação do Nó
int ehfolha(Arv23Mem *no); //Função auxiliar que identifica que estou em uma folha
Arv23Mem *Adiciona_chave(Arv23Mem *no_atual, Inf23 Info, Arv23Mem *Maior_No); //função que adiciona novas infos em um nó que não está totalmente cheio 
Arv23Mem *QuebraNo(Arv23Mem **No, Inf23 Info, Inf23 *Promove, Arv23Mem *Filho); //Função que Quebra o Nó e separa as infos, promovendo o meio
Arv23Mem *insereArv23(Arv23Mem **no, Inf23 Info, Inf23 *promove, Arv23Mem **Pai, int *situacao); //Função base de inserção na árvore 2-3
void imprimirArvore23(Arv23Mem *raiz); //Função base de impressão
void imprimirInfo(Inf23 info); //imprime informações detalhadas de cada Info
int eh_ultimo(Arv23Mem *Raiz_atual, Arv23Mem *Raiz_original, int localizacao_info); //Função pra saber se estou no ultimo bloco
int reconstruir_Arv(Arv23Mem *Raiz, Arv23Mem **Nova_Raiz); //Constrói uma nova árvore mantendo apenas as infos com a TAG Manter
int auxiliar_reconstrucao(Arv23Mem **Raiz); //Essa função modulariza operações de recriação da árvore e liberação da árvore antiga
void liberarArvore23(Arv23Mem **Raiz); 





//Prótotipo das Funções de Remoção da Arvore 2-3

int auxiliar_remocao(Arv23Mem **Raiz); //Auxiliar principal que modulariza a remoção pra essa implementação
int situacao_da_arvore(Arv23Mem **Raiz, Arv23Mem **Pai, Inf23 Info); //Ponte intermediaria da remoção
int auxiliar_reconstrucao(Arv23Mem **Raiz); //Auxiliar da reconstrução
void coletar_infos_para_remover(Arv23Mem *Raiz, Inf23 Vetor_Infos[], int *numero_infos); //Coleta as Infos destinadas a remoção
void liberarArvore23(Arv23Mem **Raiz); //Função que desaloca e libera a árvore por completo
int reconstruir_Arv(Arv23Mem *Raiz, Arv23Mem **Nova_Raiz); //Função que reconstrói a árvore
int verificador_consistencia(Arv23Mem *Raiz, Arv23Mem **Pai); //Função que verifica a consistência da árvore após a última remoção (Se houve desbalanceamento, se algum filho ficou fora do lugar, ou se alguma sub-árvore está mais profunda que a outra)
int Altura(Arv23Mem *Raiz); //Função para descobrir a áltura do Nó
int Remover_Arv23(Arv23Mem **Raiz, Arv23Mem **Pai, Inf23 Info); //Função principal de remoção
int tratando_pendencias(Arv23Mem **Raiz, Arv23Mem **Pai, Inf23 Info, int posicao); //Cuida das pendencias que não foi possivel de remover da localização atual
int Remover_Info_Nao_Folha(Arv23Mem **Raiz, int Localizacao); //Cuida de remover a Info que não está em uma Folha
int agregar_infos(Arv23Mem **Raiz, int posicao); //Função que junta Nós
int RemoverInfo1Folha(Arv23Mem **Raiz, Arv23Mem **Pai); //Cuida dos casos que a remoção é Info1 Folha (em caso de pendencias, a função tratando_pendencias)
Inf23 Pegar_Menor(Arv23Mem *Raiz, int *operacao); //pega a menor Informação
Inf23 Pegar_Maior(Arv23Mem *Raiz, int *operacao); //Pega a Maior Informação
int contar_descendentes(Arv23Mem *Raiz); //Conta o número de descendentes






//Protótipo das Funções Intermediarias

void construir_memoria_do_sistema(Arv23Mem **Raiz); //Função que monta o dataset
void alocar_memoria_para_programa(Arv23Mem **Raiz); //Função auxiliar que cuida de alocar memória para uma "aplicação", se tiver espaço disponivel
void desalocar_memoria_sistema(Arv23Mem **Raiz); //Função auxiliar que cuida de liberar a memória que está "alocada"
int alocar_memoria(Arv23Mem *Raiz, int qtd_blocos, Arv23Mem *Raiz_Original); //Função de alocação de memória
int desalocar_memoria(Arv23Mem *Raiz, int qtd_blocos, Arv23Mem *Raiz_Original); //Função de desalocação de memória
Arv23Mem *atualizar_bloco(Arv23Mem *Raiz, int qtd_blocos, int operacao, int localizacao_info, int *situacao, Arv23Mem *Raiz_original); //Função que atualiza os blocos, seja inserção ou remoção;
int ajustando_os_intervalos(Arv23Mem *Raiz, Inf23 **bloco_anterior, int opcao, Arv23Mem *Raiz_original); //função que passa um "pente-fino" garantindo que não tenha espaços em branco entre os intervalos após as operações. 
int agrupar_infos(Arv23Mem *Raiz, Inf23 **info_anterior); //Passa verificando se há blocos adjacentes iguais (desconsiderando os que estão na pendencia de serem apagados)























#endif
