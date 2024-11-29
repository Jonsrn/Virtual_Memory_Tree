#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "Gerenciamento_Memoria.h"


//Funções de criação e Inserção na 2-3

//Função de criação do Nó da 2-3
Arv23Mem *criar_no_Arv23(Inf23 Info, Arv23Mem *Filho_esq, Arv23Mem *Filho_cen){
    Arv23Mem *Novo_no; 
    Novo_no = NULL; 

    Novo_no = (Arv23Mem*)malloc(sizeof(Arv23Mem)); 
    if(Novo_no == NULL){
        exit(1);
    }else{
        memset(Novo_no, 0, sizeof(Arv23Mem));
        Novo_no->info1 = Info;  
        Novo_no->esq = Filho_esq; 
        Novo_no->cent = Filho_cen;  
        Novo_no->dir = NULL; 
        Novo_no->N_infos = 1; 
    }

    return Novo_no;    


}

// Função para verificar se o nó é folha
int ehfolha(Arv23Mem *no) {
    // Um nó é folha se não tem filho esquerdo
    return (no != NULL && no->esq == NULL);
}

//Função que adiciona infos em um nó com espaço disponivel
Arv23Mem *Adiciona_chave(Arv23Mem *no_atual, Inf23 Info, Arv23Mem *Maior_No) {
   
        // Decide onde adicionar entre info1 e info2
        if (Info.bloco_inicio < no_atual->info1.bloco_inicio) {
            no_atual->info2 = no_atual->info1; // Empurra info1 para info2
            no_atual->info1 = Info;
            if (Maior_No != NULL) {
            no_atual->dir = no_atual->cent;
            no_atual->cent = Maior_No;
            }
           
        } else {
            no_atual->info2 = Info;
            if (Maior_No != NULL) {
                no_atual->dir = Maior_No;
            }
             
        }
        
        no_atual->N_infos = 2;
    

    return no_atual;
}



//Função que quebra o nó quando não há mais espaço disponivel, o do meio é promovido, e os dois maiores vão pra um novo nó
Arv23Mem *QuebraNo(Arv23Mem **No, Inf23 Info, Inf23 *Promove, Arv23Mem *Filho) {
    Arv23Mem *Maior;

    
    // Determinar qual chave será promovida
    if (Info.bloco_inicio > (*No)->info2.bloco_inicio) {
        *Promove = (*No)->info2;
        Maior = criar_no_Arv23(Info, (*No)->dir, Filho);
       

    
    } else if (Info.bloco_inicio > (*No)->info1.bloco_inicio) {
        // Caso 2: info1 < Info < info2
        *Promove = Info;
        Maior = criar_no_Arv23((*No)->info2, Filho, (*No)->dir);
        
    } else {
        // Caso 3: Info < info1
        *Promove = (*No)->info1;
        Maior = criar_no_Arv23((*No)->info2, (*No)->cent, (*No)->dir);
        (*No)->info1 = Info;
        (*No)->cent = Filho;
        
    }

    // Atualizar o nó original
    (*No)->N_infos = 1;
    (*No)->dir = NULL;

   
    return Maior;
}





//Função base de inserção na árvore 2-3
Arv23Mem *insereArv23(Arv23Mem **no, Inf23 Info, Inf23 *promove, Arv23Mem **Pai, int *situacao) {
    Arv23Mem *MaiorNo = NULL;
    Inf23 promove_local;

    if (*no == NULL) {
        *no = criar_no_Arv23(Info, NULL, NULL);
        if (*no == NULL) {
            *situacao = 0; // Falha de alocação
        } else {
            *situacao = 1; // Sucesso
        }
    } else {
        if (ehfolha(*no)) {
            if ((*no)->N_infos == 1) {
                *no = Adiciona_chave(*no, Info, NULL);
                *situacao = 1; // Sucesso
            } else {
                MaiorNo = QuebraNo(no, Info, &promove_local, NULL);

                if (Pai == NULL || *Pai == NULL) {
                    *no = criar_no_Arv23(promove_local, *no, MaiorNo);
                    MaiorNo = NULL;
                } else {
                    *promove = promove_local;
                }
                *situacao = 1;
            }
        } else {

            if (Info.bloco_inicio < (*no)->info1.bloco_inicio) {
                //entra pela esquerda

                MaiorNo = insereArv23(&((*no)->esq), Info, &promove_local, no, situacao);

            } else if (((*no)->N_infos == 1 || Info.bloco_inicio < (*no)->info2.bloco_inicio)) {
                //entra pelo centro
               
                MaiorNo = insereArv23(&((*no)->cent), Info, &promove_local, no, situacao);

            } else if ((*no)->N_infos == 2 || (Info.bloco_inicio > (*no)->info2.bloco_inicio)) {
                //vai pela direita
              
                MaiorNo = insereArv23(&((*no)->dir), Info, &promove_local, no, situacao);

            } 

            // Após a recursão, lidar com o nó promovido
            if (MaiorNo != NULL) {
                if ((*no)->N_infos == 1) {                   
                    *no = Adiciona_chave(*no, promove_local, MaiorNo);
                    MaiorNo = NULL;
                } else {                  
                    Inf23 promove1;
                    MaiorNo = QuebraNo(no, promove_local, &promove1, MaiorNo);

                    if (Pai == NULL || *Pai == NULL) {
                        *no = criar_no_Arv23(promove1, *no, MaiorNo);
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




//Funções de impressão na árvore 2-3


//Função que imprime detalhadamente as informações de cada INFO de cada Nó
void imprimirInfo(Inf23 info) {
    if (info.bloco_fim >= info.bloco_inicio && info.status_apagar == MANTER) { 
        printf("Status: %s | Bloco Início: %d | Bloco Fim: %d | Intervalo: %d\n",
               info.status == LIVRE ? "LIVRE" : "OCUPADO",
               info.bloco_inicio, info.bloco_fim,
               info.bloco_fim - info.bloco_inicio);
    }else {
        printf("Informação inválida detectada: Início: %d, Fim: %d\n", info.bloco_inicio, info.bloco_fim);
    }
}

//Função base de impressão da 2-3
void imprimirArvore23(Arv23Mem *raiz) {
    if (raiz != NULL) {   

    // Percorre o filho esquerdo
    imprimirArvore23(raiz->esq);
    // Imprime a primeira informação
    imprimirInfo(raiz->info1);
    // Sempre percorre o primeiro filho central
    imprimirArvore23(raiz->cent);

    if (raiz->N_infos == 2) {
        // Imprime a segunda informação
        imprimirInfo(raiz->info2);
        // Percorre o segundo filho central
        imprimirArvore23(raiz->dir);
       }

    }
}


//Funções relacionadas a "alocação" e "desalocação" dos blocos. 

//essa função serve pra saber se estou na ultima info da árvore
int eh_ultimo(Arv23Mem *Raiz_atual, Arv23Mem *Raiz_original, int localizacao_info) {
    int ultimo = 0;

    if (Raiz_original != NULL && Raiz_atual != NULL) {
        // Inicia a busca pelo nó mais à direita ou mais profundo
        Arv23Mem *no_atual = Raiz_original;

        // Percorre até encontrar o nó mais à direita ou ao final do caminho central
        while (no_atual != NULL) {
            // Se o nó tiver duas infos, priorizamos o lado direito
            if (no_atual->N_infos == 2 && no_atual->dir != NULL) {
                no_atual = no_atual->dir;
            } 
            // Se o nó tiver apenas uma info ou nenhuma direita, percorremos o centro
            else if (no_atual->cent != NULL) {
                no_atual = no_atual->cent;
            } 
            // Se não houver filhos centrais ou direitos, paramos no nó atual
            else {
                break;
            }
        }


        // Verifica se o nó atual é o nó mais à direita ou profundo e se a localização da Info é a última
        if (Raiz_atual == no_atual && localizacao_info == Raiz_atual->N_infos) {
            ultimo = 1; // É o último
        } 
    }

    return ultimo; // Retorna 1 se é o último, 0 caso contrário
}





//Essa função serve para atualizar o bloco encontrado que atenda aos requisitos de alocação ou desalocação (funciona pra ambos os casos)
Arv23Mem *atualizar_bloco(Arv23Mem *Raiz, int qtd_blocos, int operacao, int localizacao_info, int *situacao, Arv23Mem *Raiz_original) {
    Inf23 *info = NULL;

    // Selecionar a Info correta com base na localização
    if (localizacao_info == 1) info = &Raiz->info1;
    else if (localizacao_info == 2) info = &Raiz->info2;

    if (info != NULL) {
        // Verifica se o bloco é o último
        if (eh_ultimo(Raiz, Raiz_original, localizacao_info)) {
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

        }
    }

    return Raiz;
}


//Essa função cuida de manter todos os intervalos estruturados após as operações de alocação/desalocação, além disso
//há duas situações, se o bloco mexido não for o ultimo, a reestruturação é da esquerda pra direita, se for o último, a reestruturação é da direita pra esquerda
int ajustando_os_intervalos(Arv23Mem *Raiz, Inf23 **bloco_anterior, int opcao, Arv23Mem *Raiz_original) {
    int ajustes_realizados = 0; // Indica se ajustes foram feitos

    if (Raiz != NULL) {
        if (opcao == 1) {
            // Processa a subárvore esquerda primeiro (ordem padrão)
            ajustes_realizados |= ajustando_os_intervalos(Raiz->esq, bloco_anterior, opcao, Raiz_original);

            // Processa Info1 e a subárvore cent
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
            ajustes_realizados |= ajustando_os_intervalos(Raiz->cent, bloco_anterior, opcao, Raiz_original);

            // Processa Info2 e a subárvore direita (se existir)
            if (Raiz->N_infos == 2 && Raiz->info2.status_apagar == MANTER) {
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
            ajustes_realizados |= ajustando_os_intervalos(Raiz->dir, bloco_anterior, opcao, Raiz_original);

            
        } else if (opcao == 2) {
            // Processa a subárvore direita primeiro (ordem invertida)
            ajustes_realizados |= ajustando_os_intervalos(Raiz->dir, bloco_anterior, opcao, Raiz_original);


            // Processa Info2 e as subárvores cent
            if (Raiz->N_infos == 2 && Raiz->info2.status_apagar == MANTER) {
                if (*bloco_anterior != NULL) {
                    if ((*bloco_anterior)->bloco_inicio - 1 != Raiz->info2.bloco_fim) {
                        Raiz->info2.bloco_fim = (*bloco_anterior)->bloco_inicio - 1;
                        ajustes_realizados = 1;
                    }
                }
                
                if(Raiz->dir != NULL){
                    if (Raiz->N_infos == 2 && (Raiz->dir->info1.status_apagar) == APAGAR && eh_ultimo(Raiz->dir, Raiz_original, 1)) {
                        Raiz->info2.bloco_fim = Raiz->info2.tam_total; // Atualiza o fim do penúltimo bloco
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
            
            ajustes_realizados |= ajustando_os_intervalos(Raiz->cent, bloco_anterior, opcao, Raiz_original);

            // Processa Info1 e a subárvore esquerda
            if (Raiz->info1.status_apagar == MANTER) {
                if (*bloco_anterior != NULL) {
                    if ((*bloco_anterior)->bloco_inicio - 1 != Raiz->info1.bloco_fim) {
                        Raiz->info1.bloco_fim = (*bloco_anterior)->bloco_inicio - 1;
                        ajustes_realizados = 1;
                    }
                    
                }
                if(Raiz->cent != NULL){
                    if (Raiz->N_infos >= 1 && (Raiz->cent->info1.status_apagar) == APAGAR && eh_ultimo(Raiz->cent, Raiz_original, 1)) {
                        Raiz->info1.bloco_fim = Raiz->info1.tam_total; // Atualiza o fim do penúltimo bloco
                        ajustes_realizados = 1;
                    
                    }
                }    

                if (Raiz->N_infos == 2 && Raiz->info2.status_apagar == APAGAR && eh_ultimo(Raiz, Raiz_original, 2)) {
                    Raiz->info1.bloco_fim = Raiz->info1.tam_total; // Atualiza o fim do penúltimo bloco
                    ajustes_realizados = 1;
                   
                }


                int novo_intervalo = Raiz->info1.bloco_fim - Raiz->info1.bloco_inicio + 1;
                if (novo_intervalo != Raiz->info1.intervalo) {
                    Raiz->info1.intervalo = novo_intervalo;
                    ajustes_realizados = 1;
                }
                *bloco_anterior = &Raiz->info1;
            }
            ajustes_realizados |= ajustando_os_intervalos(Raiz->esq, bloco_anterior, opcao, Raiz_original);
        }
    }

    return ajustes_realizados; // Retorna 1 se ajustes foram realizados, 0 caso contrário
}



//função que cuida de encontrar uma INFO com a TAG LIVRE, com espaço suficiente pra comportar a operação
int alocar_memoria(Arv23Mem *Raiz, int qtd_blocos, Arv23Mem *Raiz_Original) {
    int alocou = 0; // Status inicial: não encontrou bloco livre.
    //0, significa que não encontrou um bloco livre.
    // 1  significa que encontrei um bloco com espaço suficiente pra tomar parte de suas unidades (mas ficou pendencia, se não encontrei um bloco adjacente) (*** deve ser tratado externamente, com a criação de um novo nó)
    //2 significa que deu certo, encontrei um bloco com espaço suficiente pra tomar parte de suas unidades e que eu já aloquei o espaço pra outro bloco, não há mais pendencia (quando tudo é resolvido no próprio Nó)
    //3 significa que deu certo, encontrei um bloco com espaço suficiente pra retirar seus blocos e que eu já aloquei o espaço pra outro bloco, mas esse bloco livre ficou vazio, ele precisa ser excluído. (Sem pendencia de manipulação, os blocos foram para o outro bloco do mesmo nó)
    //4 significa que deu certo, encontrei um bloco com espaço suficiente pra retirar seus blocos e que eu já aloquei o espaço pra outro bloco, mas esse bloco livre ficou vazio, ele precisa ser excluído. (Ficou pendencia de inserção desses blocos)
    //5 significa que é o ultimo bloco, precisa ser reajustado de maneira diferente
    if (Raiz != NULL) {
        // Tentar alocar nos filhos à esquerda primeiro
        alocou = alocar_memoria(Raiz->esq, qtd_blocos, Raiz_Original);

        if (alocou == 0) {
            // Percorrer as Infos do nó atual
            for (int i = 1; i <= Raiz->N_infos; i++) {
                Inf23 *info = NULL;

                // Selecionar a Info correta
                if (i == 1){
                     info = &Raiz->info1;
                }else if (i == 2){
                     info = &Raiz->info2;
                } 

                int situacao;    

                // Verificar se a Info é LIVRE e tem espaço suficiente
                if (info->status == LIVRE && info->intervalo >= qtd_blocos) {
                    if (qtd_blocos < info->intervalo) {
                        
                        situacao = 0; 
                        // Caso: Bloco LIVRE tem mais espaço do que o necessário
                        Raiz = atualizar_bloco(Raiz, qtd_blocos, 2, i, &situacao, Raiz_Original); // Reduz o intervalo do bloco LIVRE
                        if(situacao == 1){
                            //1 significa que é normal, n está no ultimo bloco
                            alocou = 2; 
                        }else if(situacao == 2){
                            //é o ultimo bloco
                            alocou = 6; 
                        }
                        break;
                    } else {
                        // Caso: Bloco LIVRE tem exatamente o espaço necessário
                        Raiz = atualizar_bloco(Raiz, qtd_blocos, 2, i, &situacao, Raiz_Original); // Reduz o intervalo do bloco LIVRE
                        info->status_apagar = APAGAR; // Marcar o bloco para exclusão 
                        
                        if(situacao == 1){
                            //1 significa que é normal, n está no ultimo bloco
                            alocou = 3; //3 significa que preciso de todo o bloco, mas não sou o ultimo
                        }else if(situacao == 2){
                            //é o ultimo bloco
                            alocou = 5; //5 
                        }
                        
                        break;
                    }
                }
            }

            if (alocou == 0) {
                // Tentar alocar nos filhos central e à direita
                alocou = alocar_memoria(Raiz->cent, qtd_blocos, Raiz_Original);
                if (alocou == 0 && Raiz->dir != NULL){ 
                    alocou = alocar_memoria(Raiz->dir, qtd_blocos, Raiz_Original);
                }     
            }
        }

    }

    return alocou; // Retorna o status da alocação
}

//Função que cuida de encontrar a info com a TAG OCUPADO, com espaço suficiente pra liberação 
int desalocar_memoria(Arv23Mem *Raiz, int qtd_blocos, Arv23Mem *Raiz_Original){
    int desalocou = 0;
    

    if(Raiz != NULL){
         // Tentar alocar nos filhos à esquerda primeiro
        desalocou = desalocar_memoria(Raiz->esq, qtd_blocos, Raiz_Original);

        if (desalocou == 0) {
            // Percorrer as Infos do nó atual
            for (int i = 1; i <= Raiz->N_infos; i++) {
                Inf23 *info = NULL;

                // Selecionar a Info correta
                if (i == 1){
                     info = &Raiz->info1;
                }else if (i == 2){
                     info = &Raiz->info2;
                }

                int situacao; 
                // Verificar se a Info é OCUPADA e tem espaço suficiente para ser liberada
                if (info->status == OCUPADO && info->intervalo >= qtd_blocos) {
                    if (qtd_blocos < info->intervalo) {
                        
                        situacao = 0; 
                        // Caso: Bloco OCUPADO tem mais espaço do que o necessário
                        Raiz = atualizar_bloco(Raiz, qtd_blocos, 2, i, &situacao, Raiz_Original); // Reduz o intervalo do bloco OCUPADO
                        if(situacao == 1){
                            //1 significa que é normal, n está no ultimo bloco
                            desalocou = 2; 
                        }else if(situacao == 2){
                            //é o ultimo bloco
                            desalocou = 6; 
                        }
                        break;
                    } else {
                        // Caso: Bloco OCUPADO tem exatamente o espaço necessário 

                        Raiz = atualizar_bloco(Raiz, qtd_blocos, 2, i, &situacao, Raiz_Original); // Reduz o intervalo do bloco OCUPADO
                        info->status_apagar = APAGAR; // Marcar o bloco para exclusão
                        if(situacao == 1){
                            //1 significa que é normal, n está no ultimo bloco
                            desalocou = 3; 
                        }else if(situacao == 2){
                            //é o ultimo bloco
                            desalocou = 5; 
                        }
                        break;
                    }
                }
            }

            if (desalocou == 0) {
                // Tentar alocar nos filhos centrais e à direita
                desalocou = desalocar_memoria(Raiz->cent, qtd_blocos, Raiz_Original);
                if (desalocou == 0 && Raiz->dir != NULL){ 
                    desalocou = desalocar_memoria(Raiz->dir, qtd_blocos, Raiz_Original);
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

int agrupar_infos(Arv23Mem *Raiz, Inf23 **info_anterior) {
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
        agrupamento_realizado |= agrupar_infos(Raiz->cent, info_anterior);

        // Processa Info2 e a subárvore cent2 (se existir)
        if (Raiz->N_infos == 2 && Raiz->info2.status_apagar == MANTER) {
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
        agrupamento_realizado |= agrupar_infos(Raiz->dir, info_anterior);


       
   }

   return agrupamento_realizado; // Retorna 1 se agrupamentos foram realizados, 0 caso contrário

}


//Função que cuida de percorrer e fazer uma cópia de todas as infos da árvore, desconsiderando os que serão excluídos
int percorrer_recuperar_Infos(Arv23Mem *Raiz, Inf23 ***vetor_recuperado, int *numero_infos) {
    int operacao = 1; // 1 significa que a operação deu certo

    if (Raiz != NULL) {
        // Percorrer a subárvore esquerda
        operacao = percorrer_recuperar_Infos(Raiz->esq, vetor_recuperado, numero_infos);

        // Adicionar Info1 ao vetor se estiver com a TAG MANTER
        if (operacao == 1 && Raiz->info1.status_apagar == MANTER) {
            Inf23 **temp = (Inf23 **)realloc(*vetor_recuperado, (*numero_infos + 1) * sizeof(Inf23 *));
            if (temp == NULL) {
                operacao = 0; // Falha na realocação
            } else {
                *vetor_recuperado = temp;
                Inf23 *nova_info = (Inf23 *)malloc(sizeof(Inf23));
                if (nova_info == NULL) {
                    operacao = 0; // Falha na alocação
                } else {
                    *nova_info = Raiz->info1; // Copia os dados
                    (*vetor_recuperado)[*numero_infos] = nova_info;
                    (*numero_infos)++;
                }
            }
        }

        // Percorrer a subárvore cent1
        if (operacao == 1) {
            operacao = percorrer_recuperar_Infos(Raiz->cent, vetor_recuperado, numero_infos);
        }

        // Adicionar Info2 ao vetor se existir e estiver com a TAG MANTER
        if (operacao == 1 && Raiz->N_infos == 2 && Raiz->info2.status_apagar == MANTER) {
            Inf23 **temp = (Inf23 **)realloc(*vetor_recuperado, (*numero_infos + 1) * sizeof(Inf23 *));
            if (temp == NULL) {
                operacao = 0;
            } else {
                *vetor_recuperado = temp;
                Inf23 *nova_info = (Inf23 *)malloc(sizeof(Inf23));
                if (nova_info == NULL) {
                    operacao = 0;
                } else {
                    *nova_info = Raiz->info2; // Copia os dados
                    (*vetor_recuperado)[*numero_infos] = nova_info;
                    (*numero_infos)++;
                }
            }
        }

        // Percorrer a subárvore direita
        if (operacao == 1) {
            operacao = percorrer_recuperar_Infos(Raiz->dir, vetor_recuperado, numero_infos);
        }

        
   }
   return operacao; // Retorna o status da operação
}



//Função de liberação

void liberarArvore23(Arv23Mem **Raiz) {
    if (*Raiz != NULL) {
        // Libera as subárvores recursivamente
        liberarArvore23(&(*Raiz)->esq);
        liberarArvore23(&(*Raiz)->cent);
        liberarArvore23(&(*Raiz)->dir);

        // Libera o próprio nó
        free(*Raiz);
        *Raiz = NULL; 
    }
}


//Funções auxiliares de melhoria de leitura de código. 

//Essa função constrói uma nova árvore, com o vetor recuperado de Infos, e libera a árvore antiga, atribuindo a arvore nova ao antigo endereço

int reconstruir_arvore_23(Arv23Mem **Raiz, int tamanho_vetor, Inf23 **vetor_recuperado){
    int operacao = 0; //0 significa que não deu certo
    if(*Raiz != NULL){
        int situacao_atual = 1; 
        Arv23Mem *Nova_Raiz; 
        Nova_Raiz = NULL; 
        Inf23 Nova_insercao; 
        operacao = 1; //por enquanto, tratamos como uma operação que deu certo. 

        for(int i = 0; i < tamanho_vetor; i++){
           Nova_insercao = *(vetor_recuperado[i]);
           
           insereArv23(&Nova_Raiz, Nova_insercao, NULL, NULL, &situacao_atual); 

           if(situacao_atual != 1){
              //falhou na criação da nova árvore 
              liberarArvore23(&Nova_Raiz); //Como falhou, é preciso liberar o que foi alocado
              operacao = 2; //2 significa que falhou na criação da nova árvore
              break;  
           }           
        
        }

        if(situacao_atual == 1){
             //com a nova árvore criada com sucesso, podemos liberar a árvore antiga. 

             liberarArvore23(Raiz); 

             if(*Raiz == NULL){
                //A árvore foi limpa com sucesso. 
                // Com isso a gente pode atribuir a nova árvore

                *Raiz = Nova_Raiz; 
            }else{
                //A liberação falhou

                operacao = 3; //significa que a operação falhou na liberação da árvore
            }

        }
    }

    return operacao; 
}

