/*EJERCICIO 40:

Utilizando el archivo “potencia.dat” creado en el Ejercicio 39,
realizar una función que pase como parámetro, entre otros datos, la clave del registro (id).

La función ubicará el registro correspondiente al id pasado como parámetro,
y utilizando punteros imprimirá la primera palabra del campo "desc" en forma inversa,
 además cambiará el estado del bit 3 para luego actualizar el archivo.
 Además, se agregará a una pila la potencia cuando los bits 0 y 2,
 del campo estado, estén encendidos,
 en caso contrario se agregará el registro al archivo “salida.dat” de organización secuencial
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    char desc[60];
    unsigned char potencia;
    unsigned int estado;   /// ASCII(desc[0]*potencia)
    int pf;
}datos_t2;

typedef struct
{
    unsigned char potencia;
}salida;

struct pila
{
    unsigned char dato;
    struct pila *l;
};

int funcion(int,struct pila**);
int menu(void);

int main()
{
    int id,op=0;
    struct pila *p=NULL,*aux;
    FILE *fp;
    salida bf;
    datos_t2 bf2;
    do
    {
     switch(menu())
     {
        case 1:
        printf("ingrese ID:");
        scanf("%d",&id);
        funcion(id,&p);
        system("pause");
        system("cls");
        break;

        case 2:
            op=5;
        break;

        case 3:
            while(p)//si p es distinto de NULL(osea 0)
                {
                    aux=p;
                    printf("%hhu\n",aux->dato);
                    p=p->l;/// o p=aux->1;
                    free(aux); ///si pongo free(p) me borra el elemento en el que estoy parado ahora, osea el siguiente
                }
                system("pause");
        break;

        case 4:

                printf("\nprueba en el archivo salida.dat\n");
                if((fp=fopen("salida.dat","rb"))==NULL)
                {
                    printf("no se puede crear/abrir archivo");
                    return 0;
                }
                fread(&bf,sizeof(salida),1,fp);

                while(!feof(fp))
                {
                printf("potencia:%hhu\n",bf.potencia);
                fread(&bf,sizeof(salida),1,fp);
                }
                system("pause");
                fclose(fp);
                break;
        }
    }while(op!=5);

    return 0;
}

int funcion(int pf,struct pila**p)
{
    FILE *fp;
    char *c;
    datos_t2 bf2;
    char desc[100];
    unsigned char potencia;
    unsigned int estado;
    int i;
    if((fp=fopen("potencia.dat","rb+"))==NULL)
    {
        printf("no se puede crear/abrir archivo");
        return 0;
    }

    fseek(fp,(long)sizeof(datos_t2),0);
    fread(&bf2,sizeof(datos_t2),1,fp);

     while(!feof(fp))
    {
        if(pf==bf2.pf)
        {
           // printf("%04d\t %u\t %s\n",bf2.pf,bf2.estado,bf2.desc);
            potencia=bf2.potencia;
            estado=bf2.estado;
            strcpy(desc,bf2.desc);
            bf2.estado=bf2.estado^0b00001000;   ///cambiará el estado del bit 3
            break;
        }
        fread(&bf2,sizeof(datos_t2),1,fp);
    }

    printf("\nPrimera palabra del campo desc en forma inversa:\t");
    for(i=strlen(desc)+1;i>=0;i--)   ///utilizando punteros imprimirá la primera palabra del campo "desc" en forma inversa
    {
       c=&desc[i];
       printf("%c",*c);
    }
    strcpy(bf2.desc,strrev(desc));
    fseek(fp,(long)((-1)*sizeof(datos_t2)),1);
    fwrite(&bf2,sizeof(datos_t2),1,fp);
    fclose(fp);

    if(potencia&0b0000100&&potencia&0b00000001)  /// cuando los bits 0 y 2, del campo estado, estén encendidos
    {
        struct pila *aux;
        aux=(struct pila*)malloc(sizeof(struct pila));
                if(aux)
                {
                      aux->dato=potencia;
                      aux->l=(*p);
                      (*p)=aux;
                }
                else printf("\n Memoria insuficiente\n");
        printf("\nLos bits 2 y 0 del campo potencia de este registro estan en estado 1, por lo tanto la potencia de este registro sera cargada en una pila\n");    ///se agregará a una pila la potencia
    }

    else///en caso contrario se agregará el registro al archivo “salida.dat” de organización secuencial
    {
     salida bf;
        if(fopen("salida.dat","ab")==NULL)
        {
            printf("no se pude abrir\n");
            return 0;
        }
    fread(&bf,sizeof(salida),1,fp);
    bf.potencia=potencia;
    fwrite(&bf,sizeof(salida),1,fp);
    fclose(fp);
    printf("\nLos bits 2 y 0 del campo potencia de este registro no estan ambos en estado 1, por lo tanto este registro sera guardado en el archivo Salida.dat\n");    ///se agregará a una pila la potencia
    }
}

int menu(void)
{
    int op;
    system("cls");
    printf("\nMenu\n");
    printf("\n1-Ingresar ID\n");
    printf("\n2-Salir\n");
   // printf("\n3-Desapilar\n");
   //printf("\n4-imprimir archivo Salida.dat");
    scanf("%d",&op);
    system("cls");
    return op;
}
