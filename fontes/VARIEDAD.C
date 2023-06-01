  #include <graphics.h>
  #include "globais.h"
  #include "define.h"

 #define EXTERN extern

/*-----------------------------------------------------------------*\
 |            Mensagens de Erro                                    |
\*-----------------------------------------------------------------*/
  void MostraMensagem(char *Mensagem,int Opcao)
  {
    const
      MensAfX = 7,                /* Afastamento Horizontal.       */
      MensAfY = 2,                /* Afastamento Vertical.         */
      MensTam = 43;               /* Tamanho maximo de Caracteres. */

    SelecionaJanela(ValorRelativoTela( 'X',  2.3,  0.5),
                    ValorRelativoTela( 'Y', 91.2,  0.5),
                    ValorRelativoTela( 'X', 55.5, -0.5),
                    ValorRelativoTela( 'Y', 97.1, -0.5),
                    CLIP_ON, APAGA_JANELA);         /* Sel. jan. mensagem. */
    if( strlen( Mensagem) > MensTam)
    {
      closegraph();
      exit(1);               /* Erro: excedeu tamanho Campo Mensagem. */
    }
    setcolor( COR_MENSAGEM_GERAL);
    outtextxy( MensAfX, MensAfY, Mensagem);
    if(Opcao)
    {
      getch();
      clearviewport();
    }
    SelecionaJanela(MIN_COD_X,MIN_COD_Y,MAX_COD_X,MAX_COD_Y,
                    CLIP_OFF,NAO_APAGA_JANELA);     /* Sel. todo janela. */
  }

/*-----------------------------------------------------------------*\
 |            Calculo do Centro da Quadricula                      |
\*-----------------------------------------------------------------*/
  void CentroQuadricula(int NumeroQuadri,int *CodXEsq,int *CodYSup)
  {
    int
      NumLinha,              /* Numero da Linha da Quadricula atual.   */
      NumColuna,             /* Numero da coluna da Quadricula atual.  */
      DifGraLin   =  1,      /* Diferen‡a de Linhas da Grade.          */
      DifGraCol   =  3,      /* Diferen‡a de Colunas da Grade.         */
      QtColuna    = 20;      /* Quantidade Maxima de Colunas na Grade. */

    NumLinha = NumeroQuadri / QtColuna;
    if( NumLinha == 0)
    {
      NumLinha = 1;
      NumColuna = NumeroQuadri;
    }
    else
    {
      NumColuna = NumLinha * QtColuna;
      NumLinha  -= DifGraLin;
      NumColuna = NumeroQuadri - NumColuna - DifGraCol;
    }
    if( NumColuna == 0)
      NumColuna = 1;
    *CodXEsq = COD_BASE_X + (LAR_INT *  (NumColuna-1));
    *CodYSup = COD_BASE_Y + ALT_DISPO - (LAR_INT*ASPECT* (NumLinha+1));
  }

/*-----------------------------------------------------------------*\
 |                   Seleciona Janela de foco                      |
\*-----------------------------------------------------------------*/
  void SelecionaJanela(float XEsq,float YSup,
                       float XDir,float YInf,
                       int Clip,int Apaga)
       /*------------------------------------------*\
        |   XEsq: Percentual do valor X Superior.  |
        |   YSup: Percentual do valor Y Superior.  |
        |   XDir: Percentual do valor X Inferior.  |
        |   YInf: Percentual do valor Y Inferior.  |
        |   Clip   : Clipping da Janela de vis†o.  |
        |   Apaga  : Apagar Janela de vis†o.       |
       \*------------------------------------------*/
   {
     setviewport(XEsq,YSup,XDir,YInf,Clip);
     if(Apaga)
       clearviewport();
   }

/*-----------------------------------------------------------------*\
 |                      Valor Relativo a Tela                      |
\*-----------------------------------------------------------------*/
  ValorRelativoTela(char XouY,float Percentual,float Acrescimo)
       /*----------------------------------------------*\
        |   XouY   : Calculo do Valor de X ou Y.       |
        |   MIN_COD_X: Minima Coordenada do X de tela. |
        |   MIN_COD_Y: Minima Coordenada do Y de tela. |
        |   MAX_COD_X: Maxima Coordenada do X de tela. |
        |   MAX_COD_Y: Maxima Coordenada do Y de tela. |
       \*----------------------------------------------*/
  {
    Percentual = Percentual / 100;
    Acrescimo  = Acrescimo  / 100;
    switch (XouY)
    {
      case 'X':
        return((int) (MIN_COD_X + ((MAX_COD_X-MIN_COD_X) *
                     (Percentual+Acrescimo))));
      case 'Y':
        return((int) (MIN_COD_Y + ((MAX_COD_Y-MIN_COD_Y) *
                     (Percentual+Acrescimo))));
    }
    closegraph();
    exit(1);             /* Erro: parametro XouY.         */
    return(1);
  }

