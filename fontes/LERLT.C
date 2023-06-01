
  #include <stdio.h>


 void main(void)
 {
  char *STR;
  FILE *ArqLog;
  ArqLog = fopen("CRUZAM.RLT","r");
  while(!feof(ArqLog))
  {
   STR = getc(ArqLog);
   getch();
  }
  fclose(ArqLog);
 }
