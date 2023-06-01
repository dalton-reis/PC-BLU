  #include <graphics.h>
  #include <stdio.h>
  #include <alloc.h>
  #include "globais.h"
  #include "define.h"
  #define EXTERN extern


  float
    LAR_MAR,                   /* Num. de pixels da margem de Largura.    */
    LAR_INT,                   /* Num. de pixels do Intervalo na Largura. */
    LAR_DISPO,                 /* Largura Disponivel p/ desenho da Grade. */
    LAR_QT_COL ,               /* Quant. de Colunas na Largura da grade.  */
    ALT_DISPO,                 /* Altura Disponivel p/ desenho da Grade.  */
    COD_BASE_X,                /* Coordenada Base ponto X inicial Grade.  */
    COD_BASE_Y,                /* Coordenada Base ponto Y inicial Grade.  */
    ASPECT;                    /* Relacao de Aspect.                      */


/*-----------------------------------------------------------------*\
 |            Desenha Cursor Geral  (retangulo-bar)                |
\*-----------------------------------------------------------------*/
  void DesenhaCursorGeral()
  {
    int
      PosXDir,                    /* Posicao X Direito  area desenho */
      PosYSup,                    /* Posicao Y Superior area desenho */
      PosXEsq,                    /* Posicao X Esquerdo area desenho */
      PosYInf;                    /* Posicao Y Inferior area desenho */
    unsigned int SizeCursor;      /* Espaco memoria Cursor.          */
 
    PosXDir = 0;
    PosYSup = 0;
    PosXEsq = TAMANHO_CURSOR;
    PosYInf = TAMANHO_CURSOR*ASPECT;
    setcolor(COR_CURSOR_GERAL);
    bar(PosXDir,PosYSup,PosXEsq,PosYInf);
    SizeCursor = imagesize(PosXDir,PosYSup,PosXEsq,PosYInf);
    CURSOR_GERAL = malloc(SizeCursor);
    getimage(PosXDir,PosYSup,PosXEsq,PosYInf,CURSOR_GERAL);
    putimage(PosXDir,PosYSup,CURSOR_GERAL,XOR_PUT);
  }
 
/*-----------------------------------------------------------------*\
 |            Desenha Cursor Barra Scroll (tumpete)                |
\*-----------------------------------------------------------------*/
  void DesenhaCursorScrool()
  {
    int
      PosXDir,                    /* Posicao X Direito  area desenho */
      PosYSup,                    /* Posicao Y Superior area desenho */
      PosXEsq,                    /* Posicao X Esquerdo area desenho */
      PosYInf;                    /* Posicao Y Inferior area desenho */
    unsigned int SizeCursor;      /* Espaco memoria Cursor.          */
 
    setcolor(COR_QUADRADO_SCROOL);
    setfillstyle(SOLID_FILL,COR_PRE_SCROOL_QUADRA);
    PosXDir = 0;
    PosYSup = 0;
    PosXEsq = ValorRelativoTela('X',2.3,0);
    PosYInf = ValorRelativoTela('Y',2.9,0);
    bar(PosXDir,PosYSup,PosXEsq,PosYInf);
    SizeCursor = imagesize(PosXDir,PosYSup,PosXEsq,PosYInf);
    CURSOR_SCROOL = malloc(SizeCursor);
    getimage(PosXDir,PosYSup,PosXEsq,PosYInf,CURSOR_SCROOL);
    putimage(PosXDir,PosYSup,CURSOR_SCROOL,XOR_PUT);
  }

/*-----------------------------------------------------------------*\
 |            Interface                                            |
\*-----------------------------------------------------------------*/
  void Interface(void)
  {
    DesenhaCursorGeral();
    DesenhaCursorScrool();
    JanelaMoldura();
    JanelaMensagem();
    Menus();
    JanelaExibicao();
    BotaoCaminho();
    JanelaVistaGeral();
    JanelaAreaBotoes();
    DesenhaBarraScrool();
  }

/*-----------------------------------------------------------------*\
 |            Definicao da Janela de Moldura                       |
\*-----------------------------------------------------------------*/
  void JanelaMoldura(void)
  {
    const
      NaoPreenche = 1;         /* Janela Nao Preenchida. */
 
    setcolor(COR_JANELA_MOLDURA);
    DesenhaJanela(  0,  0, 100, 100,NaoPreenche);     /* Borda externa. */
    DesenhaJanela(0.9,1.2,99.1,98.8,NaoPreenche);     /* Borda Dupla.   */
  }
 
/*-----------------------------------------------------------------*\
 |            Definicao da Janela de Mensagens                     |
\*-----------------------------------------------------------------*/
  void JanelaMensagem(void)
  {
    const
      NaoAguarde = 0;             /* Nao Aguarda na Mensagem. */
 
    DesenhaJanelaMensagem();
    MostraMensagem("Aguarde: inicializando ambiente.",NaoAguarde);
  }
 
/*-----------------------------------------------------------------*\
 |            Desenha Janela de Mensagens                          |
\*-----------------------------------------------------------------*/
  void DesenhaJanelaMensagem(void)
  {
    const
      NaoPreenche = 1;         /* Janela Nao Preenchida. */
 
    setcolor(COR_JANELA_MENSAGEM);
    DesenhaJanela( 2.3,91.2,55.5,97.1,NaoPreenche);   /* Janela Mensagens. */
  }
 
/*-----------------------------------------------------------------*\
 |            Definicao dos Menus                                  |
\*-----------------------------------------------------------------*/
 
  void Menus(void)
  {
/*    EstabeleceFatorAmpliacao();
      EstabelecePassoScrool(); */
    DesenhaJanelaMenu();
    EscreveTextoMenu();
  }
 
/*-----------------------------------------------------------------*\
 |                 Desenha Janela Menu                             |
\*-----------------------------------------------------------------*/
  void DesenhaJanelaMenu(void)
  {
    const
      Preenche    = 2,         /* Janela Preenchida.     */
      NaoPreenche = 1;         /* Janela Nao Preenchida. */
 
    setcolor(COR_JANELA_MENU);
    setfillstyle(SOLID_FILL,COR_PRE_TITULO);
    DesenhaJanela( 5.5, 1.2,94.5, 7.1, Preenche);     /* Janela do titulo.  */
    DesenhaJanela( 0.9, 1.2, 5.5, 7.1, NaoPreenche);  /* Janela do bot†o-1. */
    DesenhaJanela( 1.8, 3.5, 4.5, 4.7, Preenche);     /* Traco do bot†o-1.  */
    DesenhaJanela(94.5, 1.2,99.1, 7.1, NaoPreenche);  /* Janela do bot†o-2. */
    DesenhaJanela( 0.9, 7.1,99.1,12.9, NaoPreenche);  /* Janela de menus.   */
  }
 
/*-----------------------------------------------------------------*\
 |                   Escreve Texto do Menu                         |
\*-----------------------------------------------------------------*/
  void EscreveTextoMenu(void)
  {
    char
      TextoTitulo[] = "Projeto Cartografico - Blumenau",
      TextoMenu[]   = "Parametros      Caminho      Auxilio";
    int
      XTit,    YTit,           /* Ponto Base da Men. do Titulo.  */
      XMenu,   YMenu;          /* Ponto Base da Men. do Menu.    */
 
    setcolor(COR_MENSAGEM_TITULO);
    XTit = ValorRelativoTela('X', 5.5,26);     /* Mensagem de Titulo. */
    YTit = ValorRelativoTela('Y', 1.2, 2);
    outtextxy(XTit,YTit,TextoTitulo);
    setcolor(COR_MENSAGEM_MENU);               /* Mensagem de Menu. */
    XMenu = ValorRelativoTela('X', 0.9, 5);
    YMenu = ValorRelativoTela('Y', 7.1, 2);
    outtextxy(XMenu,YMenu,TextoMenu);
  }
 
/*-----------------------------------------------------------------*\
 |            Definicao da Janela de Exibicao                      |
\*-----------------------------------------------------------------*/
  void JanelaExibicao(void)
  {
    DesenhaJanelaExibicao();
  }
 
/*-----------------------------------------------------------------*\
 |            Desenha Janela de Exebicao                           |
\*-----------------------------------------------------------------*/
  void DesenhaJanelaExibicao(void)
  {
    const
      NaoPreenche = 1;         /* Janela Nao Preenchida. */
 
    setcolor(COR_JANELA_EXEBICAO);
    DesenhaJanela( 2.3,14.7,64.5,91.2,NaoPreenche); /* Janela de Exebicao. */
  }
 
/*-----------------------------------------------------------------*\
 |            Definicao dos Botoes de Caminho                      |
\*-----------------------------------------------------------------*/
  void BotaoCaminho(void)
  {
    DesenhaBotoesCaminho();
  }
 
/*-----------------------------------------------------------------*\
 |            Desenha Botoes Caminho                               |
\*-----------------------------------------------------------------*/
  void DesenhaBotoesCaminho(void)
  {
    const
      NaoPreenche = 1;         /* Janela Nao Preenchida. */
 
    setcolor(COR_JANELA_CAMINHO);
    DesenhaJanela(55.5,91.2,60.0,97.1,NaoPreenche);   /* Janela Bot†o-1. */
    DesenhaJanela(60.0,91.2,64.5,97.1,NaoPreenche);   /* Janela Bot†o-2. */
    setcolor(COR_SETA_CAMINHO);
    setfillstyle(SOLID_FILL,COR_PRE_CAMINHO_SETA);
    DesenhaSetas(55.5,91.2,60.0,97.1,SETA_ESQ);
    DesenhaSetas(60.0,91.2,64.5,97.1,SETA_DIR);
  }
 
/*-----------------------------------------------------------------*\
 |            Desenhas setas para botoes                           |
\*-----------------------------------------------------------------*/
  void DesenhaSetas(float PerXSup,float PerYSup,
                    float PerXInf,float PerYInf,int Opcao)
       /*---------------------------------------------*\
        |   PerXSup: Percentual do valor X Superior.  |
        |   PerYSup: Percentual do valor Y Superior.  |
        |   PerXInf: Percentual do valor X Inferior.  |
        |   PerYInf: Percentual do valor Y Inferior.  |
        |   Seta[5]: Vetor dos pontos da seta.        |
        \*--------------------------------------------*/
   {
     float
       PontoBaseX,           /* Coordenada X Superior-esquerdo.   */
       PontoBaseY,           /* Coordenada Y Superior-esquerdo.   */
       AlturaSeta,           /* Altura da Seta.                   */
       LarguraSeta;          /* Largura da Seta.                  */
     int
       Seta[6];              /* Vetor dos pontos do triangulo.    */
 
     PontoBaseX  = ValorRelativoTela('X',PerXSup,0);
     PontoBaseY  = ValorRelativoTela('Y',PerYSup,0);
     LarguraSeta = (ValorRelativoTela('X',PerXInf,0) - PontoBaseX) / 3;
     AlturaSeta  = (ValorRelativoTela('Y',PerYInf,0) - PontoBaseY) / 3;
 
     switch (Opcao)
       {
         case 90:
           Seta[0] = PontoBaseX + (LarguraSeta + (LarguraSeta / 2));
           Seta[1] = PontoBaseY + AlturaSeta;
           Seta[2] = PontoBaseX + LarguraSeta;
           Seta[3] = PontoBaseY + (AlturaSeta * 2);
           Seta[4] = PontoBaseX + (LarguraSeta * 2);
           Seta[5] = PontoBaseY + (AlturaSeta * 2);
           fillpoly( 3, Seta);
         break;
         case 180:
           Seta[0] = PontoBaseX + LarguraSeta;
           Seta[1] = PontoBaseY + (AlturaSeta + (AlturaSeta / 2));
           Seta[2] = PontoBaseX + (LarguraSeta * 2);
           Seta[3] = PontoBaseY + (AlturaSeta * 2);
           Seta[4] = PontoBaseX + (LarguraSeta * 2);
           Seta[5] = PontoBaseY + AlturaSeta;
           fillpoly( 3, Seta);
         break;
         case 270:
           Seta[0] = PontoBaseX + LarguraSeta;
           Seta[1] = PontoBaseY + AlturaSeta;
           Seta[2] = PontoBaseX + (LarguraSeta + (LarguraSeta / 2));
           Seta[3] = PontoBaseY + (AlturaSeta * 2);
           Seta[4] = PontoBaseX + (LarguraSeta * 2);
           Seta[5] = PontoBaseY + AlturaSeta;
           fillpoly( 3, Seta);
         break;
         case 360:
         {
           Seta[0] = PontoBaseX + LarguraSeta;
           Seta[1] = PontoBaseY + AlturaSeta;
           Seta[2] = PontoBaseX + LarguraSeta;
           Seta[3] = PontoBaseY + (AlturaSeta * 2);
           Seta[4] = PontoBaseX + (LarguraSeta * 2);
           Seta[5] = PontoBaseY + (AlturaSeta + (AlturaSeta / 2));
           fillpoly( 3, Seta);
         }
         break;
      }
   }
 
/*-----------------------------------------------------------------*\
 |            Definicao da Janela Vista Geral                      |
\*-----------------------------------------------------------------*/
  void JanelaVistaGeral(void)
  {
    const
      NaoPreenche = 1;            /* Janela Nao Preenchida. */
 
    setcolor(COR_JANELA_VISTA);
    DesenhaJanela(65.9,18.8,97.7,85.3,NaoPreenche); /* Janela Vista Geral. */
    DesenhaJanela(65.9,14.7,97.7,18.8,NaoPreenche); /* Jan. Tit. V. Geral. */
    EscreveTextoVistaGeral();
    ConstroiGradeMapa();
    RealcaQuadriculasAtivas();
    DesenhaNorte();
    DesenhaCursorGrade();
    DesenhaMarcaGrade();
    ExibeEnibeCursorGrade(QUADRICULA);
  }
 
/*-----------------------------------------------------------------*\
 |            Escreve Texto Vista Geral                            |
\*-----------------------------------------------------------------*/
  void EscreveTextoVistaGeral(void)
  {
    char
      TextoVistaGeral[] = "Vista Geral";
    int
      XVisGer, YVisGer;        /* Ponto Base da Men. da Vista Geral. */
 
    setcolor(COR_MENSAGEM_VISTA);            /* Mensagem da Vista Geral. */
    XVisGer = ValorRelativoTela('X',69.9,3.5);
    YVisGer = ValorRelativoTela('Y',14.7,1.5);
    outtextxy(XVisGer,YVisGer,TextoVistaGeral);
  }

/*-----------------------------------------------------------------*\
 |            Constroi Grade do Mapa                               |
\*-----------------------------------------------------------------*/
  void ConstroiGradeMapa(void)
  {
    float
      LarMax,            /* Num. Maximo de pixels de Largura.       */
      AltMax,            /* Num. Maximo de pixels de Altura.        */
      AltQtCol = 32,     /* Quant. de Colunas na Largura da grade.  */
      AltMar,            /* Num. de pixels da margem de Altura.     */
      Cont;              /* Variavel Contadora.                     */
 
          /* Margem da Jan. Vista Geral ate a grade em pixels. */
    LAR_MAR = ValorRelativoTela('X',1.8,0);
    AltMar = ValorRelativoTela('Y',2.4,0);
          /* Largura e Altura Maxima da janela de Vista Geral em pixels. */
    LarMax = ValorRelativoTela('X',97.7,0) - ValorRelativoTela('X',65.9,0);
    AltMax = ValorRelativoTela('Y',85.3,0) - ValorRelativoTela('Y',18.8,0);
           /* Calculo do Intervalo da Largura da Grade. */
    LAR_INT = (LarMax - (LAR_MAR * 2)) / LAR_QT_COL;
    IntLargura(LarMax,AltQtCol,AltMax);
    ALT_DISPO = AltQtCol * LAR_INT * ASPECT;
    AltMar = (AltMax - ALT_DISPO) / 2;
          /* Coordenadas do ponto Base p/ coonstrucao da grade. */
    COD_BASE_X = ValorRelativoTela('X',65.9,0) + LAR_MAR;
    COD_BASE_Y = ValorRelativoTela('Y',18.8,0) + AltMar;
    setcolor( COR_GRADE);
          /* Desenho das linhas horizontais da Grade. */
    for( Cont=0; Cont < AltQtCol+1; Cont++)
    {
      line( COD_BASE_X, COD_BASE_Y+( LAR_INT*Cont*ASPECT),
            COD_BASE_X+LAR_DISPO,COD_BASE_Y+(LAR_INT*Cont*ASPECT));
    }
          /* Desenho das linhas verticais da Grade. */
    for( Cont=0; Cont < LAR_QT_COL+1; Cont++)
    {
      line( COD_BASE_X+(LAR_INT*Cont),COD_BASE_Y,
            COD_BASE_X+(LAR_INT*Cont),COD_BASE_Y+ALT_DISPO);
    }
  }
 
/*-----------------------------------------------------------------*\
 |            Calculo do Intervalo da Largura da Grade             |
\*-----------------------------------------------------------------*/
  void IntLargura( float LarMax, float AltQtCol, float AltMax)
  {
    if(LAR_INT < 2)
    {
      LAR_QT_COL -= 4;
      LAR_INT = (LarMax - (LAR_MAR * 2)) / LAR_QT_COL;
      IntLargura(LarMax,AltQtCol,AltMax);
    }
    else
    {
      LAR_DISPO = LAR_QT_COL * LAR_INT;
      LAR_MAR   = (LarMax - LAR_DISPO) / 2;
    }
    if (((AltQtCol+1) * LAR_INT * ASPECT) > AltMax)
    {
      LAR_INT -= 1;
      IntLargura(LarMax,AltQtCol,AltMax);
    }
  }
 
/*-----------------------------------------------------------------*\
 |            Realca Quadriculas Ativas na Grade                   |
\*-----------------------------------------------------------------*/
  void RealcaQuadriculasAtivas(void)
  {
    const
      Aguarde = 1;                /* Flag parada na mensagem. */
    int
      PosXCurGrade,               /* Posicao X do Cursor na Grade.  */
      PosYCurGrade,               /* Posicao Y do Cursor na Grade.  */
      NumeroQuadri;               /* Numero da Quadricula ativa.    */
    FILE
      *ArqLog;                    /* Variavel do Arquivo de quadriculas. */
    char
      *Mensagem,
      ArquivoQuadricula[] = "QUADRI.DIG";

    if((ArqLog = fopen(ArquivoQuadricula,"r")) == NULL)
    {
      setcolor(COR_MENSAGEM_GERAL);
/*    strcpy(Mensagem,strcat("Arquivo nao acessado -> ",ArquivoQuadricula)); */
      MostraMensagem("Arquivo nao acessado ->  QUADRI.DIG ",Aguarde);
    }
    else
    {
      setcolor(COR_QUADRICULA_ATIVA);
      setfillstyle(SOLID_FILL,COR_PRE_QUAD_ATIVA);
      while(!feof(ArqLog))
      {
        fscanf(ArqLog,"%d",&NumeroQuadri);
        if((NumeroQuadri >= 1) && (NumeroQuadri <= 700))
        {
          CentroQuadricula(NumeroQuadri,&PosXCurGrade,&PosYCurGrade);
          fillellipse(PosXCurGrade+(LAR_INT/2),
                      PosYCurGrade+(LAR_INT*ASPECT/2),1,1*ASPECT);
        }
        else
        {
          setcolor(COR_MENSAGEM_GERAL);
          MostraMensagem("Arquivo acessado INCORRETO -> QUADRI.DIG ",Aguarde);
          closegraph();
          exit(1);                /* Erro: Arquivo incorreto. */
        }
      }
      fclose(ArqLog);
    }
  }
 
/*-----------------------------------------------------------------*\
 |            Desenha a representacao do Norte                     |
\*-----------------------------------------------------------------*/
  void DesenhaNorte()
  {
    SelecionaJanela(COD_BASE_X-(LAR_INT*2)+1,COD_BASE_Y+(LAR_INT*ASPECT*2)+1,
                    COD_BASE_X+(LAR_INT*2)-1,COD_BASE_Y+(LAR_INT*ASPECT*8)-1,
                    CLIP_OFF, APAGA_JANELA);
    setcolor(COR_ICONE_NORTE);
    outtextxy(LAR_INT+(LAR_INT/2),(LAR_INT*ASPECT/2),"N");
    line(LAR_INT  ,LAR_INT*3*ASPECT,LAR_INT*3,LAR_INT*3*ASPECT);
    line(LAR_INT*2,LAR_INT*2*ASPECT  ,LAR_INT*2,LAR_INT*5*ASPECT);
    circle(LAR_INT*2,LAR_INT*3*ASPECT, 5);
    SelecionaJanela(MIN_COD_X,MIN_COD_Y,MAX_COD_X,MAX_COD_Y,
                    CLIP_OFF,NAO_APAGA_JANELA);     /* Sel. todo janela. */
  }
 
/*-----------------------------------------------------------------*\
 |            Desenha Cursor Grade  (circulo)                      |
\*-----------------------------------------------------------------*/
  void DesenhaCursorGrade()
  {
    int
      PosXDir,                    /* Posicao X Direito  area desenho */
      PosYSup,                    /* Posicao Y Superior area desenho */
      PosXEsq,                    /* Posicao X Esquerdo area desenho */
      PosYInf;                    /* Posicao Y Inferior area desenho */
    unsigned int SizeCursor;      /* Espaco memoria Cursor.          */
 
    PosXDir = MAX_COD_X / 2;
    PosYSup = MAX_COD_Y / 2;
    PosXEsq = PosXDir + LAR_INT;
    PosYInf = PosYSup + (LAR_INT*ASPECT);
    setcolor(COR_CURSOR_GRADE);
    circle(PosXDir+(LAR_INT/2),PosYSup+(LAR_INT*ASPECT/2), 2);
    SizeCursor = imagesize(PosXDir,PosYSup,PosXEsq,PosYInf);
    CURSOR_GRADE = malloc(SizeCursor);
    getimage(PosXDir,PosYSup,PosXEsq,PosYInf,CURSOR_GRADE);
    putimage(PosXDir,PosYSup,CURSOR_GRADE,XOR_PUT);
  }

/*-----------------------------------------------------------------*\
 |            Desenha Marca Grade  (circulo)                       |
\*-----------------------------------------------------------------*/
  void DesenhaMarcaGrade()
  {
    int
      PosXDir,                    /* Posicao X Direito  area desenho */
      PosYSup,                    /* Posicao Y Superior area desenho */
      PosXEsq,                    /* Posicao X Esquerdo area desenho */
      PosYInf;                    /* Posicao Y Inferior area desenho */
    unsigned int SizeCursor;      /* Espaco memoria Cursor.          */
 
    PosXDir = MAX_COD_X / 2;
    PosYSup = MAX_COD_Y / 2;
    PosXEsq = PosXDir + LAR_INT;
    PosYInf = PosYSup + (LAR_INT*ASPECT);
    setcolor(COR_MARCA_GRADE);
    setfillstyle(SOLID_FILL,COR_MARCA_GRADE);
    fillellipse(PosXDir+(LAR_INT/2),PosYSup+(LAR_INT*ASPECT/2), 4, 4*ASPECT);
    SizeCursor = imagesize(PosXDir,PosYSup,PosXEsq,PosYInf);
    MARCA_GRADE = malloc(SizeCursor);
    getimage(PosXDir,PosYSup,PosXEsq,PosYInf,MARCA_GRADE);
    putimage(PosXDir,PosYSup,MARCA_GRADE,XOR_PUT);
  }
 
/*-----------------------------------------------------------------*\
 |            Exibe ou Enibe o Cursor na Grade                     |
\*-----------------------------------------------------------------*/
  void ExibeEnibeCursorGrade(int NumeroQuadri)
  {
    int
      CodXEsq,                   /* Coordenada do X Esquerdo. */
      CodYSup;                   /* Coordenada do Y Superior. */
    CentroQuadricula(NumeroQuadri,&CodXEsq,&CodYSup);
    putimage(CodXEsq,CodYSup,CURSOR_GRADE,XOR_PUT);
  }
 
/*-----------------------------------------------------------------*\
 |            Janela Area Botoes                                   |
\*-----------------------------------------------------------------*/
  void JanelaAreaBotoes(void)
  {
    const
      NaoPreenche = 1;         /* Janela Nao Preenchida. */
 
    setcolor(COR_BOTAO_VISTA);
    DesenhaJanela(65.9,85.3,73.9,91.2,NaoPreenche); /* Janela Bot†o-1. */
    DesenhaJanela(73.9,85.3,81.8,91.2,NaoPreenche); /* Janela Bot†o-2. */
    DesenhaJanela(81.8,85.3,89.8,91.2,NaoPreenche); /* Janela Bot†o-3. */
    DesenhaJanela(89.8,85.3,97.7,91.2,NaoPreenche); /* Janela Bot†o-4. */
    DesenhaJanela(65.9,91.2,73.9,97.1,NaoPreenche); /* Janela Bot†o-5. */
    DesenhaJanela(73.9,91.2,81.8,97.1,NaoPreenche); /* Janela Bot†o-6. */
    DesenhaJanela(81.8,91.2,89.8,97.1,NaoPreenche); /* Janela Bot†o-7. */
    DesenhaJanela(89.8,91.2,97.7,97.1,NaoPreenche); /* Janela Bot†o-8. */
    EscreveTextoBotoes();
    setcolor(COR_SETA_GRADE);
    setfillstyle(SOLID_FILL,COR_PRE_GRADE_SETA);
    DesenhaSetas(65.9,85.3,73.9,91.2,SETA_ESQ);     /* Seta Bot†o-1.   */
    DesenhaSetas(73.9,85.3,81.8,91.2,SETA_DIR);     /* Seta Bot†o-2.   */
    DesenhaSetas(81.8,85.3,89.8,91.2,SETA_BAI);     /* Seta Bot†o-3.   */
    DesenhaSetas(89.8,85.3,97.7,91.2,SETA_CIM);     /* Seta Bot†o-4.   */
  }
 
/*-----------------------------------------------------------------*\
 |                   Escreve Texto dos Botoes                      |
\*-----------------------------------------------------------------*/
  void EscreveTextoBotoes(void)
  {
    char
      TextoBotao5[] = "AMPLIA",   /* Texto do Botao 5. */
      TextoBotao6[] = "REDUZ",    /* Texto do Botao 6. */
      TextoBotao7[] = "MARCA",    /* Texto do Botao 7. */
      TextoBotao8[] = "OK";       /* Texto do Botao 8. */
    int
      XBot5,   YBot5,             /* Ponto Base da Men. do Bot†o 5. */
      XBot6,   YBot6,             /* Ponto Base da Men. do Bot†o 6. */
      XBot7,   YBot7,             /* Ponto Base da Men. do Bot†o 7. */
      XBot8,   YBot8;             /* Ponto Base da Men. do Bot†o 8. */
 
    setcolor(COR_MENSAGEM_BOTAO);
    XBot5 = ValorRelativoTela('X',65.9,0.5);      /* Mensagem do Bot†o 5. */
    YBot5 = ValorRelativoTela('Y',91.2,2.3);
    outtextxy(XBot5,YBot5,TextoBotao5);
    XBot6 = ValorRelativoTela('X',73.9,1.0);      /* Mensagem do Bot†o 6. */
    YBot6 = ValorRelativoTela('Y',91.2,2.3);
    outtextxy(XBot6,YBot6,TextoBotao6);
    XBot7 = ValorRelativoTela('X',81.8,1.0);      /* Mensagem do Bot†o 7. */
    YBot7 = ValorRelativoTela('Y',91.2,2.3);
    outtextxy(XBot7,YBot7,TextoBotao7);
    XBot8 = ValorRelativoTela('X',89.8,2.5);      /* Mensagem do Bot†o 8. */
    YBot8 = ValorRelativoTela('Y',91.2,2.3);
    outtextxy(XBot8,YBot8,TextoBotao8);
  }
 
/*-----------------------------------------------------------------*\
 |            Definicao da Barra de Scrool                         |
\*-----------------------------------------------------------------*/
  void DesenhaBarraScrool(void)
  {
    const
      NaoPreenche = 1;         /* Janela Nao Preenchida. */

    setcolor(COR_BARRA_SCROOL);
    DesenhaJanela( 2.3,14.7, 4.5,88.2,NaoPreenche); /* Coluna Vertical.   */
    DesenhaJanela( 4.5,88.2,64.5,91.2,NaoPreenche); /* Coluna Horizontal. */
    setcolor(COR_BOTAO_SCROOL);
    DesenhaJanela( 2.3,14.7, 4.5,17.6,NaoPreenche); /* Qd. Superior Ver.  */
    DesenhaJanela( 2.3,85.3, 4.5,88.2,NaoPreenche); /* Qd. Inferior Ver.  */
    DesenhaJanela( 4.5,88.2, 6.8,91.2,NaoPreenche); /* Qd. Esquerdo Hor.  */
    DesenhaJanela(62.3,88.2,64.5,91.2,NaoPreenche); /* Qd. Direito  Hor.  */
    setcolor(COR_SETA_SCROOL);
    setfillstyle(SOLID_FILL,COR_PRE_SCROOL_SETA);
    DesenhaSetas( 2.3,14.7, 4.5,17.6,SETA_CIM);    /* Seta Qd. Sup Ver.  */
    DesenhaSetas( 2.3,85.3, 4.5,88.2,SETA_BAI);    /* Seta Qd. Inf Ver.  */
    DesenhaSetas( 4.5,88.2, 6.8,91.2,SETA_ESQ);    /* Seta Qd. Esq Hor.  */
    DesenhaSetas(62.3,88.2,64.5,91.2,SETA_DIR);    /* Seta Qd. Dir Hor.  */
    SCROOL_X_VERTICAL = ValorRelativoTela('X', 2.3,0);
    SCROOL_Y_VERTICAL = ValorRelativoTela('Y',17.6,0);
    putimage(SCROOL_X_VERTICAL,SCROOL_Y_VERTICAL,CURSOR_SCROOL,XOR_PUT);
    SCROOL_X_HORIZONTAL = ValorRelativoTela('X', 6.8,0);
    SCROOL_Y_HORIZONTAL = ValorRelativoTela('Y',88.2,0);
    putimage(SCROOL_X_HORIZONTAL,SCROOL_Y_HORIZONTAL,CURSOR_SCROOL,XOR_PUT);
  }
 
/*-----------------------------------------------------------------*\
 |                     Desenha Janelas                             |
\*-----------------------------------------------------------------*/
  void DesenhaJanela( float PerXSup, float PerYSup,
                      float PerXInf, float PerYInf, int Opcao)
       /*---------------------------------------------*\
        |   PerXSup: Percentual do valor X Superior.  |
        |   PerYSup: Percentual do valor Y Superior.  |
        |   PerXInf: Percentual do valor X Inferior.  |
        |   PerYInf: Percentual do valor Y Inferior.  |
        |   Opcao:   normal, preenchida e botao.      |
       \*---------------------------------------------*/
  {
    switch (Opcao)
    {
      case 1:          /* Janela normal. */
      {
        rectangle( ValorRelativoTela('X',PerXSup,0),
                   ValorRelativoTela('Y',PerYSup,0),
                   ValorRelativoTela('X',PerXInf,0),
                   ValorRelativoTela('Y',PerYInf,0));
      }
      break;
      case 2:          /* Janela preenchida.  */
      {
              bar( ValorRelativoTela('X',PerXSup,0),
                   ValorRelativoTela('Y',PerYSup,0),
                   ValorRelativoTela('X',PerXInf,0),
                   ValorRelativoTela('Y',PerYInf,0));
      }
      break;
    }
  }
 
