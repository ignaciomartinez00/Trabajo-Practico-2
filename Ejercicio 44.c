/*
EJERCICIO 44:

El servicio técnico utiliza la pila generada en el ejercicio 43 en su labor diaria.
Cada técnico toma una tarea de la pila y genera un orden de extracción de repuestos al depósito. Para optimizar los viajes al depósito se arma una lista con los repuestos que cada orden necesita utilizando la siguiente estructura:

typedef struct{
    repuestos_t repuesto;
    int cantidad;
}extraccionRepuestos_t;

Se pide cargar la lista de repuestos solicitados por los técnicos.
Tener en cuenta que varios técnicos pueden necesitar la misma parte,
y en esos casos se debe incrementar la cantidad pedida en la lista.
*/

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
}orden_t;

struct pila
{
    orden_t orden;///producto
    struct pila *l;
};

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   char ubicacion[100];
}repuestos_t;


typedef struct{
    repuestos_t repuesto;
    int cantidad;
}extraccionRepuestos_t;

struct lista
{
    extraccionRepuestos_t dato;
    struct lista *l;
};

int main()
{
    FILE *fp;
    orden_t bf;
    int op,cont=0;
    struct pila *p=NULL,*aux=NULL,*u,*r;
    struct lista *pl=NULL, *ul, *auxl=NULL, *rl;


    if((fp=fopen("trabajo.dat","rb"))==NULL)
    {
        printf("no se puede abrir el archivo");
    }

    fread(&bf,sizeof(orden_t),1,fp);
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
        fread(&bf,sizeof(orden_t),1,fp);
    }
    fclose(fp);



        printf("\nPresione una tecla para tomar la tarea mas antigua");
        aux=p;
        p=p->l;
        printf("\nNum Orden: %d",aux->orden.numeroDeOrden);
        printf("\nCliente: %s",aux->orden.cliente);
        printf("\nDescripcion de falla; %s",aux->orden.descripciondeFalla);
        printf("\nModelo: %s",aux->orden.modelo);
        printf("\nFecha: %s",aux->orden.fecha);
        printf("\nHora: %s",aux->orden.hora);
        free(aux);
        auxl=(struct lista*)malloc(sizeof(struct lista));
        printf("\n\nPartNumber del repuesto solicitado: ");
        scanf("%d",&auxl->dato.repuesto.partNumber);
        printf("\nCuantos repuestos necesita?\t");
        scanf("%d",&auxl->dato.cantidad);


        if(!pl) pl=auxl;
        rl=pl;
        if(pl->dato.repuesto.partNumber==auxl->dato.repuesto.partNumber){
                pl->dato.cantidad= pl->dato.cantidad + auxl->dato.cantidad;
                cont=1;
        }
        while(rl->l && cont==0){

            if(rl->l->dato.repuesto.partNumber==auxl->dato.repuesto.partNumber){
                rl->l->dato.cantidad=rl->dato.cantidad+auxl->dato.cantidad;
                cont=1;
            }else r=r->l;
        }
        if(cont=0){
            ul->l=auxl;
            ul=auxl;
            ul->l=NULL;
        }

    return 0;
}


