#include <stdio.h> 
#include <stdlib.h>
#include "Gerenciamento_Memoria.h"

void construir_memoria_do_sistema(Arv45Mem **Raiz) {
    if (*Raiz == NULL) {
        int tamanho;
        Inf45 Informacao;

        printf("Digite quantos GB sua memória possui: ");
        scanf("%d", &tamanho);

        tamanho = tamanho * 1024; // Converter GB para blocos
        Informacao.status = LIVRE;
        Informacao.bloco_inicio = 0;

        while (Informacao.bloco_inicio < tamanho) {
            // Determinar o tamanho do próximo intervalo
            if (Informacao.status == LIVRE) {
                printf("Digite quantos blocos que a memória está livre: ");
            } else {
                printf("Digite quantos blocos que a memória está ocupada: ");
            }
            scanf("%d", &Informacao.intervalo);

            // Ajustar o bloco final baseado no intervalo
            Informacao.bloco_fim = Informacao.bloco_inicio + Informacao.intervalo;

            // Ajustar para não exceder o tamanho total
            if (Informacao.bloco_fim > tamanho) {
                Informacao.bloco_fim = tamanho;
                Informacao.intervalo = Informacao.bloco_fim - Informacao.bloco_inicio;
            }

            // Inserir na árvore (função a ser implementada)
            inserir_na_arvore_45(Raiz, Informacao);

            // Alternar o status (livre/ocupado) para o próximo intervalo
            if (Informacao.status == LIVRE) {
                Informacao.status = OCUPADO;
            } else {
                Informacao.status = LIVRE;
            }


            // Atualizar o início para o próximo bloco
            Informacao.bloco_inicio = Informacao.bloco_fim;
        }

        printf("Memória alocada com sucesso!\n");
    } else {
        printf("Memória já construída.\n");
    }
}
