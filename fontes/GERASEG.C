  #include <stdio.h>

  typedef struct
    {
      char
	palavra[30];
    }RegTipado;

  void main(void)
  {
    char
      ArqTexto[12]  = "PALAVRA.TXT",
      ArqTipado[12] = "PALAVRA.TIP";
    char
      palavratxt[30];

    FILE *ArqTip;
    FILE *ArqTxt;
    RegTipado Tipado;

    ArqTip = fopen(ArqTipado,"wb");
    ArqTxt = fopen(ArqTexto,"r");
    {
    while(!feof( ArqTxt))
      {
	fscanf(ArqTxt,"%s30",&palavratxt);
	printf ("%s\n",palavratxt);
/*	Tipado.palavra = palavratxt; */
	fwrite(&Tipado,sizeof(Tipado), 1, ArqTip);
      }
      fclose(ArqTxt);
      fclose(ArqTip);
    }
  }
