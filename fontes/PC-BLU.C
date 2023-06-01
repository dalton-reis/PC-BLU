/*-----------------------------------------------------------------*\
 |                      Arquivos de Inclusao                       |
\*-----------------------------------------------------------------*/
  #include <graphics.h>
  #include <stdlib.h>
  #include <conio.h>
  #include <stdio.h>
/*  #include "globais.h"  */


/*-----------------------------------------------------------------*\
 |            Modulo Principal   -   PC-Blumenau                   |
\*-----------------------------------------------------------------*/
  void main(void)
  {
    InicializaModoGrafico();
    Interface();
    Rota();
    Caminho();
    PontosReferencias();
    ImagemFundo();
/*    ImagemDigitalizada();  */
    GerenciaTecladoMouse();
  }


/*-----------------------------------------------------------------*\
 |            Controle do Help OnLine                              |
\*-----------------------------------------------------------------*/
  void HelpOnLine(void)
  {

  }

