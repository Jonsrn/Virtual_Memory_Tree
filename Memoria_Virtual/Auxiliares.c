#include <stdio.h> 
#include <stdlib.h>
#include "Gerenciamento_Memoria.h"


//Essa função monta o dataset na árvore, para que as operações possam ser realizadas
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
        Informacao.tam_total = tamanho; 

        situacao = 1; //1 significa que deu certo

        while (Informacao.bloco_inicio < tamanho) {
            // Determinar o tamanho do próximo intervalo
            if (Informacao.status == LIVRE) {
                printf("Digite quantos blocos que a memória está livre: ");
            } else {
                printf("Digite quantos blocos que a memória está ocupada: ");
            }
            scanf("%d", &Informacao.intervalo);

            //falta uma validação aqui, se digitar 0 ou negativo

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



//Função auxiliar que cuida das operações de "alocação", ou seja, transferir blocos do status LIVRE, pra OCUPADO
void alocar_memoria_para_programa(Arv45Mem **Raiz){
    int situacao;  
    if(*Raiz != NULL){
        int qtd_blocos, operacao, numero_infos;
        printf("Essa é a alocação de memória do sistema\n"); 
        printf("Digite quantos blocos de memória (1mb) que o programa precisa: ");

        //validar, para não inserir valores negativos ou 0
        scanf("%d", &qtd_blocos); 
        Inf45 *bloco_anterior, *Info_anterior, **vetor_recuperado;
        bloco_anterior = NULL;
        Info_anterior = NULL; 
        vetor_recuperado = NULL;
        situacao = 1; //deu certo
        


     
       operacao = alocar_memoria((*Raiz), qtd_blocos); 
       if(operacao == 2 || operacao == 3 || operacao == 4){
           ajustando_os_intervalos(*Raiz, &bloco_anterior, 1); // A alocação não usou o bloco final
       }else if(operacao == 5 || operacao == 6){
        
           ajustando_os_intervalos(*Raiz, &bloco_anterior, 2); //A alocação usou o bloco final
           
       }
       
       
      
       

       

       if(operacao == 0){
            //Não há espaço disponivel suficiente na memória
          
            situacao = 4;
       }else if((*Raiz)->N_infos == 1 && (*Raiz)->esq == NULL){
          //A quantidade de memoria foi reservada, mas como não há mais blocos ocupados, um precisa ser criado 
          // chama a função de criação do Nó, coleta o Último bloco da Info1, e o novo passa a ser o inicio, e depois adiciona o intervalo
         
          Inf45 Informacao_inserir; 
          int operacao_insercao; 
          Informacao_inserir.bloco_inicio = 0; 
          Informacao_inserir.bloco_fim = qtd_blocos - 1; 
          Informacao_inserir.intervalo = qtd_blocos; 
          Informacao_inserir.status = OCUPADO; 
          Informacao_inserir.status_apagar = MANTER; 
          Informacao_inserir.tam_total = (*Raiz)->info1.tam_total; 
          insereArv45(Raiz, Informacao_inserir, NULL, NULL, &operacao_insercao); 
          
          if(operacao_insercao != 1){
              //A operação falhou, pois houve falha na criação de um novo bloco
              situacao = 3;
          }
          //o retorno com sucesso
       }else if(operacao == 4 || operacao == 5 || operacao == 3){
          //4 significa que tudo deu certo, mas um bloco precisa ser apagado

         

          operacao = agrupar_infos(*Raiz, &Info_anterior); //o agrupamento vai juntar blocos que ficarão adjacentes e sinalizará mais um bloco pra remoção

          

          numero_infos = 0; 

          
          
          operacao = percorrer_recuperar_Infos(*Raiz, &vetor_recuperado, &numero_infos); 

          
          

          if(vetor_recuperado != NULL){
             Inf45 Nova_insercao;
             Arv45Mem *Nova_Raiz; 
             Nova_Raiz = NULL; 
             int situacao_atual = 1; 

             for(int i = 0; i < numero_infos; i++){
                Nova_insercao = *(vetor_recuperado[i]); 

                insereArv45(&Nova_Raiz, Nova_insercao, NULL, NULL, &situacao_atual); 
                if(situacao_atual != 1){
                    break; 
                    //para tudo
                }


             }
            
             
             if(situacao_atual == 1){
                //liberamos a árvore antiga e a árvore nova se torna a arvore padrão. 

                liberarArvore45(Raiz); 

                if(*Raiz == NULL){
                    //a raiz é nula, podemos atribuir a nova árvore 
                    
                    *Raiz = Nova_Raiz; 

                }else{
                    //A liberação da árvore antiga falhou
                    situacao = 4; 
                }



             }else{
                situacao = 3; //Falhou na construção da nova árvore
             }  




          }else{
             //houve falha na reconstrução dos Nós
               situacao = 2;          
          }
          
          
          
          
        

          

          

          

        
       }


    }else{
        //Falhou porque não tem memória alocada ainda. 
        situacao = 0;
    }

    situacao_alocacao_memoria(situacao); 
}

//Função auxiliar que cuida das operações de "desalocação", ou seja, transferir blocos do status OCUPADO, pra LIVRE
void desalocar_memoria_sistema(Arv45Mem **Raiz){
   int situacao; 

   if(*Raiz != NULL){
       int qtd_blocos, operacao, numero_infos; 
       printf("Essa é a liberação de memória do sistema\n"); 
       printf("Digite quantos blocos de memória (1mb) que deseja liberar: ");

       //Validar pra não inserir valores negativos ou 0. 
       scanf("%d", &qtd_blocos); 
       Inf45 *bloco_anterior, *Info_anterior, **vetor_recuperado;  
       bloco_anterior = NULL; 
       Info_anterior = NULL; 
       vetor_recuperado = NULL;
       situacao = 1; 
       numero_infos = 0;

       operacao = desalocar_memoria((*Raiz), qtd_blocos); 
      
       if(operacao == 2 || operacao == 3 || operacao == 4){
          
          
           ajustando_os_intervalos(*Raiz, &bloco_anterior, 1); // A alocação não usou o bloco final
       }else if(operacao == 5 || operacao == 6){ 
          
          
           ajustando_os_intervalos(*Raiz, &bloco_anterior, 2); //A alocação usou o bloco final
           
       }

       if(operacao == 0){
            //Não há memória suficiente pra ser liberada, não faço mais nada
            situacao = 4;
       }else if((*Raiz)->N_infos == 1 && (*Raiz)->esq == NULL){
          //A quantidade de memoria foi reservada, mas como não há blocos livres, um precisa ser criado 
          // chama a função de criação do Nó, coleta o Último bloco da Info1, e adiciona 1 pra ser o inicio, e depois adiciona o intervalo
          
          Inf45 Informacao_inserir; 
          int operacao_insercao; 
          Informacao_inserir.bloco_inicio = 0; 
          Informacao_inserir.bloco_fim = qtd_blocos - 1; 
          Informacao_inserir.intervalo = qtd_blocos; 
          Informacao_inserir.status = LIVRE; 
          Informacao_inserir.status_apagar = MANTER; 
          Informacao_inserir.tam_total = (*Raiz)->info1.tam_total; 

          insereArv45(Raiz, Informacao_inserir, NULL, NULL, &operacao_insercao); 
          
          if(operacao_insercao != 1){
              //A operação falhou, pois houve falha na criação de um novo bloco
              situacao = 3;
          }

          //o retorno com sucesso
       }else if(operacao == 4 || operacao == 5 || operacao == 3){
          //4 significa que tudo deu certo, mas um bloco precisa ser apagado

          
          
          operacao = agrupar_infos(*Raiz, &Info_anterior);

            
          percorrer_recuperar_Infos(*Raiz, &vetor_recuperado, &numero_infos); 
          

          
          

               
          
          if(vetor_recuperado != NULL){
             Inf45 Nova_insercao;
             Arv45Mem *Nova_Raiz; 
             Nova_Raiz = NULL; 
             int situacao_atual = 1; 

             for(int i = 0; i < numero_infos; i++){
                Nova_insercao = *(vetor_recuperado[i]); 

                insereArv45(&Nova_Raiz, Nova_insercao, NULL, NULL, &situacao_atual); 
                if(situacao_atual != 1){
                    break; 
                    //para tudo
                }


             }
             

            
             
             if(situacao_atual == 1){
                //liberamos a árvore antiga e a árvore nova se torna a arvore padrão. 

                liberarArvore45(Raiz); 

                if(*Raiz == NULL){
                    //a raiz é nula, podemos atribuir a nova árvore 
                    
                    *Raiz = Nova_Raiz; 

                }else{
                    //A liberação da árvore antiga falhou
                    situacao = 4; 
                }
                
               



             }else{
                situacao = 3; //Falhou na construção da nova árvore
             }  
          

          

          //aqui chama a função que vai excluir o Nó. 

          if(operacao != 1){
               //houve falha na exclusão do Nó
               situacao = 2;
          }
       }






      
       








   }



   }else{
      //Não há dataset montado
      situacao = 0; 
   }


   situacao_desalocacao_memoria(situacao); 
   
 

}


