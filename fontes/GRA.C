#include <graphics.h>                            // Declaracoes da biblioteca grafica.
#include <conio.h>                               //
#include <stdlib.h>                              //
#include <stdio.h>                               //

   const
       TAMCUR = 3;                               // Tamanho do Cursor.

   int POSX = 0,                                 // Posicao inicial X.
       POSY = 0,                                 // Posicao inicial Y.
       PLIX = 0,                                 // Posicao inic. X da linha.
       PLIY = 0,                                 // Posicao inic. Y da linha.
       INC  = 9;                                 // Incremento inic. cursor.

   unsigned int SIZE;
   void *MENU;
   int CANESQ,                                   // canto esquerdo.
       CANINF;                                   // canto inferior.

   char ATIMENU  = 'N',
	DESLINHA = 'N',
	TECLA;

   void Inicializa();                            // Inicializa Modo grafico/Tela Inicial.
   void PosicaoCursor();                         // Janela Posicao Cursor.
   void Menu();                                  // Gerenciador Menus.
   void Cursor();                                // Movimentacao Cursor.


   int main(void)
   {
      Inicializa();
      Cursor();

      closegraph();                              // fecha o modo grafico.
      return 0;
   }

// ---------------- Inicializa ------------------
   void Inicializa()
   {
      int gdriver = DETECT, gmode, errorcode;    // Requisita auto-deteccao.
      initgraph(&gdriver, &gmode, "");           // Inicializa modo grafico.
      errorcode = graphresult();                 // Resultado da inicializacao.
      if (errorcode != grOk)                     // Ocorrencia erro inicializacao.
      {
	 printf("Erro grafico: %s\n", grapherrormsg(errorcode));
	 printf("Pressione uma tecla p/ sair:");
	 getch();
	 exit(1);                                // Returna c/ codigo erro.
      }
      rectangle(0, 9, getmaxx(), getmaxy()-11); // Area de desenho.
      bar(0, 0, getmaxx(), 9);
      moveto(02,01);
      outtext("Menu 1");
   }

// ---------------- PosicaoCursor ---------------
   void PosicaoCursor()
   {
      char MSG[10];
      int  MAXX = getmaxx(),
	   MAXY = getmaxy();

      moveto(POSX, POSY);
      sprintf(MSG, "%d, %d", getx(), gety());
      rectangle(0, getmaxy()-11 , 80, getmaxy());    // janela coordenadas.
      setviewport(1, getmaxy()-10, 79, getmaxy()-1, 0);
      clearviewport();
      setviewport(0, 0, MAXX, MAXY, 1);
      moveto(10, getmaxy()-9);
      outtext(MSG);
   }

// ---------------- LinhaUpDown ---------------
   void LinhaUpDown()
   {
      int  MAXX = getmaxx(),
	   MAXY = getmaxy();


      moveto(POSX, POSY);
      rectangle(getmaxx()-20, getmaxy()-11 , getmaxx(), getmaxy());
      setviewport(getmaxx()-19, getmaxy()-10, getmaxx()-1, getmaxy()-1, 0);
      clearviewport();
      setviewport(0, 0, MAXX, MAXY, 1);
      moveto(getmaxx()-12, getmaxy()-9);
      if (DESLINHA == 'N')
	 outtext(" ");
      else
	 if (TECLA == 'U')
	    outtext("U");
	 else
	    outtext("D");
   }

// ---------------- Menu ------------------------
   void Menu()
   {

      if (POSY < 10)
      {
	 if (ATIMENU == 'N')
	 {
	    if (POSX >= 0  && POSX < 106)              // Menu - 1.
	       {
		  CANESQ =   2;
		  CANINF =  80;
	       }
	    if (POSX >= 105 && POSX < 211)             // Menu - 2.
	       {
		  CANESQ = 107;
		  CANINF =  50;
	       }
	    if (POSX >= 210 && POSX < 316)             // Menu - 3.
	       {
		  CANESQ = 212;
		  CANINF = 110;
	       }
	    if (POSX >= 315 && POSX < 421)             // Menu - 4.
	       {
		  CANESQ = 317;
		  CANINF = 150;
	       }
	    if (POSX >= 420 && POSX < 526)             // Menu - 5.
	       {
		  CANESQ = 422;
		  CANINF =  50;
	       }
	    if (POSX >= 525 && POSX < getmaxx()-6)     // Menu - 6.
	       {
		  CANESQ = 527;
		  CANINF =  80;
	       }
	    bar(CANESQ, 10, CANESQ+100, CANINF);
	    SIZE = imagesize(CANESQ, 10, CANESQ+100, CANINF);
	    MENU = malloc(SIZE);
	    getimage(CANESQ, 10, CANESQ+100, CANINF, MENU);
	    ATIMENU = 'S';
	 }
      }
      else
	 if (ATIMENU == 'S')
	 {
	    putimage(CANESQ, 10, MENU, XOR_PUT);
	    free( MENU);
	    ATIMENU = 'N';
	 }
   }


// ---------------- Cursor ----------------------
   void Cursor()
   {
      int COR,
	  PLIX = 0,                                 // Posicao inic. X da linha.
	  PLIY = 0,                                 // Posicao inic. Y da linha.
	  PATX = 0,
	  PATY = 0;
      void *CURSOR;
      unsigned int SIZE;

      POSX = (getmaxx() / 2),                    // centraliza posicao X.
      POSY = (getmaxy() / 2);                    // centraliza posicao Y.

      bar(POSX, POSY, POSX+TAMCUR, POSY+TAMCUR);
      SIZE = imagesize(POSX, POSY, POSX+TAMCUR, POSY+TAMCUR);
      CURSOR = malloc(SIZE);
      getimage(POSX, POSY, POSX+TAMCUR, POSY+TAMCUR, CURSOR);
      PosicaoCursor();

      for (;;)
      {
	 TECLA = getch();
	 if (TECLA == 'd' || TECLA == 'D')
	 {
	    TECLA = 'D';
	    PLIX = PATX = POSX;
	    PLIY = PATY = POSY;
	    DESLINHA = 'S';
	 }
	 if (TECLA == '\r')
	    DESLINHA = 'N';
	 LinhaUpDown();
	 if (TECLA == '\x0')                     // Teclas Especiais.
	 {
	    if (ATIMENU == 'N')
	    {
	       putimage(POSX, POSY, CURSOR, XOR_PUT);
	    }
	    TECLA = getch();
	    switch (TECLA)
	    {
	       case 'H': if (POSY-INC > 0)                 // Seta p/ cima.
			     POSY -= INC;
			 else
			     POSY = getmaxy()-(11+TAMCUR);       // 10;
			 break;
	       case 'P': if (POSY+INC < getmaxy()-(11+TAMCUR))      // Seta p/ baixo.
			     POSY += INC;
			 else
			     POSY = 10;                    // getmaxy()-16;
			 break;
	       case 'K': if (POSX-INC > 0)                 // Seta p/ esquerda.
			     POSX -= INC;
			 else
			     POSX = getmaxx()-(1+TAMCUR);            // 0;
			 break;
	       case 'M': if (POSX+INC < getmaxx()-(1+TAMCUR))       // Seta p/ direita.
			     POSX += INC;
			 else
			     POSX = 0;                     // getmaxx()-7;
			 break;
	       case 'G': POSX = 0;                         // Tecla Home.
			 break;
	       case 'O': POSX = getmaxx()-(1+TAMCUR);               // Tecla Fim.
			 break;
	       case 'I': POSY = 10;                        // Tecla PU.
			 break;
	       case 'Q': POSY = getmaxy()-(11+TAMCUR);              // Tecla PD.
			 break;
	    }
	    Menu();
	    if (ATIMENU == 'N')
	       putimage(POSX, POSY, CURSOR, XOR_PUT);
	    PosicaoCursor();
	 }
	 if (DESLINHA == 'S')
	 {
	    COR = getcolor();
	    setcolor(0);
	    line( PLIX, PLIY, PATX, PATY);
	    setcolor(COR);
	    line( PLIX, PLIY, POSX, POSY);
	    PATX = POSX;
	    PATY = POSY;
	 }
	 switch (TECLA)
	    {
	       case '+' : if (INC < 50)                    // Incremento Passo.
			      INC += 2;
			  break;
	       case '-' : if (INC > 1)                     // Decremento Passo.
			      INC -= 2;
			  break;
	       case '\x1B' : closegraph();                 // Fecha o modo grafico.
			     exit(0);                      // Finaliza execucao.
	    }
      }
   }

// ----------------------------------------------
