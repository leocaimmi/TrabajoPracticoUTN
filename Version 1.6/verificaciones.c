#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"
#include "menu.h"
#include "verificaciones.h"


int buscarUltimoID(char archivoEstudiante[])
{
    FILE*buffer=fopen(archivoEstudiante,"rb");
    stEstudiante aux;
    int legajo=0;
    if(buffer != NULL)
    {
        fseek(buffer,sizeof(stEstudiante)*-1,SEEK_END); // si el archivo existe busco el ultimo ID y le sumo 1
        fread(&aux,sizeof(stEstudiante),1,buffer);
        legajo= aux.legajo;

        fclose(buffer);
    }
    else
    {

        legajo=0; // si no existe el archivo, por defecto el legajo va a ser 1
    }
    return legajo;
}

int validarNumEnString(char dato[])
{
    int validosPalabras = strlen(dato);
    int flag = 0;

    for(int i = 0; i<validosPalabras; i++)
    {
        if(!isalpha(dato[i]))
        {

            flag = 1;
        }
    }
    if(flag==1)
    {
        puts("No se pueden ingresar numeros aqui, Reintente...");
    }

    return flag;
}

int validarComision(int dato)
{
    int flag=0;
    if(dato<=0 || dato>3)
    {
        puts("Ingrese una comision valida (1 o 2 o 3)");
        flag=1;
    }

    return flag;
}

int validarNota(int dato)
{

    int flag = 0;
    if(dato > 10 || dato<1)
    {
        puts("Ingrese una nota valida...");
        flag = 1;
    }

    return flag;
}

int validarLegajo(char archivo[],int legajo)
{
    stEstudiante aux;
    int flag=1;
    FILE*buffer= fopen(archivo,"rb");

    if(buffer!= NULL)
    {
        while(fread(&aux,sizeof(stEstudiante),1,buffer)>0 && flag==1)
        {
            if(aux.legajo == legajo)
            {
                flag=0;
            }

        }
        fclose(buffer);
    }
    else
    {
        puts("Error con el archivo");
    }

    if(flag==1)
    {
        puts("Ingrese un legajo valido");
    }
    return flag;
}

int validarEstado(int dato)
{
    int flag=0;
    switch(dato)
    {
    case 0:
        flag=0;
        break;
    case 1:
        flag=0;
        break;
    default:
        puts("Ingrese un estado valido(1-activo, 0-inactivo)");
        flag=1;
        break;
    }
    return flag;
}
