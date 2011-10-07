#include <stdio.h>

char matriz[3][3];

void init_matriz(){
     int i, j;
     
     for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++) matriz[i][j] = ' ';
}

void disp_matriz(){
     int i, j;
     printf(" --- --- --- \n");
     for(i = 0; i < 3; i++){
        printf("|");
        for(j = 0; j < 3; j++) printf(" %c |", matriz[i][j]);
        printf("\n|---|---|---|\n");
     }
}

void move_jogador(){
     int x, y;
     printf("\n\nDigite em qual pos(x, y) deseja jogar: ");
     scanf("%d%d", &x, &y);
     x--;
     y--;
     
     if(matriz[x][y] != ' '){
        printf("Posicao invalida ou ja jogada, tente novamente...\n\n");
        move_jogador();
     }
     else matriz[x][y] = 'X';
}

void move_cpu(){
     int i, j;
     
     for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++)
              if(matriz[i][j] == ' ') break;
        if(matriz[i][j] == ' ') break;
     }
     
     if(i*j == 9){
            printf("\nEMPATE");
            getchar();
            exit(0);
     }
     else matriz[i][j] = 'O';
}

char check_vencedor(){
     int i;
     
     for(i = 0; i < 3; i++)
        if( (matriz[i][0] == matriz[i][1]) && (matriz[i][0] == matriz[i][2]) )
           return matriz[i][0];
           
     for(i = 0; i < 3; i++)
        if( (matriz[0][i] == matriz[1][i]) && (matriz[0][i] == matriz[2][i]) )
           return matriz[0][i];
           
     if( (matriz[0][0] == matriz[2][2]) && (matriz[1][1] == matriz[2][2]) )
        return matriz[1][1];
     if( (matriz[1][1] == matriz[0][2]) && (matriz[1][1] == matriz[2][0]) )
        return matriz[1][1];
     
     return ' ';
}

int main(){
    char terminado = ' ';
    
    printf("\t\tJogo da Velha :)\n");
    printf("Modo: vs cpu\n\n");
    init_matriz();
    do{
       disp_matriz();
       move_jogador();
       terminado = check_vencedor();
       
       if(terminado != ' ') break;
       
       move_cpu();
       terminado = check_vencedor();
    }while( terminado == ' ');
    
    if(terminado == 'X') printf("\n\nParabens, voce venceu!\n");
    else printf("\n\nQue pena, voce perdeu!\n");
    
    disp_matriz();
    fflush(stdin);
    getchar();
    return 0;
}
