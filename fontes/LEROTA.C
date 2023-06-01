
#include <stdio.h>;
#include <alloc.h>;

  void LeRota(void);

  void main(void)
  {
    LeRota();
  }

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
    int   i,
      ArqSetorInicial,                  /* Setor Inicial da Rota.       */
      ArqCruzaInicial,                  /* Cruzamento Inicial da Rota.  */
      ArqSetorFinal,                    /* Setor Final da Rota.         */
      ArqCruzaFinal,                    /* Cruzamento Final da Rota.    */
      ArqDistancia,
      ArqCota;
    char *Rua, *Bairro, *lixo;
    FILE
      *ArqLog;                          /* Variavel do Arquivo da Rota. */
    char
      *Mensagem,
      ArquivoRota[] = "CRUZAM.RLT";     /* Arquivo c/ Rota do CRUZAM.    */



    if((ArqLog = fopen(ArquivoRota,"r")) == NULL)
    {
      printf("erro!\n");
    }
    else
    {
      PrimeiroRota    = malloc(sizeof(struct TipoRota));
      PredecessorRota = PrimeiroRota;
      for (i=1; i<7; i++)
	fscanf( ArqLog,"%s ", lixo);
      fscanf( ArqLog,"%s \n", lixo);
      for (i=1; i<8; i++)
      fscanf( ArqLog,"%s",lixo);
      fscanf( ArqLog,"%s \n", lixo);
      while( !feof( ArqLog))
      {
	if((AtualRota = malloc(sizeof(struct TipoRota))) == NULL)
	{
      printf("erro memoria!\n");

        }
        else
        {
	  fscanf(ArqLog,"%d"  ,&ArqSetorInicial);
	  fscanf(ArqLog,"%d"  ,&ArqCruzaInicial);
	  fscanf(ArqLog,"%d"  ,&ArqSetorFinal);
	  fscanf(ArqLog,"%d"  ,&ArqCruzaFinal);
	  fscanf(ArqLog,"%d %d"  ,&ArqDistancia,&ArqCota);

	  fgets(Rua,33 , ArqLog);
	  fgets(Bairro, 20, ArqLog);
	  fscanf(ArqLog, "\n");
	  printf("\n %s ", Rua );
	  printf(" %s \n", Bairro );



	  PredecessorRota ->ProximoRota = AtualRota;
	  Rota.SetorInicial = ArqSetorInicial;
	  Rota.CruzaInicial = ArqCruzaInicial;
	  Rota.SetorFinal   = ArqSetorFinal;
	  Rota.CruzaFinal   = ArqCruzaFinal;
        }
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
