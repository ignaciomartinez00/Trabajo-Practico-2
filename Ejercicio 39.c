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

struct cola
{
    datos_t dato;
    struct cola *l;
};
int  menu(void);

int main()
{
    int op;
    datos_t dato[100],auxo;
    struct cola *p=NULL, *aux,*u;
    unsigned int val; //Valor Ascii Letra
    int i=0,j,k;
    ///toma de datos  //tome los datos de medición de potencia, cargados por el usuario, de un sistema de medición a distancia.
    do
    {
        switch(menu())
        {
        case 1:
        printf("datos:\n");
        printf("ingrese potencia: ");
        fflush(stdin);
        scanf("%hhu",&dato[i].potencia);
        printf("ingrese descripcion: ");
        fflush(stdin);
        scanf("%s",(dato[i].desc));
        val=dato[i].desc[0];
        printf("\nvalor:%d\t",val);
        (dato[i].estado)=val*dato[i].potencia;   ///Donde estado es la multiplicación del valor ASCII de la primer letra de la descripción por la potencia.
        printf("descripcion:%s\t",dato[i].desc);
        printf("estado:%d\n",dato[i].estado);
        i++;
   ///ORDEN mayor a menor
    for(j=0;j<i-1;j++)
    {
        for(k=j+1;k<i;k++)
        {
            if(((dato[j].potencia))<((dato[k].potencia)))  //es al reves porque dsp en la lista es LIFO??
            {
                auxo=dato[k];
                dato[k]=dato[j];
                dato[j]=auxo;
            }
        }
    }

    ///CARGA EN LISTA  Los datos cargados se deberán guardar en una lista ordenada, de mayor a menor, del valor de potencia.
    printf("\nRevision\n");
    for(j=0;j<i;j++)
{
                aux=(struct cola*)malloc(sizeof(struct cola));
                if(aux)///sin abreviar if(aux!=0)
                {
                    aux->dato=dato[j];
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

    ///Una vez finalizada la carga guardar los datos en un archivo de organización directa llamado "potencia.dat" imprimiendo en pantalla los datos.
    FILE*fp;
    datos_t2 bf2;
    if((fp=fopen("potencia.dat","wb"))==NULL)
    {
        printf("no se puede crear/abrir archivo");
        return 0;
    }
    for(j=0;j<i;j++)
    {
       if(p)
                {
                    bf2.potencia=p->dato.potencia;
                    strcpy(bf2.desc,p->dato.desc);
                    bf2.estado=p->dato.estado;
                    bf2.pf=j;
                    fwrite(&bf2,sizeof(datos_t2),1,fp);
                    aux=p;
                    p=p->l;
                    free(aux);
                }
    }
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

