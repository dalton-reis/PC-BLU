  #include <stdio.h>

  typedef struct
    {
      int NumReg;
      float
	XI, YI, XF, YF;
    }Segmento;


  void main(void)
  {
    FILE *ArqSeg;
    Segmento Segment;

    ArqSeg = fopen("CAMINHO2.COD","rb");
    while(!feof( ArqSeg))
      {
	fread(&Segment,sizeof(Segmento), 1, ArqSeg);
	printf("%d  ",Segment.NumReg);
	printf("%f %f %f %f \n",Segment.XI,Segment.YI,Segment.XF,Segment.YF);
      }
      fclose(ArqSeg);
    }
