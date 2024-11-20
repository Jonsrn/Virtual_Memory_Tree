#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "Gerenciamento_Memoria.h"

//

Arv45Mem *criar_no_Arv45(Inf45 Info, Arv45Mem *Filho_esq, Arv45Mem *Filho_cen1){
    Arv45Mem *Novo_no; 
    Novo_no = NULL; 

    Novo_no = (Arv45Mem*)malloc(sizeof(Arv45Mem)); 
    if(Novo_no == NULL){
        printf("Falha na alocação\n"); 
        exit(1);
    }else{
        memset(Novo_no, 0, sizeof(Arv45Mem));
        Novo_no->info1 = Info;  
        Novo_no->esq = Filho_esq; 
        Novo_no->cent1 = Filho_cen1; 
        Novo_no->cent2 = NULL;  
        Novo_no->cent3 = NULL; 
        Novo_no->dir = NULL; 
        Novo_no->N_infos = 1; 


    }

    return Novo_no;    


}

// Função para verificar se o nó é folha
int ehfolha(Arv45Mem *no) {
    // Um nó é folha se não tem filho esquerdo
    return (no != NULL && no->esq == NULL);
}

Arv45Mem *Adiciona_chave(Arv45Mem *no_atual, Inf45 Info, Arv45Mem *Maior_No) {
    printf("Adicionando chave [%d, %d] no nó.\n", Info.bloco_inicio, Info.bloco_fim);

    if (no_atual->N_infos == 0) {
        // Adiciona diretamente na primeira posição
        no_atual->info1 = Info;
        no_atual->esq = Maior_No; // Atualiza o filho esquerdo
    } else if (no_atual->N_infos == 1) {
        // Decide onde adicionar entre info1 e info2
        if (Info.bloco_inicio < no_atual->info1.bloco_inicio) {
            no_atual->info2 = no_atual->info1; // Empurra info1 para info2
            no_atual->info1 = Info;
            no_atual->cent1 = Maior_No; // Atualiza o ponteiro do centro
        } else {
            no_atual->info2 = Info;
            no_atual->cent2 = Maior_No; // Atualiza o próximo ponteiro central
        }
    } else if (no_atual->N_infos == 2) {
        // Decide onde adicionar entre info1, info2 e info3
        if (Info.bloco_inicio < no_atual->info1.bloco_inicio) {
            no_atual->info3 = no_atual->info2; // Empurra info2 para info3
            no_atual->info2 = no_atual->info1; // Empurra info1 para info2
            no_atual->info1 = Info;
            no_atual->cent2 = no_atual->cent1; // Ajusta os ponteiros
            no_atual->cent1 = Maior_No;
        } else if (Info.bloco_inicio < no_atual->info2.bloco_inicio) {
            no_atual->info3 = no_atual->info2; // Empurra info2 para info3
            no_atual->info2 = Info;
            no_atual->cent3 = no_atual->cent2; // Ajusta os ponteiros
            no_atual->cent2 = Maior_No;
        } else {
            no_atual->info3 = Info;
            no_atual->cent3 = Maior_No;
        }
    } else if (no_atual->N_infos == 3) {
        // Decide onde adicionar entre info1, info2, info3 e info4
        if (Info.bloco_inicio < no_atual->info1.bloco_inicio) {
            no_atual->info4 = no_atual->info3; // Empurra info3 para info4
            no_atual->info3 = no_atual->info2; // Empurra info2 para info3
            no_atual->info2 = no_atual->info1; // Empurra info1 para info2
            no_atual->info1 = Info;
            no_atual->cent3 = no_atual->cent2; // Ajusta os ponteiros
            no_atual->cent2 = no_atual->cent1;
            no_atual->cent1 = Maior_No;
        } else if (Info.bloco_inicio < no_atual->info2.bloco_inicio) {
            no_atual->info4 = no_atual->info3; // Empurra info3 para info4
            no_atual->info3 = no_atual->info2; // Empurra info2 para info3
            no_atual->info2 = Info;
            no_atual->cent3 = no_atual->cent2; // Ajusta os ponteiros
            no_atual->cent2 = Maior_No;
        } else if (Info.bloco_inicio < no_atual->info3.bloco_inicio) {
            no_atual->info4 = no_atual->info3; // Empurra info3 para info4
            no_atual->info3 = Info;
            no_atual->dir = no_atual->cent3; // Ajusta os ponteiros
            no_atual->cent3 = Maior_No;
        } else {
            no_atual->info4 = Info;
            no_atual->dir = Maior_No; // Atualiza o ponteiro direito
        }
    }

    // Incrementar o número de informações no nó
    no_atual->N_infos++;

    // Logs para depuração
    printf("Nó atualizado após adicionar chave:\n");
    printf("Info1: [%d, %d] | Info2: [%d, %d] | Info3: [%d, %d] | Info4: [%d, %d]\n",
           no_atual->info1.bloco_inicio, no_atual->info1.bloco_fim,
           no_atual->info2.bloco_inicio, no_atual->info2.bloco_fim,
           no_atual->info3.bloco_inicio, no_atual->info3.bloco_fim,
           no_atual->info4.bloco_inicio, no_atual->info4.bloco_fim);

    return no_atual;
}




Arv45Mem *QuebraNo(Arv45Mem **No, Inf45 Info, Inf45 *Promove, Arv45Mem *Filho) {
    Arv45Mem *Maior;

    // Logs iniciais
    printf("Iniciando quebra do nó...\n");
    printf("Nó atual antes da quebra:\n");
    printf("Info1: [%d, %d] | Info2: [%d, %d] | Info3: [%d, %d] | Info4: [%d, %d]\n",
           (*No)->info1.bloco_inicio, (*No)->info1.bloco_fim,
           (*No)->info2.bloco_inicio, (*No)->info2.bloco_fim,
           (*No)->info3.bloco_inicio, (*No)->info3.bloco_fim,
           (*No)->info4.bloco_inicio, (*No)->info4.bloco_fim);

    // Determinar qual chave será promovida
    if (Info.bloco_inicio > (*No)->info4.bloco_inicio) {
        *Promove = (*No)->info3; // Promove info3
        Maior = criar_no_Arv45((*No)->info4, (*No)->cent3, (*No)->dir);
        Maior = Adiciona_chave(Maior, Info, Filho);

    } else if (Info.bloco_inicio > (*No)->info3.bloco_inicio) {
        *Promove = (*No)->info3; // Promove info3
        Maior = criar_no_Arv45(Info, (*No)->cent3, (*No)->dir);
        Maior = Adiciona_chave(Maior, (*No)->info4, Filho);

    } else if (Info.bloco_inicio > (*No)->info2.bloco_inicio) {
        *Promove = Info; // Promove o novo valor
        Maior = criar_no_Arv45((*No)->info3, (*No)->cent2, (*No)->cent3);
        Maior = Adiciona_chave(Maior, (*No)->info4, (*No)->dir);

    } else if (Info.bloco_inicio > (*No)->info1.bloco_inicio) {
        *Promove = (*No)->info2; // Promove info2
        Maior = criar_no_Arv45((*No)->info3, (*No)->cent1, (*No)->cent2);
        Maior = Adiciona_chave(Maior, (*No)->info4, (*No)->dir);
        (*No)->info2 = Info;

    } else {
        *Promove = (*No)->info2; // Promove info2
        Maior = criar_no_Arv45((*No)->info3, (*No)->cent1, (*No)->cent2);
        Maior = Adiciona_chave(Maior, (*No)->info4, (*No)->dir);
        (*No)->info2 = (*No)->info1;
        (*No)->info1 = Info;
    }

    // Atualizar o nó original
    (*No)->N_infos = 2;
    memset(&(*No)->info3, 0, sizeof(Inf45));
    memset(&(*No)->info4, 0, sizeof(Inf45));
    (*No)->cent3 = NULL;
    (*No)->dir = NULL;

    // Logs após a atualização
    printf("Nó original atualizado após a quebra:\n");
    printf("Info1: [%d, %d] | Info2: [%d, %d]\n",
           (*No)->info1.bloco_inicio, (*No)->info1.bloco_fim,
           (*No)->info2.bloco_inicio, (*No)->info2.bloco_fim);
    printf("Novo nó criado durante a quebra:\n");
    printf("Info1: [%d, %d]\n", Maior->info1.bloco_inicio, Maior->info1.bloco_fim);

    printf("Chave promovida: [%d, %d]\n", Promove->bloco_inicio, Promove->bloco_fim);

    return Maior;
}





Arv45Mem *insereArv45(Arv45Mem **no, Inf45 Info, Inf45 *promove, Arv45Mem **Pai, int *situacao) {
    Arv45Mem *MaiorNo = NULL;
    Inf45 promove_local;

    if (*no == NULL) {
        // Criar o primeiro nó se a árvore estiver vazia
        printf("Criando o primeiro nó com início: %d, fim: %d, status: %s\n",
               Info.bloco_inicio, Info.bloco_fim,
               Info.status == LIVRE ? "LIVRE" : "OCUPADO");

        *no = criar_no_Arv45(Info, NULL, NULL);
        if (*no == NULL) {
            printf("Erro: Falha na alocação do nó.\n");
            *situacao = 0; // Falha de alocação
        } else {
            printf("Nó criado com sucesso!\n");
            *situacao = 1; // Sucesso
        }
    } else {
        printf("Processando nó existente...\n");
        printf("Nó atual - Info1: [%d, %d] (%s)\n",
               (*no)->info1.bloco_inicio, (*no)->info1.bloco_fim,
               (*no)->info1.status == LIVRE ? "LIVRE" : "OCUPADO");

        if (ehfolha(*no)) {
            printf("Nó é folha. Tentando inserir...\n");

            if ((*no)->N_infos < 4) {
                *no = Adiciona_chave(*no, Info, NULL);
                printf("Inserção direta bem-sucedida no nó folha.\n");
                *situacao = 1; // Sucesso
            } else {
                printf("Nó está cheio. Realizando quebra.\n");
                MaiorNo = QuebraNo(no, Info, &promove_local, NULL);

                if (Pai == NULL || *Pai == NULL) {
                    printf("Criando nova raiz após a quebra...\n");
                    *no = criar_no_Arv45(promove_local, *no, MaiorNo);
                    printf("Nova raiz criada com promoção de [%d, %d].\n",
                           promove_local.bloco_inicio, promove_local.bloco_fim);
                    MaiorNo = NULL;
                } else {
                    *promove = promove_local;
                }
                *situacao = 1;
            }
        } else {
            // Nó não é folha, precisa descer na árvore
            printf("Nó não é folha. Descendo na árvore...\n");

            if (Info.bloco_inicio < (*no)->info1.bloco_inicio) {
                printf("Descendo para a esquerda.\n");
                MaiorNo = insereArv45(&((*no)->esq), Info, &promove_local, no, situacao);
            } else if ((*no)->N_infos == 1 || (Info.bloco_inicio < (*no)->info2.bloco_inicio)) {
                printf("Descendo para o centro 1.\n");
                MaiorNo = insereArv45(&((*no)->cent1), Info, &promove_local, no, situacao);
            } else if ((*no)->N_infos == 2 || (Info.bloco_inicio < (*no)->info3.bloco_inicio)) {
                printf("Descendo para o centro 2.\n");
                MaiorNo = insereArv45(&((*no)->cent2), Info, &promove_local, no, situacao);
            } else if ((*no)->N_infos == 3 || (Info.bloco_inicio < (*no)->info4.bloco_inicio)) {
                printf("Descendo para o centro 3.\n");
                MaiorNo = insereArv45(&((*no)->cent3), Info, &promove_local, no, situacao);
            } else {
                printf("Descendo para a direita.\n");
                MaiorNo = insereArv45(&((*no)->dir), Info, &promove_local, no, situacao);
            }

            // Após a recursão, lidar com o nó promovido
            if (MaiorNo != NULL) {
                if ((*no)->N_infos < 4) {
                    printf("Inserindo promovido diretamente no nó pai.\n");
                    *no = Adiciona_chave(*no, promove_local, MaiorNo);
                    MaiorNo = NULL;
                } else {
                    printf("Nó pai está cheio. Realizando quebra.\n");
                    Inf45 promove1;
                    MaiorNo = QuebraNo(no, promove_local, &promove1, MaiorNo);

                    if (Pai == NULL || *Pai == NULL) {
                        printf("Criando nova raiz após quebra do pai...\n");
                        *no = criar_no_Arv45(promove1, *no, MaiorNo);
                        MaiorNo = NULL;
                    } else {
                        *promove = promove1;
                    }
                }
            }
        }
    }

    return MaiorNo;
}








void imprimirInfo(Inf45 info) {
    // Imprime informações apenas se forem válidas
    if (info.bloco_fim > info.bloco_inicio) {
        printf("Status: %s | Bloco Início: %d | Bloco Fim: %d | Intervalo: %d\n",
               info.status == LIVRE ? "LIVRE" : "OCUPADO",
               info.bloco_inicio, info.bloco_fim,
               info.bloco_fim - info.bloco_inicio);
    }
}

void imprimirArvore45(Arv45Mem *raiz) {
    if (raiz == NULL) {
        return;
    }

    // Percorre o filho esquerdo
    imprimirArvore45(raiz->esq);
    // Imprime a primeira informação
    imprimirInfo(raiz->info1);
    // Sempre percorre o primeiro filho central
    imprimirArvore45(raiz->cent1);

    if (raiz->N_infos > 1) {
        // Imprime a segunda informação
        imprimirInfo(raiz->info2);
        // Percorre o segundo filho central
        imprimirArvore45(raiz->cent2);
    }

    if (raiz->N_infos > 2) {
        // Imprime a terceira informação
        imprimirInfo(raiz->info3);
        // Percorre o terceiro filho central
        imprimirArvore45(raiz->cent3);
    }

    if (raiz->N_infos > 3) {
        // Imprime a quarta informação
        imprimirInfo(raiz->info4);
    }

    // Percorre o filho direito
    imprimirArvore45(raiz->dir);
}
