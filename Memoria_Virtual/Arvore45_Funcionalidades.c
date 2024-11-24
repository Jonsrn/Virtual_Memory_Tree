#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "Gerenciamento_Memoria.h"


//Função de criação do Nó da 4-5
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

//Função que adiciona infos em um nó com espaço disponivel
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



//Função que quebra o nó quando não há mais espaço disponivel, o do meio é promovido, e os dois maiores vão pra um novo nó
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




//Função base de inserção na árvore 4-5
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







//Função que imprime detalhadamente as informações de cada INFO de cada Nó
void imprimirInfo(Inf45 info) {
    if (info.status_apagar == APAGAR) {
        printf("Status: APAGAR | Bloco Início: %d | Bloco Fim: %d | Intervalo: %d\n",
               info.bloco_inicio, info.bloco_fim,
               info.bloco_fim - info.bloco_inicio);
    } else if (info.bloco_fim >= info.bloco_inicio) { 
        printf("Status: %s | Bloco Início: %d | Bloco Fim: %d | Intervalo: %d| Situacao: %s \n",
               info.status == LIVRE ? "LIVRE" : "OCUPADO",
               info.bloco_inicio, info.bloco_fim,
               info.bloco_fim - info.bloco_inicio, info.status_apagar == MANTER ? "MANTER" : "APAGAR");
    } else {
        printf("Informação inválida detectada: Início: %d, Fim: %d\n", info.bloco_inicio, info.bloco_fim);
    }
}

//Função base de impressão da 4-5
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

//Funções relacionadas a alocação e desalocação dos blocos. 

//essa função serve pra saber se estou na ultima info da árvore
int eh_ultimo(Arv45Mem *Raiz, int localizacao_info) {
    int ultimo = 0;

    if (Raiz != NULL) {
        // Verifica se o nó atual é o último (não tem filhos adicionais)
        if (Raiz->dir == NULL && Raiz->cent3 == NULL && Raiz->cent2 == NULL && Raiz->cent1 == NULL) {
            // Verifica se a Info atual é a última Info válida no nó
            if (localizacao_info == Raiz->N_infos) {
                ultimo = 1; // Confirma que é o último
            }
        }
    }

    return ultimo; // Retorna 1 se é o último, 0 caso contrário
}



//Essa função serve para atualizar o bloco encontrado que atenda aos requisitos de alocação ou desalocação (funciona pra ambos os casos)
Arv45Mem *atualizar_bloco(Arv45Mem *Raiz, int qtd_blocos, int operacao, int localizacao_info, int *situacao) {
    Inf45 *info = NULL;

    // Selecionar a Info correta com base na localização
    if (localizacao_info == 1) info = &Raiz->info1;
    else if (localizacao_info == 2) info = &Raiz->info2;
    else if (localizacao_info == 3) info = &Raiz->info3;
    else if (localizacao_info == 4) info = &Raiz->info4;

    if (info != NULL) {
        // Verifica se o bloco é o último
        if (eh_ultimo(Raiz, localizacao_info)) {
            *situacao = 2; // Indica que estamos lidando com o último bloco

            if (operacao == 2) {
                // Se for o último bloco, avança o início e ajusta o intervalo
                info->bloco_inicio += qtd_blocos;
                info->intervalo = info->bloco_fim - info->bloco_inicio + 1;
            } else if (operacao == 1) {
                // Operação de adição no último bloco
                info->bloco_inicio -= qtd_blocos;
                info->intervalo += qtd_blocos;
            }

            // Log para depuração
            printf("Último bloco ajustado: [%d, %d] (Intervalo: %d)\n",
                   info->bloco_inicio, info->bloco_fim, info->intervalo);

        } else {
            *situacao = 1; // Situação convencional (não é o último bloco)

            // Operação padrão de adição ou subtração
            if (operacao == 1) {
                info->bloco_inicio -= qtd_blocos; // Recuar o início do bloco
                info->intervalo += qtd_blocos;   // Aumentar o intervalo
            } else if (operacao == 2) {
                info->bloco_fim -= qtd_blocos;   // Reduzir o tamanho do bloco
                info->intervalo -= qtd_blocos;  // Reduzir o intervalo
            }

            // Log para depuração
            printf("Bloco ajustado (não-último): [%d, %d] (Intervalo: %d)\n",
                   info->bloco_inicio, info->bloco_fim, info->intervalo);
        }
    } else {
        printf("Erro: Info não encontrada.\n");
    }

    return Raiz;
}


//Essa função cuida de manter todos os intervalos estruturados após as operações de alocação/desalocação, além disso
//há duas situações, se o bloco mexido não for o ultimo, a reestruturação é da esquerda pra direita, se for o último, a reestruturação é da direita pra esquerda
int ajustando_os_intervalos(Arv45Mem *Raiz, Inf45 **bloco_anterior, int opcao) {
    int ajustes_realizados = 0; // Indica se ajustes foram feitos

    if (Raiz != NULL) {
        if (opcao == 1) {
            // Processa a subárvore esquerda primeiro (ordem padrão)
            ajustes_realizados |= ajustando_os_intervalos(Raiz->esq, bloco_anterior, opcao);

            // Processa Info1 e a subárvore cent1
            if (Raiz->info1.status_apagar == MANTER) {
                if (*bloco_anterior == NULL) {
                    // Caso especial: Primeiro bloco válido encontrado, inicializar em 0
                    if (Raiz->info1.bloco_inicio != 0) {
                        Raiz->info1.bloco_inicio = 0;
                        Raiz->info1.intervalo = Raiz->info1.bloco_fim - Raiz->info1.bloco_inicio + 1;
                        ajustes_realizados = 1;
                    }
                } else {
                    // Verifica alinhamento dos blocos
                    if ((*bloco_anterior)->bloco_fim + 1 != Raiz->info1.bloco_inicio) {
                        Raiz->info1.bloco_inicio = (*bloco_anterior)->bloco_fim + 1;
                        ajustes_realizados = 1; // Ajuste foi feito
                    }
                }
                // Atualiza o intervalo do bloco atual
                int novo_intervalo = Raiz->info1.bloco_fim - Raiz->info1.bloco_inicio + 1;
                if (novo_intervalo != Raiz->info1.intervalo) {
                    Raiz->info1.intervalo = novo_intervalo;
                    ajustes_realizados = 1; // Ajuste foi feito
                }
                // Atualiza o bloco anterior para o atual
                *bloco_anterior = &Raiz->info1;
            }
            ajustes_realizados |= ajustando_os_intervalos(Raiz->cent1, bloco_anterior, opcao);

            // Processa Info2 e a subárvore cent2 (se existir)
            if (Raiz->N_infos >= 2 && Raiz->info2.status_apagar == MANTER) {
                if (*bloco_anterior == NULL) {
                    // Caso especial: Primeiro bloco válido encontrado, inicializar em 0
                    if (Raiz->info2.bloco_inicio != 0) {
                        Raiz->info2.intervalo = Raiz->info2.bloco_fim - Raiz->info2.bloco_inicio + 1;
                        Raiz->info2.bloco_inicio = 0;
                        ajustes_realizados = 1;
                    }
                } else {
                    if ((*bloco_anterior)->bloco_fim + 1 != Raiz->info2.bloco_inicio) {
                        Raiz->info2.bloco_inicio = (*bloco_anterior)->bloco_fim + 1;
                        ajustes_realizados = 1;
                    }
                }
                int novo_intervalo = Raiz->info2.bloco_fim - Raiz->info2.bloco_inicio + 1;
                if (novo_intervalo != Raiz->info2.intervalo) {
                    Raiz->info2.intervalo = novo_intervalo;
                    ajustes_realizados = 1;
                }
                *bloco_anterior = &Raiz->info2;
            }
            ajustes_realizados |= ajustando_os_intervalos(Raiz->cent2, bloco_anterior, opcao);

            // Processa Info3 e a subárvore cent3
            if (Raiz->N_infos >= 3 && Raiz->info3.status_apagar == MANTER) {
                if (*bloco_anterior != NULL) {
                    if ((*bloco_anterior)->bloco_fim + 1 != Raiz->info3.bloco_inicio) {
                        Raiz->info3.bloco_inicio = (*bloco_anterior)->bloco_fim + 1;
                        ajustes_realizados = 1;
                    }
                }
                int novo_intervalo = Raiz->info3.bloco_fim - Raiz->info3.bloco_inicio + 1;
                if (novo_intervalo != Raiz->info3.intervalo) {
                    Raiz->info3.intervalo = novo_intervalo;
                    ajustes_realizados = 1;
                }
                *bloco_anterior = &Raiz->info3;
            }
            ajustes_realizados |= ajustando_os_intervalos(Raiz->cent3, bloco_anterior, opcao);

            // Processa Info4 e a subárvore direita
            if (Raiz->N_infos >= 4 && Raiz->info4.status_apagar == MANTER) {
                if (*bloco_anterior != NULL) {
                    if ((*bloco_anterior)->bloco_fim + 1 != Raiz->info4.bloco_inicio) {
                        Raiz->info4.bloco_inicio = (*bloco_anterior)->bloco_fim + 1;
                        ajustes_realizados = 1;
                    }
                }
                int novo_intervalo = Raiz->info4.bloco_fim - Raiz->info4.bloco_inicio + 1;
                if (novo_intervalo != Raiz->info4.intervalo) {
                    Raiz->info4.intervalo = novo_intervalo;
                    ajustes_realizados = 1;
                }
                *bloco_anterior = &Raiz->info4;
            }
            ajustes_realizados |= ajustando_os_intervalos(Raiz->dir, bloco_anterior, opcao);
        } else if (opcao == 2) {
            // Processa a subárvore direita primeiro (ordem invertida)
            ajustes_realizados |= ajustando_os_intervalos(Raiz->dir, bloco_anterior, opcao);

            // Processa Info4 e a subárvore cent3 (se existir)
            if (Raiz->N_infos >= 4 && Raiz->info4.status_apagar == MANTER) {
                if (*bloco_anterior != NULL) {
                    if ((*bloco_anterior)->bloco_inicio - 1 != Raiz->info4.bloco_fim) {
                        Raiz->info4.bloco_fim = (*bloco_anterior)->bloco_inicio - 1;
                        ajustes_realizados = 1; // Ajuste foi feito
                    }
                }
                int novo_intervalo = Raiz->info4.bloco_fim - Raiz->info4.bloco_inicio + 1;
                if (novo_intervalo != Raiz->info4.intervalo) {
                    Raiz->info4.intervalo = novo_intervalo;
                    ajustes_realizados = 1;
                }
                *bloco_anterior = &Raiz->info4;
            }
            ajustes_realizados |= ajustando_os_intervalos(Raiz->cent3, bloco_anterior, opcao);

            // Processa Info3 e as subárvores cent2
            if (Raiz->N_infos >= 3 && Raiz->info3.status_apagar == MANTER) {
                if (*bloco_anterior != NULL) {
                    if ((*bloco_anterior)->bloco_inicio - 1 != Raiz->info3.bloco_fim) {
                        Raiz->info3.bloco_fim = (*bloco_anterior)->bloco_inicio - 1;
                        ajustes_realizados = 1;
                    }
                }
                int novo_intervalo = Raiz->info3.bloco_fim - Raiz->info3.bloco_inicio + 1;
                if (novo_intervalo != Raiz->info3.intervalo) {
                    Raiz->info3.intervalo = novo_intervalo;
                    ajustes_realizados = 1;
                }
                *bloco_anterior = &Raiz->info3;
            }
            ajustes_realizados |= ajustando_os_intervalos(Raiz->cent2, bloco_anterior, opcao);

            // Processa Info2 e as subárvores cent1
            if (Raiz->N_infos >= 2 && Raiz->info2.status_apagar == MANTER) {
                if (*bloco_anterior != NULL) {
                    if ((*bloco_anterior)->bloco_inicio - 1 != Raiz->info2.bloco_fim) {
                        Raiz->info2.bloco_fim = (*bloco_anterior)->bloco_inicio - 1;
                        ajustes_realizados = 1;
                    }
                }
                int novo_intervalo = Raiz->info2.bloco_fim - Raiz->info2.bloco_inicio + 1;
                if (novo_intervalo != Raiz->info2.intervalo) {
                    Raiz->info2.intervalo = novo_intervalo;
                    ajustes_realizados = 1;
                }
                *bloco_anterior = &Raiz->info2;
            }
            ajustes_realizados |= ajustando_os_intervalos(Raiz->cent1, bloco_anterior, opcao);

            // Processa Info1 e a subárvore esquerda
            if (Raiz->info1.status_apagar == MANTER) {
                if (*bloco_anterior != NULL) {
                    if ((*bloco_anterior)->bloco_inicio - 1 != Raiz->info1.bloco_fim) {
                        Raiz->info1.bloco_fim = (*bloco_anterior)->bloco_inicio - 1;
                        ajustes_realizados = 1;
                    }
                }
                int novo_intervalo = Raiz->info1.bloco_fim - Raiz->info1.bloco_inicio + 1;
                if (novo_intervalo != Raiz->info1.intervalo) {
                    Raiz->info1.intervalo = novo_intervalo;
                    ajustes_realizados = 1;
                }
                *bloco_anterior = &Raiz->info1;
            }
            ajustes_realizados |= ajustando_os_intervalos(Raiz->esq, bloco_anterior, opcao);
        }
    }

    return ajustes_realizados; // Retorna 1 se ajustes foram realizados, 0 caso contrário
}

//função que cuida de encontrar uma INFO com a TAG LIVRE, com espaço suficiente pra comportar a operação
int alocar_memoria(Arv45Mem *Raiz, int qtd_blocos) {
    int alocou = 0; // Status inicial: não encontrou bloco livre.
    //0, significa que não encontrou um bloco livre.
    // 1  significa que encontrei um bloco com espaço suficiente pra tomar parte de suas unidades (mas ficou pendencia, se não encontrei um bloco adjacente) (*** deve ser tratado externamente, com a criação de um novo nó)
    //2 significa que deu certo, encontrei um bloco com espaço suficiente pra tomar parte de suas unidades e que eu já aloquei o espaço pra outro bloco, não há mais pendencia (quando tudo é resolvido no próprio Nó)
    //3 significa que deu certo, encontrei um bloco com espaço suficiente pra retirar seus blocos e que eu já aloquei o espaço pra outro bloco, mas esse bloco livre ficou vazio, ele precisa ser excluído. (Sem pendencia de manipulação, os blocos foram para o outro bloco do mesmo nó)
    //4 significa que deu certo, encontrei um bloco com espaço suficiente pra retirar seus blocos e que eu já aloquei o espaço pra outro bloco, mas esse bloco livre ficou vazio, ele precisa ser excluído. (Ficou pendencia de inserção desses blocos)
    //5 significa que é o ultimo bloco, precisa ser reajustado de maneira diferente
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

                int situacao;    

                // Verificar se a Info é LIVRE e tem espaço suficiente
                if (info->status == LIVRE && info->intervalo >= qtd_blocos) {
                    if (qtd_blocos < info->intervalo) {
                        
                        situacao = 0; 
                        // Caso: Bloco LIVRE tem mais espaço do que o necessário
                        Raiz = atualizar_bloco(Raiz, qtd_blocos, 2, i, &situacao); // Reduz o intervalo do bloco LIVRE
                        if(situacao == 1){
                            //1 significa que é normal, n está no ultimo bloco
                            alocou = 2; 
                        }else if(situacao == 2){
                            //é o ultimo bloco
                            alocou = 5; 
                        }
                        break;
                    } else {
                        // Caso: Bloco LIVRE tem exatamente o espaço necessário
                        Raiz = atualizar_bloco(Raiz, qtd_blocos, 2, i, &situacao); // Reduz o intervalo do bloco LIVRE
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

    }

    return alocou; // Retorna o status da alocação
}

//Função que cuida de encontrar a info com a TAG OCUPADO, com espaço suficiente pra liberação 
int desalocar_memoria(Arv45Mem *Raiz, int qtd_blocos){
    int desalocou = 0;
    

    if(Raiz != NULL){
         // Tentar alocar nos filhos à esquerda primeiro
        desalocou = desalocar_memoria(Raiz->esq, qtd_blocos);

        if (desalocou == 0) {
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
                int situacao; 
                // Verificar se a Info é OCUPADA e tem espaço suficiente para ser liberada
                if (info->status == OCUPADO && info->intervalo >= qtd_blocos) {
                    if (qtd_blocos < info->intervalo) {
                        
                        situacao = 0; 
                        // Caso: Bloco OCUPADO tem mais espaço do que o necessário
                        Raiz = atualizar_bloco(Raiz, qtd_blocos, 2, i, &situacao); // Reduz o intervalo do bloco OCUPADO
                        if(situacao == 1){
                            //1 significa que é normal, n está no ultimo bloco
                            desalocou = 2; 
                        }else if(situacao == 2){
                            //é o ultimo bloco
                            desalocou = 5; 
                        }
                        break;
                    } else {
                        // Caso: Bloco OCUPADO tem exatamente o espaço necessário
                        Raiz = atualizar_bloco(Raiz, qtd_blocos, 2, i, &situacao); // Reduz o intervalo do bloco OCUPADO
                        info->status_apagar = APAGAR; // Marcar o bloco para exclusão
                        desalocou = 4; // Pendência de exclusão
                        break;
                    }
                }
            }

            if (desalocou == 0) {
                // Tentar alocar nos filhos centrais e à direita
                desalocou = desalocar_memoria(Raiz->cent1, qtd_blocos);
                if (desalocou == 0 && Raiz->cent2 != NULL){ 
                    desalocou = desalocar_memoria(Raiz->cent2, qtd_blocos);
                }    
                if (desalocou == 0 && Raiz->cent3 != NULL){
                     desalocou = desalocar_memoria(Raiz->cent3, qtd_blocos);
                }     
                
                if (desalocou == 0){
                     desalocou = desalocar_memoria(Raiz->dir, qtd_blocos);
                }     
            }
        }
    }
    return desalocou; 
}

//Falta as funções de agrupamento, e remoção. 

//o agrupamento vai percorrer a árvore, em busca de nós adjacentes iguais (LIVRE com LIVRE ou OCUPADO com OCUPADO)
//Desconsiderando as infos que estão com a TAG APAGAR, a função ao encontrar essa situação, pegará os blocos da info atual e atualizará a anterior com a soma
//A info atual receberá tbm a TAG APAGAR

int agrupar_infos(Arv45Mem *Raiz, Inf45 **info_anterior) {
    int agrupamento_realizado = 0; // Indica se agrupamentos foram realizados

    if (Raiz != NULL) {
        // Percorre a subárvore esquerda primeiro
        agrupamento_realizado |= agrupar_infos(Raiz->esq, info_anterior);

        // Processa Info1 e a subárvore cent1
        if (Raiz->info1.status_apagar == MANTER) {
            if (*info_anterior != NULL) {
                // Verifica se os blocos adjacentes têm o mesmo status
                if ((*info_anterior)->status == Raiz->info1.status) {
                    // Agrupa os blocos
                    (*info_anterior)->bloco_fim = Raiz->info1.bloco_fim;
                    (*info_anterior)->intervalo = (*info_anterior)->bloco_fim - (*info_anterior)->bloco_inicio + 1;

                    // Marca a Info1 atual como APAGAR
                    Raiz->info1.status_apagar = APAGAR;
                    agrupamento_realizado = 1; // Indica que um agrupamento foi realizado
                }
            }
            // Atualiza a Info anterior para a próxima iteração
            *info_anterior = &Raiz->info1;
        }
        agrupamento_realizado |= agrupar_infos(Raiz->cent1, info_anterior);

        // Processa Info2 e a subárvore cent2 (se existir)
        if (Raiz->N_infos >= 2 && Raiz->info2.status_apagar == MANTER) {
            if (*info_anterior != NULL) {
                if ((*info_anterior)->status == Raiz->info2.status) {
                    (*info_anterior)->bloco_fim = Raiz->info2.bloco_fim;
                    (*info_anterior)->intervalo = (*info_anterior)->bloco_fim - (*info_anterior)->bloco_inicio + 1;
                    Raiz->info2.status_apagar = APAGAR;
                    agrupamento_realizado = 1;
                }
            }
            *info_anterior = &Raiz->info2;
        }
        agrupamento_realizado |= agrupar_infos(Raiz->cent2, info_anterior);

        // Processa Info3 e a subárvore cent3 (se existir)
        if (Raiz->N_infos >= 3 && Raiz->info3.status_apagar == MANTER) {
            if (*info_anterior != NULL) {
                if ((*info_anterior)->status == Raiz->info3.status) {
                    (*info_anterior)->bloco_fim = Raiz->info3.bloco_fim;
                    (*info_anterior)->intervalo = (*info_anterior)->bloco_fim - (*info_anterior)->bloco_inicio + 1;
                    Raiz->info3.status_apagar = APAGAR;
                    agrupamento_realizado = 1;
                }
            }
            *info_anterior = &Raiz->info3;
        }
        agrupamento_realizado |= agrupar_infos(Raiz->cent3, info_anterior);

        // Processa Info4 e a subárvore direita (se existir)
        if (Raiz->N_infos >= 4 && Raiz->info4.status_apagar == MANTER) {
            if (*info_anterior != NULL) {
                if ((*info_anterior)->status == Raiz->info4.status) {
                    (*info_anterior)->bloco_fim = Raiz->info4.bloco_fim;
                    (*info_anterior)->intervalo = (*info_anterior)->bloco_fim - (*info_anterior)->bloco_inicio + 1;
                    Raiz->info4.status_apagar = APAGAR;
                    agrupamento_realizado = 1;
                }
            }
            *info_anterior = &Raiz->info4;
        }
        agrupamento_realizado |= agrupar_infos(Raiz->dir, info_anterior);
    }

    return agrupamento_realizado; // Retorna 1 se agrupamentos foram realizados, 0 caso contrário
}





//A função de apagar, percorrerá toda a árvore e removerá todas infos com a TAG apagar, mantendo a alternancia dos blocos da árvore. 








void removerInfosApagar(Arv45Mem **Raiz) {
    if (*Raiz != NULL) {
        // Percorrer as subárvores
        removerInfosApagar(&(*Raiz)->esq);
        removerInfosApagar(&(*Raiz)->cent1);
        removerInfosApagar(&(*Raiz)->cent2);
        removerInfosApagar(&(*Raiz)->cent3);
        removerInfosApagar(&(*Raiz)->dir);

        // Processar as informações do nó atual
        for (int i = 1; i <= (*Raiz)->N_infos; i++) {
            Inf45 *info = NULL;

            // Selecionar a Info correta
            if (i == 1) info = &(*Raiz)->info1;
            else if (i == 2) info = &(*Raiz)->info2;
            else if (i == 3) info = &(*Raiz)->info3;
            else if (i == 4) info = &(*Raiz)->info4;

            // Verificar se a Info possui a TAG APAGAR
            if (info != NULL && info->status_apagar == APAGAR) {
                // Ajustar os ponteiros das subárvores associados a essa Info
                if (i == 1) {
                    (*Raiz)->esq = (*Raiz)->cent1;
                    (*Raiz)->cent1 = (*Raiz)->cent2;
                    (*Raiz)->cent2 = (*Raiz)->cent3;
                    (*Raiz)->cent3 = (*Raiz)->dir;
                    (*Raiz)->dir = NULL;
                } else if (i == 2) {
                    (*Raiz)->cent1 = (*Raiz)->cent2;
                    (*Raiz)->cent2 = (*Raiz)->cent3;
                    (*Raiz)->cent3 = (*Raiz)->dir;
                    (*Raiz)->dir = NULL;
                } else if (i == 3) {
                    (*Raiz)->cent2 = (*Raiz)->cent3;
                    (*Raiz)->cent3 = (*Raiz)->dir;
                    (*Raiz)->dir = NULL;
                } else if (i == 4) {
                    (*Raiz)->cent3 = (*Raiz)->dir;
                    (*Raiz)->dir = NULL;
                }

                // Deslocar as outras Infos para preencher o espaço
                for (int j = i; j < (*Raiz)->N_infos; j++) {
                    if (j == 1) (*Raiz)->info1 = (*Raiz)->info2;
                    if (j == 2) (*Raiz)->info2 = (*Raiz)->info3;
                    if (j == 3) (*Raiz)->info3 = (*Raiz)->info4;
                }
                (*Raiz)->N_infos--; // Reduz o número de infos no nó
                i--; // Reprocessar o índice atual, pois as infos foram deslocadas
            }
        }

        // Se o nó ficar vazio, liberar a memória e ajustar o ponteiro
        if ((*Raiz)->N_infos == 0) {
            // Mover filhos do nó vazio para o pai
            if ((*Raiz)->esq) {
                Arv45Mem *subarvore = (*Raiz)->esq;
                **Raiz = *subarvore; // Substitui o nó pelo filho
                free(subarvore);
            } else {
                free(*Raiz);
                *Raiz = NULL;
            }
        }
    }
}

void balancearArvore45(Arv45Mem **Raiz) {
    if (*Raiz != NULL) {
        // Balancear as subárvores primeiro
        balancearArvore45(&(*Raiz)->esq);
        balancearArvore45(&(*Raiz)->cent1);
        balancearArvore45(&(*Raiz)->cent2);
        balancearArvore45(&(*Raiz)->cent3);
        balancearArvore45(&(*Raiz)->dir);

        // Verificar o equilíbrio do nó atual
        if ((*Raiz)->N_infos < 2) {
            Arv45Mem *pai = NULL;
            Arv45Mem **irmao_maior = NULL;

            // Identificar o pai e o irmão com mais informações
            encontrarPaiEIrmao(*Raiz, &pai, &irmao_maior);

            if (irmao_maior != NULL && (*irmao_maior)->N_infos > 2) {
                // Caso 1: Redistribuir com o irmão
                redistribuirInfos(*Raiz, *irmao_maior, pai);
            } else if (pai != NULL) {
                // Caso 2: Fusão com o irmão
                fundirNos(*Raiz, pai, irmao_maior);
            }
        }
    }
}


void encontrarPaiEIrmao(Arv45Mem *no_atual, Arv45Mem **pai, Arv45Mem ***irmao_maior) {
    if (*pai != NULL) {
        for (int i = 1; i <= (*pai)->N_infos + 1; i++) {
            Arv45Mem **filho = NULL;

            if (i == 1) filho = &(*pai)->esq;
            else if (i == 2) filho = &(*pai)->cent1;
            else if (i == 3) filho = &(*pai)->cent2;
            else if (i == 4) filho = &(*pai)->cent3;
            else if (i == 5) filho = &(*pai)->dir;

            if (*filho == no_atual) {
                // Identifica o irmão com mais informações
                if (i > 1 && (*pai)->N_infos >= i - 1) {
                    Arv45Mem *irmao_esquerda = (i == 2) ? (*pai)->esq : *(&(*pai)->cent1 + i - 2);
                    if (irmao_esquerda && irmao_esquerda->N_infos > 2) {
                        *irmao_maior = &irmao_esquerda;
                    }
                }
                if (i <= (*pai)->N_infos) {
                    Arv45Mem *irmao_direita = *(&(*pai)->cent1 + i - 1);
                    if (irmao_direita && irmao_direita->N_infos > 2) {
                        *irmao_maior = &irmao_direita;
                    }
                }
                return;
            }
        }
    }
}


void redistribuirInfos(Arv45Mem *no, Arv45Mem *irmao, Arv45Mem *pai) {
    if (irmao->N_infos > 2) {
        if (no->N_infos < 2) {
            // Redistribuição simples
            if (irmao->info1.bloco_inicio < no->info1.bloco_inicio) {
                // Redistribuir do irmão esquerdo
                no->info1 = pai->info1;
                pai->info1 = irmao->info1;

                // Ajustar ponteiros do irmão
                irmao->info1 = irmao->info2;
                irmao->info2 = irmao->info3;
                irmao->N_infos--;
            } else {
                // Redistribuir do irmão direito
                no->info1 = pai->info2;
                pai->info2 = irmao->info1;

                // Ajustar ponteiros do irmão
                irmao->info1 = irmao->info2;
                irmao->info2 = irmao->info3;
                irmao->N_infos--;
            }
            no->N_infos++;
        }
    }
}



void fundirNos(Arv45Mem *no, Arv45Mem *pai, Arv45Mem **irmao) {
    if (*irmao != NULL) {
        // Fusão entre o nó e o irmão
        if ((*irmao)->info1.bloco_inicio < no->info1.bloco_inicio) {
            // Fusão com irmão esquerdo
            (*irmao)->info2 = pai->info1;
            (*irmao)->info3 = no->info1;

            // Ajustar ponteiros
            (*irmao)->N_infos += no->N_infos + 1;

            // Liberar o nó
            free(no);
        } else {
            // Fusão com irmão direito
            no->info2 = pai->info1;
            no->info3 = (*irmao)->info1;

            // Ajustar ponteiros
            no->N_infos += (*irmao)->N_infos + 1;

            // Liberar o irmão
            free(*irmao);
        }
    }
}


