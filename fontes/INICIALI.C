 #include <graphics.h>
 #include <stdio.h>
 #include "define.h"

 #define EXTERN extern
 #include "globais.h"

 int
    COR_CURSOR_GERAL,
    COR_JANELA_EXEBICAO,
    COR_VIA,
    COR_RIO,
    COR_REFERENCIA,
    COR_JANELA_VISTA,
    COR_GRADE,
    COR_MENSAGEM_VISTA,
    COR_BOTAO_VISTA,
    COR_MENSAGEM_BOTAO,
    COR_CURSOR_GRADE,
    COR_MARCA_GRADE,
    COR_PRE_MARCA,
    COR_QUADRICULA_ATIVA,
    COR_PRE_QUAD_ATIVA,
    COR_ICONE_NORTE,
    COR_SETA_GRADE,
    COR_PRE_GRADE_SETA,
    COR_JANELA_MOLDURA,
    COR_JANELA_MENU,
    COR_PRE_TITULO,
    COR_MENSAGEM_TITULO,
    COR_MENSAGEM_MENU,
    COR_BARRA_SCROOL,
    COR_QUADRADO_SCROOL,
    COR_PRE_SCROOL_QUADRA,
    COR_SETA_SCROOL,
    COR_PRE_SCROOL_SETA,
    COR_BOTAO_SCROOL,
    COR_CAMINHO,
    COR_JANELA_CAMINHO,
    COR_SETA_CAMINHO,
    COR_PRE_CAMINHO_SETA,
    COR_JANELA_MENSAGEM,
    COR_MENSAGEM_GERAL;

/*-----------------------------------------------------------------*\
 |            Inicializa Modo Grafico                              |
\*-----------------------------------------------------------------*/
  void InicializaModoGrafico(void)
  {
    int
      mode,                            /* numero do tipo de inic.  */
      gmode,                           /* modo de inicializacao.   */
      errorcode,                       /* codigo do erro de inic.  */
      gdriver = DETECT;                /* Requisita auto-deteccao. */
 
    initgraph(&gdriver, &gmode,"");
    errorcode = graphresult();
    if (errorcode != grOk)
    {
      clrscr();
      printf("\n\n\n   Erro gr fico: %s\n", grapherrormsg(errorcode));
      exit(1);                    /* Erro: drive p/ inic. nao encontrado. */
    }
    mode = getgraphmode();        /* Seleciona padrao de Video.      */
    MIN_COD_X = 0;                /* Minimo valor na horizontal.     */
    MIN_COD_Y = 0;                /* Minimo valor na vertical.       */
    MAX_COD_X = getmaxx();        /* Maximo valor na horizontal.     */
    MAX_COD_Y = getmaxy();        /* Maximo valor na Vertical.       */
    InicializaCores( mode);
  }
 
/*-----------------------------------------------------------------*\
 |            Inicializa Cores                                     |
\*-----------------------------------------------------------------*/
  void InicializaCores( int Opcao)
  {
    switch ( Opcao)               /* Opcao: padrao de Video. */
    {
      case 4 :
      {                 /*  Padrao CGA */
        ASPECT = 0.48;
        COR_CURSOR_GERAL     = WHITE;
 
        COR_JANELA_EXEBICAO  = WHITE;
        COR_VIA              = WHITE;
        COR_RIO              = WHITE;
        COR_REFERENCIA       = WHITE;
 
        COR_JANELA_VISTA     = WHITE;
        COR_GRADE            = WHITE;
        COR_MENSAGEM_VISTA   = WHITE;
        COR_BOTAO_VISTA      = WHITE;
        COR_MENSAGEM_BOTAO   = WHITE;
        COR_CURSOR_GRADE     = WHITE;
        COR_MARCA_GRADE      = WHITE;
        COR_QUADRICULA_ATIVA = WHITE;
        COR_PRE_QUAD_ATIVA   = WHITE;
        COR_ICONE_NORTE      = WHITE;
        COR_SETA_GRADE       = WHITE;
        COR_PRE_GRADE_SETA   = WHITE;
 
        COR_JANELA_MOLDURA   = WHITE;
        COR_JANELA_MENU      = WHITE;
        COR_PRE_TITULO       = WHITE;
        COR_MENSAGEM_TITULO  = BLACK;
        COR_MENSAGEM_MENU    = WHITE;
 
        COR_BARRA_SCROOL     = WHITE;
        COR_QUADRADO_SCROOL  = WHITE;
        COR_PRE_SCROOL_QUADRA= WHITE;
        COR_SETA_SCROOL      = WHITE;
        COR_PRE_SCROOL_SETA  = WHITE;
        COR_BOTAO_SCROOL     = WHITE;
 
        COR_CAMINHO          = WHITE;
        COR_JANELA_CAMINHO   = WHITE;
        COR_SETA_CAMINHO     = WHITE;
        COR_PRE_CAMINHO_SETA = WHITE;
 
        COR_JANELA_MENSAGEM  = WHITE;
        COR_MENSAGEM_GERAL   = WHITE;
      }
      break;
/*    case  :
      {                      Padrao EGA
      }
      break;
      case  :
      {                      Padrao Hercules
      }
      break;
*/    case 2 :
      {                   /* Padrao VGA  */
        ASPECT = 1;
        COR_CURSOR_GERAL     = WHITE;
 
        COR_JANELA_EXEBICAO  = WHITE;
        COR_VIA              = BROWN;
        COR_RIO              = BLUE;
        COR_REFERENCIA       = RED;
 
        COR_JANELA_VISTA     = WHITE;
        COR_GRADE            = GREEN;
        COR_MENSAGEM_VISTA   = CYAN;
        COR_BOTAO_VISTA      = WHITE;
        COR_MENSAGEM_BOTAO   = CYAN;
        COR_CURSOR_GRADE     = YELLOW;
        COR_MARCA_GRADE      = LIGHTRED;
        COR_QUADRICULA_ATIVA = WHITE;
        COR_PRE_QUAD_ATIVA   = WHITE;
        COR_ICONE_NORTE      = LIGHTMAGENTA;
        COR_SETA_GRADE       = RED;
        COR_PRE_GRADE_SETA   = LIGHTRED;
 
        COR_JANELA_MOLDURA   = WHITE;
        COR_JANELA_MENU      = WHITE;
        COR_PRE_TITULO       = DARKGRAY;
        COR_MENSAGEM_TITULO  = BLACK;
        COR_MENSAGEM_MENU    = RED;
 
        COR_BARRA_SCROOL     = CYAN;
        COR_QUADRADO_SCROOL  = DARKGRAY;
        COR_PRE_SCROOL_QUADRA= LIGHTGRAY;
        COR_SETA_SCROOL      = GREEN;
        COR_PRE_SCROOL_SETA  = LIGHTGREEN;
        COR_BOTAO_SCROOL     = LIGHTCYAN;
 
        COR_CAMINHO          = RED;
        COR_JANELA_CAMINHO   = WHITE;
        COR_SETA_CAMINHO     = RED;
        COR_PRE_CAMINHO_SETA = LIGHTRED;
 
        COR_JANELA_MENSAGEM  = WHITE;
        COR_MENSAGEM_GERAL   = LIGHTRED;
      }
      break;
    }
  }
 
