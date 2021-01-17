#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#define MAX_USER 10
#define MAX_CHAR 15

typedef struct
{
    char utilizador[MAX_CHAR];
    char senha [MAX_CHAR];
} REGISTO;


void tabuleiro();
int jogador1(REGISTO r[], int uTIExiste);
int jogador2();
void jogadorpc1();
void jogadorpc2();
int verifica_vencedor();
int verifica_vencedorpc();
void jogar2p(REGISTO r[], int userOK1);
void jogar1p(REGISTO r[], int userOK);
void ver();
int menu(REGISTO r[], int uTIExiste);
int menujogar(REGISTO r[], int uTIExiste);
void estatisticas(REGISTO r[], int userOK);
void limpacampos();
//void MenuJogo (REGISTO r[], int uTiExiste);
void CriaRegisto (REGISTO r[], int *nRegistos);
int Login (REGISTO r[], int nRegistos);

char mapa[3][3], j2[25];
int jogada=0, jogosjogados1=0, jogosjogados2=0, ganhojogador2=0, perdidojogador1=0, ganhojogador1=0, perdidojogador2=0, empate=0, resultado=0;


REGISTO registo[MAX_USER];


int main()
{
    int nRegistos =0, userOK ;  //userOK: 1 pode jogar  2 senha ivalida 0 nao encontrou o nome
    char opcao;
    //REGISTO registo[MAX_USER]; //= {"", ""};

    setlocale(LC_ALL, "");

    do
    {

        do
        {
            printf("\t$$$   Bem-Vindo ao Jogo do Galo   $$$\n");
            printf("\t\t Escolha uma opção \n");
            printf("\t\t 1 - Registo\n");
            printf("\t\t 2 - Login\n");
            printf("\t\t 0 - Sair\n");
            printf("\t\t >");
            scanf(" %c", &opcao);
        }
        while (opcao < '0' && opcao > '2');
        switch(opcao)
        {
        case '1':
            system("CLS");
            printf("\t Registo\n");
            // Sleep(1000);
            CriaRegisto(registo, &nRegistos);
            break;
        case '2':
            system("CLS");
            printf("\tLogin\n");
            userOK=Login (registo,  nRegistos);
            //printf(" %s", registar.utilizador);
            //Sleep(2000);
            if (userOK >=0)
                menujogar(registo, userOK);
            // MenuJogo(registo, userOK);
            break;
        }


    }
    while (opcao != '0');
    printf("Obrigado e até à próxima \n");

    return 0;
}

void CriaRegisto(REGISTO r[], int *nRegistos)
{
    char r_utilizador[MAX_CHAR];
    int n, i, uTiExiste =0;
    n=*nRegistos;
    do
    {
        uTiExiste =0;
        printf("\t Nome de Utilizador?\n");
        printf("\t >");
        fflush(stdin);
        gets(&r_utilizador);//é capaz de ser erro
        for (i=0; i<n; i++)         //verifica se já existe o utilizador
        {
            //printf("nome pretendido:%s\n" , r_utilizador);
            //printf("Nome a comparar %s\n", r[i].utilizador);
            //printf("n de registos %d\n", n);
            if(strcmp(r_utilizador, r[i].utilizador)==0)
            {
                printf("\tUtilizador já existe\n");
                uTiExiste =-1;//ERRO!!!
                Sleep(2000);
                system("CLS");
                break;
            }
        }
    }
    while (uTiExiste);

    strcpy(r[n].utilizador,r_utilizador);
    printf("\n\t Senha?\n");
    printf("\t >");
    fflush(stdin);
    gets(&r[n].senha);
    //printf("%s", r->utilizador);
    //printf("%s", r->senha);
    //getch();
    Sleep(1000);
    uTiExiste =i;
    *nRegistos = *nRegistos+1;
    system("CLS");
}

int Login (REGISTO r[], int nRegistos)
{
    char v_utilizador[MAX_CHAR], v_senha[MAX_CHAR];
    int i;
    int encontrou =-1;

    /*    do
        {   do
            {
                printf("\tNome de Utilizador:\n");
                printf("\t >");
                fflush(stdin);
                gets(&v_utilizador);
                fflush(stdin);
            }while (strcmp(v_utilizador, r->utilizador != 0));
                printf("\n\tSenha do Utilizador:\n");
                printf("\t >");
                fflush(stdin);
                gets(&v_senha);
                fflush(stdin);
        }while (strcmp(v_utilizador, r->utilizador != 0));
            printf("Login feito com sucesso\n");
    */

    printf("\tNome de Utilizador:\n");
    printf("\t >");
    fflush(stdin);
    gets(&v_utilizador);
    fflush(stdin);

    for (i=0; i<nRegistos; i++)
    {

        if(strcmp(v_utilizador, r[i].utilizador)==0) //o user exste e está na posição i
        {
            printf("\tPass:\n");
            printf("\t >");
            fflush(stdin);
            gets(&v_senha); //buffer overflow  - fgets -   gets remained an official part of the language up to the 1999 ISO C standard, but it was officially removed by the 2011 standard.
            fflush(stdin);
            if(strcmp(v_senha, r[i].senha)==0)
            {
                {
                    encontrou = i;
                    break;
                }
            }else
            {
                encontrou =-99;
                break;
            }
        }

    }
//estatisticas();r[userOK].utilizador
    if (encontrou == -99)
        printf("\tSenha não coincide com o utilizador\n");
    else if (encontrou>=0)
        printf("\tLogin feito com sucesso\n");
    else
        printf("\tUtilizador não existe\n");

    Sleep(2000);
    system ("CLS");
    return encontrou;
}





/*
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/


//Começa aqui o jogo
int menujogar(REGISTO r[], int userOK)
{
    char escolha;
    do
    {

        printf("\t$$$   Bem-Vindo ao Jogo %s $$$\n", r[userOK].utilizador);
        printf("\t\t Escolha uma opção \n");
        printf("\t\t 1 - Jogar\n");
        printf("\t\t 2 - Estatisticas\n");
        printf("\t\t 0 - Sair (menu anterior)\n");
        printf("\t\t >");
        scanf(" %c", &escolha);


        switch(escolha)
        {
        case '1':
        {
            system("CLS");
            while(menu(r,userOK));
            break;
        }
        case '2':
        {
            estatisticas(r, userOK);
            break;
        }
        }
    }
    while (escolha <= '2' && escolha !='0' );


    return 0;

}

//apresenta o tabuleiro
void tabuleiro()
{

    int i;

    for (i = 0; i < 3; i++)
    {
        printf(" %c | %c | %c ", mapa[i][0], mapa[i][1], mapa[i][2]);


        if ( i != 2)
        {
            printf("\n");
            printf("---|---|---");
            printf("\n");
        }

    }

}
//escolher o jogo
int menu(REGISTO r[], int userOK)
{
    int userOK1;
    int nRegistos = 0;
    char opcao;
    //REGISTO registo[MAX_USER];
    system("CLS");


    printf("\n\t %s Quer jogar vs Humano, vs Pc, Ver ou Sair? [H, P, V ou S]\n", r[userOK].utilizador);
    printf("\t\t>");
    scanf(" %c", &opcao);

    limpacampos();
    //void menujogar(REGISTO r[], int uTiExiste);
//void CriaRegisto (REGISTO r[], int *nRegistos);
//int Login (REGISTO r[], int nRegistos);
    switch(opcao)
    {
    case 'h':
    case 'H':
    {
 printf("Jogador 2 Introduza o nome\n");
 scanf(" %s", &j2);
        jogar2p(r, userOK);
        break;
    }
    case 'p' :
    case 'P' :
    {
        jogar1p(r, userOK);
        break;
    }
    case 'V' :
    case 'v':
    {
        ver();
        break;
    }
    case 's':
    case 'S':
    {
        return 0;
    }
    default:
        printf("Invalid Option\n\n");
        menu(r,userOK);
    }
    return 1;
}


// user vs user
void jogar2p(REGISTO r[], int userOK)
{
    printf("%d - %d\n",jogada,resultado);
    while(jogada!=9 && !jogador1(r, userOK) && !jogador2());
    Sleep(500);
}

//user vs pc
void jogar1p(REGISTO r[], int userOK)
{
    jogada=0;
    resultado=0;
    while(jogada!=9 && resultado==0 )
    {
        jogador1(r,userOK);
        jogadorpc1();
    }
    Sleep(500);
}
//pc vs pc
void ver()
{
    jogada=0;
    resultado=0;
    while(jogada!=9 && resultado==0 )
    {
        jogadorpc1();
        Sleep(700);
        jogadorpc2();
        Sleep(500);

    }
    Sleep(500);
}



//1ºjogador (user)
int jogador1(REGISTO r[], int userOK)
{
    int x, y;

    printf("\nJogador1- %s - X\n",  r[userOK].utilizador);

    printf("Onde quer jogar?\n");
    do
    {
        printf("Introduza a linha [1-3]:\n");
        scanf(" %d", &x);
        fflush(stdin);
        printf("Introduza a coluna [1-3]:\n");
        scanf(" %d", &y);
        fflush(stdin);

    }
    while((x<1 || x>3) || (y<1 || y>3));

    x--;
    y--;
    if(mapa[x][y]==NULL)
    {
        mapa[x][y] = 'X';
        printf("\n");
        tabuleiro();
        jogada++;
        return verifica_vencedor();


    }
    else
    {
        printf("Casa Ocupada\n");
        jogador1(r,userOK);
    }
}
//2ºjogador (user)
int jogador2()
{
    int x, y;

    printf("\nJogador2- %s - O\n", j2);

    printf("Onde quer jogar?\n");
    do
    {
        printf("Introduza a linha [1-3]:\n");
        scanf(" %d", &x);
        fflush(stdin);
        printf("Introduza a coluna [1-3]:\n");
        scanf(" %d", &y);
        fflush(stdin);

    }
    while((x<1 || x>3) || (y<1 || y>3));

    x--;
    y--;
    if(mapa[x][y]==NULL)
    {
        mapa[x][y] = 'O';
        printf("\n");
        tabuleiro();
        jogada++;
        return verifica_vencedor();


    }
    else
    {
        printf("Casa Ocupada\n");
        jogador2();
    }
}
// pc 1
void jogadorpc1()
{
    int x, y;

    srand(time(NULL));
    Sleep(200);
    x=rand()%(2-0+1)+0;
    y=rand()%(2-0+1)+0;


    if(mapa[x][y]==NULL)
    {
        printf("\n\n Jogador PC 1 jogou:\n");
        mapa[x][y] = 'O';
        printf("\n");
        tabuleiro();
        jogada++;
        verifica_vencedorpc();

    }
    else
    {
        jogadorpc1();
    }
}
//Pc 2
void jogadorpc2()
{
    int x, y;

    srand(time(NULL));
    Sleep(200);
    x=rand()%(2-0+1)+0;
    y=rand()%(2-0+1)+0;


    if(mapa[x][y]==NULL)
    {
        printf("\n\n Jogador PC 2 jogou:\n");
        mapa[x][y] = 'X';
        printf("\n");
        tabuleiro();
        jogada++;
        verifica_vencedorpc();

    }
    else
    {
        jogadorpc2();
    }
}


// verifica quem ganha
int verifica_vencedor()
{
    if((mapa[0][0]=='X' && mapa[0][1]=='X' && mapa[0][2]=='X')||(mapa[1][0]=='X' && mapa[1][1]=='X' && mapa[1][2]=='X')||(mapa[2][0]=='X' && mapa[2][1]=='X' && mapa[2][2]=='X')||(mapa[0][0]=='X' && mapa[1][0]=='X' && mapa[2][0]=='X')||(mapa[0][1]=='X' && mapa[1][1]=='X' && mapa[2][1]=='X')||(mapa[0][2]=='X' && mapa[1][2]=='X' && mapa[2][2]=='X')||(mapa[0][0]=='X' && mapa[1][1]=='X' && mapa[2][2]=='X')||(mapa[0][2]=='X' && mapa[1][1]=='X' && mapa[2][0]=='X'))
    {
        printf("\n\n\n\n\t\tJogador 1 Ganhou!!!\n");
        ganhojogador1++;
        perdidojogador2++;
        // jogosjogados++;
        // estatisticas();
        resultado =1;
        return 1;

    }
    else if((mapa[0][0]=='O' && mapa[0][1]=='O' && mapa[0][2]=='O') || (mapa[1][0]=='O' && mapa[1][1]=='O' && mapa[1][2]=='O')||(mapa[2][0]=='O' && mapa[2][1]=='O' && mapa[2][2]=='O')||(mapa[0][0]=='O' && mapa[1][0]=='O' && mapa[2][0]=='O')||(mapa[0][1]=='O' && mapa[1][1]=='O' && mapa[2][1]=='O')||(mapa[0][2]=='O' && mapa[1][2]=='O' && mapa[2][2]=='O')||(mapa[0][0]=='O' && mapa[1][1]=='O' && mapa[2][2]=='O')||(mapa[0][2]=='O' && mapa[1][1]=='O' && mapa[2][0]=='O'))
    {
        printf("\n\n\n\n\t\tJogador 2 Ganhou!!!\n");
        ganhojogador2++;
        perdidojogador1++;
        resultado =1;
        return 2;

    }
    else if(jogada==9)
    {
        printf("\n\n\n\n\t\tEMPATE!!!\n");
        empate++;
        resultado =1;
        return 3;

    }
    else
    {
        return 0;
    }

}
int verifica_vencedorpc()
{
    if((mapa[0][0]=='X' && mapa[0][1]=='X' && mapa[0][2]=='X')||(mapa[1][0]=='X' && mapa[1][1]=='X' && mapa[1][2]=='X')||(mapa[2][0]=='X' && mapa[2][1]=='X' && mapa[2][2]=='X')||(mapa[0][0]=='X' && mapa[1][0]=='X' && mapa[2][0]=='X')||(mapa[0][1]=='X' && mapa[1][1]=='X' && mapa[2][1]=='X')||(mapa[0][2]=='X' && mapa[1][2]=='X' && mapa[2][2]=='X')||(mapa[0][0]=='X' && mapa[1][1]=='X' && mapa[2][2]=='X')||(mapa[0][2]=='X' && mapa[1][1]=='X' && mapa[2][0]=='X'))
    {
        printf("\n\n\n\n\t\tJogador PC2 Ganhou!!!\n");

        resultado =1;
        return 1;

    }
    else if((mapa[0][0]=='O' && mapa[0][1]=='O' && mapa[0][2]=='O') || (mapa[1][0]=='O' && mapa[1][1]=='O' && mapa[1][2]=='O')||(mapa[2][0]=='O' && mapa[2][1]=='O' && mapa[2][2]=='O')||(mapa[0][0]=='O' && mapa[1][0]=='O' && mapa[2][0]=='O')||(mapa[0][1]=='O' && mapa[1][1]=='O' && mapa[2][1]=='O')||(mapa[0][2]=='O' && mapa[1][2]=='O' && mapa[2][2]=='O')||(mapa[0][0]=='O' && mapa[1][1]=='O' && mapa[2][2]=='O')||(mapa[0][2]=='O' && mapa[1][1]=='O' && mapa[2][0]=='O'))
    {
        printf("\n\n\n\n\t\tJogador PC1 Ganhou!!!\n");

        resultado =1;
        return 2;

    }
    else if(jogada==9)
    {
        printf("\n\n\n\n\t\tEMPATE!!!\n");
        resultado =1;
        return 3;

    }
    else
    {
        return 0;
    }

}



// estatisticas
void estatisticas(REGISTO r[], int userOK)
{

    int pontos1=0, pontos2=0;
    pontos1=(ganhojogador1*3+empate);
    pontos2=(ganhojogador2*3+empate);

    jogosjogados1=ganhojogador1+perdidojogador1+empate;
    jogosjogados2=ganhojogador2+perdidojogador2+empate;

    printf("Jogador1 %s: \n vitorias:%d \n derrotas:%d \n empates: %d \n jogos jogados:%d\n pontos: %d\n",r[userOK].utilizador, ganhojogador1, perdidojogador1, empate, jogosjogados1, pontos1);
    printf("Jogador2 %s: \n vitorias:%d \n derrotas:%d \n empates: %d \n jogos jogados:%d\n pontos: %d\n",j2, ganhojogador2, perdidojogador2, empate, jogosjogados2, pontos2);
}

void limpacampos()
{
    jogada=0;
    memset(mapa, NULL, sizeof mapa);

}

