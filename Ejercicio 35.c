/*
EJERCICIO 35:
Hacer un programa que tome los datos de contacto de una persona
(Nombre, Apellido, edad, teléfono, mail) y los cargue, en forma directa,
 en una pila de memoria dinámica.
  Imprimir en pantalla y cargar(dar de alta) en un archivo llamado "contactos.dat", de organización secuencial,
  los registros ingresados por el usuario si la persona tiene una edad mayor a 21 años.
  */

  /* IDEAS
  la clave primaria puede ser o el telefono o el mail

  pasaje por referencia para usar funciones
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

void alta(datos_t);
void listar(FILE *,char * n);
void consulta(void);

struct pila
{
    datos_t dato;
    struct pila *l;
};


int menu(void);
datos_t carga_datos(void);

int main()
{
    int op;
    datos_t datos;
    struct pila *p=NULL, *aux;
    do
    {
        switch(menu())
        {

        case 1:///apilar
                aux=(struct pila*)malloc(sizeof(struct pila));
                if(aux)
                {
                      aux->dato=carga_datos();
                      printf("\nresultados\n nombre \n");
                      fflush(stdin);
                      puts(aux->dato.nombre);
                      printf("apellido:");
                      fflush(stdin);
                      puts(aux->dato.apellido);
                      printf("\nedad %d\n",aux->dato.edad);
                      printf("telefono:");
                      fflush(stdin);
                      puts(aux->dato.telefono);
                      printf("mail:");
                      fflush(stdin);
                      puts(aux->dato.mail);
                      system("pause");
                      //alta(aux->dato); ///cargar(dar de alta) en un archivo llamado "contactos.dat", de organización secuencial,  los registros ingresados por el usuario si la persona tiene una edad mayor a 21 años.
                      //listar(stdout,"alumnos.dat");
                      //system("pause");
                      aux->l=p;
                      p=aux;
                }
                else printf("\n Memoria insuficiente\n");
                system("pause");
                break;
                //fin del guardado
        case 2:
                while(p)
                {
                    printf("%s\n",p->dato.apellido);
    datos_t bf;
    FILE *fp;
    int legajo;
    fflush(stdin);
    datos_t dato;
    dato=p->dato;

    if((fp=fopen("contactos.dat","ab+"))==NULL)
    {
        printf("no se puede abrir el archivo alumnos.dat\n");
        system("pause");
        //return;
    }
    system("cls");
    fflush(stdin);

    fread(&bf,sizeof(datos_t),1,fp);
    while(!feof(fp))  //preguntamos si no es fin de archivo (clase 8)
    {
        if(strcmp(bf.telefono,dato.telefono)==0)
        {

            printf("Este legajo ya fue dado de alta \n");
            system("pause");
            fclose(fp);
            //return;
        }
        fread(&bf,sizeof(datos_t),1,fp);
    }

    if(dato.edad>=21)
    {
        strcpy(bf.nombre,dato.nombre);
        strcpy(bf.apellido,dato.apellido);
        bf.edad=dato.edad;

        strcpy(bf.telefono,dato.telefono);
        strcpy(bf.mail,dato.mail);
    ///guardado
    fwrite(&bf,sizeof(datos_t),1,fp);
    }
    else printf("\n tiene menos de 21 años ,por lo tanto no sera cargado el registro\n");
    system("pause");
    fclose(fp);
                    aux=p;
                    p=p->l;/// o p=aux->1;
                    free(aux); ///si pongo free(p) me borra el elemento en el que estoy parado ahora, osea el siguiente
                    //system("pause");
                }

               // else printf("\n pila vacia\n");
               // system("pause");
            listar(stdout,"alumnos.dat");
            break;

        case 3:op=4;
            break;
        }
    }while(op!=4);
    return 0;
}



int menu(void)
{
    int op;
    system("cls");
    printf("\nMenu\n");
    printf("\n1-Apilar\n");
    printf("\n2-ver listado\n");
    printf("\n3-Salir\n");
    scanf("%d",&op);
    return op;
}


datos_t carga_datos(void)  ///cargue, en forma directa, en una pila de memoria dinámica.
{
    struct pila *aux;
    datos_t valor;
    aux=(struct pila*)malloc(sizeof(struct pila));
    printf("n Dato a apilar:\n");

    fflush(stdin);
    printf("nombre:");
    gets(aux->dato.nombre);
    strcpy(valor.nombre,aux->dato.nombre);

    fflush(stdin);
    printf("apellido:");
    gets(aux->dato.apellido);
    strcpy(valor.apellido,aux->dato.apellido);


    printf("edad:");
    scanf("%d",&aux->dato.edad);
    valor.edad=aux->dato.edad;

    fflush(stdin);
    printf("telefono:");
    gets(aux->dato.telefono);
    strcpy(valor.telefono,aux->dato.telefono);

    fflush(stdin);
    printf("mail:");
    gets(aux->dato.mail);
    strcpy(valor.mail,aux->dato.mail);
    system("pause");
    system("cls");

    return valor;
}



void alta(datos_t dato)
{
    datos_t bf;
    FILE *fp;
    int legajo;
    fflush(stdin);

    if((fp=fopen("contactos.dat","ab+"))==NULL)
    {
        printf("no se puede abrir el archivo alumnos.dat\n");
        system("pause");
        return;
    }
    system("cls");
    fflush(stdin);

    fread(&bf,sizeof(datos_t),1,fp);
    while(!feof(fp))  //preguntamos si no es fin de archivo (clase 8)
    {
        if(strcmp(bf.telefono,dato.telefono)==0)
        {
            printf("Este legajo ya fue dado de alta \n");
            system("pause");
            fclose(fp);
            return;
        }
        fread(&bf,sizeof(datos_t),1,fp);
    }

    if(dato.edad>=21)
    {
        strcpy(bf.nombre,dato.nombre);
        strcpy(bf.apellido,dato.apellido);
        bf.edad=dato.edad;
        strcpy(bf.telefono,dato.telefono);
        strcpy(bf.mail,dato.mail);
    ///guardado
    fwrite(&bf,sizeof(datos_t),1,fp);
    }
    else printf("\n tiene menos de 21 años ,por lo tanto no sera cargado el registro\n");
    system("pause");
    fclose(fp);
}

void listar(FILE *fps,char* n)
{
    datos_t bf;
    FILE *fp;
    if((fp=fopen("contactos.dat","rb"))==NULL)
    {
        printf("no existe archivo.\n");
        system("PAUSE");
        return;
    }
    system("cls");
    fread(&bf,sizeof(datos_t),1,fp);
    fprintf(fps,"\n *** Listado de Alumnos ***\n\n");
    fprintf(fps,"Nombre.\t                   Apellido\t            Edad\t           telefono\t           mail\n");
    fprintf(fps,"-------------------------------------------------------------------------------------------------------------------\n");

    while(!feof(fp))
    {
        fprintf(fps,"%-20s\t     %-20s    %-20d  %-20s    %-20s\n",bf.nombre,bf.apellido,bf.edad,bf.telefono,bf.mail);
        fread(&bf,sizeof(datos_t),1,fp);
    }
    system("pause");
    system("cls");
    fclose(fp);
}

/*
void consulta(void)
{
    datos_t bf;
    FILE *fp;
    int legajo,esta=0;
    fp=fopen("contactos.dat","rb");
    printf("ingrese legajo:");

    fread(&bf,sizeof(datos_t),1,fp);
    while(!feof(fp))  //preguntamos si no es fin de archivo (clase 8)
    {
         if(bf.edad>=21)
         {

                printf("legajo.       Apellido       Nombre          Fecha.\n");
                printf("-------------------------------------------------------\n");
                printf("%s\t     %-20s    %d  %s    %s\n",bf.nombre,bf.apellido,bf.edad,bf.telefono,bf.mail);
         }

        fread(&bf,sizeof(datos_t),1,fp);
    }//estoy en el final del archivo

    if(!esta)
    {
        printf("\n*** No se encontro el legajo ***\n");
    }

    system("pause");
    system("cls");
    fclose(fp);
}
*/
