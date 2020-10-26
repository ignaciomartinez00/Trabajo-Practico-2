/*
EJERCICIO 37:
Existe un archivo llamado "datos.dat", de tipo binario, cuya organización es secuencial.
Los datos están organizados según la siguiente estructura:
Se Pide: Realizar una funciún que pase como parámetro la clave, entre otros parámetros, y
apile dos valores, la Clave y su posición física respecto al archivo (registro 1, 2, etc),
si es que el campo tipo tiene el bit 4 con valor 1.
En caso de no encontrarlo mostrar por pantalla "Registro no encontrado".
La función debe devolver el puntero de pila.
Realizar el main con varias llamadas a dicha función y
proceder a mostrar las descripciones del archivo,
 mediante la pila como acceso directo,
 NO USAR VARIABLES GLOBALES.
 */
#include<stdio.h>
#include<stdlib.h>

struct d
{
long clave; //Clave o Id del registro
char d[30]; // Descripcion
unsigned char tipo; //Tipo de datos como entero sin signo
char b; //'A':Alta 'B':Baja
};

struct pila
{
    long clave;
    int pf;
    struct pila *l;
};

typedef struct
{
    struct pila *p;
    struct pila *aux;
}punteros;

struct pila* funcion(long ,unsigned char,struct pila**,int*);
int menu(void);

 int main()
 {
     int i=0,cont=0,op=0;
     long clave;
     unsigned char tipo;
     struct pila *p,*aux;
         p=NULL;
         do
         {
         switch(menu())
         {
         case 1:
             printf("clave:");
             scanf("%ld",&clave);
             printf("tipo:");
             scanf("%hhu",&tipo);
             p=funcion(clave,tipo,&p,&cont);
             i++;
             break;
         case 2:
            op=4;
            break;
         case 3:
           while(p)
                {
                    printf("\n posicion fisica: %d\t", p->pf);
                    printf("clave: %ld", p->clave);
                    aux=p;
                    p=p->l;
                    free(aux);
                }
                break;
            }
         }while(op!=4);
     return 0;
 }

 int menu(void)
{
    int op;
    system("cls");
    printf("Menu\n");
    printf("1-Ingresar datos\n");
    printf("2-Salir\n");
    scanf("%d",&op);
    system("cls");
    return op;
}

 struct pila* funcion(long clave,unsigned char tipo,struct pila**p,int *cont) //apilar clave y posicion fisica
 {
     struct pila *aux;
     int i=0;
     struct d bf;
     FILE *fp;
     if(tipo&0b0010000)///si es que el campo tipo tiene el bit 4 con valor 1.
     {
         ///RECUPERO DATOS
         if((fp=fopen("datos.dat","rb"))==NULL)
         {
             printf("\nNo se pudo abrir el archivo datos.dat\n");
             system("pause");
             return 0;
         }
         fread(&bf,sizeof(struct d),1,fp);

         while(feof(fp)!=0)
         {
         if(bf.b=='A')
         {
         if(bf.clave==clave)
         {
             aux=(struct pila*)malloc(sizeof(struct pila));///  apile dos valores
             aux->clave=bf.clave;  ///la Clave
             aux->pf=*cont;         ///su posición física
             aux->l=*p;
             *p=aux;
             i++;
             *cont=*cont+i;
             printf("%d",*cont);
             break;
         }
         }
         else printf("este registro fue dado de baja\n");
        fread(&bf,sizeof(struct d),1,fp);
        }
        printf("Registro no encontrado\n");
        fclose(fp);
     }
     system("pause");
     return *p;
 }
