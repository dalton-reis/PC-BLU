/*-----------------------------------------------------------------*\
 |                      Arquivos de Inclusao                       |
\*-----------------------------------------------------------------*/
  #include <graphics.h>
  #include <stdlib.h>
  #include <conio.h>
  #include <stdio.h>
  #include <io.h>

/*-----------------------------------------------------------------*\
 |                      Variaveis Globais                          |
\*-----------------------------------------------------------------*/
  const
    SETA_OFF         = 0,    /* Janela sem bot†o de seta.                */
    SETA_CIM         = 90,   /* Janela c/ seta p/ cima.                  */
    SETA_ESQ         = 180,  /* Janela c/ seta p/ esquerda.              */
    SETA_BAI         = 270,  /* Janela c/ seta p/ baixo.                 */
    SETA_DIR         = 360,  /* Janela c/ seta p/ direita.               */
    CLIP_ON          = 1,    /* Ativa o Clipping na Janela de exibi‡†o.  */
    CLIP_OFF         = 0,    /* Desativa o Clipping na Janela de vis†o.  */
    APAGA_JANELA     = 1,    /* Apaga a janela de exibi‡†o.              */
    NAO_APAGA_JANELA = 0;    /* N†o apaga Janela de exibi‡†o.            */

  void
    *CURSOR_GERAL,             /* Identificador Cursor Geral.            */
    *CURSOR_SCROOL,            /* Identificador Cursor Scrool.           */
    *CURSOR_GRADE,             /* Identificador Cursor Grade.            */
    *CURSOR_CAMINHO,           /* Identificador Cursor Caminho.          */
    *MARCA_GRADE;              /* Identificador Marca Grade.             */

       /* Estrutura de fila - Quadriculas */
    struct TipoQuadricula
      {
	int NumeroQuadricula;             /* Numero da Quadricula.       */
	struct TipoQuadricula
	  *ProximaQuadricula;             /* Aponta proxima Quadricula.  */
      } Quadricula;
    struct TipoQuadricula
      *AnteriorQuadricula = NULL,         /* Aponta Anterior Quadiucula. */
      *AtualQuadricula    = NULL,         /* Aponta atual Quadiucula.    */
      *EspacoQuadricula   = NULL,         /* Aponta espaco alocado.      */
      *PrimeiraQuadricula = NULL;         /* Aponta primeira Quadricula. */

      /* Estrutura de fila - Segmentos. */
    struct TipoSegmento
      {
	float
	  XInicial,                       /* X inicial do segmento.      */
	  YInicial,                       /* Y inicial do segmento.      */
	  XFinal,                         /* X final do segmento.        */
	  YFinal;                         /* Y final do segmento.        */
	  struct TipoSegmento
	    *ProximoSegmento;             /* Aponta proximo segmento.    */
      }Segmento;
    struct TipoSegmento
      *AtualSeg      = NULL,              /* Aponta atual segmento.      */
      *EspacoSeg     = NULL;              /* Aponta espaco Alocado.      */

      /* Estrutura de fila-multiniveis - Rota. */
    struct TipoRota
      {
	unsigned int
	  SetorInicial,                   /* Setor inicial da rota.      */
	  CruzaInicial,                   /* Cruzameto inicial da rota.  */
	  SetorFinal,                     /* Setor final da rota.        */
	  CruzaFinal,                     /* Cruzamneto final da rota.   */
	  Distancia,                      /* Distancia da rota.          */
	  CotaEnchente;                   /* Cota enchente da rota.      */
	char
	  *Rua,                           /* Nome da rua da rota.        */
	  *Bairro;                        /* Nome do bairro da rota.     */
	struct TipoSegmento
	  *PrimeiroSegmento;              /* Aponta primeiro segmento.   */
	struct TipoRota
	  *AnteriorRota,                  /* Aponta anterior rota.       */
	  *ProximaRota;                   /* Aponta proxima rota.        */
      } Rota;
    struct TipoRota
      *PrimeiraRota  = NULL,              /* Aponta primeira rota.       */
      *AtualRota     = NULL,              /* Aponta atual rota.          */
      *EspacoRota    = NULL;              /* Aponta espaco alocado.      */

  float
    SELECAO_X_ESQUERDO,        /* Coluna esquerda da janela de selecao.  */
    SELECAO_X_DIREITO,         /* Coluna direita da janela de selecao.   */
    SELECAO_Y_SUPERIOR,        /* Linha superior da janela de selecao.   */
    SELECAO_Y_INFERIOR,        /* Linha inferior da janela de selecao.   */
    EXIBICAO_X_ESQUERDO,       /* Coluna esquerda da janela de exibicao. */
    EXIBICAO_X_DIREITO,        /* Coluna direita da janela de exibicao.  */
    EXIBICAO_Y_SUPERIOR,       /* Linha superior da janela de exibicao.  */
    EXIBICAO_Y_INFERIOR;       /* Linha inferior da janela de exibicao.  */

  int
    QUADRICULA     = 232,      /* Quadricula Inicial.                    */
    QUANTIDADE_QUADRICULA = 0, /* Quantidade de Quadriculas da Lista.    */

    MIN_COD_X,                 /* Minima Coordenada de X.                */
    MIN_COD_Y,                 /* Minima Coordenada de Y.                */
    MAX_COD_X,                 /* Maxima Coordenada de X.                */
    MAX_COD_Y,                 /* Maxima Coordenada de Y.                */


    INC_CURSOR     = 10,       /* Passo incremento Cursor.               */
    TAMANHO_CURSOR = 1,        /* Tamanho do Cursor Ativo.               */
    POS_X_CURSOR,              /* Posi‡†o X do cursor na Tela.           */
    POS_Y_CURSOR,              /* Posi‡†o Y do cursor na Tela.           */

    PASSO_SCROOL   = 3,        /* Passo de incremento do Scrool.         */
    SCROOL_X_VERTICAL,         /* Coordenada X do Scrool Vertical.       */
    SCROOL_Y_VERTICAL,         /* Coordenada Y do Scrool Vertical.       */
    SCROOL_X_HORIZONTAL,       /* Coordenada X do Scrool Horizontal.     */
    SCROOL_Y_HORIZONTAL,       /* Coordenada Y do Scrool Horizontal.     */

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
    COR_PRE_SCROOL,
    COR_PRE_SCROOL_SETA,
    COR_QUADRADO_SCROOL,
    COR_PRE_SCROOL_QUADRA,
    COR_SETA_SCROOL,
    COR_PRE_SCROOL_SETA,
    COR_BOTAO_SCROOL,
    COR_CAMINHO,
    COR_CURSOR_CAMINHO,
    COR_PRE_CURSOR_CAMINHO,
    COR_JANELA_CAMINHO,
    COR_SETA_CAMINHO,
    COR_PRE_CAMINHO_SETA,
    COR_JANELA_MENSAGEM,
    COR_MENSAGEM_GERAL;

  float
    LAR_MAR,                   /* Num. de pixels da margem de Largura.    */
    LAR_INT,                   /* Num. de pixels do Intervalo na Largura. */
    LAR_DISPO,                 /* Largura Disponivel p/ desenho da Grade. */
    LAR_QT_COL = 15,           /* Quant. de Colunas na Largura da grade.  */
    ALT_DISPO,                 /* Altura Disponivel p/ desenho da Grade.  */
    COD_BASE_X,                /* Coordenada Base ponto X inicial Grade.  */
    COD_BASE_Y,                /* Coordenada Base ponto Y inicial Grade.  */
    ASPECT;                    /* Relacao de Aspect.                      */

/*-----------------------------------------------------------------*\
 |            Prototipacao das Funcoes                             |
\*-----------------------------------------------------------------*/
  void InicializaModoGrafico(void);
  void InicializaCores( int Opcao);
  void DesenhaCursorGeral(void);
  void DesenhaCursorScrool(void);
  void DesenhaCursorCaminho(void);
  void Interface(void);
  void JanelaMoldura(void);
  void JanelaMensagem(void);
  void DesenhaJanelaMensagem(void);
  void Menus(void);
  void DesenhaJanelaMenu(void);
  void EscreveTextoMenu(void);
  void JanelaExibicao(void);
  void DesenhaJanelaExibicao(void);
  void BotaoCaminho(void);
  void DesenhaBotoesCaminho(void);
  void JanelaVistaGeral(void);
  void DesenhaSetas(float PerXSup,float PerYSup,
		    float PerXInf,float PerYInf,int Opcao);
  void EscreveTextoVistaGeral(void);
  void ConstroiGradeMapa(void);
  void IntLargura(float LarMax,float AltQtCol,float AltMax);
  void RealcaQuadriculasAtivas(void);
  void DesenhaNorte(void);
  void DesenhaCursorGrade(void);
  void DesenhaMarcaGrade(void);
  void ExibeEnibeCursorGrade(int NumeroQuadri);
  void ExibeEnibeCursorCaminho(void);
  void JanelaAreaBotoes(void);
  void EscreveTextoBotoes(void);
  void DesenhaBarraScrool(void);
  void RotaCaminho(void);
  int LeRota(void);
  void MontaRota(void);
  void Erro (char *Mensagem, int Estado);
  struct TipoSegmento *AlocaSegmento(void);
  void CadastraSegmentos(FILE *ArqLog, int ArqInicioSementos,int ArqQuantidadeSeg);
  void IdentificaFundoRota(void);
  void ErroSetorCruzamentoNaoEncontrado (void);
  int PesquisaBinaria(FILE *ArqLog,int Setor, int Cruzamento,
		      int Inicio, int Final, int TamRegistro);
  int PesqBinTrecho(FILE *ArqLog,int SetInicial, int CruzaInicial,
		   int SetFinal, int CruzaFinal,
		   int Inicio, int Final, int TamRegistro);
  void LiberaQuadriculasMarcadas(void);
  void RepresentaQuadriculasMarcadas(void);
  void Caminho(void);
  void PontosReferencias(void);
  void ImagemFundo(void);
  void EstabeleceCoordenadasJanelaExibicao(void);
  void EstabeleceCoordenadasJanelaSelecao(void);
  void ExibeRota(void);
  void PlanoVias(void);
  void PlanoRios(void);
  void PlanoReferencias(void);
  void HelpOnLine(void);
  void MostraMensagem(char *Mensagem,int Opcao);
  void CentroQuadricula(int NumeroQuadri,
			int *PosXCurGrade, int *PosYCurGrade);
  void DesenhaJanela(float PerXSup,float PerYSup,
		     float PerXInf,float PerYInf,int Opcao);
  void SelecionaJanela(float XEsq,float YSup,float XDir,float YInf,
		       int Clip,int Apaga);
  ValorRelativoTela(char XouY,float Percentual,float Acrescimo);
  void GerenciaTecladoMouse(void);
  void LiberaMemoria(void);
  void LiberaRota(void);
  void PressionouEnter(void);
  void JanelaCorrente(char *NomeJanela);
  void MarcaDesmacarQuadricula(void);
  void CadastraQuadriculas(void);
  int  ContemJanela( float PerXSup, float PerYSup,
                    float PerXInf, float PerYInf);
  void TeclaEspecial(void);

/*-----------------------------------------------------------------*\
 |            Modulo Principal   -   PC-Blumenau                   |
\*-----------------------------------------------------------------*/
  void main(void)
  {
    InicializaModoGrafico();
    Interface();
    RotaCaminho();
    Caminho();
    PontosReferencias();
    ImagemFundo();
/*    ImagemDigitalizada();  */
    GerenciaTecladoMouse();
  }

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
	COR_CURSOR_GERAL       = WHITE;

	COR_JANELA_EXEBICAO    = WHITE;
	COR_VIA                = WHITE;
	COR_RIO                = WHITE;
	COR_REFERENCIA         = WHITE;

	COR_JANELA_VISTA       = WHITE;
	COR_GRADE              = WHITE;
	COR_MENSAGEM_VISTA     = WHITE;
	COR_BOTAO_VISTA        = WHITE;
	COR_MENSAGEM_BOTAO     = WHITE;
	COR_CURSOR_GRADE       = WHITE;
	COR_MARCA_GRADE        = WHITE;
	COR_QUADRICULA_ATIVA   = WHITE;
	COR_PRE_QUAD_ATIVA     = WHITE;
	COR_ICONE_NORTE        = WHITE;
	COR_SETA_GRADE         = WHITE;
	COR_PRE_GRADE_SETA     = WHITE;

	COR_JANELA_MOLDURA     = WHITE;
	COR_JANELA_MENU        = WHITE;
	COR_PRE_TITULO         = WHITE;
	COR_MENSAGEM_TITULO    = BLACK;
	COR_MENSAGEM_MENU      = WHITE;

	COR_BARRA_SCROOL       = WHITE;
	COR_PRE_SCROOL_SETA    = WHITE;
	COR_QUADRADO_SCROOL    = WHITE;
	COR_PRE_SCROOL_QUADRA  = WHITE;
	COR_SETA_SCROOL        = WHITE;
	COR_BOTAO_SCROOL       = WHITE;

	COR_CAMINHO            = WHITE;
	COR_CURSOR_CAMINHO     = WHITE;
	COR_PRE_CURSOR_CAMINHO = WHITE;
	COR_JANELA_CAMINHO     = WHITE;
	COR_SETA_CAMINHO       = WHITE;
	COR_PRE_CAMINHO_SETA   = WHITE;

	COR_JANELA_MENSAGEM    = WHITE;
	COR_MENSAGEM_GERAL     = WHITE;
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
	COR_CURSOR_GERAL       = WHITE;

	COR_JANELA_EXEBICAO    = WHITE;
	COR_VIA                = BROWN;
	COR_RIO                = BLUE;
	COR_REFERENCIA         = RED;

	COR_JANELA_VISTA       = WHITE;
	COR_GRADE              = GREEN;
	COR_MENSAGEM_VISTA     = CYAN;
	COR_BOTAO_VISTA        = WHITE;
	COR_MENSAGEM_BOTAO     = CYAN;
	COR_CURSOR_GRADE       = YELLOW;
	COR_MARCA_GRADE        = LIGHTRED;
	COR_QUADRICULA_ATIVA   = WHITE;
	COR_PRE_QUAD_ATIVA     = WHITE;
	COR_ICONE_NORTE        = LIGHTMAGENTA;
	COR_SETA_GRADE         = RED;
	COR_PRE_GRADE_SETA     = LIGHTRED;

	COR_JANELA_MOLDURA     = WHITE;
	COR_JANELA_MENU        = WHITE;
	COR_PRE_TITULO         = DARKGRAY;
	COR_MENSAGEM_TITULO    = BLACK;
	COR_MENSAGEM_MENU      = RED;

	COR_BARRA_SCROOL       = CYAN;
	COR_PRE_SCROOL         = LIGHTGRAY;
	COR_QUADRADO_SCROOL    = DARKGRAY;
	COR_PRE_SCROOL_QUADRA  = LIGHTGRAY;
	COR_SETA_SCROOL        = GREEN;
	COR_PRE_SCROOL_SETA    = LIGHTGREEN;
	COR_BOTAO_SCROOL       = LIGHTCYAN;

	COR_CAMINHO            = YELLOW;
	COR_CURSOR_CAMINHO     = MAGENTA;
	COR_PRE_CURSOR_CAMINHO = MAGENTA;
	COR_JANELA_CAMINHO     = WHITE;
	COR_SETA_CAMINHO       = RED;
	COR_PRE_CAMINHO_SETA   = LIGHTRED;

	COR_JANELA_MENSAGEM    = WHITE;
	COR_MENSAGEM_GERAL     = LIGHTRED;
      }
      break;
    }
  }

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
    PosXEsq = 0;
    PosYSup = 0;
    PosXDir = ValorRelativoTela('X',2.3,0);
    PosYInf = ValorRelativoTela('Y',2.9,0);
    bar(PosXEsq,PosYSup,PosXDir,PosYInf);
    SizeCursor = imagesize(PosXEsq,PosYSup,PosXDir,PosYInf);
    CURSOR_SCROOL = malloc(SizeCursor);
    getimage(PosXEsq,PosYSup,PosXDir,PosYInf,CURSOR_SCROOL);
    putimage(PosXEsq,PosYSup,CURSOR_SCROOL,XOR_PUT);
  }

/*-----------------------------------------------------------------*\
 |            Desenha Cursor Caminho - esfera.                     |
\*-----------------------------------------------------------------*/
  void DesenhaCursorCaminho(void)
  {
    int
      PosXDir,                    /* Posicao X Direito  area desenho */
      PosYSup,                    /* Posicao Y Superior area desenho */
      PosXEsq,                    /* Posicao X Esquerdo area desenho */
      PosYInf;                    /* Posicao Y Inferior area desenho */
    unsigned int SizeCursor;      /* Espaco memoria Cursor.          */

    setcolor(COR_CURSOR_CAMINHO);
    setfillstyle(SOLID_FILL,COR_PRE_CURSOR_CAMINHO);
    PosXEsq = 0;
    PosYSup = 0;
    PosXDir = ValorRelativoTela('X',2.3,0);
    PosYInf = ValorRelativoTela('Y',2.9,0);
    fillellipse((PosXDir-PosXEsq)/2,(PosYInf-PosYSup)/2, 3, 3*ASPECT);
    SizeCursor = imagesize(PosXEsq,PosYSup,PosXDir,PosYInf);
    CURSOR_CAMINHO = malloc(SizeCursor);
    getimage(PosXEsq,PosYSup,PosXDir,PosYInf,CURSOR_CAMINHO);
    putimage(PosXEsq,PosYSup,CURSOR_CAMINHO,XOR_PUT);
  }

/*-----------------------------------------------------------------*\
 |            Interface                                            |
\*-----------------------------------------------------------------*/
  void Interface(void)
  {
    DesenhaCursorGeral();
    DesenhaCursorScrool();
    DesenhaCursorCaminho();
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
      NaoAguarde = 0,             /* Flag nao parada mensagem. */
      Aguarde    = 1;             /* Flag parada na mensagem. */
    int
      PosXCurGrade,               /* Posicao X do Cursor na Grade.  */
      PosYCurGrade,               /* Posicao Y do Cursor na Grade.  */
      NumeroQuadri;               /* Numero da Quadricula ativa.    */
    FILE
      *ArqLog;                    /* Variavel do Arquivo.           */
    char
      *Mensagem,
      *ArquivoQuadricula = "QUADRI.DIG";

    if((ArqLog = fopen(ArquivoQuadricula,"r")) == NULL)
    {
      setcolor(COR_MENSAGEM_GERAL);
      strcpy(Mensagem,"Arquivo nao encontrado -> ");
      strcat(Mensagem, ArquivoQuadricula);
      MostraMensagem(Mensagem,Aguarde);
      MostraMensagem("Aguarde: inicializando ambiente.",NaoAguarde);
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
	  strcpy(Mensagem,"Arquivo nao encontrado -> ");
	  strcat(Mensagem, ArquivoQuadricula);
	  MostraMensagem(Mensagem,Aguarde);
	  LiberaMemoria();
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
 |            Exibe ou Enibe o Cursor do Caminho                   |
\*-----------------------------------------------------------------*/
  void ExibeEnibeCursorCaminho(void)
  {
    const NaoAguarde = 0;
    float
      DeltaXSelecao,            /* Delta X janela selecao.       */
      DeltaYSelecao,            /* Delta Y janela selecao.       */
      DeltaXExibicao,           /* Delta X janela exibicao.      */
      DeltaYExibicao;           /* Delta Y janela exibicao.      */
    int
      CodX,                   /* Coordenada do X Esquerdo. */
      CodY;                   /* Coordenada do Y Superior. */

    SelecionaJanela((ValorRelativoTela('X', 4.5, 0.45)),
		    (ValorRelativoTela('Y',14.7, 0.59)),
		    (ValorRelativoTela('X',64.5,-0.45)),
		    (ValorRelativoTela('Y',88.2,-0.59)),
		     CLIP_ON, NAO_APAGA_JANELA);
    EXIBICAO_X_ESQUERDO = (long) ValorRelativoTela('X', 4.5, 0.45);
    EXIBICAO_Y_SUPERIOR = (long) ValorRelativoTela('Y',14.7, 0.59);
    EXIBICAO_X_DIREITO  = (long) ValorRelativoTela('X',64.5,-0.45);
    EXIBICAO_Y_INFERIOR = (long) ValorRelativoTela('Y',88.2,-0.59);
    DeltaXSelecao  = SELECAO_X_DIREITO   - SELECAO_X_ESQUERDO;
    DeltaYSelecao  = SELECAO_Y_SUPERIOR  - SELECAO_Y_INFERIOR;
    DeltaXExibicao = EXIBICAO_X_DIREITO  - EXIBICAO_X_ESQUERDO;
    DeltaYExibicao = EXIBICAO_Y_INFERIOR - EXIBICAO_Y_SUPERIOR;
    if(AtualRota->ProximaRota != NULL)
    {
      CodX = (int) ((AtualRota->PrimeiroSegmento->XInicial - SELECAO_X_ESQUERDO) *
	     (DeltaXExibicao / DeltaXSelecao));
      CodY = (int) ((SELECAO_Y_SUPERIOR - AtualRota->PrimeiroSegmento->YInicial) *
				  (DeltaYExibicao / DeltaYSelecao));
    }
    else
    {
      CodX = (int) ((AtualRota->PrimeiroSegmento->XFinal- SELECAO_X_ESQUERDO) *
	     (DeltaXExibicao / DeltaXSelecao));
      CodY = (int) ((SELECAO_Y_SUPERIOR - AtualRota->PrimeiroSegmento->YFinal) *
				  (DeltaYExibicao / DeltaYSelecao));
    }
    putimage(CodX-3,CodY-3*ASPECT,CURSOR_CAMINHO,XOR_PUT);
    MostraMensagem(AtualRota->Rua,NaoAguarde);
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
      Preenche    = 2,         /* Janela Preenchida.     */
      NaoPreenche = 1;         /* Janela Nao Preenchida. */

    setcolor(COR_BARRA_SCROOL);
    setfillstyle(CLOSE_DOT_FILL,COR_PRE_SCROOL);
    DesenhaJanela( 2.3,14.7, 4.5,88.2,Preenche);    /* Coluna Vertical.   */
    DesenhaJanela( 4.5,88.2,64.5,91.2,Preenche);    /* Coluna Horizontal. */
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
 |            Rota do Caminho                                      |
\*-----------------------------------------------------------------*/
  void RotaCaminho(void)
  {
      if(LeRota())
      {
	IdentificaFundoRota();
	MontaRota();
      }
  }

/*-----------------------------------------------------------------*\
 |            Le a Rota do Arquivo em Disco                        |
\*-----------------------------------------------------------------*/
  int LeRota(void)
  {
    const
      Aguarde = 1;                      /* Flag parada na mensagem. */

    int  i,
      Indice,
      CodXEsq,                   /* Coordenada do X Esquerdo. */
      CodYSup,                   /* Coordenada do Y Superior. */
      ArqSetorInicial,                  /* Setor Inicial da Rota.       */
      ArqCruzaInicial,                  /* Cruzamento Inicial da Rota.  */
      ArqSetorFinal,                    /* Setor Final da Rota.         */
      ArqCruzaFinal,                    /* Cruzamento Final da Rota.    */
      ArqDistancia,
      ArqCota;
    char
      *ArqRua,
      *ArqBairro,
      *ArqLixo;
    FILE
      *ArqLog;                          /* Variavel do Arquivo da Rota. */
    char
      *Mensagem,
      *ArquivoRota = "CRUZAM.RLT";     /* Arquivo c/ Rota do CRUZAM.    */

    if((ArqLog = fopen(ArquivoRota,"r")) == NULL)
    {
      setcolor(COR_MENSAGEM_GERAL);
      strcpy(Mensagem,"Arquivo nao encontrado -> ");
      strcat(Mensagem, ArquivoRota);
      MostraMensagem(Mensagem,Aguarde);
      MarcaDesmacarQuadricula();
      CentroQuadricula(QUADRICULA,&CodXEsq,&CodYSup);
      putimage(CodXEsq,CodYSup,MARCA_GRADE,XOR_PUT);
      return(0);         /* Arquivo CRUZAM.RLT nao encontrado. */
    }
    else
    {
      LiberaQuadriculasMarcadas();
      for (Indice=1; Indice<7; Indice++)
	fscanf( ArqLog,"%s ", ArqLixo);
      fscanf( ArqLog,"%s \n", ArqLixo);
      for (Indice=1; Indice<8; Indice++)
      fscanf( ArqLog,"%s",ArqLixo);
      fscanf( ArqLog,"%s \n", ArqLixo);
      while( !feof( ArqLog))
      {
	if((EspacoRota = malloc(sizeof(struct TipoRota))) == NULL)
	{
	  setcolor(COR_MENSAGEM_GERAL);
	  MostraMensagem("Memoria insuficiente, estrutura ROTA ",Aguarde);
	  LiberaMemoria();
	  closegraph();
	  exit(1);                /* Erro: Arquivo incorreto. */
	}
	else
	{
	  fscanf(ArqLog,"%d %d",&ArqSetorInicial,&ArqCruzaInicial);
	  fscanf(ArqLog,"%d %d",&ArqSetorFinal,  &ArqCruzaFinal);
	  fscanf(ArqLog,"%d %d"  ,&ArqDistancia,   &ArqCota);
	  fgets(ArqRua, 33, ArqLog);
	  for (i=0; i<33; i++)
	    EspacoRota->Rua[i]        = ArqRua[i];
	  fgets(ArqBairro, 20, ArqLog);
	  for (i=0; i<20; i++)
	    EspacoRota->Bairro[i]        = ArqBairro[i];
	  fscanf(ArqLog, "\n");
	  if(PrimeiraRota == NULL)
	  {
	    PrimeiraRota = EspacoRota;
	    EspacoRota->AnteriorRota = NULL;
	  }
	  else
	  {
	    EspacoRota->AnteriorRota = AtualRota;
	    AtualRota->ProximaRota = EspacoRota;
	  }
	  AtualRota = EspacoRota;
	  AtualRota->SetorInicial = ArqSetorInicial;
	  AtualRota->CruzaInicial = ArqCruzaInicial;
	  AtualRota->SetorFinal   = ArqSetorFinal;
	  AtualRota->CruzaFinal   = ArqCruzaFinal;
	  AtualRota->Distancia    = ArqDistancia;
	  AtualRota->CotaEnchente = ArqCota;
	  EspacoRota->ProximaRota = NULL;
	  AtualRota->PrimeiroSegmento = NULL;
	}
      }
      fclose(ArqLog);
      return(1);
    }
  }

/*-----------------------------------------------------------------*\
 |            Monta a rota do caminho c/ segmentos.                |
\*-----------------------------------------------------------------*/
  void MontaRota(void)
  {

   typedef struct
    {
      int
	SetorIni,
	CruzaIni,
	SetorFin,
	CruzaFin,
	InicioSeg,
	QuantiSeg;
    } Trecho;

    Trecho RegTrecho;

    const
      NumReg = 1389,                    /* nro reg arq CAMINHO.SEG  */
      Aguarde = 1;                      /* Aguarda na Mensagem.       */
    char
      *temp,
      *Mensagem,
      *ArqArco = "CAMINHO.SEG",
      *NomeArqCod = "CAMINHO2.COD";
    int
      Posicao,
      TamRegistro,
      SetorInicial,
      CruzaInicial,
      SetorFinal,
      CruzaFinal,
      SegInicial,                       /* Numero de inicio Segmentos.  */
      QtdSeg;                           /* Quantidade de segmentos.     */
    FILE
      *ArqLog,
      *ArqCod;                          /* Variavel do Arquivo.         */

  if((ArqCod = fopen(NomeArqCod,"rb")) == NULL)
    {
      strcpy(Mensagem,"Arquivo nao encontrado -> ");
      strcat(Mensagem, NomeArqCod);
      Erro(Mensagem, Aguarde);
    }
    if((ArqLog = fopen(ArqArco,"rb")) == NULL)
    {
      strcpy(Mensagem,"Arquivo nao encontrado -> ");
      strcat(Mensagem, ArqArco);
      Erro (Mensagem,Aguarde);
    }

    AtualRota = PrimeiraRota;
    while(AtualRota != NULL)
    {
     if ((AtualRota->SetorInicial > AtualRota->SetorFinal) ||
	 ((AtualRota->SetorInicial == AtualRota->SetorFinal) &&
	  (AtualRota->CruzaInicial >  AtualRota->CruzaFinal)) )
       {
	 SetorInicial = AtualRota->SetorFinal;
	 CruzaInicial = AtualRota->CruzaFinal;
	 SetorFinal   = AtualRota->SetorInicial;
	 CruzaFinal   = AtualRota->CruzaInicial;
       }
       else
       {
	 SetorInicial = AtualRota->SetorInicial;
	 CruzaInicial = AtualRota->CruzaInicial;
	 SetorFinal   = AtualRota->SetorFinal;
	 CruzaFinal   = AtualRota->CruzaFinal;
       }

      TamRegistro  = sizeof(Trecho);
      Posicao = PesqBinTrecho(ArqLog,SetorInicial,CruzaInicial,SetorFinal,
			    CruzaFinal, 0, NumReg-1, TamRegistro);
      if (Posicao >= 0)
       {
	  fseek(ArqLog, Posicao*TamRegistro,SEEK_SET);
	  fread(&RegTrecho,TamRegistro, 1, ArqLog);
	  SegInicial = RegTrecho.InicioSeg;
	  QtdSeg     = RegTrecho.QuantiSeg;
	  CadastraSegmentos(ArqCod, SegInicial, QtdSeg);
       }
       else
       {
	 strcpy(Mensagem, "S. ");
	 itoa(AtualRota->SetorInicial, temp, 10);
	 strcat(Mensagem,temp);
	 strcat(Mensagem, " C. ");
	 itoa(AtualRota->CruzaInicial, temp, 10);
	 strcat(Mensagem, temp);
	 strcat(Mensagem, " S. ");
	 itoa(AtualRota->SetorFinal, temp, 10);
	 strcat(Mensagem,temp);
	 strcat(Mensagem, " C. ");
	 itoa(AtualRota->CruzaFinal, temp, 10);
	 strcat(Mensagem, temp);
	 strcat(Mensagem, " NAO Cadast. !");
	 Erro (Mensagem,Aguarde);
       }
      EspacoRota = AtualRota;
      AtualRota = AtualRota->ProximaRota;
    }
    fclose(ArqCod);
    fclose(ArqLog);
  }


/*-----------------------------------------------------------------*\
 |  Efetua pesquisa binaria no arq de trechos - CAMINHO.SEG.       |
\*-----------------------------------------------------------------*/
  int PesqBinTrecho(FILE *ArqLog,int SetInicial, int CruzaInicial,
		   int SetFinal, int CruzaFinal,
		   int Inicio, int Final, int TamRegistro)
  {
   typedef struct
    {
      int
	SetorIni,
	CruzaIni,
	SetorFin,
	CruzaFin,
	InicioSeg,
	QuantiSeg;
    } Trecho;

    Trecho RegTrecho;

    int Media = (Inicio + Final) / 2;
    fseek(ArqLog, Media*TamRegistro,SEEK_SET);
    fread(&RegTrecho,TamRegistro, 1, ArqLog);

    if((SetInicial   == RegTrecho.SetorIni) &&
       (CruzaInicial == RegTrecho.CruzaIni) &&
       (SetFinal     == RegTrecho.SetorFin) &&
       (CruzaFinal   == RegTrecho.CruzaFin))
      {
	return(Media);
      }
    else
    {
      if(Inicio > Final) return(-1);
      if((SetInicial <  RegTrecho.SetorIni) ||  /* setor inic pesquisado e' */
					     /* menor que o encontrado */
	((SetInicial == RegTrecho.SetorIni)  &&
	 (CruzaInicial < RegTrecho.CruzaIni)) || /* cruz. inic pesquisado e' */
					      /* menor que o encontrado */
	((SetInicial   == RegTrecho.SetorIni)  &&
	 (CruzaInicial == RegTrecho.CruzaIni) &&
	 (SetFinal     <  RegTrecho.SetorFin))  || /* setor fin pesquisado e' */
						/* menor que o encontrado */
	((SetInicial   ==  RegTrecho.SetorIni)  &&
	 (CruzaInicial ==  RegTrecho.CruzaIni) &&
	 (SetFinal     ==  RegTrecho.SetorFin) &&
	 (CruzaFinal   <   RegTrecho.CruzaFin )) ) /* cruz. final pesquisado e' */
						   /* menor que o encontrado */

	 PesqBinTrecho(ArqLog, SetInicial, CruzaInicial,SetFinal,CruzaFinal,
		       Inicio, Media-1, TamRegistro);
      else
	 PesqBinTrecho(ArqLog, SetInicial, CruzaInicial,SetFinal,CruzaFinal,
		       Media+1,Final,TamRegistro);
    }
  }



  void Erro (char *Mensagem, int Estado)
  {
    setcolor(COR_MENSAGEM_GERAL);
    MostraMensagem (Mensagem, Estado);
    LiberaMemoria();
    closegraph();
    exit(1);
  }


/*-----------------------------------------------------------------*\
 |            Identifica o plano de fundo da rota.                 |
\*-----------------------------------------------------------------*/
  void CadastraSegmentos(FILE *ArqLog, int InicioSegmentos,int QuantidadeSeg)
  {
    char
      *Mensagem;
    int
      Indice;

  typedef struct
  {                               /* Indice de segmentos lidos.   */
    int ArqNumeroRegistro;                /* Numero do registro arquivo.  */
    float
      ArqXInicial,                      /* Valor de x inicial.          */
      ArqYInicial,                      /* Valor de y inicial.          */
      ArqXFinal,                        /* Valor de x final.            */
      ArqYFinal;                        /* Valor de y final.            */
  } Segmento;

    Segmento Seg;

    fseek(ArqLog, (InicioSegmentos -1)*sizeof(Segmento), SEEK_SET);

    EspacoSeg = AlocaSegmento();
    AtualRota->PrimeiroSegmento = EspacoSeg;
    fread(&Seg,sizeof(Segmento), 1, ArqLog);
    AtualSeg = EspacoSeg;
    EspacoSeg->XInicial = Seg.ArqXInicial;
    EspacoSeg->YInicial = Seg.ArqYInicial;
    EspacoSeg->XFinal   = Seg.ArqXFinal;
    EspacoSeg->YFinal   = Seg.ArqYFinal;
    for(Indice=1;Indice<QuantidadeSeg;Indice++)
    {
      fread(&Seg,sizeof(Segmento), 1, ArqLog);
      EspacoSeg = AlocaSegmento();
      AtualSeg->ProximoSegmento = EspacoSeg;
      AtualSeg = EspacoSeg;
      EspacoSeg->XInicial = Seg.ArqXInicial;
      EspacoSeg->YInicial = Seg.ArqYInicial;
      EspacoSeg->XFinal   = Seg.ArqXFinal;
      EspacoSeg->YFinal   = Seg.ArqYFinal;
    }
  }

  struct TipoSegmento *AlocaSegmento(void)
  {
    const
      Aguarde = 1;               /* Aguarda na Mensagem.       */

   struct TipoSegmento *ponteiro;

   if( (ponteiro = malloc(sizeof(struct TipoSegmento))) == NULL)
    {
      setcolor(COR_MENSAGEM_GERAL);
      MostraMensagem("Memoria insuficiente, estrutura SEGMENTO",Aguarde);
      LiberaMemoria();
      closegraph();
      exit(1);                /* Erro: Arquivo incorreto. */
    }
    ponteiro->ProximoSegmento = NULL;
    return(ponteiro);
  }


/*-----------------------------------------------------------------*\
 |            Identifica o plano de fundo da rota.                 |
\*-----------------------------------------------------------------*/
  void IdentificaFundoRota(void)
  {
    const
      Aguarde = 1;               /* Aguarda na Mensagem.       */

    typedef struct
      {
	int Setor, Cruzamento;
	float
	  XI, YI;
	int Quadricula;
      }EstrutSet;

    char
      *Mensagem,
      *ArqNodoQuadricula = "CAMINHO.SET";
    int
      TamRegistro,               /* Tamanho do reg. CAMINHO.SET.  */
      NaoAchouInicio,            /* Flag nao achou quadricula. */
      NaoAchouFim,               /* Flag nao achou quadricula. */
      ArqSetor,                  /* Setor do arquivo.          */
      ArqCruza,                  /* Cruzamento do arquivo.     */
      NumeroQuadricula,          /* Numero da Quadricula.      */
      CodXEsq,                   /* Coordenada do X Esquerdo.  */
      CodYSup;                   /* Coordenada do Y Superior.  */
 int   QtdRegistros = 1798;      /* Qtd reg. arquivo CAMINHO.SET. */

    float
      ArqPontoX,                 /* Ponto do X.                */
      ArqPontoY;                 /* Ponto do Y.                */
    FILE
      *ArqLog;                    /* Variavel do Arquivo de quadriculas. */

    AtualRota= PrimeiraRota;
    if((ArqLog = fopen(ArqNodoQuadricula,"rb")) == NULL)
    {
      strcpy(Mensagem,"Arquivo nao encontrado -> ");
      strcat(Mensagem, ArqNodoQuadricula);
      Erro(Mensagem,Aguarde);
    }

    while(AtualRota != NULL)
    {
      TamRegistro  = sizeof(EstrutSet);
      QUADRICULA = PesquisaBinaria(ArqLog,AtualRota->SetorInicial,
		   AtualRota->CruzaInicial,0,QtdRegistros-1,TamRegistro);
      if (QUADRICULA != 0)
	CadastraQuadriculas();
       else
	ErroSetorCruzamentoNaoEncontrado();

      EspacoRota = AtualRota;
      AtualRota = AtualRota->ProximaRota;
    }
    QUADRICULA = PesquisaBinaria(ArqLog,EspacoRota->SetorFinal,
		 EspacoRota->CruzaFinal,0,QtdRegistros-1,TamRegistro);
    if (QUADRICULA != 0)
      CadastraQuadriculas();
     else
      ErroSetorCruzamentoNaoEncontrado();

    fclose(ArqLog);
    RepresentaQuadriculasMarcadas();
 }

/*-----------------------------------------------------------------*\
 |            Erro Setor e Cruzamento nao encontrado.              |
\*-----------------------------------------------------------------*/
  void ErroSetorCruzamentoNaoEncontrado (void)
  {
    const Aguarde = 1;
    char *Mensagem, *temp;

    setcolor(COR_MENSAGEM_GERAL);
    strcpy(Mensagem, "Setor ");
    itoa(AtualRota->SetorInicial, temp, 10);
    strcat(Mensagem,temp);
    strcat(Mensagem, " Cruzamento ");
    itoa(AtualRota->CruzaInicial, temp, 10);
    strcat(Mensagem, temp);
    strcat(Mensagem, " NAO Cadastrado !");
    MostraMensagem(Mensagem,Aguarde);
    LiberaMemoria();
    closegraph();
    exit(1);                /* Erro: Arquivo incorreto. */
  }



/*-----------------------------------------------------------------*\
 |            Efetua pesquisa binaria - CAMINHO.SET.               |
\*-----------------------------------------------------------------*/
  int PesquisaBinaria(FILE *ArqLog,int Setor, int Cruzamento,
		      int Inicio, int Final, int TamRegistro)
  {
    typedef struct
      {
	int Setor, Cruzamento;
	float
	  XI, YI;
	int Quadricula;
      }EstrutSet;
    EstrutSet RegSet;

    int Media = (Inicio + Final) / 2;
    fseek(ArqLog, Media*TamRegistro,SEEK_SET);
    fread(&RegSet,TamRegistro, 1, ArqLog);
    if((Setor == RegSet.Setor) && (Cruzamento == RegSet.Cruzamento))
      return(RegSet.Quadricula);
    else
    {
      if(Inicio > Final) return(0);
      if((Setor < RegSet.Setor) ||
	((Setor == RegSet.Setor) && (Cruzamento < RegSet.Cruzamento)))
	  PesquisaBinaria(ArqLog,Setor,Cruzamento,Inicio,Media-1,TamRegistro);
      else
	  PesquisaBinaria(ArqLog,Setor,Cruzamento,Media+1,Final,TamRegistro);
    }
  }

/*-----------------------------------------------------------------*\
 |            Libera memoria - Lista Quadriculas marcadas.         |
\*-----------------------------------------------------------------*/
  void LiberaQuadriculasMarcadas(void)
  {
    int
      CodXEsq,                   /* Coordenada do X Esquerdo.  */
      CodYSup;                   /* Coordenada do Y Superior.  */
    AtualQuadricula = PrimeiraQuadricula;
    while(AtualQuadricula != NULL)
    {
      QUADRICULA = AtualQuadricula->NumeroQuadricula;
      CentroQuadricula(QUADRICULA,&CodXEsq,&CodYSup);
      putimage(CodXEsq,CodYSup,MARCA_GRADE,XOR_PUT);
      EspacoQuadricula = AtualQuadricula->ProximaQuadricula;
      free(AtualQuadricula);
      AtualQuadricula = EspacoQuadricula;
      QUANTIDADE_QUADRICULA -= 1;
    }
    PrimeiraQuadricula = AtualQuadricula = EspacoQuadricula = NULL;
  }

/*-----------------------------------------------------------------*\
 |            Representa Quadriculas marcadas.                     |
\*-----------------------------------------------------------------*/
  void RepresentaQuadriculasMarcadas(void)
  {
    int
      CodXEsq,                   /* Coordenada do X Esquerdo.  */
      CodYSup;                   /* Coordenada do Y Superior.  */
    AtualQuadricula = PrimeiraQuadricula;
    while(AtualQuadricula != NULL)
    {
      EspacoQuadricula = AtualQuadricula->ProximaQuadricula;
      QUADRICULA = AtualQuadricula->NumeroQuadricula;
      CentroQuadricula(QUADRICULA,&CodXEsq,&CodYSup);
      putimage(CodXEsq,CodYSup,MARCA_GRADE,XOR_PUT);
      AtualQuadricula = EspacoQuadricula;
    }
  }

/*-----------------------------------------------------------------*\
 |            Definicao dos Caminho                                |
\*-----------------------------------------------------------------*/
  void Caminho(void)
  {
  }

/*-----------------------------------------------------------------*\
 |            Pontos de Referencias                                |
\*-----------------------------------------------------------------*/
  void PontosReferencias(void)
  {
  }

/*-----------------------------------------------------------------*\
 |            Imagem de Fundo                                      |
\*-----------------------------------------------------------------*/
  void ImagemFundo(void)
  {
    EstabeleceCoordenadasJanelaExibicao();
    EstabeleceCoordenadasJanelaSelecao();
    PlanoVias();
    PlanoRios();
    PlanoReferencias();
    ExibeRota();
    SelecionaJanela(MIN_COD_X,MIN_COD_Y,MAX_COD_X,MAX_COD_Y,
		    CLIP_OFF,NAO_APAGA_JANELA);     /* Sel. todo janela. */
  }

/*-----------------------------------------------------------------*\
 |            Estabelece as Coordenadas da Janela Exibicao         |
\*-----------------------------------------------------------------*/
  void EstabeleceCoordenadasJanelaExibicao(void)
  {
    SelecionaJanela((ValorRelativoTela('X', 4.5, 0.45)),
		    (ValorRelativoTela('Y',14.7, 0.59)),
		    (ValorRelativoTela('X',64.5,-0.45)),
		    (ValorRelativoTela('Y',88.2,-0.59)),
		     CLIP_ON, APAGA_JANELA);
    EXIBICAO_X_ESQUERDO = (long) ValorRelativoTela('X', 4.5, 0.45);
    EXIBICAO_Y_SUPERIOR = (long) ValorRelativoTela('Y',14.7, 0.59);
    EXIBICAO_X_DIREITO  = (long) ValorRelativoTela('X',64.5,-0.45);
    EXIBICAO_Y_INFERIOR = (long) ValorRelativoTela('Y',88.2,-0.59);
  }

/*-----------------------------------------------------------------*\
 |            Estabelece as Coordenadas da Janela Selecao          |
\*-----------------------------------------------------------------*/
  void EstabeleceCoordenadasJanelaSelecao(void)
  {
    float
      DiferencaX,                /* Diferenca X margem.        */
      DiferencaY,                /* Diferenca Y margem.        */
      Diferenca = 1,             /* Diferenca X e Y.           */
      LimiteDireito  = 18000,    /* Limite X direito.          */
      LimiteSuperior = 33000;    /* Limite Y superior.         */
    int
      LinhaGrade,                /* Numero da Linha na Grade.  */
      ColunaGrade;               /* Numero da Coluna na Grade. */
    SELECAO_X_ESQUERDO = 9999;
    SELECAO_X_DIREITO  = 0;
    SELECAO_Y_SUPERIOR = 0;
    SELECAO_Y_INFERIOR = 9999;
    AtualQuadricula = PrimeiraQuadricula;
    while(AtualQuadricula != NULL)
    {
      LinhaGrade  = (int) AtualQuadricula->NumeroQuadricula / 20;
      ColunaGrade = AtualQuadricula->NumeroQuadricula - (LinhaGrade * 20) - 1;
      if(LinhaGrade < SELECAO_Y_INFERIOR)
	SELECAO_Y_INFERIOR = LinhaGrade;
      if(LinhaGrade > SELECAO_Y_SUPERIOR)
	SELECAO_Y_SUPERIOR = LinhaGrade;
      if(ColunaGrade > SELECAO_X_DIREITO)
	SELECAO_X_DIREITO = ColunaGrade;
      if(ColunaGrade < SELECAO_X_ESQUERDO)
       SELECAO_X_ESQUERDO = ColunaGrade;
      AtualQuadricula = AtualQuadricula->ProximaQuadricula;
    }
    SELECAO_X_ESQUERDO = SELECAO_X_ESQUERDO * 1000;
    SELECAO_X_DIREITO  = (SELECAO_X_DIREITO  * 1000) + 1000;
    SELECAO_Y_SUPERIOR = (SELECAO_Y_SUPERIOR * 1000) + 1000;
    SELECAO_Y_INFERIOR = SELECAO_Y_INFERIOR * 1000;

    while(Diferenca)
    {
      Diferenca = 0;
      DiferencaX = SELECAO_X_DIREITO  - SELECAO_X_ESQUERDO;
      DiferencaY = SELECAO_Y_SUPERIOR - SELECAO_Y_INFERIOR;
      if(DiferencaX < DiferencaY)
      {
	if(SELECAO_X_DIREITO < LimiteDireito)
	  SELECAO_X_DIREITO += 1000;
	else
	  SELECAO_X_ESQUERDO -= 1000;
	Diferenca = 1;
      }
      if(DiferencaY < DiferencaX)
      {
	if(SELECAO_Y_SUPERIOR < LimiteSuperior)
	  SELECAO_Y_SUPERIOR += 1000;
	else
	  SELECAO_Y_INFERIOR -= 1000;
	Diferenca = 1;
      }
    }
  }

/*-----------------------------------------------------------------*\
 |            Exibe as quadriculas do caminho.                     |
\*-----------------------------------------------------------------*/
  void ExibeRota(void)
  {
    float
      DeltaXSelecao,            /* Delta X janela selecao.       */
      DeltaYSelecao,            /* Delta Y janela selecao.       */
      DeltaXExibicao,           /* Delta X janela exibicao.      */
      DeltaYExibicao;           /* Delta Y janela exibicao.      */
    int
      PontoXInicial,            /* ponto mapeado X inicial.      */
      PontoYInicial,            /* ponto mapeado Y inicial.      */
      PontoXFinal,              /* ponto mapeado X final.        */
      PontoYFinal;              /* ponto mapeado Y final.        */

    setcolor(COR_CAMINHO);
    DeltaXSelecao  = SELECAO_X_DIREITO   - SELECAO_X_ESQUERDO;
    DeltaYSelecao  = SELECAO_Y_SUPERIOR  - SELECAO_Y_INFERIOR;
    DeltaXExibicao = EXIBICAO_X_DIREITO  - EXIBICAO_X_ESQUERDO;
    DeltaYExibicao = EXIBICAO_Y_INFERIOR - EXIBICAO_Y_SUPERIOR;
    AtualRota = PrimeiraRota;
    while(AtualRota != NULL)
    {
      AtualSeg = AtualRota->PrimeiroSegmento;
      while(AtualSeg != NULL)
      {
	     /*  mapeamento do ponto Janela Sele‡†o/Exibicao.  */
	PontoXInicial = (int) ((AtualSeg->XInicial - SELECAO_X_ESQUERDO) *
				(DeltaXExibicao / DeltaXSelecao));
	PontoYInicial = (int) ((SELECAO_Y_SUPERIOR - AtualSeg->YInicial) *
				(DeltaYExibicao / DeltaYSelecao));
	PontoXFinal   = (int) ((AtualSeg->XFinal - SELECAO_X_ESQUERDO) *
				(DeltaXExibicao / DeltaXSelecao));
	PontoYFinal   = (int) ((SELECAO_Y_SUPERIOR - AtualSeg->YFinal) *
				(DeltaYExibicao / DeltaYSelecao));
	  // desenho da linha do mapa.
	setlinestyle(DASHED_LINE,3,1);
	line( PontoXInicial, PontoYInicial, PontoXFinal, PontoYFinal);
	AtualSeg = AtualSeg->ProximoSegmento;
      }
      AtualRota = AtualRota->ProximaRota;
    }
    AtualRota = PrimeiraRota;
    ExibeEnibeCursorCaminho();
  }

/*-----------------------------------------------------------------*\
 |            Representacao do Plano de Vias                       |
\*-----------------------------------------------------------------*/
  void PlanoVias(void)
  {
    float
      Linha,                    /* Linha atual de desenho.       */
      Coluna,                   /* Coluna atual de desenho.      */
      DeltaXSelecao,            /* Delta X janela selecao.       */
      DeltaYSelecao,            /* Delta Y janela selecao.       */
      DeltaXExibicao,           /* Delta X janela exibicao.      */
      DeltaYExibicao,           /* Delta Y janela exibicao.      */
      FXInicial,                /* Arquivo - limite X esquerdo.  */
      FYInicial,                /* Arquivo - limite Y inferior.  */
      FCoodXInicial,            /* Arq. coordenada X inicial.    */
      FCoodYInicial,            /* Arq. coordenada Y inicial.    */
      FCoodXFinal,              /* Arq. coordenada X final.      */
      FCoodYFinal;              /* Arq. coordenada Y final.      */
    int
      Quadricula,               /* Numero da quadricula atual.   */
      FQuadricula,              /* Arquivo - Numero Quadricula.  */
      PontoXInicial,            /* ponto mapeado X inicial.      */
      PontoYInicial,            /* ponto mapeado Y inicial.      */
      PontoXFinal,              /* ponto mapeado X final.        */
      PontoYFinal;              /* ponto mapeado Y final.        */
    FILE
      *ArqLog;                  /* Variavel do Arquivo de Vias.  */
    char
      StrQuadricula[3],         /* String numero quadricula.     */
      ArquivoVias[12];          /* Nome arquivo de Vias.         */

    setcolor(COR_VIA);
    DeltaXSelecao  = SELECAO_X_DIREITO   - SELECAO_X_ESQUERDO;
    DeltaYSelecao  = SELECAO_Y_SUPERIOR  - SELECAO_Y_INFERIOR;
    DeltaXExibicao = EXIBICAO_X_DIREITO  - EXIBICAO_X_ESQUERDO;
    DeltaYExibicao = EXIBICAO_Y_INFERIOR - EXIBICAO_Y_SUPERIOR;
    for(Linha=SELECAO_Y_INFERIOR;Linha < SELECAO_Y_SUPERIOR;Linha +=1000)
    {
      for(Coluna=SELECAO_X_ESQUERDO;Coluna < SELECAO_X_DIREITO;Coluna +=1000)
      {
	Quadricula = (int) (Linha / 1000) * 20;
	Quadricula = (int) Quadricula + (Coluna / 1000) + 1;
	strcpy(ArquivoVias,"QUA-");
	itoa(Quadricula,StrQuadricula,10);
	strcat(ArquivoVias,StrQuadricula);
	strcat(ArquivoVias, ".FUN");
	if((ArqLog = fopen(ArquivoVias,"r")) != NULL)
	{
	     /* extrai cabecalho */
	  fscanf( ArqLog,"%d", &FQuadricula);
	  fscanf( ArqLog,"%f", &FXInicial);
	  fscanf( ArqLog,"%f", &FYInicial);
	       /* pesquisa dos pontos X/Y do arquivo.  */
	  while( !feof( ArqLog))
	  {
	     fscanf( ArqLog,"%f", &FCoodXInicial);
	     fscanf( ArqLog,"%f", &FCoodYInicial);
	     fscanf( ArqLog,"%f", &FCoodXFinal);
	     fscanf( ArqLog,"%f", &FCoodYFinal);
	     FCoodXInicial = FCoodXInicial + FXInicial;
	     FCoodYInicial = FCoodYInicial + FYInicial;
	     FCoodXFinal   = FCoodXFinal + FXInicial;
	     FCoodYFinal   = FCoodYFinal + FYInicial;
		  /*  mapeamento do ponto Janela Sele‡†o/Exibicao.  */
	     PontoXInicial = (int) ((FCoodXInicial - SELECAO_X_ESQUERDO) *
				     (DeltaXExibicao / DeltaXSelecao));
	     PontoYInicial = (int) ((SELECAO_Y_SUPERIOR - FCoodYInicial) *
				     (DeltaYExibicao / DeltaYSelecao));
	     PontoXFinal   = (int) ((FCoodXFinal - SELECAO_X_ESQUERDO) *
				     (DeltaXExibicao / DeltaXSelecao));
	     PontoYFinal   = (int) ((SELECAO_Y_SUPERIOR - FCoodYFinal) *
				     (DeltaYExibicao / DeltaYSelecao));
	       // desenho da linha do mapa.
	     line( PontoXInicial, PontoYInicial, PontoXFinal, PontoYFinal);
	  }
	  fclose(ArqLog);
	}
      }
    }
  }

/*-----------------------------------------------------------------*\
 |            Representacao do Plano de Rios                       |
\*-----------------------------------------------------------------*/
  void PlanoRios(void)
  {
 
  }

/*-----------------------------------------------------------------*\
 |            Representacao do Plano de Referencias                |
\*-----------------------------------------------------------------*/
  void PlanoReferencias(void)
  {
 
  }
 
/*-----------------------------------------------------------------*\
 |            Controle do Help OnLine                              |
\*-----------------------------------------------------------------*/
  void HelpOnLine(void)
  {

  }

/*-----------------------------------------------------------------*\
\*-----------------------------------------------------------------*/

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
      LiberaMemoria();
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
    LiberaMemoria();
    closegraph();
    exit(1);             /* Erro: parametro XouY.         */
    return(1);
  }

/*-----------------------------------------------------------------*\
 |            Controle do mouse/teclado                            |
\*-----------------------------------------------------------------*/
  void GerenciaTecladoMouse(void)
  {
    char
      Tecla;                           /* Tecla pressionada.       */

    POS_X_CURSOR = (MAX_COD_X / 2),      /* Centraliza posicao X.  */
    POS_Y_CURSOR = (MAX_COD_Y / 2);      /* Centraliza posicao Y.  */
      /* Desenha Cursor Geral */
    putimage(POS_X_CURSOR,POS_Y_CURSOR,CURSOR_GERAL,XOR_PUT);
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
	case '\x1B' :    /* ESC */
	{
	  LiberaMemoria();
	  closegraph();
	  exit(0);                                    /* Finaliza execucao.  */
	}
      }
    }
  }

/*-----------------------------------------------------------------*\
 |            Libera memoria - alocacao dinamica.                  |
\*-----------------------------------------------------------------*/
  void LiberaMemoria(void)
  {
    LiberaQuadriculasMarcadas();
    LiberaRota();
  }


/*-----------------------------------------------------------------*\
 |            Libera memoria - Lista Rota.                         |
\*-----------------------------------------------------------------*/
  void LiberaRota(void)
  {
    AtualRota = PrimeiraRota;
    while(AtualRota != NULL)
    {
      EspacoRota = AtualRota->ProximaRota;
      AtualSeg = AtualRota->PrimeiroSegmento;
      while(AtualSeg != NULL)
      {
	EspacoSeg = AtualSeg->ProximoSegmento;
	free(AtualSeg);
	AtualSeg = EspacoSeg;
      }
      free(AtualRota);
      AtualRota = EspacoRota;
    }
    PrimeiraRota = AtualRota = EspacoRota = NULL;
    AtualSeg = EspacoSeg = NULL;
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
    if(!strcmp(NomeJanela,"BotaoCaminho1"))
    {
      ExibeEnibeCursorCaminho();
      if(AtualRota->AnteriorRota != NULL)
      {
	AtualRota = AtualRota->AnteriorRota;

      /*	JanelaMensagem*/
      }
      ExibeEnibeCursorCaminho();
      SelecionaJanela(MIN_COD_X,MIN_COD_Y,MAX_COD_X,MAX_COD_Y,
		      CLIP_OFF,NAO_APAGA_JANELA);     /* Sel. todo janela. */
    }
    if(!strcmp(NomeJanela,"BotaoCaminho2"))
    {
      ExibeEnibeCursorCaminho();
      if(AtualRota->ProximaRota != NULL)
      {
	AtualRota = AtualRota->ProximaRota;
      }
      ExibeEnibeCursorCaminho();
      SelecionaJanela(MIN_COD_X,MIN_COD_Y,MAX_COD_X,MAX_COD_Y,
		      CLIP_OFF,NAO_APAGA_JANELA);     /* Sel. todo janela. */
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
      MarcaDesmacarQuadricula();
      CentroQuadricula(QUADRICULA,&CodXEsq,&CodYSup);
      putimage(CodXEsq,CodYSup,MARCA_GRADE,XOR_PUT);
    }
    if(!strcmp(NomeJanela,"BotaoVistaGeral-8"))
    {
      ImagemFundo();
    }
  }

/*-----------------------------------------------------------------*\
 |            Marca Desmarca quadricula marcada.                   |
\*-----------------------------------------------------------------*/
  void MarcaDesmacarQuadricula(void)
  {
    const
      Aguarde = 1;                        /* Flag parada na mensagem.    */
    char
      *Mensagem;
    int
      SaiWhile = 1,                       /* Flag termina loop while      */
      QuadriculaNaoExiste = 1;            /* Quadricula nao existe        */

    AtualQuadricula = PrimeiraQuadricula;
    AnteriorQuadricula = PrimeiraQuadricula;
    if(QUANTIDADE_QUADRICULA > 0)
    {
      while(SaiWhile)
      {
	if(AtualQuadricula->NumeroQuadricula == QUADRICULA)
	{
	  QuadriculaNaoExiste = 0;            /* Encontrou Quadricula */
	  SaiWhile = 0;
	}
	else
	  if((AtualQuadricula->NumeroQuadricula > QUADRICULA) ||
	     (AtualQuadricula->ProximaQuadricula == NULL))
	    SaiWhile = 0;                    /* Nao encontrou Quadricula */
	  else
	  {
	    AnteriorQuadricula = AtualQuadricula;
	    AtualQuadricula = AtualQuadricula->ProximaQuadricula;
	  }
      }
    }
    if(QuadriculaNaoExiste)    /* Cadastra Quadricula na Lista */
    {
      if((EspacoQuadricula = malloc(sizeof(struct TipoQuadricula))) == NULL)
      {
	setcolor(COR_MENSAGEM_GERAL);
	MostraMensagem("Memoria insuficiente, estrutura QUADRICULAS. ",Aguarde);
	LiberaMemoria();
	closegraph();
	exit(1);                /* Erro: Arquivo incorreto. */
      }
      if(QUANTIDADE_QUADRICULA == 0)           /* Lista Vazia */
      {
	PrimeiraQuadricula = EspacoQuadricula;
	PrimeiraQuadricula->NumeroQuadricula = QUADRICULA;
	PrimeiraQuadricula->ProximaQuadricula = NULL;
	QUANTIDADE_QUADRICULA = 1;
      }
      else
      {
	if(AtualQuadricula->NumeroQuadricula > QUADRICULA)  /* meio lista */
	{
	  EspacoQuadricula->ProximaQuadricula = AtualQuadricula;
	  if(AtualQuadricula == PrimeiraQuadricula)
	    PrimeiraQuadricula = EspacoQuadricula;     /* inclui inicio */
	  else
	    AnteriorQuadricula->ProximaQuadricula = EspacoQuadricula;
	}
	else
	{
	  EspacoQuadricula->ProximaQuadricula = NULL;     /* inclui fim */
	  AtualQuadricula->ProximaQuadricula = EspacoQuadricula;
	}
	EspacoQuadricula->NumeroQuadricula  = QUADRICULA;
	QUANTIDADE_QUADRICULA += 1;
      }
    }
    else                       /* Exclui Quadricula da Lista */
    {
      if(QUANTIDADE_QUADRICULA == 1)
      {
	free(AtualQuadricula);            /* Llista vazia */
	QUANTIDADE_QUADRICULA = 0;
      }
      else
      {
	AnteriorQuadricula->ProximaQuadricula =
		      AtualQuadricula->ProximaQuadricula;
	if(AtualQuadricula == PrimeiraQuadricula)     /* Exclui priemiro */
	  PrimeiraQuadricula = AtualQuadricula->ProximaQuadricula;
	free(AtualQuadricula);
	QUANTIDADE_QUADRICULA -= 1;
      }
    }
  }

/*-----------------------------------------------------------------*\
 |            Cadastra a quadricula Marcada                        |
\*-----------------------------------------------------------------*/
  void CadastraQuadriculas(void)
  {
    const
      Aguarde = 1;                        /* Flag parada na mensagem.    */
    char
      *Mensagem;
    int
      SaiWhile = 1,                       /* Flag termina loop while      */
      QuadriculaNaoExiste = 1;            /* Quadricula nao existe        */

    AtualQuadricula = PrimeiraQuadricula;
    AnteriorQuadricula = PrimeiraQuadricula;
    if(QUANTIDADE_QUADRICULA > 0)
    {
      while(SaiWhile)
      {
	if(AtualQuadricula->NumeroQuadricula == QUADRICULA)
	{
	  QuadriculaNaoExiste = 0;            /* Encontrou Quadricula */
	  SaiWhile = 0;
	}
	else
	  if((AtualQuadricula->NumeroQuadricula > QUADRICULA) ||
	     (AtualQuadricula->ProximaQuadricula == NULL))
	    SaiWhile = 0;                    /* Nao encontrou Quadricula */
	  else
	  {
	    AnteriorQuadricula = AtualQuadricula;
	    AtualQuadricula = AtualQuadricula->ProximaQuadricula;
	  }
      }
    }
    if(QuadriculaNaoExiste)    /* Cadastra Quadricula na Lista */
    {
      if((EspacoQuadricula = malloc(sizeof(struct TipoQuadricula))) == NULL)
      {
	setcolor(COR_MENSAGEM_GERAL);
	MostraMensagem("Memoria insuficiente, estrutura QUADRICULAS. ",Aguarde);
	LiberaMemoria();
	closegraph();
	exit(1);                /* Erro: Arquivo incorreto. */
      }
      if(QUANTIDADE_QUADRICULA == 0)           /* Lista Vazia */
      {
	PrimeiraQuadricula = EspacoQuadricula;
	PrimeiraQuadricula->NumeroQuadricula = QUADRICULA;
	PrimeiraQuadricula->ProximaQuadricula = NULL;
	QUANTIDADE_QUADRICULA = 1;
      }
      else
      {
	if(AtualQuadricula->NumeroQuadricula > QUADRICULA)  /* meio lista */
	{
	  EspacoQuadricula->ProximaQuadricula = AtualQuadricula;
	  if(AtualQuadricula == PrimeiraQuadricula)
	    PrimeiraQuadricula = EspacoQuadricula;     /* inclui inicio */
	  else
	    AnteriorQuadricula->ProximaQuadricula = EspacoQuadricula;
	}
	else
	{
	  EspacoQuadricula->ProximaQuadricula = NULL;     /* inclui fim */
	  AtualQuadricula->ProximaQuadricula = EspacoQuadricula;
	}
	EspacoQuadricula->NumeroQuadricula  = QUADRICULA;
	QUANTIDADE_QUADRICULA += 1;
      }
    }
  }

/*-----------------------------------------------------------------*\
 |            Define a Janela Corrente do Cursor                   |
\*-----------------------------------------------------------------*/
  void JanelaCorrente(char *NomeJanela)
  {
/*    if(ContemJanela(0.9,1.2,5.5,7.1))
       strcpy(NomeJanela, "BotaoTitulo-1");
    if(ContemJanela(0.9,7.1,99.1,12.9))
       strcpy(NomeJanela, "Menus");
    if(ContemJanela(2.3,14.7,64.5,91.2))
       strcpy(NomeJanela, "AreaCliente");
    if(ContemJanela(2.3,91.2,55.5,97.1))
       strcpy(NomeJanela, "Mensagem");             */

    if(ContemJanela(55.5,91.2,60.0,97.1))
       strcpy(NomeJanela, "BotaoCaminho1");
    if(ContemJanela(60.0,91.2,64.5,97.1))
       strcpy(NomeJanela, "BotaoCaminho2");
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
