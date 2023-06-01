  #include<alloc.h>

  #define EXTERN extern

/*-----------------------------------------------------------------*\
 |                      Variaveis Globais                          |
\*-----------------------------------------------------------------*/

  EXTERN void
    *CURSOR_GERAL;             /* Identificador do Cursor Geral.         */
  EXTERN void
    *CURSOR_SCROOL,            /* Identificador Cursor Scrool.           */
    *CURSOR_GRADE,             /* Identificador do Cursor Grade.         */
    *MARCA_GRADE;              /* Identificador da Marca Grade.          */


  EXTERN float
    SELECAO_X_ESQUERDO,        /* Coluna esquerda da janela de selecao.  */
    SELECAO_X_DIREITO,         /* Coluna direita da janela de selecao.   */
    SELECAO_Y_SUPERIOR,        /* Linha superior da janela de selecao.   */
    SELECAO_Y_INFERIOR,        /* Linha inferior da janela de selecao.   */
    EXIBICAO_X_ESQUERDO,       /* Coluna esquerda da janela de exibicao. */
    EXIBICAO_X_DIREITO,        /* Coluna direita da janela de exibicao.  */
    EXIBICAO_Y_SUPERIOR,       /* Linha superior da janela de exibicao.  */
    EXIBICAO_Y_INFERIOR;       /* Linha inferior da janela de exibicao.  */


  EXTERN int
    MIN_COD_X,                 /* Minima Coordenada de X.                */
    MIN_COD_Y,                 /* Minima Coordenada de Y.                */
    MAX_COD_X,                 /* Maxima Coordenada de X.                */
    MAX_COD_Y;                 /* Maxima Coordenada de Y.                */

  EXTERN int
    INC_CURSOR,                /* Passo incremento Cursor.               */
    TAMANHO_CURSOR,            /* Tamanho do Cursor Ativo.               */
    POS_X_CURSOR,              /* Posi‡†o X do cursor na Tela.           */
    POS_Y_CURSOR;              /* Posi‡†o Y do cursor na Tela.           */

  EXTERN int
    PASSO_SCROOL,              /* Passo de incremento do Scrool.         */
    SCROOL_X_VERTICAL,         /* Coordenada X do Scrool Vertical.       */
    SCROOL_Y_VERTICAL,         /* Coordenada Y do Scrool Vertical.       */
    SCROOL_X_HORIZONTAL,       /* Coordenada X do Scrool Horizontal.     */
    SCROOL_Y_HORIZONTAL;       /* Coordenada Y do Scrool Horizontal.     */
 EXTERN int
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

  EXTERN int
    QUADRICULA     ,      /* Quadricula Inicial.                    */
    QUANTIDADE_QUADRICULA ; /* Quantidade de Quadriculas da Lista.    */

  EXTERN float
    LAR_MAR,                   /* Num. de pixels da margem de Largura.    */
    LAR_INT,                   /* Num. de pixels do Intervalo na Largura. */
    LAR_DISPO,                 /* Largura Disponivel p/ desenho da Grade. */
    LAR_QT_COL ,               /* Quant. de Colunas na Largura da grade.  */
    ALT_DISPO,                 /* Altura Disponivel p/ desenho da Grade.  */
    COD_BASE_X,                /* Coordenada Base ponto X inicial Grade.  */
    COD_BASE_Y,                /* Coordenada Base ponto Y inicial Grade.  */
    ASPECT;                    /* Relacao de Aspect.                      */


 EXTERN struct TipoQuadricula
      {
	int NumeroQuadricula;    /* Numero da Quadricula.       */
	struct TipoQuadricula
	  *ProximaQuadricula;             /* Aponta proxima Quadricula.  */
      } Quadricula;
 EXTERN struct TipoQuadricula
      *AnteriorQuadricula,         /* Aponta Anterior Quadiucula. */
      *AtualQuadricula,         /* Aponta atual Quadiucula.    */
      *EspacoQuadricula,         /* Aponta espaco alocado.      */
      *PrimeiraQuadricula;         /* Aponta primeira Quadricula. */


/*-----------------------------------------------------------------*\
 |            Prototipacao das Funcoes                             |
\*-----------------------------------------------------------------*/
  EXTERN void InicializaModoGrafico(void);
  EXTERN void InicializaCores( int Opcao);
  EXTERN void DesenhaCursorGeral(void);
  EXTERN void DesenhaCursorScrool(void);
  EXTERN void Interface(void);
  EXTERN void JanelaMoldura(void);
  EXTERN void JanelaMensagem(void);
  EXTERN void DesenhaJanelaMensagem(void);
  EXTERN void Menus(void);
  EXTERN void DesenhaJanelaMenu(void);
  EXTERN void EscreveTextoMenu(void);
  EXTERN void JanelaExibicao(void);
  EXTERN void DesenhaJanelaExibicao(void);
  EXTERN void BotaoCaminho(void);
  EXTERN void DesenhaBotoesCaminho(void);
  EXTERN void JanelaVistaGeral(void);
  EXTERN void DesenhaSetas(float PerXSup,float PerYSup,
                    float PerXInf,float PerYInf,int Opcao);
  EXTERN void EscreveTextoVistaGeral(void);
  EXTERN void ConstroiGradeMapa(void);
  EXTERN void IntLargura(float LarMax,float AltQtCol,float AltMax);
  EXTERN void RealcaQuadriculasAtivas(void);
  EXTERN void DesenhaNorte(void);
  EXTERN void DesenhaCursorGrade(void);
  EXTERN void DesenhaMarcaGrade(void);
  EXTERN void ExibeEnibeCursorGrade(int NumeroQuadri);
  EXTERN void JanelaAreaBotoes(void);
  EXTERN void EscreveTextoBotoes(void);
  EXTERN void DesenhaBarraScrool(void);
  EXTERN void Rota(void);
  EXTERN void LeRota(void);
  EXTERN void Caminho(void);
  EXTERN void PontosReferencias(void);
  EXTERN void ImagemFundo(void);
  EXTERN void EstabeleceCoordenadasJanelaExibicao(void);
  EXTERN void EstabeleceCoordenadasJanelaSelecao(void);
  EXTERN void PlanoVias(void);
  EXTERN void PlanoRios(void);
  EXTERN void PlanoReferencias(void);
  EXTERN void HelpOnLine(void);
  EXTERN void MostraMensagem(char *Mensagem,int Opcao);
  EXTERN void CentroQuadricula(int NumeroQuadri,
                        int *PosXCurGrade, int *PosYCurGrade);
  EXTERN void DesenhaJanela(float PerXSup,float PerYSup,
		     float PerXInf,float PerYInf,int Opcao);
  EXTERN void SelecionaJanela(float XEsq,float YSup,float XDir,float YInf,
                       int Clip,int Apaga);
  EXTERN int  ValorRelativoTela(char XouY,float Percentual,float Acrescimo);
  EXTERN void GerenciaTecladoMouse(void);
  EXTERN void PressionouEnter(void);
  EXTERN void JanelaCorrente(char *NomeJanela);
  EXTERN void CadastraQuadriculaMarcada(void);
  EXTERN int ContemJanela( float PerXSup, float PerYSup,
                    float PerXInf, float PerYInf);
  EXTERN void TeclaEspecial(void);
