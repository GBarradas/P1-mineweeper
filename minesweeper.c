#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include"mine_functions.c"
void main()
{
    int nlinha,ncoluna, mines,linha,coluna=0,j=0, count=0,countmines=0,i=0,automatico=0,mineline,minacoluna=0;
    char play,lcol,lcol2,minaletra;             
    char *nfile[40]={0};                            //Vamos começar por defenir a nossa interação inicial.
    printf("                      Olá                        \n");
    printf("             Bem vindo ao minisweeper            \n"); 
    printf("                Vamos Começar??                  \n");
    printf("              Escolha Um dos Modos               \n");
    printf("0-Exit\n1-Generate Board\n2-Read Board\n");
    scanf("%d",&automatico);        //Vamos ler o modo de jogo
    float board[50][50];
    float show_board[50][50];
    if(automatico==0)       // Caso o modo selecionado seja zero vai sair do jogo
    {
        printf("Tank You for play");
        printf("\nBy:Gonçalo Barradas\n& Andre Baião\n");
        exit(EXIT_SUCCESS);
    }
    else if(automatico==1)      //Caso o modo selecionado seja igual a um vamos defenir um tabuleiro personalizado
    {
        printf("Vamos começar por defenir o tamanho do tabuleiro.\n");//Aqui começamos por defenir o nosso tabuleiro
        printf("                Numero de linhas:                \n");
        scanf("%d",&nlinha);
        printf("                Numero de colunas:               \n");
        scanf("%d",&ncoluna);
        printf("           Indique o numero de minas:            \n");
        scanf("%d",&mines);
        printf("\n\n\n\n\n\n");
        for (int i = 0; i < ncoluna; i++)           //Vamos defenir o show_bord que no inicio sera todo preenchido por '.'
        {
            while(j<nlinha)         //Aqui começamos por defenir o nosso tabuleiro
                                      //Nesta função para cada coluna corre uma linha, isto permite que todas as células do nosso tabuleiro sejam definidas.
            {                       
                board[i][j]=0;
                show_board[i][j]=9;
                j++;
            }
            j=0;
        
        }
    }
    else if(automatico==2)  //Caso o modo escolhido seja igual a 2 vamos ler um board
    {
        printf("Indique o nome do ficheiro:\n");
        scanf("%s",&nfile);     //Aqui vamos ler o nome do ficheiro
        FILE *f=fopen(nfile,"r");   //Aqui abrimos o ficheiro
        fscanf(f,"%d %d %d",&nlinha,&ncoluna,&mines);//Agora vamos ler o tamanho do board e o numero de minas
        for (int i = 0; i < ncoluna; i++)           //Vamos defenir o show_bord que no inicio sera todo preenchido por '.'
        {                                           //Nesta função para cada coluna corre uma linha, isto permite que todas as células do nosso tabuleiro sejam definidas.
            while(j<nlinha)  
            {
                board[i][j]=0;
                show_board[i][j]=9;
                j++;
            }
            j=0;
        
        }
        while (i<mines)     //Aqui vamos indicar as cordenadas das minas defenidas no ficheiro
        {
            fscanf(f,"%d %c",&mineline,&minaletra);
            for (char r = 'A'; r!= minaletra; r++)
            {
                minacoluna++;
            }
            board[mineline-1][minacoluna]=-1;
            i++;
            minacoluna=0;
        }
        
    }
    
    if(automatico==1)  //Caso o modo escolhido seja o 1 vamos criar o board com x minas posicionadas aleatoriamente
    {
        generate_board(board,nlinha,ncoluna,mines);
    }
    else if(automatico==2)//Caso o modo escolhido seja 2 vamos criar um board com as dimensoes indicadas
    {       //Neste caso não é necessasario indicar o numero de minas pois estas ja estão pre definidas
        generate_board(board,nlinha,ncoluna,0);
    }
    int nflag=mines;
    count=nlinha*ncoluna;
    print_board(board,show_board,nlinha,ncoluna); //Imprimimos o quadro inicial.
    printf("Flags left: %d\n",nflag);              //E o numero de bandeiras que é igual ao numero de minas
    while (count>mines)
    {                                                 //Vamos inciar o ciclo de jogo que so termina quando ganar ou perder
        printf("     u (uncover) ou f (flag)     \n");
        printf("Indique o numero a letra e a ação:");   // Vai ser pedida a cordenada e a função
        scanf("%d %c %c",&linha,&lcol2,& play);
        lcol=toupper(lcol2);
        for (char t = 'A'; t < lcol; t++)   // este for serve para determinar o valor da letra da coordenada selecionada
        {
            coluna++;
        }
        linha=linha-1;
        if(linha<=nlinha && coluna<=ncoluna)
        {
            //Caso o valor já tenha sido descoberto será detetado por este if  
            if( show_board[linha][coluna] != 9 && show_board[linha][coluna] != 10)
            {
                printf("\n>>Insira um valor que não tenha sido inserido<<\n");

            }
            //Caso a coordenada iserida não pertença ao tabuleiro, a mesma será detetada por este else if
            else if( (linha >= nlinha) || (linha < 0) || (coluna < 0) || (coluna >= ncoluna) )
            {
                printf("\n>>Insira um valor que pertença ao tabuleiro<<\n");
            }  
            //Caso nenhum dos casos se detete vai realizar a função escolhida 
            else
            {
                if(play=='u')
                {           //Caso o utilizador escolher a função uncover e a coordenada for uma mina o jogador perde
                    if( board[linha][coluna] == -1 )                            
                    {
                        
                        game_over(board,show_board,nlinha,ncoluna,linha,coluna);
                    }
                    else //se a coredenada escolhida não for uma mina é chamada a função uncover para revelar a celula ou celulas em questão
                    {
                        uncover(board,show_board,nlinha,ncoluna,linha,coluna);
                        print_board(board,show_board,nlinha,ncoluna);
                        printf("Flags left: %d\n",nflag);
                    }
                }
                if(play=='f'&& nflag>=0)  //Caso o utilizador opte por flag é chamada a função flag para marcar ou desmarcar a célula
                {
                    nflag=nflag+flag(board,show_board,linha,coluna);
                    print_board(board,show_board,nlinha,ncoluna);
                    printf("Flags left: %d\n",nflag);
                }
            }
        
        }
        countmines=0;
        count=0;
        j=0;
        for (int i = 0; i < nlinha; i++)
        {
            while(j<ncoluna)       //Estes dois ciclos servem para vericar coordenada a coordenada
            {
                if(show_board[i][j]==10) //Caso a cordenada esteja sinalizada
                {
                    if (board[i][j]==-1)// e se essa cordenada for uma mina então é adicinado 1 ao countmines
                    {
                        countmines++;
                    }
                    if(countmines==mines)// se o numero de countmines for igual ao numero de mines quer dizer que todas as celulas sinalizadas correspondem a minas logo o jogador ganhau
                    {
                        win(board,show_board,nlinha,ncoluna); 
                    }
                    
                }                       //Caso o jogador não sinalize so revele celulas
                if(show_board[i][j]==9 || show_board[i][j]==10)//quando o numero de celulas por revelar for igual ao numero de minas o ciclo while é interropido e o jogador ganha
                {
                    count++;
                }
                j++;
            }
            j=0;
        }
        coluna=0;
    }
    win(board,show_board,nlinha,ncoluna);  //Função que chama a mensagem para o jogador de parabéns e perguntra se o jogador pretende jogar outra vez.
}