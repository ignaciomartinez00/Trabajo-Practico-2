/*
EJERCICIO 45:

La lista creada en el ejercicio 44 es procesada por el depósito.
Para dicha tarea se pide hacer un programa que:

Descuente las cantidades solicitadas del archivo de stock, creado en el Ejercicio 41.
Hacer una cola con los repuestos en los que no se encontró stock suficiente
para poder notificar a los clientes la demora de la reparación.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   char ubicacion[100];
   char estado;  //(baja o alta)
}repuestos_t;

typedef struct{
    repuestos_t repuesto;
    int cantidad;
}extraccionRepuestos_t;

struct cola{
    long partNumber;
    struct cola *l;
};

//de la lista anterior
struct lista{
    extraccionRepuestos_t datos;
    struct lista *l;
};

int main()
{
    struct lista *pl, *ul, *auxl, *rl;
    struct cola *p=NULL, *u=NULL, *aux;
    FILE *fp;
    repuestos_t bf;
    int contl;
    int cant=0;

    if(fp=fopen("stock_cosmefulanito.dat","rb+")==0){
        printf("\n No se puede abrir el archivo ");
        return 0;
    }

    auxl=pl;
    fread(&bf,sizeof(repuestos_t),1,fp);
    while(!feof(fp))
        {
        if(auxl->datos.repuesto.partNumber==bf.partNumber){
            bf.estado='B';
            fseek(fp,-1L*sizeof(repuestos_t),1);
            fwrite(&bf,sizeof(repuestos_t),1,fp);
            cant++;
        }
        if(cant<=auxl->datos.cantidad) contl=1;

        fread(&bf,sizeof(repuestos_t),1,fp);
    }
    fclose(fp);

    if(contl != 1){
        aux=(struct lista*)malloc(sizeof(struct lista));
        aux->partNumber=auxl->datos.repuesto.partNumber;

        free(auxl);

        if(!p) p=u=aux;
        else{
            u->l=aux;
            u=aux;
            u->l=NULL;
        }
    }

    return 0;
}
