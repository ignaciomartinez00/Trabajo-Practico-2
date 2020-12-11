/*
EJERCICIO 41:

El depósito de la empresa CosmeFulanito necesita cargar su stock de repuestos en forma ordenada.
Para dicha tarea se solicitó categorizar a los respuestos bajo la siguiente estructura de datos:

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   chat ubicacion[100];
}repuestos_t;
Los repuestos no están ordenados, se solicita cargarlos en una lista,
la cual ordene por descripción a los repuestos
para luego guardarlos en un archivo de stock con organización secuencial.

Imprimir en pantalla la lista con cada inserción.
El archivo se generará cuando el usuario decide no cargar mas productos.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int menu(void);


typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   char ubicacion[100];
}repuestos_t;

struct lista
{
    repuestos_t prod;//producto
    struct lista *l;
};


int main()
{
    int op;
    struct lista *p=NULL,*u=NULL, *aux,*r;
    repuestos_t valor;

    op=menu();
    while(op!=2)
    {
    ///lectura de datos
    ///se solicita cargarlos en una lista, la cual ordene por descripción a los repuestos
        printf("partNumber:");
        scanf("%ld",&valor.partNumber);
        printf("serialNumbre:");
        scanf("%ld",&valor.serialNumber);
        printf("Descripcion:");
        fflush(stdin);
        gets(valor.descripcion);
        printf("ubicacion:");
        fflush(stdin);
        gets(valor.ubicacion);
        op=menu();

            aux=(struct lista*)malloc(sizeof(struct lista));
            if(aux!=0)
            {
                aux->prod=valor;
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
                        if(strcmp(r->prod.descripcion,aux->prod.descripcion)==-1)
                        {
                           // printf("\n Primer lugar");
                           // system("pause");
                            aux->l=p;
                            p=aux;
                            break;
                        }

                        ///No es el primer lugar entonces busco en el resto 30:00
                        while(r->l!=0)  ///mientras el lazo del puntero no llegue al final
                        {
                            if(strcmp(r->l->prod.descripcion,aux->prod.descripcion)==-1)
                            {
                                r=r->l;
                            }
                            else break;  ///si el dato del siguiente elemento del puntero r es mayor  se rompe el mientras
                        }

                       /// si esta en el medio o es el ultimo
                        aux->l=r->l;
                        r->l=aux;
                        break;
                    }
                }
            }
    }

     aux=p;
    FILE *fp;
    repuestos_t bf;
    if((fp=fopen("archivo_de_stock","ab"))==NULL)
    {
        printf("no se puede abrir el archivo");
    }


                while(aux!=0)
                {
                    printf(" %s ",aux->prod.descripcion);
                    bf=aux->prod;
                    aux=aux->l;
                    fwrite(&bf,sizeof(struct lista),1,fp);
                }
               // printf("\n");
               // system("pause");
        fclose(fp);

    ///prueba
    if((fp=fopen("archivo_de_stock","rb"))==NULL)
    {
        printf("no se puede abrir el archivo");
    }
    fread(&bf,sizeof(struct lista),1,fp);
    while(!feof(fp))
    {


        if(bf.serialNumber&0b00100000&&bf.serialNumber&0b00001000&&bf.partNumber==1234)
        {
            aux=(struct lista*)malloc(sizeof(struct lista));
                if(aux)///sin abreviar if(aux!=0)
                {
                    printf("cola:\t");
                    aux->prod=bf;
                    if(p==NULL) p=u=aux;
                    else
                    {
                        u->l=aux;
                        u=aux;
                    }
                    u->l=NULL;
                }
                else printf("\n Memoria insuficiente\n");


        }

        printf("PartNumbre:%ld\t",bf.partNumber);
        printf("SerialNumber%ld\t",bf.serialNumber);
        printf("Descripcion:%s\t",bf.descripcion);
        printf("Ubicacion:%-20s",bf.ubicacion);
        printf("\n");
        fread(&bf,sizeof(struct lista),1,fp);
    }
    fclose(fp);

    ///se solicita cargarlos en una lista, la cual ordene por descripción a los repuestos
    return 0;
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
