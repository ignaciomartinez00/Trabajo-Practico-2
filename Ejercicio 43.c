/*
EJERCICIO 43:

El servicio técnico de CosmeFulanito recibe órdenes de trabajo diarias.
Las mismas son cargadas en un archivo secuencial por el personal de recepción
bajo la siguiente estructura de datos:

typedef struct{
   long numeroDeOrden;
   char cliente[40];
   char descripciondeFalla[200];
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos_t;
Se pide:

Hacer una pila con las órdenes de trabajo de forma tal que
la más vieja sea la última en cargarse.
*/

//guarda primero en una lista y dsp lo guarda un pila ya ordenados

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int menu(void);

typedef struct{
   long numeroDeOrden;
   char cliente[40];
   char descripciondeFalla[200];
   char modelo[65];
   char fecha[10];///AAAAMMDD
   char hora[10];
}repuestos_t;

struct pila
{
    repuestos_t orden;///producto
    struct pila *l;
};

int main()
{
    FILE *fp;
    repuestos_t bf;
    int op;
    struct pila *p=NULL,*aux=NULL,*u,*r;

    if((fp=fopen("trabajo.dat","rb"))==NULL)
    {
        printf("no se puede abrir el archivo");
    }

    fread(&bf,sizeof(repuestos_t),1,fp);
    while(!feof(fp))
    {
        aux=(struct pila*)malloc(sizeof(struct pila));
        if(aux)
                {
                        aux->orden=bf;

                        if(p==NULL)
                {
                    p=u=aux;
                    u->l=NULL;
                }
                else
                {
                    r=p;
                    while(1)
                    {
                        if(strcmp(r->orden.fecha , aux->orden.fecha)==1)  ///si el dato del puntero r es mayor que el dato del puntero aux ///si le cambio el > por < y modifico otra linea con los siguientes sea hace de mayor a menor
                        {
                            aux->l=p;
                            p=aux;
                            break;
                        }

                        while(r->l!=0)  ///mientras el lazo del puntero no llegue al final
                        {
                            if(strcmp(r->l->orden.fecha , aux->orden.fecha)==-1)   ///si el dato del siguiente elemento del puntero r  es menor al dato del puntero aux//ESTA LINEA
                            {
                                r=r->l;  ///r es igual al siguiente
                            }
                            else break;  ///si el dato del siguiente elemento del puntero r es mayor  se rompe el mientras
                        }
                        aux->l=r->l;
                        r->l=aux;
                        break;
                    }
                }
                }
        else printf("\n Memoria insuficiente\n");
        fread(&bf,sizeof(repuestos_t),1,fp);
    }
    fclose(fp);


   // printf("\ndesapilar\n");
    aux=p;

        while(p)
                {
                  //  printf("\n dato desapilado: %s\n", aux->orden.fecha);                  //  aux=p;
                    p=p->l;/// o p=aux->1;
                    if(p==NULL)break;
                    aux=p;
                    free(aux);
                }

}

int menu(void)
{
    int op;
    system("cls");
    printf("\nMenu\n");
    printf("\n1-cargar producto\n");
    printf("\n2-salir\n");
    scanf("%d",&op);
    return op;
}
