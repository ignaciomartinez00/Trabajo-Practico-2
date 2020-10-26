/*EJERCICIO 36:

Hacer un programa que lea al archivo "contactos.dat" creado en el Ejercicio 35
y crear una lista, en memoria din�mica, ordenada alfab�ticamente.

Una vez creada la lista guardarla en un archivo de organizaci�n directa
llamado "contactos_ordenados.dat" imprimiendola en pantalla.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    char nombre[30];
    char apellido[30];
    int edad;
    char telefono[15];
    char mail[50];
}datos_t;

typedef struct
{
    char nombre[30];
    char apellido[30];
    int edad;
    char telefono[15];
    char mail[50];
    int pf; //Posicion Fisica
}datos_t2;

void alta(datos_t);
void listar(FILE *,char * n);
void consulta(void);

struct cola
{
    datos_t dato;
    struct cola *l;
};

int menu(void);
datos_t carga_datos(void);

int main()
{
    int op,i=0,j,k,id;
    datos_t ordenar[100];
    datos_t datos;
    datos_t auxo;//auxiliar para ordenar
    struct cola *p=NULL, *aux,*u;
    datos_t bf;
    FILE *fp;
    ///RECUPERO DATOS   lea al archivo "contactos.dat" creado en el Ejercicio 35
    fp=fopen("contactos.dat","rb");
    fread(&bf,sizeof(datos_t),1,fp);

    while(!feof(fp))
    {
         ordenar[i]=bf;
         i++;
         fread(&bf,sizeof(datos_t),1,fp);
    }
    fclose(fp);
///FIN DE RECUPERACION DE DATOS

///ORDEN ALFABETICO
    for(j=0;j<i-1;j++)
    {
        for(k=j+1;k<i;k++)
        {
            if(strcmp(ordenar[j].apellido,ordenar[k].apellido)==1)
            {
                auxo=ordenar[k];
                ordenar[k]=ordenar[j];
                ordenar[j]=auxo;
            }
        }
    }
///FIN ORDEN ALFABETICO

///GUARDADO EN LISTA  crear una lista, en memoria din�mica, ordenada alfab�ticamente.
//printf("lista:\n");
for(j=0;j<i;j++)
{
                aux=(struct cola*)malloc(sizeof(struct cola));
                if(aux)///sin abreviar if(aux!=0)
                {
                    aux->dato=ordenar[j];
              //      printf("%s\t     %-20s    %04d            %-20s    %-20s     \n",aux->dato.nombre,aux->dato.apellido,aux->dato.edad,aux->dato.telefono,aux->dato.mail);
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
//system("pause");

   ///lista guardarla en un archivo de organizaci�n directa llamado "contactos_ordenados.dat"
   ///GUARDADO
   printf("imprimir:\nApellido:    Nombre:                 Edad:           Telefono:               Mail:              Posicion Fisica:\n");

    datos_t2 bf2;
    if((fp=fopen("contactos_ordenados.dat","ab"))==NULL)
    {
        printf("no se puede crear/abrir archivo");
        return 0;
    }
    j=0;
    while(p)
       {
        if(p)
        {
        strcpy(bf2.nombre,p->dato.nombre);
        strcpy(bf2.apellido,p->dato.apellido);
        bf2.edad=p->dato.edad;
        strcpy(bf2.telefono,p->dato.telefono);
        strcpy(bf2.mail,p->dato.mail);
        printf("%s\t     %-20s    %04d            %-20s    %-20s     %d\n",bf2.apellido,bf2.nombre,bf2.edad,bf2.telefono,bf2.mail,bf2.pf);
        j++;
        bf2.pf=j;
        fwrite(&bf2,sizeof(datos_t2),1,fp);
        aux=p;
        p=p->l;
        free(aux);
        }
        else printf("\n pila vacia\n");
       }
    fclose(fp);
    return 0;
}
