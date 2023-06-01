 /*   retira espaco do arquivo caminho.seg */

  #include <stdio.h>

  void main(void)
  {
    char
      ArqArco[12] = "CAMINHO.SEG";
    int
      ArqSetIni,
      ArqCruIni,
      ArqSetFin,
      ArqCruFin,
      ArqIniSeg,
      ArqQuaSeg;
    FILE *ArqLog;
    FILE *ArqSeg;

    ArqSeg = fopen("CAMINHO.2","w");
    ArqLog = fopen(ArqArco,"r");
    while(!feof( ArqLog))
      {
	fscanf(ArqLog,"%d %d",&ArqSetIni,&ArqCruIni);
	fscanf(ArqLog,"%d %d",&ArqSetFin,&ArqCruFin);
	fscanf(ArqLog,"%d \n %d \n",&ArqIniSeg, &ArqQuaSeg);

	printf ("%d %d\n",ArqSetIni,ArqCruIni);

	fprintf(ArqSeg,"%d %d ",ArqSetIni,ArqCruIni);
	fprintf(ArqSeg,"%d %d ",ArqSetFin,ArqCruFin);
	fprintf(ArqSeg,"%d %d \n",ArqIniSeg,ArqQuaSeg);
      }
      fclose(ArqLog);
      fclose(ArqSeg);
  }
