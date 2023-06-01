{ Programa verifica o n£mero m ximo de segmentos possiveis de serem
     armazenados em 640 Kbytes.                                     }
 
#include <stdio.h>
#include <stdlib.h>
#include <alloc.h>
 
struct segmentos
{
   float x1, y1, x2, y2;
   struct segmentos *proximo;
};
 
void main (void)
{
 int i = 0;
 struct segmentos *prim_seg, *seg, *seg_ant;
 
 /* aloca segmentos ate o limite da memoria */
 
 prim_seg = calloc(1,sizeof(struct segmentos));
 seg_ant = prim_seg;
 while ( (seg = calloc(1,sizeof(struct segmentos))) != NULL )
 {
   i+= 1;
   seg_ant->proximo = seg;
 }
 printf ("\n estourou em %d ", i);
 
/* desaloca os segmentos */
 
 seg_ant = prim_seg;
 seg = prim_seg->proximo;
 while ( seg != NULL )
 {
   free(seg_ant);
   seg_ant = seg;
   seg = seg->proximo;
 }
 
}
