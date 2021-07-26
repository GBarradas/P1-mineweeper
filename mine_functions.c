#include"mine_functions.h"
float generate_board(float board[50][50],int nlinha, int ncoluna, int mines)
{
    int totalmines=0, a=0,b=0,coluna=0,linha=0;   
    while(totalmines<mines)                   // Vamos escolher as cordenadas das minas usando a função rand()
    {
        a=rand()%nlinha;
        b=rand()%ncoluna;
        if(board[a][b]!= -1)
        {
            board[a][b]= -1;
            totalmines++;
        }
       
    }
    for (int linha = 0; linha < nlinha; linha++)            //Vamos analizar cada cordenada para determinar 
    {                                                     //O valor de cada celula depede do numero de minas ao redor
        for (int coluna = 0; coluna < ncoluna; coluna++)// O valor maximo que uma celula pode atingir o valor maximo de 8
        {
            if( board[linha][coluna] != -1)
            {
                board[linha][coluna] = 0;
            }   
            if((board[linha-1][coluna-1] == -1) && (board[linha][coluna] != -1))
            {
                board[linha][coluna]++;
            }
            if((board[linha-1][coluna] == -1) && (board[linha][coluna] != -1))
            {
                board[linha][coluna]++;
            }
            if((board[linha][coluna-1] == -1) && (board[linha][coluna] != -1))
            {
                board[linha][coluna]++;
            }
            if((board[linha-1][coluna+1] == -1) && (board[linha][coluna] != -1))
            {
                board[linha][coluna]++;
            }
            if((board[linha+1][coluna-1] == -1) && (board[linha][coluna] != -1))
            {
                board[linha][coluna]++;
            }
            if((board[linha+1][coluna] == -1) && (board[linha][coluna] != -1))
            {
                board[linha][coluna]++;
            }
            if((board[linha][coluna+1] == -1) && (board[linha][coluna] != -1))
            {
                board[linha][coluna]++;
            }
            if((board[linha+1][coluna+1] == -1) && (board[linha][coluna] != -1))
            {
                board[linha][coluna]++;
            }
        }
        coluna = 0;
    }  
} 
float print_board(float board[50][50],float show_board[50][50], int nlinha, int ncoluna)
{                           //show_bord são os vaores inicias que vão ser imprimidos ao longo do jogos esses valores vão sendo alterados
    printf("\n");           
    int numero= 0;
    char letra='A';
    printf("      ");   
    for (int coluna = 0; coluna < ncoluna; coluna++)          //Vamos mostrar ao utilizador uma linha com as cordenadas para se orientar
    {
        printf("%c ",letra);                // aqui as letras
        letra++;
    }
    printf("\n");

    for (int linha = 00; linha < nlinha; linha++)
    {
        if(linha+1<10)
        {
            printf("  0%d  ",linha+1);          // e agora os numeros
        }
        else
        {
            printf("  %d  ",linha+1);   
        }  
       for (int coluna = 0; coluna < ncoluna; coluna++)       //de seguida vamos imprimir o show_board
       {
                                                    //os valores do show board vão sendo alterados ao logo do jogo pelas funções uncover, flag e game_over
           if (show_board[linha][coluna]==9)         
           {
              printf(". ");
           }
           else if(show_board[linha][coluna]==-2)
           {
               printf("B ");
           }
           else if (show_board[linha][coluna]==10)
           {
               printf("f ");
           }
            else if (show_board[linha][coluna]==-1)
           {
               printf("* ");
           }
           else if (show_board[linha][coluna]==0)
           {
               printf("  ");
           }
           
           else
           {
               printf("%.0f ",show_board[linha][coluna]);
           }
        }
        printf("\n");
    }

}
int game_over(float board[50][50], float show_board[50][50],int nlinha, int ncoluna, int line, int colun)
{
    int coluna=0;
    for (int linha = 0; linha < nlinha; linha++)              //Caso o jogador revele uma mina esta função sera ativa e o jogador perde
    {
        while(coluna<ncoluna) 
        {
            if(board[linha][coluna]==-1)
            {
                show_board[linha][coluna]=board[linha][coluna];
            }
            coluna++;
        }
        coluna=0;
        
    }                                           //Esta função revelar todas as minas e vai imprimir um 'B' na mina que esplodio
    show_board[line][colun]=-2;
    print_board(board,show_board,nlinha,ncoluna);
    printf("\t\tGAME OVER!!\n\t\tTRY AGAIN\n");
    main();
}
float win(float board[50][50],float show_board[50][50],int nlinha,int ncoluna)
{                            //caso o jogador revele todas as celulas sem rebentar nunhuma mina esta função é ativa 
    print_board(board,show_board,nlinha,ncoluna);
    printf("\n\nCongratulation!!\n");       // e é emitida uma mensagem felecitando o jogador
    printf("    YOU WIN     \n");
    main();
}
int uncover(float board[50][50], float show_board[50][50],int nlinha, int ncoluna, int line, int coluna)
{                                       //esta função serve para revelar celulas aol longo do jogo
    if( show_board[line][coluna] != 9 && show_board[line][coluna] != 10 )     // Caso a celula ja tenha sido revelada não a cotece nada    
    {
       
       return 0;
    }

    else           // Caso não tenha sido revelada essa celula é revelada                                     
    {
        show_board[line][coluna] = board[line][coluna];
        if( board[line][coluna] == 0 )      // Caso essa celula seja igual a zero todas as celulas ao lado vão ser revelados
        {
            if( board[line-1][coluna-1] != 0 && board[line-1][coluna-1] != -1 && show_board[line-1][coluna-1] != 10 )// Se as celuas á volta forem minas não são reveladas
            {
                show_board[line-1][coluna-1] = board[line-1][coluna-1];
            }
            if( board[line-1][coluna] != 0&& board[line-1][coluna] != -1  && show_board[line-1][coluna] != 10 )
            {
                show_board[line-1][coluna] = board[line-1][coluna];
            }
            if( board[line][coluna-1] != 0 && board[line][coluna-1] != -1 && show_board[line][coluna-1] != 10 )
            {
                show_board[line][coluna-1] = board[line][coluna-1];
            }
            if( board[line-1][coluna+1] != 0 && board[line-1][coluna+1] != -1 && show_board[line-1][coluna+1] != 10 )
            {
                show_board[line-1][coluna+1] = board[line-1][coluna+1];
            }
            if( board[line+1][coluna-1] != 0 && board[line+1][coluna-1] != -1 && show_board[line+1][coluna-1] != 10 )
            {
                show_board[line+1][coluna-1] = board[line+1][coluna-1];
            }
            if( board[line+1][coluna] != 0 && board[line+1][coluna] != -1 && show_board[line+1][coluna] != 10 )
            {
                show_board[line+1][coluna] = board[line+1][coluna];
            }
            if( board[line][coluna+1] != 0 && board[line][coluna+1] != -1  && show_board[line][coluna+1] != 10)
            {
                show_board[line][coluna+1] = board[line][coluna+1];
            }
            if( board[line+1][coluna+1] != 0 && board[line+1][coluna+1] != -1 && show_board[line+1][coluna+1] != 10 )
            {
                show_board[line+1][coluna+1] = board[line+1][coluna+1];
            }
            if( board[line-1][coluna-1] ==0  && show_board[line-1][coluna-1] != 10 )
            {
                uncover(board,show_board,nlinha,ncoluna,line-1,coluna-1);//Caso as células agregadas forem 0 todas as células em seu redor são reveladas 
            }
            if( board[line-1][coluna] == 0 && show_board[line-1][coluna] != 10)                     //é por isso que usamos a recursividade para revelar as celulas á volta da celula em questão
            {
                uncover(board,show_board,nlinha,ncoluna,line-1,coluna);
            }
            if( board[line][coluna-1] == 0 && show_board[line][coluna-1] != 10)
            {
                uncover(board,show_board,nlinha,ncoluna,line,coluna-1);
            }
            if( board[line-1][coluna+1] == 0 && show_board[line-1][coluna+1] != 10)
            {
                uncover(board,show_board,nlinha,ncoluna,line-1,coluna+1);
            }
            if( board[line+1][coluna-1] == 0 && show_board[line+1][coluna-1] != 10)
            {
                uncover(board,show_board,nlinha,ncoluna,line+1,coluna-1);
            }
            if( board[line+1][coluna] == 0&& show_board[line+1][coluna] != 10 )
            {
                uncover(board,show_board,nlinha,ncoluna,line+1,coluna);
            }
            if( board[line][coluna+1] == 0 && show_board[line][coluna+1] != 10)
            {
                uncover(board,show_board,nlinha,ncoluna,line,coluna+1);
            }
            if( board[line+1][coluna+1] == 0 && show_board[line+1][coluna+1] != 10)
            {
                uncover(board,show_board,nlinha,ncoluna,line+1,coluna+1);
            }
        }
    }
}
int flag(float board[50][50], float show_board[50][50], int lin, int col)  // esta função serve para sinalizar celulas
{   
    if(show_board[lin][col]==10) //caso a celula esteja marcada com fla
    {
        show_board[lin][col]=9; //vai ser desmarcada e a bandeira é adicionada ao número de flags
        return 1;

    }
    else                         //Caso não esteja sinalizada 
    {
        show_board[lin][col]=10;//a culula vai ser sinalizada  e sobretai-se uma flag ao numero de flags
        return -1;
    }
}
