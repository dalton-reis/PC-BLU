 /*   gera o arquivo CAMINHO2.COD    */


  #include <stdio.h>

  typedef struct
    {
      int NumReg;
      float
	XI, YI, XF, YF;
    }Segmento;


  void main(void)
  {
    char
      ArqArco[12] = "CAMINHO.COD";
    int ArqNumeroRegistro;
    float
      ArqXInicial,                      /* Valor de x inicial.          */
      ArqYInicial,                      /* Valor de y inicial.          */
      ArqXFinal,                        /* Valor de x final.            */
      ArqYFinal;                        /* Valor de y final.            */
    FILE *ArqLog;                          /* Variavel do Arquivo.         */
    FILE *ArqSeg;
    Segmento Segment;

    ArqSeg = fopen("CAMINHO2.COD","wb");
    ArqLog = fopen(ArqArco,"r");
    {
    while(!feof( ArqLog))
      {
	fscanf(ArqLog,"%d",   &ArqNumeroRegistro);
	fscanf(ArqLog,"%f %f",&ArqXInicial,&ArqYInicial);
	fscanf(ArqLog,"%f %f",&ArqXFinal,  &ArqYFinal);
	printf ("%d \n",ArqNumeroRegistro);
	Segment.NumReg = ArqNumeroRegistro;
	Segment.XI = ArqXInicial;
	Segment.YI = ArqYInicial;
	Segment.XF = ArqXFinal;
	Segment.YF = ArqYFinal;
	fwrite(&Segment,sizeof(Segmento), 1, ArqSeg);
      }
      fclose(ArqLog);
      fclose(ArqSeg);
    }
  }
