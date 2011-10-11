#include <stdio.h>
#include <conio.h>

char matriz[3][3];

void carregaMenu();

void opcaoInvalida(){
     printf("\nOpcao invalida... Tente novamente!\n");
     getch();
}

void limpaCls(){
     #ifdef LINUX
           system("clear");
     #elif defined WIN32 || WIN64
           system("cls");
     #else
           printf("\nERRO: Plataforma nao suportada.\n");
           printf("Disponivel apenas para Linux e Windows");
           getchar();
           exit(1);
     #endif
}

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

void move_jogador( char ch, const char *player ){
     int x, y;
     printf("\n\n%s: Digite em qual pos(x, y) deseja jogar: ", player);
     scanf("%d%d", &x, &y);
     x--;
     y--;
     
     if(matriz[x][y] != ' '){
        opcaoInvalida();
        move_jogador( ch, player );
     }
     else matriz[x][y] = ch;
}

void move_cpu( char ch ){
     int i, j;
     
     for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++)
              if(matriz[i][j] == ' ') break;
        if(matriz[i][j] == ' ') break;
     }
     
     matriz[i][j] = ch;
}

int deu_velha(){
    int i, j;
    
    for(i = 0; i < 3; i++)
       for(j = 0; j < 3; j++)
             if(matriz[i][j] == ' ') return 0;
             
    return 1;
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
     
     if(deu_velha()) return 'V';
     
     return ' ';
}

void playMultiplayer(){
     char terminado = ' ';
     init_matriz();
     printf("Modo Multiplayer\n\t\tPlayer 1 - X\n\t\tPlayer 2 - O\n\n");
     
     do{
        disp_matriz();
        move_jogador( 'X', "Player 1" );
        terminado = check_vencedor();
        if(terminado != ' ') break;
        
        disp_matriz();
        move_jogador( 'O', "Player 2" );
        terminado = check_vencedor();
    }while( terminado == ' ');
    
    if(terminado == 'X') printf("O player 1 venceu! Parabéns!\n");
    else if(terminado == 'O') printf("O player 2 venceu! Parabéns!\n");
    else printf("\n\nOps, deu velha!\n");
    disp_matriz();
    
    printf("...");
    getch();
    carregaMenu();
}

void playCPU(){
     char terminado = ' ';
     init_matriz();
     limpaCls();
     printf("\t\t\tModo vs. CPU\nComece jogando\n\n");
     
     do{
        disp_matriz();
        move_jogador( 'X' , "Player 1");
        terminado = check_vencedor();
        
        if(terminado != ' ') break;
        
        move_cpu( 'O' );
        terminado = check_vencedor();
    }while( terminado == ' ');
    
    if(terminado == 'X') printf("\n\nParabens, voce venceu!\n");
    else if(terminado == 'O') printf("\n\nQue pena, voce perdeu!\n");
    else printf("\n\nOps, deu velha!\n");
    
    disp_matriz();
    printf("...");
    getch();
    carregaMenu();
}

void play( int modo ){
     if( modo == 1 ) playCPU();
     else playMultiplayer();
     
}

void carregaMenu(){
     int escolha;
     
     while(1){
              limpaCls();
              printf("\t\t\t0,1\n\n Menu Principal:\n");
              printf(" 1 - vs. CPU\n");
              printf(" 2 - Modo Multiplayer\n");
              printf(" 3 - Sair\n");

              printf("Digite um numero para escolher uma opcao e de ENTER: ");
              scanf("%d", &escolha);
       
              if( escolha < 1 || escolha > 3 ) opcaoInvalida();
              else if( escolha == 3 ) exit(0);
              else break;
    }
    
    play(escolha);
}

int main(){    
    printf("\t\tJogo da Velha :)\n");
    printf("\n\n\nPrecione qualquer tecla para continuar...");
    getch();
    carregaMenu();

    getchar();
    return 0;
}
