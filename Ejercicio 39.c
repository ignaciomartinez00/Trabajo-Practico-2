/*EJERCICIO 39:

Hacer un programa que tome los datos de medición de potencia, cargados por el usuario, de un sistema de medición a distancia.

Los datos que cargará el usuario tienen la siguiente estructura:

    char desc[60];
    unsigned char potencia;
    unsigned int estado;

Donde estado es la multiplicación del valor ASCII de la primer letra de la descripción por la potencia.
Los datos cargados se deberán guardar en una lista ordenada, de mayor a menor, del valor de potencia.
Una vez finalizada la carga guardar los datos en un archivo de organización directa llamado "potencia.dat"
imprimiendo en pantalla los datos.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    char desc[60];
    unsigned char potencia;
    unsigned int estado;   /// ASCII(desc[0]*potencia)
}datos_t;

typedef struct
{
    char desc[60];
    unsigned char potencia;
    unsigned int estado;   /// ASCII(desc[0]*potencia)
    int pf;
}datos_t2;

struct lista
{
    datos_t dato;
    struct lista *l;
};
int  menu(void);

int main()
{
    int op;
    datos_t auxo;
    struct lista *p=NULL, *aux,*u,*r;
    unsigned int val; //Valor Ascii Letra
    int i=0,j,k;
    ///toma de datos  //tome los datos de medición de potencia, cargados por el usuario, de un sistema de medición a distancia.
    do
    {
        switch(menu())
        {

        case 1:
            aux=(struct lista*)malloc(sizeof(struct lista));
            if(aux)
            {

                printf("datos:\n");
        printf("ingrese potencia: ");
        scanf("%hhu",&aux->dato.potencia);
        printf("ingrese descripcion: ");
        fflush(stdin);
        scanf("%s",aux->dato.desc);
       (aux->dato.estado)=atoi(aux->dato.desc)*(aux->dato.potencia);   ///Donde estado es la multiplicación del valor ASCII de la primer letra de la descripción por la potencia.
        printf("descripcion:%s\t",aux->dato.desc);
        printf("estado:%d\n",aux->dato.estado);




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
                        if(strcmp(r->dato.potencia , aux->dato.potencia)==1)  ///si el dato del puntero r es mayor que el dato del puntero aux
                        {

                            aux->l=p;
                            p=aux;
                            break;
                        }

                        ///No es el primer lugar entonces busco en el resto 30:00
                        while(r->l!=0)  ///mientras el lazo del puntero no llegue al final
                        {
                            if(strcmp(r->dato.potencia , aux->dato.potencia)==-1)   ///si el dato del siguiente elemento del puntero r  es menor al dato del puntero aux
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
i=0;
    ///Una vez finalizada la carga guardar los datos en un archivo de organización directa llamado "potencia.dat" imprimiendo en pantalla los datos.
    FILE*fp;
    datos_t2 bf2;
    if((fp=fopen("potencia.dat","wb"))==NULL)
    {
        printf("no se puede crear/abrir archivo");
        return 0;
    }


           aux=p;
           fread(&bf2,sizeof(datos_t2),1,fp);
            while(aux)
            {

                    bf2.potencia=p->dato.potencia;
                    strcpy(bf2.desc,p->dato.desc);
                    bf2.estado=p->dato.estado;
                    bf2.pf=j;
                    bf2.pf=i;
                    i++;
                    fwrite(&bf2,sizeof(datos_t2),1,fp);
                    aux=p;
                    p=p->l;
                    free(aux);
                    aux=aux->l;
                    fread(&bf2,sizeof(datos_t2),1,fp);
            }
            system("pause");
    fclose(fp);
    break;

    case 2:
    ///imprimir
    if((fp=fopen("potencia.dat","rb"))==NULL)
    {
        printf("no se puede crear/abrir archivo");
        return 0;
    }
    printf("\n archivo directo\n");
    printf("potencia:         estado           descripcion\n");
    fread(&bf2,sizeof(datos_t2),1,fp);
     while(!feof(fp))
    {
            printf("%04d\t            %d\t             %s\n",bf2.pf,bf2.potencia,bf2.desc);
            fread(&bf2,sizeof(datos_t2),1,fp);
    }
    fclose(fp);
    system("pause");
    break;

        case 3:
            op=4;
            break;
        }
    }while(op!=4);
}

int menu(void)
{
    int op;
    system("cls");
    printf("\nMenu\n");
    printf("\n1-Agregar\n");
    printf("\n2-imprimir\n");
    printf("\n3-Salir\n");
    scanf("%d",&op);
    return op;
}
