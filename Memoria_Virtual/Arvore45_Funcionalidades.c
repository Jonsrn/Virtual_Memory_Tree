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

    return no_atual;
}




Arv45Mem *QuebraNo(Arv45Mem **No, Inf45 Info, Inf45 *Promove, Arv45Mem *Filho) {
    Arv45Mem *Maior;

    
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

    return Maior;
}





Arv45Mem *insereArv45(Arv45Mem **no, Inf45 Info, Inf45 *promove, Arv45Mem **Pai, int *situacao) {
    Arv45Mem *MaiorNo = NULL;
    Inf45 promove_local;

    if (*no == NULL) {
        *no = criar_no_Arv45(Info, NULL, NULL);
        if (*no == NULL) {
            *situacao = 0; // Falha de alocação
        } else {
            *situacao = 1; // Sucesso
        }
    } else {
        if (ehfolha(*no)) {
            if ((*no)->N_infos < 4) {
                *no = Adiciona_chave(*no, Info, NULL);
                *situacao = 1; // Sucesso
            } else {
                MaiorNo = QuebraNo(no, Info, &promove_local, NULL);

                if (Pai == NULL || *Pai == NULL) {
                    *no = criar_no_Arv45(promove_local, *no, MaiorNo);
                    MaiorNo = NULL;
                } else {
                    *promove = promove_local;
                }
                *situacao = 1;
            }
        } else {

            if (Info.bloco_inicio < (*no)->info1.bloco_inicio) {

                MaiorNo = insereArv45(&((*no)->esq), Info, &promove_local, no, situacao);

            } else if ((*no)->N_infos == 1 || (Info.bloco_inicio < (*no)->info2.bloco_inicio)) {
               
                MaiorNo = insereArv45(&((*no)->cent1), Info, &promove_local, no, situacao);

            } else if ((*no)->N_infos == 2 || (Info.bloco_inicio < (*no)->info3.bloco_inicio)) {
              
                MaiorNo = insereArv45(&((*no)->cent2), Info, &promove_local, no, situacao);

            } else if ((*no)->N_infos == 3 || (Info.bloco_inicio < (*no)->info4.bloco_inicio)) {
              
                MaiorNo = insereArv45(&((*no)->cent3), Info, &promove_local, no, situacao);

            } else {
                
                MaiorNo = insereArv45(&((*no)->dir), Info, &promove_local, no, situacao);
            }

            // Após a recursão, lidar com o nó promovido
            if (MaiorNo != NULL) {
                if ((*no)->N_infos < 4) {                   
                    *no = Adiciona_chave(*no, promove_local, MaiorNo);
                    MaiorNo = NULL;
                } else {                  
                    Inf45 promove1;
                    MaiorNo = QuebraNo(no, promove_local, &promove1, MaiorNo);

                    if (Pai == NULL || *Pai == NULL) {
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
    if (raiz != NULL) {
        
    

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
}


Arv45Mem *atualizar_bloco(Arv45Mem *Raiz, int qtd_blocos, int operacao, int localizacao_info) {
    Inf45 *info = NULL;

    // Selecionar a Info correta com base na localização
    if (localizacao_info == 1){ 
        info = &Raiz->info1;
    }else if (localizacao_info == 2){ 
        info = &Raiz->info2;
    }else if (localizacao_info == 3){ 
        info = &Raiz->info3;
    }else if (localizacao_info == 4){ 
        info = &Raiz->info4;
    }

    if (operacao == 1) {
        // Operação de adicionar blocos
        info->bloco_inicio -= qtd_blocos; // Recuar o início do bloco
        info->intervalo += qtd_blocos;   // Aumentar o intervalo
    } else if (operacao == 2) {
        // Operação de subtrair blocos
        info->bloco_fim -= qtd_blocos;   // Reduzir o tamanho do bloco
        info->intervalo -= qtd_blocos;  // Reduzir o intervalo

    }

    return Raiz;
}



int alocar_memoria(Arv45Mem *Raiz, int qtd_blocos) {
    int alocou = 0; // Status inicial: não encontrou bloco livre.
    //0, significa que não encontrou um bloco livre.
    // 1  significa que encontrei um bloco com espaço suficiente pra tomar parte de suas unidades (mas ficou pendencia, se não encontrei um bloco adjacente) (*** deve ser tratado externamente, com a criação de um novo nó)
    //2 significa que deu certo, encontrei um bloco com espaço suficiente pra tomar parte de suas unidades e que eu já aloquei o espaço pra outro bloco, não há mais pendencia (quando tudo é resolvido no próprio Nó)
    //3 significa que deu certo, encontrei um bloco com espaço suficiente pra retirar seus blocos e que eu já aloquei o espaço pra outro bloco, mas esse bloco livre ficou vazio, ele precisa ser excluído. (Sem pendencia de manipulação, os blocos foram para o outro bloco do mesmo nó)
    //4 significa que deu certo, encontrei um bloco com espaço suficiente pra retirar seus blocos e que eu já aloquei o espaço pra outro bloco, mas esse bloco livre ficou vazio, ele precisa ser excluído. (Ficou pendencia de inserção desses blocos)

    if (Raiz != NULL) {
        // Tentar alocar nos filhos à esquerda primeiro
        alocou = alocar_memoria(Raiz->esq, qtd_blocos);

        if (alocou == 0) {
            // Percorrer as Infos do nó atual
            for (int i = 1; i <= Raiz->N_infos; i++) {
                Inf45 *info = NULL;

                // Selecionar a Info correta
                if (i == 1){
                     info = &Raiz->info1;
                }else if (i == 2){
                     info = &Raiz->info2;
                }else if (i == 3){
                     info = &Raiz->info3;
                }else if (i == 4){
                     info = &Raiz->info4;
                }     

                // Verificar se a Info é LIVRE e tem espaço suficiente
                if (info->status == LIVRE && info->intervalo >= qtd_blocos) {
                    if (qtd_blocos < info->intervalo) {
                        // Caso: Bloco LIVRE tem mais espaço do que o necessário
                        Raiz = atualizar_bloco(Raiz, qtd_blocos, 2, i); // Reduz o intervalo do bloco LIVRE
                        alocou = 2; // Alocação resolvida no próprio nó
                        break;
                    } else {
                        // Caso: Bloco LIVRE tem exatamente o espaço necessário
                        info->status_apagar = APAGAR; // Marcar o bloco para exclusão
                        alocou = 4; // Pendência de exclusão
                        break;
                    }
                }
            }

            if (alocou == 0) {
                // Tentar alocar nos filhos centrais e à direita
                alocou = alocar_memoria(Raiz->cent1, qtd_blocos);
                if (alocou == 0 && Raiz->cent2 != NULL){ 
                    alocou = alocar_memoria(Raiz->cent2, qtd_blocos);
                }    
                if (alocou == 0 && Raiz->cent3 != NULL){
                     alocou = alocar_memoria(Raiz->cent3, qtd_blocos);
                }     
                
                if (alocou == 0){
                     alocou = alocar_memoria(Raiz->dir, qtd_blocos);
                }     
            }
        }

        // Resolver pendências de inserção (casos alocou == 2 ou == 4)
        if (alocou == 2 || alocou == 4) {
            for (int i = 1; i <= Raiz->N_infos; i++) {
                Inf45 *info = NULL;

                // Selecionar a Info correta
                if (i == 1) info = &Raiz->info1;
                else if (i == 2) info = &Raiz->info2;
                else if (i == 3) info = &Raiz->info3;
                else if (i == 4) info = &Raiz->info4;

                if (info->status == OCUPADO) {
                    // Verificar se este bloco é adjacente ao LIVRE reduzido

                    // Expandir o bloco OCUPADO
                    Raiz = atualizar_bloco(Raiz, qtd_blocos, 1, i); // Operação 1 = somar blocos

                    if (alocou == 4) {
                        alocou = 3; // Resolvido completamente, mas o bloco original deve ser apagado
                    }
                    break;
                }
            }
        }
    }

    return alocou; // Retorna o status da alocação
}
