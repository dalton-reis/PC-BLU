 /*   gera o arquivo CAMINHO.SET    */


  #include <stdio.h>

  typedef struct
    {
      int Setor, Cruzamento;
      float
	XI, YI;
      int Quadricula;
    }Segmento;


  void main(void)
  {
    char
      ArqArco[12] = "CAMINHO.7";
    int ArqSet, ArqCruz, ArqQuad;
    float
      ArqXi,                      /* Valor de x inicial.          */
      ArqYi;                      /* Valor de y inicial.          */
    FILE *ArqLog;                          /* Variavel do Arquivo.         */
    FILE *ArqSeg;
    Segmento Segment;

    ArqSeg = fopen("CAMINHO.SET","wb");
    ArqLog = fopen(ArqArco,"r");
    {
    while(!feof( ArqLog))
      {
	fscanf(ArqLog,"%d %d",   &ArqSet, &ArqCruz);
	fscanf(ArqLog,"%f %f %d \n",&ArqXi, &ArqYi, &ArqQuad);
	printf ("%d %d \n",ArqSet, ArqCruz);
	Segment.Setor      = ArqSet;
	Segment.Cruzamento = ArqCruz;
	Segment.XI = ArqXi;
	Segment.YI = ArqYi;
	Segment.Quadricula = ArqQuad;
	fwrite(&Segment,sizeof(Segmento), 1, ArqSeg);
      }
      fclose(ArqLog);
      fclose(ArqSeg);
    }
  }
