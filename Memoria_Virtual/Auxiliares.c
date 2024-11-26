#include <stdio.h> 
#include <stdlib.h>
#include "Gerenciamento_Memoria.h"


//Essa função monta o dataset na árvore, para que as operações possam ser realizadas
void construir_memoria_do_sistema(Arv45Mem **Raiz) {
    int situacao; 
    if (*Raiz == NULL) {
        int tamanho, status, confirmacao;
        Inf45 Informacao;

        
        do{
            printf("Digite quantos GB sua memória possui(1gb a 4 gb): "); // de fato pode ser qualquer tamanho, mas acho melhor limitar
            scanf("%d", &tamanho);

            if(tamanho > 0 && tamanho <= 4){ //validação
                confirmacao = 1; 
            }else{
                confirmacao = 0; 
                printf("Por favor, digite um valor entre o intervalo mencionado, 1 a 4.\n"); 
            }  
 

        }while(confirmacao == 0);     

        tamanho = tamanho * 1024; // Converter GB para blocos
        Informacao.status = LIVRE;
        Informacao.status_apagar = MANTER; 
        Informacao.bloco_inicio = 0;
        Informacao.tam_total = tamanho - 1; //coloca o tamanho total em cada um dos blocos. Como a memoria inicia em 0, 1gb, que é 1024, vai de 0 a 1023

        situacao = 1; //1 significa que deu certo

        while (Informacao.bloco_inicio < tamanho) {
            confirmacao = 0; 
            // Determinar o tamanho do próximo intervalo
            do{
                if (Informacao.status == LIVRE) {
                    printf("Digite quantos blocos que a memória está livre: ");
                } else {
                    printf("Digite quantos blocos que a memória está ocupada: ");
                }
                scanf("%d", &Informacao.intervalo);

                if(Informacao.intervalo > 0){ //validação
                    confirmacao = 1; 
                }else{
                    confirmacao = 0; 
                    printf("Digite um valor positivo\n"); 
                }

            }while(confirmacao == 0);     

           

            // Ajustar o bloco final baseado no intervalo
            Informacao.bloco_fim = Informacao.bloco_inicio + Informacao.intervalo - 1;

            // Garantir que o último bloco seja preenchido
            if (Informacao.bloco_fim >= tamanho) {
                Informacao.bloco_fim = tamanho - 1;
                Informacao.intervalo = Informacao.bloco_fim - Informacao.bloco_inicio + 1;
            }

            // Inserir na árvore
            insereArv45(Raiz, Informacao, NULL, NULL, &status);

            // Verificar se a inserção foi bem-sucedida
            if (status != 1) {
                situacao = 2; //A operação falhou porque houve falha na alocação da Inserção
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
        int qtd_blocos, operacao, numero_infos, confirmacao;
        Inf45 *bloco_anterior, *Info_anterior, **vetor_recuperado;
        bloco_anterior = NULL;
        Info_anterior = NULL; 
        vetor_recuperado = NULL;
        situacao = 1; //deu certo, partimos desse pressuposto
        numero_infos = 0; 



        printf("Essa é a alocação de memória do sistema\n"); 
        
        do{
            printf("Digite quantos blocos de memória (1mb) que o programa precisa: ");
            scanf("%d", &qtd_blocos); 

            if(qtd_blocos > 0){//validação
                confirmacao = 1; 
            }else{
                confirmacao = 0; 
                printf("Digite um valor positivo\n"); 
            }

        }while(confirmacao == 0); 

        qtd_blocos = qtd_blocos + 1;     
        
        
     
       operacao = alocar_memoria((*Raiz), qtd_blocos); //primeiro passo, buscar, se encontrar, manipular o bloco e confirmar
       
       if(operacao == 0){
          //Não há espaço disponivel suficiente na memória
          situacao = 7; 
       }else if(operacao == 2 || operacao == 3 || operacao == 4){
           ajustando_os_intervalos(*Raiz, &bloco_anterior, 1); // A alocação não usou o bloco final
       }else if(operacao == 5 || operacao == 6){        
           ajustando_os_intervalos(*Raiz, &bloco_anterior, 2); //A alocação usou o bloco final           
       }
       
       
      
       
       if((*Raiz)->N_infos == 1 && (*Raiz)->esq == NULL && operacao != 0){
          //A quantidade de memoria foi reservada, mas como não há mais blocos ocupados, um precisa ser criado 
          // chama a função de criação do Nó, coleta o Último bloco da Info1, e o novo passa a ser o inicio, e depois adiciona o intervalo
          
          Inf45 Informacao_inserir = { .bloco_inicio = 0, .bloco_fim = qtd_blocos - 1, .intervalo = qtd_blocos, .status = OCUPADO, .status_apagar = MANTER, .tam_total = (*Raiz)->info1.tam_total };
          int operacao_insercao; 
          insereArv45(Raiz, Informacao_inserir, NULL, NULL, &operacao_insercao); 
          
          if(operacao_insercao != 1){
              //A operação de inserção do novo nó falhou, pois houve falha na criação de um novo bloco
              situacao = 6;
          }
          if((*Raiz)->info2.status_apagar == APAGAR && operacao_insercao == 1){
             //na condição de ter só uma Info, ao alocar o total da Info original LIVRE pra OCUPADO, LIVRE Se torna Lixo, precisa ser eliminado
        

             operacao = percorrer_recuperar_Infos(*Raiz, &vetor_recuperado, &numero_infos); //A função irá percorrer a árvore e recuperar todas as Infos Válidas na árvore

             if(operacao == 1){
                //como recuperamos a Info util, reconstruiremos em uma nova árvore
                operacao =  reconstruir_arvore_45(Raiz, numero_infos, vetor_recuperado);

                if(operacao != 1){
                    //falhou

                    if(operacao == 0){
                        //Falhou porque a Raiz que foi pra lá era Nula
                        situacao = 5; //5 Significa que a árvore original que deveria ser liberada era inválida
                    }
                    if(operacao == 2){
                        //Falhou na reconstrução da árvore
                        situacao = 4; //4 significa que houve uma falha na reconstrução da árvore
                    }
                    if(operacao == 3){
                        //Falhou na liberação da árvore antiga
                        situacao = 3; //3 significa que houve uma falha na liberação da antiga árvore
                    }
               }



             }else{
                //houve falha na recuperação dos Nós
                situacao = 2; 
             }

          }
          
       }else if(operacao == 3 || operacao == 4 || operacao == 5){
          //3, 4 e 5 significam que tudo deu certo, mas um ou mais blocos precisam ser apagados        
          
          //se tem bloco que vai sumir, precisamos ver se vai precisar agrupar, agrupando caso necessário
          operacao = agrupar_infos(*Raiz, &Info_anterior); //o agrupamento vai juntar blocos que ficarão adjacentes e sinalizará mais um bloco pra remoção, caso necessário 
          //A função de agrupar Infos retorna 1 se precisou agrupar, e 0 caso não tenha sido preciso, nesse caso, não é preciso validar, pq de toda forma tem pelo menos uma Info que tem de ser eliminada  
          
          //No melhor dos cenários (apagando a Info do Final), teremos de apagar uma INFO, no pior dos casos, agrupamos e eliminamos duas Infos
          operacao = percorrer_recuperar_Infos(*Raiz, &vetor_recuperado, &numero_infos); //A função irá percorrer a árvore e recuperar todas as Infos Válidas na árvore
          
          //criar uma função pra percorrer o vetor, criar a nova arvore, liberar a árvore antiga e retornar a nova
          
          if(operacao == 1){
             //Deu certo a recuperação de todas Infos
            operacao =  reconstruir_arvore_45(Raiz, numero_infos, vetor_recuperado);  

            if(operacao != 1){
                //falhou

                if(operacao == 0){
                    //Falhou porque a Raiz que foi pra lá era Nula
                    situacao = 5; //5 Significa que a árvore original que deveria ser liberada era inválida
                }
                if(operacao == 2){
                    //Falhou na reconstrução da árvore
                    situacao = 4; //4 significa que houve uma falha na reconstrução da árvore
                }
                if(operacao == 3){
                    //Falhou na liberação da árvore antiga
                    situacao = 3; //3 significa que houve uma falha na liberação da antiga árvore
                }
            }




          }else{
             //houve falha na recuperação dos Nós
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
       int qtd_blocos, operacao, numero_infos, confirmacao;
       Inf45 *bloco_anterior, *Info_anterior, **vetor_recuperado;
       bloco_anterior = NULL;
       Info_anterior = NULL; 
       vetor_recuperado = NULL;
       situacao = 1; //deu certo, partimos desse pressuposto
       numero_infos = 0;


       printf("Essa é a liberação de memória do sistema\n"); 

       do{
            printf("Digite quantos blocos de memória (1mb) que deseja liberar: ");
            //Validar pra não inserir valores negativos ou 0. 
            scanf("%d", &qtd_blocos); 

            if(qtd_blocos > 0){ //validação de entrada
                confirmacao = 1; 
            }else{
                confirmacao = 0; 
                printf("Digite um valor positivo\n"); 
            }


       }while(confirmacao == 0);    

       qtd_blocos = qtd_blocos + 1;  
       






       operacao = desalocar_memoria((*Raiz), qtd_blocos); 
      
       if(operacao == 0){
          //Não há espaço disponivel suficiente na memória
          situacao = 7; 
       }else if(operacao == 2 || operacao == 3 || operacao == 4){
           ajustando_os_intervalos(*Raiz, &bloco_anterior, 1); // A alocação não usou o bloco final
       }else if(operacao == 5 || operacao == 6){        
           ajustando_os_intervalos(*Raiz, &bloco_anterior, 2); //A alocação usou o bloco final           
       }



       
       if((*Raiz)->N_infos == 1 && (*Raiz)->esq == NULL && operacao != 0){
            //A quantidade de memoria foi reservada, mas como não há mais blocos ocupados, um precisa ser criado 
            // chama a função de criação do Nó, coleta o Último bloco da Info1, e o novo passa a ser o inicio, e depois adiciona o intervalo
          
            Inf45 Informacao_inserir = { .bloco_inicio = 0, .bloco_fim = qtd_blocos - 1, .intervalo = qtd_blocos, .status = LIVRE, .status_apagar = MANTER, .tam_total = (*Raiz)->info1.tam_total };
            int operacao_insercao; 
            insereArv45(Raiz, Informacao_inserir, NULL, NULL, &operacao_insercao); 
            
            if(operacao_insercao != 1){
                //A operação de inserção do novo nó falhou, pois houve falha na criação de um novo bloco
                situacao = 6;
            }
            if((*Raiz)->info2.status_apagar == APAGAR && operacao_insercao == 1){
                //na condição de ter só uma Info, ao alocar o total da Info original OCUPADO pra LIVRE, OCUPADO Se torna Lixo, precisa ser eliminado
            

                operacao = percorrer_recuperar_Infos(*Raiz, &vetor_recuperado, &numero_infos); //A função irá percorrer a árvore e recuperar todas as Infos Válidas na árvore

                if(operacao == 1){
                    //como recuperamos a Info util, reconstruiremos em uma nova árvore
                    operacao =  reconstruir_arvore_45(Raiz, numero_infos, vetor_recuperado);

                    if(operacao != 1){
                        //falhou

                        if(operacao == 0){
                            //Falhou porque a Raiz que foi pra lá era Nula
                            situacao = 5; //5 Significa que a árvore original que deveria ser liberada era inválida
                        }
                        if(operacao == 2){
                            //Falhou na reconstrução da árvore
                            situacao = 4; //4 significa que houve uma falha na reconstrução da árvore
                        }
                        if(operacao == 3){
                            //Falhou na liberação da árvore antiga
                            situacao = 3; //3 significa que houve uma falha na liberação da antiga árvore
                        }
                }



                }else{
                    //houve falha na recuperação dos Nós
                    situacao = 2; 
                }

            }
       }else if(operacao == 3 || operacao == 4 || operacao == 5){
          //3, 4 e 5 significam que tudo deu certo, mas um ou mais blocos precisam ser apagados        
          
          //se tem bloco que vai sumir, precisamos ver se vai precisar agrupar, agrupando caso necessário
          operacao = agrupar_infos(*Raiz, &Info_anterior); //o agrupamento vai juntar blocos que ficarão adjacentes e sinalizará mais um bloco pra remoção, caso necessário 
          //A função de agrupar Infos retorna 1 se precisou agrupar, e 0 caso não tenha sido preciso, nesse caso, não é preciso validar, pq de toda forma tem pelo menos uma Info que tem de ser eliminada  
          
          //No melhor dos cenários (apagando a Info do Final), teremos de apagar uma INFO, no pior dos casos, agrupamos e eliminamos duas Infos
          operacao = percorrer_recuperar_Infos(*Raiz, &vetor_recuperado, &numero_infos); //A função irá percorrer a árvore e recuperar todas as Infos Válidas na árvore
          
          //criar uma função pra percorrer o vetor, criar a nova arvore, liberar a árvore antiga e retornar a nova
          
          if(operacao == 1){
             //Deu certo a recuperação de todas Infos
            operacao =  reconstruir_arvore_45(Raiz, numero_infos, vetor_recuperado);  

            if(operacao != 1){
                //falhou

                if(operacao == 0){
                    //Falhou porque a Raiz que foi pra lá era Nula
                    situacao = 5; //5 Significa que a árvore original que deveria ser liberada era inválida
                }
                if(operacao == 2){
                    //Falhou na reconstrução da árvore
                    situacao = 4; //4 significa que houve uma falha na reconstrução da árvore
                }
                if(operacao == 3){
                    //Falhou na liberação da árvore antiga
                    situacao = 3; //3 significa que houve uma falha na liberação da antiga árvore
                }
            }




          }else{
             //houve falha na recuperação dos Nós
             situacao = 2;          
        }     
          
    }  
       

   }else{
      //Não há dataset montado
      situacao = 0; 
   }


   situacao_desalocacao_memoria(situacao);   
 

}


