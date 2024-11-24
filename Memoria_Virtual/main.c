#include <stdio.h> 
#include <stdlib.h> 
#include "Gerenciamento_Memoria.h"

int main(){

    Arv45Mem *Memoria; 
    Memoria = NULL; 
    int op1, op2; 

    do{
        menu_principal(); 
        scanf("%d", &op1); 

        switch(op1){

            case 0: 
               break; 
            case 1: 
               //Monta os blocos
               construir_memoria_do_sistema(&Memoria);  
               break; 
            case 2: 
                //Funcionalidades
                do{
                    funcionalidades(); 
                    scanf("%d", &op2);

                    switch(op2){
                        case 0: 
                           break;
                        case 1: 
                             //Alocar Memória 
                             alocar_memoria_para_programa(&Memoria);  
                             break; 
                        case 2: 
                             //Liberar Memória
                             desalocar_memoria_sistema(&Memoria); 
                             break; 
                        case 3: 
                             imprimirArvore45(Memoria); 
                             break; 
                                   
                        default: 
                           printf("Opção Inválida, tente novamente\n");  
                    }

                }while(op2 != 0); 


                break; 
            case 3: 
                sobre(); 
                break; 
            default: 
              printf("Opção inválida, digite novamente\n"); 
        }  
    
    
    
    }while(op1 != 0); 

    return 0; 
}


