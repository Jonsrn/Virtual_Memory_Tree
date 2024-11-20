#include <stdio.h> 
#include <stdlib.h>
#include "Gerenciamento_Memoria.h"

void construir_memoria_do_sistema(Arv45Mem **Raiz) {
    if (*Raiz == NULL) {
        int tamanho, situacao;
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
            Informacao.bloco_fim = Informacao.bloco_inicio + Informacao.intervalo - 1;

            // Garantir que o último bloco seja preenchido
            if (Informacao.bloco_fim >= tamanho) {
                Informacao.bloco_fim = tamanho;
                Informacao.intervalo = Informacao.bloco_fim - Informacao.bloco_inicio + 1;
            }

            printf("Tentando inserir: Início: %d, Fim: %d, Intervalo: %d, Status: %s\n",
                   Informacao.bloco_inicio, Informacao.bloco_fim, Informacao.intervalo,
                   Informacao.status == LIVRE ? "LIVRE" : "OCUPADO");

            // Inserir na árvore
            insereArv45(Raiz, Informacao, NULL, NULL, &situacao);

            // Verificar se a inserção foi bem-sucedida
            if (situacao == 1) {
                printf("Intervalo [%d, %d] (%s) inserido com sucesso.\n",
                       Informacao.bloco_inicio, Informacao.bloco_fim,
                       Informacao.status == LIVRE ? "LIVRE" : "OCUPADO");
            } else {
                printf("Falha ao inserir o intervalo [%d, %d].\n",
                       Informacao.bloco_inicio, Informacao.bloco_fim);
                break;
            }

            // Alternar o status (livre/ocupado) para o próximo intervalo
            Informacao.status = (Informacao.status == LIVRE) ? OCUPADO : LIVRE;

            // Atualizar o início para o próximo bloco
            Informacao.bloco_inicio = Informacao.bloco_fim + 1;
        }

        printf("Memória alocada com sucesso!\n");
    } else {
        printf("Memória já construída.\n");
    }
}





