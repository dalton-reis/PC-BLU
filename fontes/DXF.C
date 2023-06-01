/*-----------------------------------------------------------------*\
 |  Programa para coletar dados de arquivos *.dxf gerados pelo     |
 |     AutoCad, criando um novo arquivo do tipo:                   |
 |     QUAD.: ###                 -> indica num. quadricula.       |
 |     Xi: ##.###                 -> limite de X inicial.          |
 |     Yi: ##.###                 -> limite de Y inicial.          |
 |     ##### ##### [##### #####]  -> X, Y inic. e finais.          |
 |                                                                 |
 |  Arquivo Entrada:                                               |
 |     Pesquisa atraves do arquivo QUADRI.DIG (contem os numeros   |
 |     de quadriculas a ser pesquisadas) ou atraves de parametro   |
 |     do nome especifico do arquivo.                              |
 |     Nome especifico: Q###-LLL                                   |
 |                                                                 |
 |  Arquivo Saida: QUA-###.LLL                                     |
 |                                                                 |
 |  Onde:                                                          |
 |          ### -> indica num. quadricula.                         |
 |          LLL -> indica layer ( FUN, RIO, REF).                  |
 |                                                                 |
 |     Dalton Solano dos Reis          31.10.92                    |
\*-----------------------------------------------------------------*/

/* ----------------------------------------------------------------*\
 |                   Arquivos de Inclusao                          |
\*-----------------------------------------------------------------*/

  #include <conio.h>
  #include <stdio.h>
  #include <string.h>


/*-----------------------------------------------------------------*\
 |                       Variaveis Globais                         |
\*-----------------------------------------------------------------*/

  char
    ARQUIVO[8],              // arquivo de pesquisa
    ARQ_ENT[12],             // arquivo de entrada
    ARQ_SAI[12],             // arquivo de saida
    F_QUADRI[3],             // quadrivula do arquivo.
    C_QUAD[3],               // quadricula
    OPCAO[3],                // variavel de selecao
    SECAO[8],                // token SECTION
    ENTIDADES[8],            // token ENTITIES
    TIPO[4],                 // token LINE
    LAYER[15],               // identifica o LAYER
    LIXO;                    // descarrega linhas

  long
    TEMP,                    // variavel temporaria
    QUAD,                    // numero quadricula
    Xi,                      // limite inf. x quadr.
    Yi,                      // limite inf. y quadr.
    ZERO,                    // token 0
    DOIS,                    // token 2
    COD_LAYER,               // codigo do layer
    COD_XI,                  // codigo do x inicial
    XI,                      // ponto do x inicial
    COD_YI,                  // codigo do y inicial
    YI,                      // ponto do y inicial
    COD_ZI,                  // codigo do z inicial
    ZI,                      // ponto do z inicial
    COD_XF,                  // codigo do x final
    XF,                      // ponto do x final
    COD_YF,                  // codigo do y final
    YF,                      // ponto do y final
    COD_ZF,                  // codigo do z final
    ZF,                      // ponto do z final
    COD_ATRIB,               // codigo do atributo
    ATRIB,                   // valor atributo
    COD_TEXT,                // codigo do texto
    TEXT;                    // valor do texto

    FILE
      *ENTRADA,              // ponteiro de entrada
      *SAIDA,                // ponteiro de saida
      *QUADRI;               // ponteiro de entradas.


/*-----------------------------------------------------------------*\
 |                    Prototipacao das Funcoes                     |
\*-----------------------------------------------------------------*/

  void Inicializa( void);         // Inicializa a Tela.
  void Arquivos( void);           // Arquivos a serem pesquisados.
  SelecionaEntrada( void);        // Inf. nome arquivo/abre e cria
  SelecionaQuadri( void);         // Selec. muitas entradas.
  void Fundo( void);              // Abre arquivo de Fundo.
  void Rios( void);               // Abre arquivo de Rios.
  void Ref( void);                // Abre arquivo de Referencias.
  void Cam( void);                // Abre arquivo de Caminhos.
  SelecionaSaida( void);          // Selec. saida e abre arq. saida
  FundoRio( void);                // Dados do layer Fundo e Rios
  Referencias( void);             // Dados do layer Referencias
  Caminhos( void);                // Dados do layer Caminho.
  void CalculaXY( void);          // Calcula Xs e Ys da quadricula n


/*-----------------------------------------------------------------*\
 |                     Funcao Principal                            |
\*-----------------------------------------------------------------*/

  main(int argc, char *argv[])
  {
    if( argc > 2)
    {
      printf("\n\n\Erro na passagem dos Parametros  !!!");
      printf("\n\Formato: DXF <arquivo_de_entrada> \n\n");
      return(1);
    }
    Inicializa();
    if( argc == 2)
    {
      strcat(ARQUIVO,argv[1]);
      if( SelecionaEntrada() == 0)
      {
	if( SelecionaSaida() == 0)
	{
	  Arquivos();
	}
	fclose(ENTRADA);
      }
    }
    else
    {
      if( SelecionaQuadri() == 0)
      {
	fscanf(QUADRI,"%s", F_QUADRI);
	while (!feof(QUADRI))
	{
	  Fundo();
	  Rios();
	  Ref();
	  Cam();
	  fscanf(QUADRI,"%s", F_QUADRI);
	}
	fclose( QUADRI);
      }
    }
    gotoxy(22,24);
    printf("  Terminio de Pesquisa !! ");
    return(0);
  }


/*-----------------------------------------------------------------*\
 |                      Inicializa a Tela                          |
\*-----------------------------------------------------------------*/

  void Inicializa( void)
  {
    clrscr();
    gotoxy(13,2);
    printf(" Coleta dados de arquivos *.dxf (AutoCad),");
    gotoxy(13,3);
    printf("     criando  novos arquivos contendo:");
    gotoxy(10,5);
    printf("  QUA-###.FUN -> informa‡oes do plano de Fundo. ");
    gotoxy(10,6);
    printf("  QUA-###.RIO -> informa‡oes do plano de Rios. ");
    gotoxy(10,7);
    printf("  QUA-###.REF -> informa‡oes do plano de Referencias. ");
    gotoxy(10,8);
    printf("  QUA-###.CAM -> informa‡oes do Plano de Caminhos. ");
    gotoxy(03,13);
    printf("     --  AGUARDE  --");
  }


/*-----------------------------------------------------------------*\
 |                    Arquivos a serem Gerados                     |
\*-----------------------------------------------------------------*/

  void Arquivos( void)
  {
    int
      COMP;

    COMP = strcmp(OPCAO,"FUN");
    if(( COMP == 0) || ( COMP == 0))
       FundoRio();
    COMP = strcmp(OPCAO,"RIO");
    if(( COMP == 0) || ( COMP == 0))
       FundoRio();
    COMP = strcmp(OPCAO,"REF");
    if( COMP == 0)
       Referencias();
    COMP = strcmp(OPCAO,"CAM");
    if( COMP == 0)
       Caminhos();
    fclose(SAIDA);
  }


/*-----------------------------------------------------------------*\
 |                    Seleciona Arquivo de Entrada                 |
\*-----------------------------------------------------------------*/

  SelecionaEntrada( void)
  {
    strcpy(ARQ_ENT,ARQUIVO);
    strcat(ARQ_ENT,".DXF");                       // anexo extensao
    gotoxy(03,15);
    printf(" -> Abrindo arquivo: %s",ARQ_ENT);
    if((ENTRADA = fopen(ARQ_ENT, "r")) == NULL)   // abrindo arq.
    {
       gotoxy(03,20);
       fprintf(stderr, " -> %s: Arquivo nao acessado !\n",ARQ_ENT);
       return(1);
    }
    return(0);
  }


/*-----------------------------------------------------------------*\
 |                Seleciona Arquivo Muitas Entrada                 |
\*-----------------------------------------------------------------*/

  SelecionaQuadri( void)
  {
    strcpy(ARQ_ENT,"QUADRI.DIG");
    gotoxy(03,15);
    printf(" -> Abrindo arquivo: %s",ARQ_ENT);
    if(( QUADRI= fopen(ARQ_ENT, "r")) == NULL)   // abrindo arq.
    {
       gotoxy(03,20);
       fprintf(stderr, " -> %s: Arquivo nao acessado !\n",ARQ_ENT);
       return(1);
    }
    return(0);
  }


/*-----------------------------------------------------------------*\
 |                    Abre arquivo de FUNDO.DXF                    |
\*-----------------------------------------------------------------*/

  void Fundo( void)
  {
    strcpy(ARQUIVO,"Q");
    strcat(ARQUIVO,F_QUADRI);
    strcat(ARQUIVO,"-FUN");
    strcpy(ARQ_ENT,"Q");
    strcat(ARQ_ENT,F_QUADRI);
    strcat(ARQ_ENT,"-FUN.DXF");
    gotoxy(03,15);
    printf(" -> Abrindo arquivo: %s",ARQ_ENT);
    if((ENTRADA = fopen(ARQ_ENT, "r")) == NULL)   // abrindo arq.
    {
       gotoxy(03,20);
       fprintf(stderr, " -> %s: Arquivo nao acessado !\n",ARQ_ENT);
       (ENTRADA = fopen("QUADRI.ERR", "a"));
       fprintf(ENTRADA," Arquivo n†o acessado -> %s\n",ARQ_ENT);
    }
    else
    {
      if( SelecionaSaida() == 0)
	Arquivos();
    }
    fclose(ENTRADA);
  }


/*-----------------------------------------------------------------*\
 |                    Abre arquivo de RIOS.DXF                     |
\*-----------------------------------------------------------------*/

  void Rios( void)
  {
    strcpy(ARQUIVO,"Q");
    strcat(ARQUIVO,F_QUADRI);
    strcat(ARQUIVO,"-RIO");
    strcpy(ARQ_ENT,"Q");
    strcat(ARQ_ENT,F_QUADRI);
    strcat(ARQ_ENT,"-RIO.DXF");
    gotoxy(03,15);
    printf(" -> Abrindo arquivo: %s",ARQ_ENT);
    if((ENTRADA = fopen(ARQ_ENT, "r")) == NULL)   // abrindo arq.
    {
       gotoxy(03,20);
       fprintf(stderr, " -> %s: Arquivo nao acessado !\n",ARQ_ENT);
       (ENTRADA = fopen("QUADRI.ERR", "a"));
       fprintf(ENTRADA," Arquivo n†o acessado -> %s\n",ARQ_ENT);
    }
    else
    {
      if( SelecionaSaida() == 0)
	Arquivos();
    }
    fclose(ENTRADA);
  }


/*-----------------------------------------------------------------*\
 |                Abre arquivo de REFERENCIAS.DXF                  |
\*-----------------------------------------------------------------*/

  void Ref( void)
  {
    strcpy(ARQUIVO,"Q");
    strcat(ARQUIVO,F_QUADRI);
    strcat(ARQUIVO,"-REF");
    strcpy(ARQ_ENT,"Q");
    strcat(ARQ_ENT,F_QUADRI);
    strcat(ARQ_ENT,"-REF.DXF");
    gotoxy(03,15);
    printf(" -> Abrindo arquivo: %s",ARQ_ENT);
    if((ENTRADA = fopen(ARQ_ENT, "r")) == NULL)   // abrindo arq.
    {
       gotoxy(03,20);
       fprintf(stderr, " -> %s: Arquivo nao acessado !\n",ARQ_ENT);
       (ENTRADA = fopen("QUADRI.ERR", "a"));
       fprintf(ENTRADA," Arquivo n†o acessado -> %s\n",ARQ_ENT);
    }
    else
    {
      if( SelecionaSaida() == 0)
	Arquivos();
    }
    fclose(ENTRADA);
  }


/*-----------------------------------------------------------------*\
 |                Abre arquivo de CAMINHO.DXF                      |
\*-----------------------------------------------------------------*/

  void Cam( void)
  {
    strcpy(ARQUIVO,"Q");
    strcat(ARQUIVO,F_QUADRI);
    strcat(ARQUIVO,"-CAM");
    strcpy(ARQ_ENT,"Q");
    strcat(ARQ_ENT,F_QUADRI);
    strcat(ARQ_ENT,"-CAM.DXF");
    gotoxy(03,15);
    printf(" -> Abrindo arquivo: %s",ARQ_ENT);
    if((ENTRADA = fopen(ARQ_ENT, "r")) == NULL)   // abrindo arq.
    {
       gotoxy(03,20);
       fprintf(stderr, " -> %s: Arquivo nao acessado !\n",ARQ_ENT);
       (ENTRADA = fopen("QUADRI.ERR", "a"));
       fprintf(ENTRADA," Arquivo n†o acessado -> %s\n",ARQ_ENT);
    }
    else
    {
      if( SelecionaSaida() == 0)
	Arquivos();
    }
    fclose(ENTRADA);
  }


/*-----------------------------------------------------------------*\
 |                    Seleciona Arquivo de Saida                   |
\*-----------------------------------------------------------------*/

  SelecionaSaida( void)
  {
    sscanf(&ARQUIVO[1],"%d3",&QUAD);
    if( QUAD < 100)
       sscanf(&ARQUIVO[4],"%s3",OPCAO);
    else
       sscanf(&ARQUIVO[5],"%s3",OPCAO);
    ltoa(QUAD,C_QUAD,10);
    strcpy(ARQ_SAI,"QUA-");
    strcat(ARQ_SAI,C_QUAD);
    strcat(ARQ_SAI,".");
    strcat(ARQ_SAI,OPCAO);
    CalculaXY();
    gotoxy(03,16);
    printf(" -> Gerando arquivo: %s",ARQ_SAI);
    if((SAIDA = fopen(ARQ_SAI, "w")) == NULL)   // abrindo arq.
    {
       fprintf(stderr, " \n\n\n%s -> Arquivo nao pode ser aberto !\n");
       return(1);
    }
    fprintf(SAIDA,"%d\n",QUAD);
    fprintf(SAIDA,"%d\n",Xi);
    fprintf(SAIDA,"%d\n",Yi);
    return(0);
  }


/*-----------------------------------------------------------------*\
 |                  Pesquisa Dados p/ FUNDO e RIOS                 |
\*-----------------------------------------------------------------*/

  FundoRio( void)
  {
    int
      LINHA,
      PRT;
    gotoxy(03,18);
    LINHA = 0;
    printf(" -> Pesquisando linha: %d",LINHA);
    fscanf(ENTRADA,"%d", &ZERO);
    fscanf(ENTRADA,"%s", SECAO);
    fscanf(ENTRADA,"%d", &DOIS);
    fscanf(ENTRADA,"%s", ENTIDADES);
    while (!feof(ENTRADA))
    {
      fscanf(ENTRADA,"%d", &ZERO);
      fscanf(ENTRADA,"%s", TIPO);
      PRT = strcmp(TIPO,"LINE");
      if (PRT == 0)
      {
	fscanf(ENTRADA,"%d", &COD_LAYER);
	fscanf(ENTRADA,"%s", LAYER);
	fscanf(ENTRADA,"%d", &COD_XI);
	fscanf(ENTRADA,"%d", &XI);
	fscanf(ENTRADA,"%d", &COD_YI);
	fscanf(ENTRADA,"%d", &YI);
	fscanf(ENTRADA,"%d", &COD_ZI);
	fscanf(ENTRADA,"%d", &ZI);
	fscanf(ENTRADA,"%d", &COD_XF);
	fscanf(ENTRADA,"%d", &XF);
	fscanf(ENTRADA,"%d", &COD_YF);
	fscanf(ENTRADA,"%d", &YF);
	fscanf(ENTRADA,"%d", &COD_ZF);
	fscanf(ENTRADA,"%d", &ZF);
      }
      else
      {
	fscanf(ENTRADA,"%d", &COD_LAYER);
	fscanf(ENTRADA,"%s", LAYER);
	PRT = strcmp(LAYER, "EOF");
	if (PRT == 0)
	{
	  return(0);
	}

      }
      ++LINHA;
      gotoxy(26,18);
      printf("%d",LINHA);
      fprintf(SAIDA,"%d ", XI-Xi);
      fprintf(SAIDA,"%d ", YI-Yi);
      fprintf(SAIDA,"%d ", XF-Xi);
      fprintf(SAIDA,"%d\n", YF-Yi);
    }
    return(1);
  }


/*-----------------------------------------------------------------*\
 |                  Pesquisa Dados p/ REFERENCIAS                  |
\*-----------------------------------------------------------------*/

  Referencias( void)
  {
    int
      CONT,
      LINHA,
      PRT;

    gotoxy(03,18);
    LINHA = 0;
    printf(" -> Pesquisando linha: %d",LINHA);
    fscanf(ENTRADA,"%d", &ZERO);
    fscanf(ENTRADA,"%s", SECAO);
    fscanf(ENTRADA,"%d", &DOIS);
    fscanf(ENTRADA,"%s", ENTIDADES);
    while (!feof(ENTRADA))
    {
      fscanf(ENTRADA,"%d", &ZERO);
      fscanf(ENTRADA,"%s", TIPO);
      PRT = strcmp(TIPO,"TEXT");
      if (PRT == 0)
      {
	fscanf(ENTRADA,"%d", &COD_LAYER);
	fscanf(ENTRADA,"%s", LAYER);
	fscanf(ENTRADA,"%d", &COD_XI);
	fscanf(ENTRADA,"%d", &XI);
	fscanf(ENTRADA,"%d", &COD_YI);
	fscanf(ENTRADA,"%d", &YI);
	fscanf(ENTRADA,"%d", &COD_ZI);
	fscanf(ENTRADA,"%d", &ZI);
	fscanf(ENTRADA,"%d", &COD_ATRIB);
	fscanf(ENTRADA,"%d", &ATRIB);
	fscanf(ENTRADA,"%d", &COD_TEXT);
	fscanf(ENTRADA,"%d", &TEXT);
	for (CONT=0;CONT < 54;CONT++)
	  fscanf(ENTRADA,"%s", LIXO);
      }
      else
      {
	fscanf(ENTRADA,"%d", &COD_LAYER);
	fscanf(ENTRADA,"%s", LAYER);
	PRT = strcmp(LAYER, "EOF");
	if (PRT == 0)
	{
	  return(0);
	}
      }
      ++LINHA;
      gotoxy(26,18);
      printf("%d",LINHA);
      fprintf(SAIDA,"%d ", XI-Xi);
      fprintf(SAIDA,"%d ", YI-Yi);
      fprintf(SAIDA,"%d\n", TEXT);
    }
    return(1);
  }


/*-----------------------------------------------------------------*\
 |                  Pesquisa Dados p/ CAMINHO                      |
\*-----------------------------------------------------------------*/

  Caminhos( void)
  {

    typedef
      char STR05[5];              // Define string 5 posicao.

    STR05
      EXI_SET_NODO[100] = {""};   // Vetor de Setores/Nodos existentes.

    int
      CONT,                       // Flag p/ contar.
      QUANT = 0,                  // Quantidade de Setores/Nodos.
      LINHA,                      // Linha de Pesquisa.
      TEXT,                       // Inicio da secao de TEXTO.
      LINE,                       // Inicio da secao de LINHA.
      SETOR,                      // Numero do SETOR.
      NODO,                       // Numero do NODO.
      X_NODO,                     // Localizacao do nodo em X.
      Y_NODO;                     // Localizacao do nodo em Y.
    char
      ZERO,                       // Flag de pesquisa do ZERO.
      SET_NODO[5];                // Flag de pesquisa do SETOR e NODO.

    gotoxy(03,18);
    LINHA = 0;
    printf(" -> Pesquisando linha: %d",LINHA);
    fscanf(ENTRADA,"%s", ZERO);
    fscanf(ENTRADA,"%s", SECAO);
    fscanf(ENTRADA,"%d", &DOIS);
    fscanf(ENTRADA,"%s", ENTIDADES);
    while ( !feof( ENTRADA))
    {
      ZERO = '9';
      while (( ZERO != '0') && ( !feof( ENTRADA)))
      {
	if (strcmp( TIPO, "0"))
	  fscanf(ENTRADA,"%s", &ZERO);
	else
	  ZERO = '0';
	if (ZERO == '0')
	{
	  fscanf(ENTRADA,"%s", TIPO);
	  TEXT   = strcmp( TIPO,"TEXT");
	  LINE   = strcmp( TIPO,"LINE");
	  if (( TEXT != 0) && (LINE != 0))
	    ZERO = '9';
	}
      }
      if (TEXT == 0)
      {
	for (CONT=0;CONT < 11;CONT++)
	  fscanf(ENTRADA,"%s", LIXO);       // salta 11 linhas.
	fscanf(ENTRADA,"%s",SET_NODO);
	CONT = 0;
	while (( CONT <= QUANT) && ( strcmp( EXI_SET_NODO[CONT], SET_NODO)))
	  CONT += 1;
	if ( CONT > QUANT)
	{
	  strcpy( EXI_SET_NODO[QUANT], SET_NODO);
	  strcat( EXI_SET_NODO[QUANT], "\0");
//	  sscanf( EXI_SET_NODO[QUANT], "%s5", SET_NODO);
	  QUANT += 1;
	  sscanf( &SET_NODO[0], "%d1", &SETOR);
	  sscanf( &SET_NODO[2], "%d3", &NODO);
	  for ( CONT=0;CONT < 3;CONT++)
	    fscanf( ENTRADA, "%s", LIXO);       // salta 3 linhas.
	  fscanf( ENTRADA, "%d", &X_NODO);
	  fscanf( ENTRADA, "%s", LIXO);         // salta 1 linha.
	  fscanf( ENTRADA, "%d", &Y_NODO);

	  fprintf( SAIDA, "%d ", SETOR);
	  fprintf( SAIDA, "%d ", NODO);
	  fprintf( SAIDA, "%d ", X_NODO);
	  fprintf( SAIDA, "%d\n", Y_NODO);
	}
      }
      ++LINHA;
      gotoxy(26,18);
      printf("%d",LINHA);
    }
    return(1);
  }


/*-----------------------------------------------------------------*\
 |                  Calculo dos Limites                            |
\*-----------------------------------------------------------------*/

  void CalculaXY()
  {
    TEMP = (QUAD * 1000) /20;
    Yi   = TEMP / 1000;
    Yi   = Yi * 1000;
    Xi   = (QUAD * 1000) - (Yi * 20);
    if( Xi == 0)
      Yi = Yi - 1000;
    if( Xi == 0)
      Xi = 20000;
    Xi = Xi - 1000;
  }

/* ----------------------------------------------------------------*/

