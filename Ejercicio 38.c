/*
EJERCICIO 38:

Hacer una cola con los valores muestreados de un cuarto de ciclo de una señal sinusoidal,
en 8 bits, para luego recorrerla y recomponer la señal completa. Las muetras deberán ir de
127 a -127 utilizando el bit más significativo en 1 para los valores negativos y
en 0 para los valores positivos. Imprimir en pantalla los valores.

*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct cola
{
    char d;
    struct cola *der;
    struct cola *izq;
};

int main()
{
    int x;
    int op=1,i;
    struct cola *p=NULL,*u=NULL, *aux;


   for(x=0; x<91; x=x+5)  ///Hacer una cola con los valores muestreados de un cuarto de ciclo de una señal sinusoidal
        {
                aux=(struct cola*)malloc(sizeof(struct cola));
                aux->d= (char)((double)127.0*sin((double)x*3.141592/180));
                //printf("%d\t",aux->d);
                if(!p)
                {
                    p=u=aux;
                    p->izq=NULL;
                    p->der=NULL;
                }
                else
                {
                   aux->der=NULL;
                   aux->izq=u;
                    u->der=aux;
                    u=aux;
                }
        }


          aux=p;
          for(x=0; x<85; x=x+5)
          {
              printf("%d\n",aux->d);
              aux=aux->der;
          }

          aux=u;
          aux=aux->izq;
          for(x=0; x<85; x=x+5)
          {
              printf("%d\n",aux->d);
              aux=aux->izq;

          }

          aux=p;
          for(x=0; x<85; x=x+5)
          {
              printf("%d\n",aux->d|0b10000000);
              aux=aux->der;
          }

          aux=u;
          aux=aux->izq;
          for(x=0; x<85; x=x+5)
          {
              printf("%d\n",aux->d|0b10000000);
              aux=aux->izq;

          }
    system("pause");
    return 0;
}
