/* ####################################
   #                                  #
   #           JOGO DA VELHA          #
   #       by Wesna Araujo - 2022     #
   #                                  #
   ####################################
 _____________________________________________________________
 Esse jogo foi desenvolvido durante um curso online para aprender
 a linguagem C. Basicamente foram utilizados conceitos de funções
 e matrizes.
 É importante dizer que a posição para se colocar o 'X' ou 'O' é
 feita escolhendo-se a linha e a coluna, ambas iniciando do zero
 e indo até 2. A seguir o tabuleiro numerado com as posições:

 00 | 01 | 02
 10 | 11 | 12
 20 | 21 | 22

 Por exemplo, para posicionar 'X' no centro do tabuleiro é
 necessário escolher para linha o valor 1 e para coluna
 o valor 1. Então:

 Linha: 1
 Coluna: 1

  |   |
  | X |
  |   |

Note que o próprio programa insere os caracteres do jogo da velha.
O usuário deve apenas indicar as linhas e colunas.

________________________________________________________________
*/

//Bibliotecas
#include <stdio.h>
#define DIM 3

//prototipos funções
void tabu(int tabuleiro[][DIM]);
void jogador(int tabuleiro[][DIM], int count);
int pos_ocupada(int linha, int coluna, int tabuleiro[][DIM]);
int confere_coluna(int tabuleiro[][DIM]);
int confere_digonal(int tabuleiro[][DIM]);
int confere_empate(int tabuleiro[][DIM]);
void limpar_Tabuleiro(int tabuleiro[][DIM]);
int checa_termino(int tabuleiro[][DIM]);
int menu(int tabuleiro[][DIM]);

//função principal
int main(){

    int tabuleiro[DIM][DIM];
    int opcao, count;

    count = 0;
    printf("------- BEM VINDO(A) AO JOGO DA VELHA! -------\n\n");

    do{
        jogador(tabuleiro, count);           //chama função que faz o jogo
        opcao = checa_termino(tabuleiro);    //chama a função que verifica a situação do jogo
        count++;

        //se cair aqui é porque o jogo acabou
        if(opcao == 1){
            printf("\t\t\t\t\tJogo da velha :\) - Wesna 2022\n\n");
            printf("E agora O que deseja fazer?\n\n ");
            opcao = menu(tabuleiro);        //chama a função menu para o usuario decidir se quer parar ou jogar mais
            count = 0;                      //zera contador inicial
            system("cls");                  //limpa a tela
            if(opcao == 1){
                printf("------- BEM VINDO(A) AO JOGO DA VELHA! -------\n\n");
            }
        }
    }while(opcao != 0);
}

//monta tabuleiro
void tabu(int tabuleiro[][DIM]){

    int linha, coluna;

    printf("\n");
    for(linha =0; linha < DIM; linha++){
          for(coluna =0; coluna < DIM; coluna++){
             if(coluna < DIM-1){
                if(tabuleiro[linha][coluna] == 1){
                    printf(" X |");
                }else{
                    if(tabuleiro[linha][coluna] == 2){
                        printf(" O |");
                    }else{
                        printf("   |");
                    }
                }
            }
            else{
                if(tabuleiro[linha][coluna] == 1){
                    printf(" X");
                }else{
                    if(tabuleiro[linha][coluna] == 2){
                        printf(" O");
                    }
                    else{
                        printf(" ");
                    }
                }
             }
          }
          printf("\n");
    }
    printf("\n");
}

//faz a jogada para cada jogador
void jogador(int tabuleiro[][DIM], int count){

    int linha, coluna, ocupada;
    int caracter;

    //para jogador 1
    if(count%2 == 0){
        printf("--> Jogador 1\n");
        caracter = 1; //X
    }
    //para jogador 2
    else{
        printf("--> Jogador 2\n");
        caracter = 2; //O
    }

    do{
        //escolhe posição do tabuleiro
        printf("Linha: ");
        scanf("%d", &linha);
        printf("Coluna: ");
        scanf("%d", &coluna);

        //verifica se a posição está vazia
        ocupada = pos_ocupada(linha, coluna, tabuleiro);

    }while(ocupada != 0);

    //insere caracter na respectica posição de acordo com o jogador
    tabuleiro[linha][coluna] = caracter;

    //chama função que printa tabuleiro
    tabu(tabuleiro);
}

//verifica se a posição escolhida esta disponivel
int pos_ocupada(int linha, int coluna, int tabuleiro[][DIM]){

    if(linha >= 0 && linha < DIM && coluna >= 0 && coluna < DIM){
        if(tabuleiro[linha][coluna] != 1 && tabuleiro[linha][coluna] != 2){
            return 0;
    }
        else{
            printf("Opa, essa posicao ja esta ocupada. Digite outra posicao\n");
            return 1;
        }
    }
    else{
        printf("Posicao invalida!\n");
        return 1;
    }

}

//confere as linhas
int confere_linha(int tabuleiro[][DIM]){

    int linha, count;
    count = 0;

    for(linha =0; linha < DIM; linha++){
         if(tabuleiro[linha][0] == tabuleiro[linha][1]){
                if(tabuleiro[linha][1] == 1 || tabuleiro[linha][1]== 2){
                    if(tabuleiro[linha][1] == tabuleiro[linha][2]){
                        count++;
                }
            }
        }
    }
     //verifica se teve pelo menos uma coluna igual
    if(count >= 1){
        return 1; //se sim;
    }
    else{
        return 2; //se não
    }
}

//confere as colunas
int confere_coluna(int tabuleiro[][DIM]){

    int coluna, count;

    count = 0;
    for(coluna =0; coluna < DIM; coluna++){
         if(tabuleiro[0][coluna] == tabuleiro[1][coluna]){
                if(tabuleiro[1][coluna] == 1 || tabuleiro[1][coluna]== 2){
                    if(tabuleiro[1][coluna] == tabuleiro[2][coluna]){
                        count++;
                    }
                }
         }
    }
    //verifica se teve pelo menos uma coluna igual
    if(count >= 1){
        return 1; //se sim;
    }
    else{
        return 2; //se não
    }
}

//confere diagonal secundaria e primaria
int confere_digonal(int tabuleiro[][DIM]){

    int linha, confirma_principal, confirma_secundaria, dig_principal, dig_secundaria;
    dig_principal = 0;
    dig_secundaria = 0;

    confirma_principal = 0;
    confirma_secundaria = 0;

    //diagonal principal e secundaria
    for(linha = 0; linha < DIM; linha++){

        dig_principal += tabuleiro[linha][linha];
        dig_secundaria += tabuleiro[linha][DIM-linha-1];

        //verifica se não há nenhum elemento zerado, pois pode dar 3
        if(tabuleiro[linha][linha] == 0){
            confirma_principal = 1;
        }

        if(tabuleiro[linha][DIM-linha-1] == 0){
            confirma_secundaria = 1;
        }
    }

    if(dig_principal == DIM || dig_secundaria == 2*DIM ||
       dig_principal == 2*DIM || dig_secundaria == DIM){
           //trata o caso de dar 3 mas haver um elemento nulo
           if((confirma_principal == 1 && dig_principal == DIM) ||
              (confirma_secundaria == 1 && dig_secundaria == DIM)){
                return 2;   //ainda ninguem ganhou
           }else{
                return 1;  //alguem ganhou
           }
    }
    else{
        return 2;         //ainda ninguem ganhou
    }
}

//verifica empate
int confere_empate(int tabuleiro[][DIM]){

    int linha, coluna, qtd_elem;

    qtd_elem = 1; //qtd de elementos no tabuleiro

    for(linha = 0; linha < DIM; linha++){
        for(coluna = 0; coluna < DIM; coluna++){
            if(tabuleiro[linha][coluna]== 1 || tabuleiro[linha][coluna]== 2 ){
                qtd_elem++;
            }
        }
    }

    return qtd_elem;


}

//limpa tabuleira para uma proxima partida
//adiciona zeros na matriz
void limpar_Tabuleiro(int tabuleiro[][DIM]){

    int linha, coluna;

    for(linha = 0; linha < DIM; linha++){
        for(coluna = 0; coluna < DIM; coluna++){
            tabuleiro[linha][coluna] = 0;
        }
    }
}

//verifica se o jogo acabou
int checa_termino(int tabuleiro[][DIM]){
    int opcao;

    if(confere_linha(tabuleiro) == 1){
        printf("O jogo acabou :\(\n");
        printf("Parabens voce venceu!\n\n");
        opcao = 1;
        return opcao;
    }

    if(confere_coluna(tabuleiro)== 1){
        printf("O jogo acabou :\(\n");
        printf("Parabens voce venceu!\n\n");
        opcao = 1;
        return opcao;
    }

    if(confere_digonal(tabuleiro)== 1){
        printf("O jogo acabou :\(\n");
        printf("Parabens voce venceu!\n\n");
        opcao = 1;
        return opcao;
    }

    if(confere_empate(tabuleiro)== DIM*DIM && opcao != 1){
        printf("O jogo acabou :\(\n");
        printf("Oloco, os dois jogadores sao muito bons. Houve empate!\n\n");
        return 1;
    }
     return 2; //ainda ninguem ganhou
}

//menu para o usurario decidir se quer jogar mais ou parar
int menu(int tabuleiro[][DIM]){

    int opcao;

    printf("----- Menu -----\n\n");
    printf("[1] - Bora jogar mais uma partida!\n");
    printf("[0] - Ja deu por hoje...\n\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    printf("\n\n");

    switch(opcao){

        case 1:
        case 0:
            break;
        default:
            //clear();
            printf("Opcao invalida. Tente de novo!\n");
    }

    if(opcao == 1){
        limpar_Tabuleiro(tabuleiro);
        //clear();
    }

    return opcao;
}



