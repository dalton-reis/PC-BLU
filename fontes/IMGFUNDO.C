  #include <stdio.h>
  #include "globais.h"
  #include "define.h"

  #define EXTERN extern

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
 |            Representacao do Plano de Vias                       |
\*-----------------------------------------------------------------*/
  void PlanoVias(void)
  {
    const
      Aguarde = 1;              /* Nao Aguarda na Mensagem. */
    float
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
      FQuadricula,              /* Arquivo - Numero Quadricula.  */
      PontoXInicial,            /* ponto mapeado X inicial.      */
      PontoYInicial,            /* ponto mapeado Y inicial.      */
      PontoXFinal,              /* ponto mapeado X final.        */
      PontoYFinal;              /* ponto mapeado Y final.        */
    FILE
      *ArqLog;                  /* Variavel do Arquivo de Vias.  */
    char
      Quadricula[3],            /* Numero da quadricula atual.   */
      ArquivoVias[12],          /* Nome arquivo de Vias.         */
      *Mensagem;
 
    setcolor(COR_VIA);
    DeltaXSelecao  = SELECAO_X_DIREITO   - SELECAO_X_ESQUERDO;
    DeltaYSelecao  = SELECAO_Y_SUPERIOR  - SELECAO_Y_INFERIOR;
    DeltaXExibicao = EXIBICAO_X_DIREITO  - EXIBICAO_X_ESQUERDO;
    DeltaYExibicao = EXIBICAO_Y_INFERIOR - EXIBICAO_Y_SUPERIOR;
    AtualQuadricula = PrimeiraQuadricula;
    while(AtualQuadricula != NULL)
    {
      strcpy(ArquivoVias,"QUA-");
      itoa(AtualQuadricula->NumeroQuadricula,Quadricula,10);
      strcat(ArquivoVias,Quadricula);
      strcat(ArquivoVias, ".FUN");
      if((ArqLog = fopen(ArquivoVias,"r")) == NULL)
      {
        setcolor(COR_MENSAGEM_GERAL);
        MostraMensagem("Arquivo nao acessado -> VIAS ??? " ,Aguarde);
        SelecionaJanela((ValorRelativoTela('X', 4.5, 0.45)),
                        (ValorRelativoTela('Y',14.7, 0.59)),
                        (ValorRelativoTela('X',64.5,-0.45)),
                        (ValorRelativoTela('Y',88.2,-0.59)),
                         CLIP_ON, NAO_APAGA_JANELA);
      }
      else
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
	     /* desenho da linha do mapa.  */
           line( PontoXInicial, PontoYInicial, PontoXFinal, PontoYFinal);
        }
        fclose(ArqLog);
      }
      AtualQuadricula = AtualQuadricula->ProximaQuadricula;
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
 |            Cadastra a quadricula Marcada                        |
\*-----------------------------------------------------------------*/
  void CadastraQuadriculaMarcada(void)
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

