  #include <stdio.h>
  #include <graphics.h>
  #include "globais.h"
  #include "define.h"

 #define EXTERN extern

/*-----------------------------------------------------------------*\
 |            Controle do mouse/teclado                            |
\*-----------------------------------------------------------------*/
  void GerenciaTecladoMouse(void)
  {
    const
      NaoAguarde = 0;             /* Nao Aguarda na Mensagem. */
    char
      Tecla;                           /* Tecla pressionada.       */

    POS_X_CURSOR = (MAX_COD_X / 2),      /* Centraliza posicao X.  */
    POS_Y_CURSOR = (MAX_COD_Y / 2);      /* Centraliza posicao Y.  */
      /* Desenha Cursor Geral */
    putimage(POS_X_CURSOR,POS_Y_CURSOR,CURSOR_GERAL,XOR_PUT);
    MostraMensagem("",NaoAguarde);

    for (;;)
    {
      Tecla = getch();
      switch(Tecla)
      {
        case '\r' : PressionouEnter();
        break;
        case '\x0':
        {
          putimage(POS_X_CURSOR,POS_Y_CURSOR,CURSOR_GERAL,XOR_PUT);
          TeclaEspecial();
          putimage(POS_X_CURSOR,POS_Y_CURSOR,CURSOR_GERAL,XOR_PUT);
        }
        break;
        case '+' : if ((INC_CURSOR + 2) < 50)
                         INC_CURSOR +=2;               /* Incremento Passo.  */
        break;
        case '-' : if ((INC_CURSOR - 2) > 1)
                         INC_CURSOR -=2;               /* Decremento Passo.  */
        break;
        case '\x1B' :
        {
          closegraph();
          exit(0);                                    /* Finaliza execucao.  */
        }
      }
    }
  }

/*-----------------------------------------------------------------*\
 |            Controle da Tecla ENTER                              |
\*-----------------------------------------------------------------*/
  void PressionouEnter(void)
  {
    int
      CodXEsq,                   /* Coordenada do X Esquerdo. */
      CodYSup,                   /* Coordenada do Y Superior. */
      LinhaGrade,                /* Numero da Linha na Grade.  */
      ColunaGrade;               /* Numero da Coluna na Grade. */
    char
      *NomeJanela;

    strcpy(NomeJanela,"SEM_JANELA");
    JanelaCorrente(NomeJanela);
    LinhaGrade  = QUADRICULA / 20;
    ColunaGrade = QUADRICULA - (LinhaGrade * 20);

    if(!strcmp(NomeJanela,"ScroolVertical"))
    {
      putimage(SCROOL_X_VERTICAL,SCROOL_Y_VERTICAL,CURSOR_SCROOL,XOR_PUT);
      SCROOL_Y_VERTICAL = POS_Y_CURSOR;
      putimage(SCROOL_X_VERTICAL,SCROOL_Y_VERTICAL,CURSOR_SCROOL,XOR_PUT);
    }
    if(!strcmp(NomeJanela,"ScroolVertSup"))
    {
      putimage(SCROOL_X_VERTICAL,SCROOL_Y_VERTICAL,CURSOR_SCROOL,XOR_PUT);
      if((SCROOL_Y_VERTICAL - (PASSO_SCROOL*ASPECT)) >
                               (ValorRelativoTela('Y',17.6,0)))
        SCROOL_Y_VERTICAL = SCROOL_Y_VERTICAL - (PASSO_SCROOL*ASPECT);
      else
        SCROOL_Y_VERTICAL = ValorRelativoTela('Y',17.6,0);
      putimage(SCROOL_X_VERTICAL,SCROOL_Y_VERTICAL,CURSOR_SCROOL,XOR_PUT);
    }
    if(!strcmp(NomeJanela,"ScroolVertInf"))
    {
      putimage(SCROOL_X_VERTICAL,SCROOL_Y_VERTICAL,CURSOR_SCROOL,XOR_PUT);
      if((SCROOL_Y_VERTICAL + (PASSO_SCROOL*ASPECT)) <
                               (ValorRelativoTela('Y',82.4,0)))
        SCROOL_Y_VERTICAL = SCROOL_Y_VERTICAL + (PASSO_SCROOL*ASPECT);
      else
        SCROOL_Y_VERTICAL = ValorRelativoTela('Y',82.4,0);
      putimage(SCROOL_X_VERTICAL,SCROOL_Y_VERTICAL,CURSOR_SCROOL,XOR_PUT);
    }
    if(!strcmp(NomeJanela,"ScroolHorizontal"))
    {
      putimage(SCROOL_X_HORIZONTAL,SCROOL_Y_HORIZONTAL,CURSOR_SCROOL,XOR_PUT);
      SCROOL_X_HORIZONTAL = POS_X_CURSOR;
      putimage(SCROOL_X_HORIZONTAL,SCROOL_Y_HORIZONTAL,CURSOR_SCROOL,XOR_PUT);
    }
    if(!strcmp(NomeJanela,"ScroolHoriEsq"))
    {
    putimage(SCROOL_X_HORIZONTAL,SCROOL_Y_HORIZONTAL,CURSOR_SCROOL,XOR_PUT);
      if((SCROOL_X_HORIZONTAL - PASSO_SCROOL) > ValorRelativoTela('X',6.8,0))
        SCROOL_X_HORIZONTAL = SCROOL_X_HORIZONTAL - PASSO_SCROOL;
      else
        SCROOL_X_HORIZONTAL = ValorRelativoTela('X',6.8,0);
      putimage(SCROOL_X_HORIZONTAL,SCROOL_Y_HORIZONTAL,CURSOR_SCROOL,XOR_PUT);
    }
    if(!strcmp(NomeJanela,"ScroolHoriDir"))
    {
      putimage(SCROOL_X_HORIZONTAL,SCROOL_Y_HORIZONTAL,CURSOR_SCROOL,XOR_PUT);
      if((SCROOL_X_HORIZONTAL + PASSO_SCROOL) < ValorRelativoTela('X',60.0,0))
        SCROOL_X_HORIZONTAL = SCROOL_X_HORIZONTAL + PASSO_SCROOL;
      else
        SCROOL_X_HORIZONTAL = ValorRelativoTela('X',60.0,0);
      putimage(SCROOL_X_HORIZONTAL,SCROOL_Y_HORIZONTAL,CURSOR_SCROOL,XOR_PUT);
    }
    if(!strcmp(NomeJanela,"BotaoVistaGeral-1"))
    {
      if(ColunaGrade > 4)
      {
        if((LinhaGrade < 24) || (LinhaGrade > 30))
        {
          ExibeEnibeCursorGrade(QUADRICULA);
          QUADRICULA -= 1;
          ExibeEnibeCursorGrade(QUADRICULA);
        }
        else
          if(ColunaGrade > 6)
          {
            ExibeEnibeCursorGrade(QUADRICULA);
            QUADRICULA -= 1;
            ExibeEnibeCursorGrade(QUADRICULA);
          }
      }
    }
    if(!strcmp(NomeJanela,"BotaoVistaGeral-2"))
    {
      if(ColunaGrade < 18)
      {
        ExibeEnibeCursorGrade(QUADRICULA);
        QUADRICULA += 1;
        ExibeEnibeCursorGrade(QUADRICULA);
      }
    }
 
    if(!strcmp(NomeJanela,"BotaoVistaGeral-3"))
    {
      if(LinhaGrade > 1)
      {
        ExibeEnibeCursorGrade(QUADRICULA);
        if((ColunaGrade < 6) && (LinhaGrade == 31))
          QUADRICULA = QUADRICULA - (20*7);
        else
          QUADRICULA -= 20;
        ExibeEnibeCursorGrade(QUADRICULA);
      }
    }
    if(!strcmp(NomeJanela,"BotaoVistaGeral-4"))
    {
      if(LinhaGrade < 32)
      {
        ExibeEnibeCursorGrade(QUADRICULA);
        if((ColunaGrade < 6) && (LinhaGrade == 24))
          QUADRICULA += (20*7);
        else
          QUADRICULA += 20;
        ExibeEnibeCursorGrade(QUADRICULA);
      }
    }
    if(!strcmp(NomeJanela,"BotaoVistaGeral-5"))
    {
    }
    if(!strcmp(NomeJanela,"BotaoVistaGeral-6"))
    {
    }
    if(!strcmp(NomeJanela,"BotaoVistaGeral-7"))
    {
      CadastraQuadriculaMarcada();
      CentroQuadricula(QUADRICULA,&CodXEsq,&CodYSup);
      putimage(CodXEsq,CodYSup,MARCA_GRADE,XOR_PUT);
    }
    if(!strcmp(NomeJanela,"BotaoVistaGeral-8"))
    {
      ImagemFundo();
    }
  }

/*-----------------------------------------------------------------*\
 |            Define a Janela Corrente do Cursor                   |
\*-----------------------------------------------------------------*/
  void JanelaCorrente(char *NomeJanela)
  {
    if(ContemJanela(0.9,1.2,5.5,7.1))
       strcpy(NomeJanela, "BotaoTitulo-1");
    if(ContemJanela(0.9,7.1,99.1,12.9))
       strcpy(NomeJanela, "Menus");
    if(ContemJanela(2.3,14.7,64.5,91.2))
       strcpy(NomeJanela, "AreaCliente");
    if(ContemJanela(2.3,91.2,55.5,97.1))
       strcpy(NomeJanela, "Mensagem");
    if(ContemJanela( 2.3,14.7, 4.5,88.2))
       strcpy(NomeJanela, "ScroolVertical");
    if(ContemJanela( 2.3,14.7, 4.5,17.6))
       strcpy(NomeJanela, "ScroolVertSup");
    if(ContemJanela( 2.3,85.3, 4.5,88.2))
       strcpy(NomeJanela, "ScroolVertInf");
    if(ContemJanela( 4.5,88.2,64.5,91.2))
       strcpy(NomeJanela, "ScroolHorizontal");
    if(ContemJanela( 4.5,88.2, 6.8,91.2))
       strcpy(NomeJanela, "ScroolHoriEsq");
    if(ContemJanela(62.3,88.2,64.5,91.2))
       strcpy(NomeJanela, "ScroolHoriDir");
    if(ContemJanela(55.5,91.2,60.0,97.1))
       strcpy(NomeJanela, "BotaoMensagem-1");
    if(ContemJanela(60.0,91.2,64.5,97.1))
       strcpy(NomeJanela, "BotoaMensagem-2");
    if(ContemJanela(65.9,85.3,73.9,91.2))
       strcpy(NomeJanela, "BotaoVistaGeral-1");
    if(ContemJanela(73.9,85.3,81.8,91.2))
       strcpy(NomeJanela, "BotaoVistaGeral-2");
    if(ContemJanela(81.8,85.3,89.8,91.2))
       strcpy(NomeJanela, "BotaoVistaGeral-3");
    if(ContemJanela(89.8,85.3,97.7,91.2))
       strcpy(NomeJanela, "BotaoVistaGeral-4");
    if(ContemJanela(65.9,91.2,73.9,97.1))
       strcpy(NomeJanela, "BotaoVistaGeral-5");
    if(ContemJanela(73.9,91.2,81.8,97.1))
       strcpy(NomeJanela, "BotaoVistaGeral-6");
    if(ContemJanela(81.8,91.2,89.8,97.1))
       strcpy(NomeJanela, "BotaoVistaGeral-7");
    if(ContemJanela(89.8,91.2,97.7,97.1))
       strcpy(NomeJanela, "BotaoVistaGeral-8");
  }

/*-----------------------------------------------------------------*\
 |            Verefica qual Janela esta o Cursor                   |
\*-----------------------------------------------------------------*/
  int ContemJanela( float PerXSup, float PerYSup,
                    float PerXInf, float PerYInf)
  {
    if((POS_X_CURSOR >= ValorRelativoTela('X',PerXSup,0)) &&
       (POS_Y_CURSOR >= ValorRelativoTela('Y',PerYSup,0)) &&
       (POS_X_CURSOR <= ValorRelativoTela('X',PerXInf,0)) &&
       (POS_Y_CURSOR <= ValorRelativoTela('Y',PerYInf,0)))
    {
      return(1);               /* Janela Contem o Cursor. */
    }
    return(0);                 /* Janela Nao Contem o Cursor. */
  }

/*-----------------------------------------------------------------*\
 |            Controle das Teclas Especiais                        |
\*-----------------------------------------------------------------*/
  void TeclaEspecial(void)
  {
    char
      Tecla;                           /* Tecla pressionada.    */
 
    Tecla = getch();
    switch (Tecla)
    {
      case 'H': if (POS_Y_CURSOR-INC_CURSOR > MIN_COD_Y)
                    POS_Y_CURSOR -= INC_CURSOR;         /* Seta cima. */
        break;
      case 'P': if (POS_Y_CURSOR+INC_CURSOR < MAX_COD_Y-TAMANHO_CURSOR)
                    POS_Y_CURSOR += INC_CURSOR;         /* Seta baixo. */
        break;
      case 'K': if (POS_X_CURSOR-INC_CURSOR > MIN_COD_X)
                    POS_X_CURSOR -= INC_CURSOR;         /* Seta esquerda. */
        break;
      case 'M': if (POS_X_CURSOR+INC_CURSOR < MAX_COD_X-(1+TAMANHO_CURSOR))
                    POS_X_CURSOR += INC_CURSOR;         /* Seta direita. */
        break;
      case 'G': POS_X_CURSOR = MIN_COD_X;               /* Tecla Home. */
        break;
      case 'O': POS_X_CURSOR = MAX_COD_X-(1+TAMANHO_CURSOR);  /* Tecla Fim. */
        break;
      case 'I': POS_Y_CURSOR = MIN_COD_Y;               /* Tecla PU. */
        break;
      case 'Q': POS_Y_CURSOR = MAX_COD_Y-TAMANHO_CURSOR;      /* Tecla PD. */
        break;
      }
   }

/*-----------------------------------------------------------------*\
 |            Le a Rota do Arquivo em Disco                        |
\*-----------------------------------------------------------------*/
  void LeRota(void)
  {
    const
      Aguarde = 1;                      /* Flag parada na mensagem. */
    struct TipoRota
      {
        unsigned int
          SetorInicial,
          CruzaInicial,
          SetorFinal,
          CruzaFinal,
          NumOrdem;
        struct TipoRota
          *AnteriorRota,
          *ProximoRota;
      } Rota;
    struct TipoRota
      *PrimeiroRota,
      *AtualRota,
      *PredecessorRota;
    int
      CodXEsq,                   /* Coordenada do X Esquerdo. */
      CodYSup,                   /* Coordenada do Y Superior. */
      ArqSetorInicial,                  /* Setor Inicial da Rota.       */
      ArqCruzaInicial,                  /* Cruzamento Inicial da Rota.  */
      ArqSetorFinal,                    /* Setor Final da Rota.         */
      ArqCruzaFinal;                    /* Cruzamento Final da Rota.    */
    FILE
      *ArqLog;                          /* Variavel do Arquivo da Rota. */
    char
      *Mensagem,
      ArquivoRota[] = "CRUZAM.RLT";     /* Arquivo c/ Rota do CRUZAM.    */

    if((ArqLog = fopen(ArquivoRota,"r")) == NULL)
    {
      setcolor(COR_MENSAGEM_GERAL);
      MostraMensagem("Arquivo nao acessado -> CRUZAM.RLT" ,Aguarde);
      CadastraQuadriculaMarcada();
      CentroQuadricula(QUADRICULA,&CodXEsq,&CodYSup);
      putimage(CodXEsq,CodYSup,MARCA_GRADE,XOR_PUT);
    }
    else
    {
      PrimeiroRota    = malloc(sizeof(struct TipoRota));
      PredecessorRota = PrimeiroRota;
      fscanf( ArqLog,"\n");
      fscanf( ArqLog,"\n");
      fscanf( ArqLog,"\n");
      while( !feof( ArqLog))
      {
        if((AtualRota = malloc(sizeof(struct TipoRota))) == NULL)
        {
          setcolor(COR_MENSAGEM_GERAL);
          MostraMensagem("Memoria insuficiente, estrutura ROTA ",Aguarde);
          closegraph();
          exit(1);                /* Erro: Arquivo incorreto. */
        }
        fscanf(ArqLog,"%d"  ,&ArqSetorInicial);
        fscanf(ArqLog,"%d"  ,&ArqCruzaInicial);
        fscanf(ArqLog,"%d"  ,&ArqSetorFinal);
        fscanf(ArqLog,"%d\n",&ArqCruzaFinal);
 
        PredecessorRota ->ProximoRota = AtualRota;
        Rota.SetorInicial = ArqSetorInicial;
        Rota.CruzaInicial = ArqCruzaInicial;
        Rota.SetorFinal   = ArqSetorFinal;
        Rota.CruzaFinal   = ArqCruzaFinal;
      }
      fclose(ArqLog);
    }
  }

/*    struct Segmento
      {
        unsigned int
          XInicial,
          YInicial,
          XFinal,
          YFinal;
          struct Segmento
            *ProSegmento;
      };
*/
