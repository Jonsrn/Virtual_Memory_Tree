#include <stdio.h> 
#include <stdlib.h>
#include "Gerenciamento_Memoria.h"

void construir_memoria_do_sistema(Arv45Mem **Raiz) {
    int situacao; 
    if (*Raiz == NULL) {
        int tamanho, status;
        Inf45 Informacao;

        printf("Digite quantos GB sua memória possui: ");
        scanf("%d", &tamanho);

        tamanho = tamanho * 1024; // Converter GB para blocos
        Informacao.status = LIVRE;
        Informacao.status_apagar = MANTER; 
        Informacao.bloco_inicio = 0;

        situacao = 1; //1 significa que deu certo

        while (Informacao.bloco_inicio < tamanho) {
            // Determinar o tamanho do próximo intervalo
            if (Informacao.status == LIVRE) {
                printf("Digite quantos blocos que a memória está livre: ");
            } else {
                printf("Digite quantos blocos que a memória está ocupada: ");
            }
            scanf("%d", &Informacao.intervalo);

            // Ajustar o bloco final baseado no intervalo
            Informacao.bloco_fim = Informacao.bloco_inicio + Informacao.intervalo - 1;

            // Garantir que o último bloco seja preenchido
            if (Informacao.bloco_fim >= tamanho) {
                Informacao.bloco_fim = tamanho;
                Informacao.intervalo = Informacao.bloco_fim - Informacao.bloco_inicio + 1;
            }

            // Inserir na árvore
            insereArv45(Raiz, Informacao, NULL, NULL, &status);

            // Verificar se a inserção foi bem-sucedida
            if (status != 1) {
                situacao = 2; //A operação falhou porque houve falha na alocação da Inserção
                //A inserção foi bem sucedida 
                break;
            }

            // Alternar o status (livre/ocupado) para o próximo intervalo
            Informacao.status = (Informacao.status == LIVRE) ? OCUPADO : LIVRE;

            // Atualizar o início para o próximo bloco
            Informacao.bloco_inicio = Informacao.bloco_fim + 1;
        }

        
    } else {
        //Memória já construída.
        situacao = 0; 
        
    }

    situacao_construcao_memoria(situacao); 
}


void alocar_memoria_para_programa(Arv45Mem **Raiz){
    int situacao;  
    if(*Raiz != NULL){
        int qtd_blocos, operacao;
        printf("Essa é a alocação de memória do sistema\n"); 
        printf("Digite quantos blocos de memória (1mb) que o programa precisa: ");
        scanf("%d", &qtd_blocos); 

        situacao = 1; //deu certo



       operacao = alocar_memoria((*Raiz), qtd_blocos); 

       

       if(operacao == 0){
            //Não há espaço disponivel suficiente na memória
            situacao = 4;
       }else if(operacao == 1){
          //A quantidade de memoria foi reservada, mas como não há blocos ocupados, um precisa ser criado 
          // chama a função de criação do Nó, coleta o Último bloco da Info1, e adiciona 1 pra ser o inicio, e depois adiciona o intervalo
          
          if(operacao != 1){
              //A operação falhou, pois houve falha na criação de um novo bloco
              situacao = 3;
          }

          //o retorno com sucesso
       }else if(operacao == 3){
          //3 significa que tudo deu certo, mas um bloco precisa ser apagado

          

          

          //aqui chama a função que vai excluir o Nó. 

          if(operacao != 1){
               //houve falha na exclusão do Nó
               situacao = 2;
          }
       }


    }else{
        //Falhou porque não tem memória alocada ainda. 
        situacao = 0;
    }

    situacao_alocacao_memoria(situacao); 
}



