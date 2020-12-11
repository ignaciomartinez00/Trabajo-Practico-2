/*EJERCICIO 36:

Hacer un programa que lea al archivo "contactos.dat" creado en el Ejercicio 35
y crear una lista, en memoria dinámica, ordenada alfabéticamente.

Una vez creada la lista guardarla en un archivo de organización directa
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

struct lista
{
    datos_t dato;
    struct lista *l;
};

int menu(void);
datos_t carga_datos(void);

int main()
{
    int op,i=0,j,k,id;
    datos_t datos;
    datos_t auxo;//auxiliar para ordenar
    struct lista *p=NULL,*u=NULL, *aux,*r;
    datos_t bf;
    FILE *fp;
    ///RECUPERO DATOS   lea al archivo "contactos.dat" creado en el Ejercicio 35
    fp=fopen("contactos.dat","rb");
    fread(&bf,sizeof(datos_t),1,fp);

    while(!feof(fp))
    {
         aux=(struct lista*)malloc(sizeof(struct lista));
            if(aux)
            {
                aux->dato=bf;
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
                        if(strcmp(r->dato.apellido,aux->dato.apellido)==1)  ///si el dato del puntero r es mayor que el dato del puntero aux
                        {
                            aux->l=p;
                            p=aux;
                            break;
                        }

                        while(r->l!=0)  ///mientras el lazo del puntero no llegue al final
                        {
                            if(strcmp(r->l->dato.apellido,aux->dato.apellido)==-1)   ///si el dato del siguiente elemento del puntero r  es menor al dato del puntero aux
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
         fread(&bf,sizeof(datos_t),1,fp);
    }
    fclose(fp);
///FIN DE RECUPERACION DE DATOS


   ///lista guardarla en un archivo de organización directa llamado "contactos_ordenados.dat"
   ///GUARDADO
    datos_t2 bf2;
    if((fp=fopen("contactos_ordenados.dat","wb"))==NULL)
    {
        printf("no se puede crear/abrir archivo");
        return 0;
    }
    j=0;
             aux=p;
            while(aux)
            {
                strcpy(bf2.nombre,aux->dato.nombre);
                strcpy(bf2.apellido,aux->dato.apellido);
                bf2.edad=aux->dato.edad;
                strcpy(bf2.telefono,aux->dato.telefono);
                strcpy(bf2.mail,aux->dato.mail);
                printf("%s\t     %-20s    %04d            %-20s    %-20s     %d\n",bf2.apellido,bf2.nombre,bf2.edad,bf2.telefono,bf2.mail,bf2.pf);
                j++;
                bf2.pf=j;
                fwrite(&bf2,sizeof(datos_t2),1,fp);

                aux=aux->l;
            }
 fclose(fp);

    return 0;
}
