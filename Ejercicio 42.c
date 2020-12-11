/*
EJERCICIO 42:

El proveedor de repuestos de CosmeFulanito informó que una partida de repuestos salió con falla y debe ser devuelta.
Para identificar la partida, el proveedor indicó que la falla fue en el partNumber: 1234
que tiene números de serie(SerialNumber) con el bit 3 y 5 en 1.

Para estas tareas se solicita:

Hacer una cola con todos los registros fallados
Realizar la baja física a todos los repuestos fallados
Crear un archivo donde se vuelque el contenido de la cola en orden inverso.
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


struct cola
{
    repuestos_t prod;//producto
    struct cola *izq;
    struct cola *der;
};


int main()
{
    struct cola *p=NULL,*u=NULL, *aux;
    FILE *fp,*fpn;
    repuestos_t bf,bf1;


    if((fp=fopen("archivo_de_stock","rb"))==NULL) printf("no se puede abrir el archivo");

    fread(&bf,sizeof(struct lista),1,fp);
    while(!feof(fp))
    {
   /*     printf("PartNumbre:%ld\t",bf.partNumber);
        printf("SerialNumber%ld\t",bf.serialNumber);
        printf("Descripcion:%s\t",bf.descripcion);
        printf("Ubicacion:%-20s",bf.ubicacion);
        printf("\n");*/
        if(bf.partNumber==1234) // el proveedor indicó que la falla fue en el partNumber: 1234


        {

        if(bf.serialNumber&0b00100000&&bf.serialNumber&0b00001000)//if(bf.serialNumber&0b00100000&&bf.serialNumber&0b00001000&&bf.partNumber==1234) //que tiene números de serie(SerialNumber) con el bit 3 y 5 en 1.
        {
            printf("fallado\n");
            aux=(struct cola*)malloc(sizeof(struct cola));//Hacer una cola con todos los registros fallados
            aux->prod=bf;

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
        else //Realizar la baja física a todos los repuestos fallados
        {
            if((fpn=fopen("narchivo_de_stock","ab"))==NULL) printf("no se puede abrir el archivo");
            bf1=bf;
            fwrite(&bf1,sizeof(struct lista),1,fpn);
            printf("NO fallado\n");
            fclose(fpn);
        }

        }

        fread(&bf,sizeof(struct lista),1,fp);
    }
    system("pause");
    fclose(fp);



    if((fpn=fopen("narchivo_de_stock","rb"))==NULL) printf("no se puede abrir el archivo");

    fread(&bf1,sizeof(struct lista),1,fpn);
    while(!feof(fp))
    {
        printf("PartNumbre:%ld\t",bf.partNumber);
        printf("SerialNumber%ld\t",bf.serialNumber);
        printf("Descripcion:%s\t",bf.descripcion);
        printf("Ubicacion:%-20s",bf.ubicacion);
        printf("\n");
        fread(&bf1,sizeof(struct lista),1,fpn);
    }
    fclose(fpn);

    if(remove("archivo_de_stock"))//==1
    {
        printf("\n error no se puede eliminar\n");

    }

    if(rename("narchivo_de_stock","archivo_de_stock")) //nalumnos se va a llamar alumnos.dat
    {
        printf("\n error no se puede renombrar\n");
    }

    //imprimir al reves


    printf("\n en archivo\n");
    if((fp=fopen("archivo_de_fallas","wb"))==NULL)  printf("no se puede abrir el archivo");//Crear un archivo donde se vuelque el contenido de la cola en orden inverso.
     aux=u;
    while(aux)
    {
        fread(&bf,sizeof(struct lista),1,fp);
        printf("PartNumbre:%ld\t",bf.partNumber);
        printf("SerialNumber%ld\t",bf.serialNumber);
        printf("Descripcion:%s\t",bf.descripcion);
        printf("Ubicacion:%-20s",bf.ubicacion);
        printf("\n");
        bf=aux->prod;
        aux=aux->izq;
        fwrite(&bf,sizeof(struct lista),1,fp);
    }
    fclose(fp);

return 0;
}
