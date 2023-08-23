#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"
#include "menu.h"
#include "verificaciones.h"
#define DIM_CHAR 30
#define DIM_NOTAS 6

stEstudiante crearUnEstdiante(char archivoEstudiante[])
{
    stEstudiante aux;
    int i = 0;
    char op;

    aux.legajo=buscarUltimoID(archivoEstudiante)+1; // legajo autoincremental
    aux.estado=1; // 1= activo , 0= inactivo
    do
    {
        printf("Ingrese el nombre del estudiante: ");
        fflush(stdin);
        gets(aux.nombre);
    }
    while(validarNumEnString(aux.nombre));

    do
    {
        printf("Ingrese el apellido del estudiante: ");
        fflush(stdin);
        gets(aux.apellido);
    }
    while(validarNumEnString(aux.apellido));

    do
    {
        printf("Ingrese la comision del estudiante: ");
        scanf("%i",&aux.comision);
    }
    while(validarComision(aux.comision)); ///agregar validacion de que no haya caracteres en numeros


    do
    {
        do
        {
            printf("Ingrese las notas correspondiente del alumno (max 6): ");
            fflush(stdin);
            scanf("%i",&aux.notas[i]);
        }
        while(validarNota(aux.notas[i]));

        i++;

        if(i < DIM_NOTAS)
        {
            puts("Desea ingresar mas notas? s/n: ");
            fflush(stdin);
            scanf("%c",&op);
        }

    }
    while((op=='s'||op == 'S') && i<DIM_NOTAS);

    aux.cantidadNotas=i;

    return aux;
}

void limpiarPantalla()
{
    system("cls");
}

void cargarEstudianteAlArchivo(char archivo[])
{
    stEstudiante aux;
    FILE*buffer=fopen(archivo,"ab");
    if(buffer != NULL)
    {
        aux=crearUnEstdiante(archivo);
        fwrite(&aux,sizeof(stEstudiante),1,buffer);

        fclose(buffer);
    }
    else
    {
        puts("Error con el archivo");
    }
}

void mostrarEstudiante(stEstudiante aux)
{
    puts("---------------------------------");
    printf("Legajo: %i \n",aux.legajo);
    printf("Nombre: %s \n",aux.nombre);
    printf("Apellido: %s \n",aux.apellido);
    printf("Comision: %i \n",aux.comision);
    printf("Notas: ");
    mostrarNotas(aux);
    printf("Estado: %i \n",aux.estado);
}
void mostrarNotas(stEstudiante aux)
{
    for (int i=0; i < aux.cantidadNotas; i++)
    {
        printf("(%i)",aux.notas[i]);
    }
    printf("\n");
}

void mostrarTodosLosEstudiantes(char archivo[])
{
    FILE*buffer=fopen(archivo,"rb");
    stEstudiante aux;
    if(buffer !=NULL)
    {
        while(fread(&aux,sizeof(stEstudiante),1,buffer)>0)
        {
            mostrarEstudiante(aux);
        }

        fclose(buffer);
    }
    else
    {
        puts("Error con el archivo");
    }


}

stEstudiante retornarEstudianteXlegajo(char archivo[], int legajo)
{
    stEstudiante aux, buscado;
    int flag=0;
    FILE*buffer=fopen(archivo,"rb");

    if(buffer!= NULL)
    {
        while(fread(&aux,sizeof(stEstudiante),1,buffer) > 0 && flag==0)
        {

            if(aux.legajo == legajo)
            {
                flag=1;
                buscado = aux;
            }
        }

        fclose(buffer);
    }
    else
    {
        puts("error con el archivo");
    }

    if(flag == 0)
    {
        puts("No se encontro un estudiante con ese legajo");
    }

    return buscado;

}

void modificarEstudiante(int opsw, char archivo[],int legajoSelecto)
{
    char auxChar[DIM_CHAR];
    int auxEntero=0;
    switch(opsw)
    {
    case 1:
        //nombre
        do
        {

            printf("Ingrese el nuevo nombre del estudiante: ");
            fflush(stdin);
            gets(auxChar);

        }
        while(validarNumEnString(auxChar));

        modificarNombreEstudiante(archivo,auxChar,legajoSelecto);
        break;
    case 2:
        //apellido
        do
        {

            printf("Ingrese el nuevo apellido del estudiante: ");
            fflush(stdin);
            gets(auxChar);

        }
        while(validarNumEnString(auxChar));

        modificarApellidoEstudiante(archivo,auxChar,legajoSelecto);

        break;
    case 3:
        //agregar notas

        agregarNotas(archivo,legajoSelecto);
        break;
    case 4:
        //cambiar comision

        do
        {
            printf("Ingrese la nueva comision del estudiante: ");
            scanf("%i",&auxEntero);

        }
        while(validarComision(auxEntero));
        cambiarComision(archivo,auxEntero,legajoSelecto);

        break;
    case 5:
        //estado
        do
        {
            printf("Ingrese el nuevo estado: ");
            scanf("%i",&auxEntero);

        }
        while(validarEstado(auxEntero));
    modificarEstado(archivo,auxEntero,legajoSelecto);
        break;
    case 6:
        //volver al menu principal
        break;
    default:
        puts("Elija una opcion valida...");
        break;
    }
}

int retornarPosEstudianteXlegajo(char archivo[], int legajoBuscado)
{
    int pos=0, flag=0;
    stEstudiante aux;
    FILE*buffer=fopen(archivo,"rb");
    if(buffer != NULL)
    {
        while(fread(&aux,sizeof(stEstudiante),1,buffer)>0 && flag==0)
        {
            if(aux.legajo == legajoBuscado)
            {
                pos=ftell(buffer)/sizeof(stEstudiante)-1;
                flag=1;
            }
        }


        fclose(buffer);
    }
    else
    {
        puts("Error con el archivo");
    }
    return pos;
}

void modificarNombreEstudiante(char archivo[], char nuevoNombre[], int legajo)
{
    int pos=retornarPosEstudianteXlegajo(archivo,legajo);
    stEstudiante aux;
    FILE*buffer=fopen(archivo,"r+b"); // abro el archivo en r+b para poder leer y modificar
    if(buffer != NULL)
    {
        fseek(buffer,sizeof(stEstudiante)*pos,SEEK_SET); // me muevo la pos retornada por la otra funcion
        fread(&aux,sizeof(stEstudiante),1,buffer);      // leo el estudiante, pero ahora debo moverme una posicion para atras para poder escribir y modificar
        strcpy(aux.nombre,nuevoNombre);
        fseek(buffer,sizeof(stEstudiante)*(-1),SEEK_CUR); // me muevo una pos. hacia atras
        fwrite(&aux,sizeof(stEstudiante),1,buffer);       //y escribo el "nuevo" estudiante

        fclose(buffer);
    }
    else
    {
        puts("Error con el archivo");
    }

}

void modificarApellidoEstudiante(char archivo[], char nuevoApellido[], int legajo)
{
    int pos=retornarPosEstudianteXlegajo(archivo,legajo);

    stEstudiante aux;
    FILE*buffer=fopen(archivo,"r+b");
    if(buffer != NULL)
    {
        fseek(buffer,sizeof(stEstudiante)*pos,SEEK_SET);
        fread(&aux,sizeof(stEstudiante),1,buffer);
        strcpy(aux.apellido,nuevoApellido);
        fseek(buffer,sizeof(stEstudiante)*pos,SEEK_SET);
        fwrite(&aux,sizeof(stEstudiante),1,buffer);

        fclose(buffer);
    }
    else
    {
        puts("Error con el archivo");
    }

}

void cambiarComision(char archivo[],int auxEntero,int legajoSelecto){
int pos=retornarPosEstudianteXlegajo(archivo,legajoSelecto);

    stEstudiante aux;
    FILE*buffer=fopen(archivo,"r+b");
    if(buffer != NULL)
    {
        fseek(buffer,sizeof(stEstudiante)*pos,SEEK_SET);
        fread(&aux,sizeof(stEstudiante),1,buffer);
        aux.comision = auxEntero;
        fseek(buffer,sizeof(stEstudiante)*pos,SEEK_SET);
        fwrite(&aux,sizeof(stEstudiante),1,buffer);

        fclose(buffer);
    }
    else
    {
        puts("Error con el archivo");
    }




}

void agregarNotas(char archivo[],int legajo)
{
    int pos=retornarPosEstudianteXlegajo(archivo,legajo);

    stEstudiante aux;
    FILE*buffer=fopen(archivo,"r+b");
    if(buffer != NULL)
    {
        fseek(buffer,sizeof(stEstudiante)*pos,SEEK_SET);
        fread(&aux,sizeof(stEstudiante),1,buffer);

        if(aux.cantidadNotas < DIM_NOTAS)
        {
            aux.cantidadNotas= preguntarMasNotas(aux.notas,aux.cantidadNotas);
        }
        else
        {
            puts("Se alcanzo el limite de notas que se le puede agregar a un alumno");
        }

        fseek(buffer,sizeof(stEstudiante)*(-1),SEEK_CUR);
        fwrite(&aux,sizeof(stEstudiante),1,buffer);

        fclose(buffer);
    }
    else
    {
        puts("Error con el archivo");
    }

}

int preguntarMasNotas(int arreglo[], int validos)
{
    char op;
    do
    {
        do
        {
            printf("Ingrese la nueva nota: ");
            fflush(stdin);
            scanf("%i",&arreglo[validos]);

        }
        while(validarNota(arreglo[validos]));
        printf("El estudiante tiene %i notas cargadas\n",validos+1);
        validos++;
        printf("Desea seguir cargando notas? s/n: ");
        fflush(stdin);
        scanf("%c",&op);
    }
    while(validos < DIM_NOTAS && (op == 'S' || op=='s'));

    if(validos == DIM_NOTAS)
    {
        puts("Se alcanzo el limite maximo de notas");
    }

    return validos;
}

void modificarEstado(char archivo[], int nuevoEstado, int legajo)
{
    int pos=retornarPosEstudianteXlegajo(archivo,legajo);

    stEstudiante aux;
    FILE*buffer=fopen(archivo,"r+b");
    if(buffer != NULL)
    {
        fseek(buffer,sizeof(stEstudiante)*pos,SEEK_SET);
        fread(&aux,sizeof(stEstudiante),1,buffer);
        aux.estado=nuevoEstado;
        fseek(buffer,sizeof(stEstudiante)*(-1),SEEK_CUR);
        fwrite(&aux,sizeof(stEstudiante),1,buffer);

        fclose(buffer);
    }
    else
    {
        puts("Error con el archivo");
    }




}

///busqueda
void buscarEstudiantePorNombre(char archivo[])
{

    char nombreAux[DIM_CHAR];
    stEstudiante aux;
    puts("-------------NOMBRE-------------");
    puts("Ingrese el dato solicitado: ");
    fflush(stdin);
    gets(nombreAux);



    FILE* buffer = fopen(archivo,"rb");
    if(buffer != NULL)
    {
        while(fread(&aux,sizeof(stEstudiante),1,buffer)>0)
        {

            if(strcmpi(nombreAux,aux.nombre)== 0)
            {
                mostrarEstudiante(aux);
            }
        }
        fclose(buffer);
    }
    else
    {

        puts("Error con el archivo...");
    }

}
void buscarEstudiantePorApellido(char archivo[])
{
    stEstudiante aux;
    char apellidoAux[DIM_CHAR];


    puts("-------------APELLIDO-------------");
    puts("Ingrese el dato solicitado: ");
    fflush(stdin);
    gets(apellidoAux);

    FILE* buffer = fopen(archivo,"rb");
    if(buffer != NULL)
    {
        while(fread(&aux,sizeof(stEstudiante),1,buffer)>0)
        {
            if(strcmpi(apellidoAux,aux.apellido)== 0)
            {
                mostrarEstudiante(aux);
            }
        }
        fclose(buffer);
    }
    else
    {

        puts("Error con el archivo...");
    }

}

void buscarPorLegajo(char archivo[])
{
    int legajo;
    stEstudiante aux;

    do
    {
        puts("---------LEGAJO---------");
        legajo = preguntarDatoEntero();//el usuario elige un legajo existente
    }
    while(validarLegajo(archivo,legajo));


    FILE* buffer = fopen(archivo,"rb");
    if(buffer != NULL)
    {
        while(fread(&aux,sizeof(stEstudiante),1,buffer)>0)
        {
            if(aux.legajo == legajo)
            {
                mostrarEstudiante(aux);
            }
        }

        fclose(buffer);
    }
    else
    {
        puts("Error con el archivo");
    }
}

 void buscarXcomi(char archivo[]){

 int datoCom = 0;
 do{
    puts("Ingrese la comision que desea buscar(1/2/3)");
    fflush(stdin);
    scanf("%i",&datoCom);

 }while(validarComision(datoCom));

 stEstudiante aux;
 FILE* buffer = fopen(archivo,"rb");
 if(buffer != NULL){
    while(fread(&aux,sizeof(stEstudiante),1,buffer)>0){
        if(aux.comision == datoCom){
            mostrarEstudiante(aux);
        }

    }

    fclose(buffer);
 }else{
 puts("Error en el archivo");
 }


 }

void buscarXestado(char archivo[]){

 int datoEstado = 0;
 do{
    puts("Ingrese el estado que desea buscar(0/1)");
    fflush(stdin);
    scanf("%i",&datoEstado);

 }while(validarEstado(datoEstado));

 stEstudiante aux;
 FILE* buffer = fopen(archivo,"rb");
 if(buffer != NULL){
    while(fread(&aux,sizeof(stEstudiante),1,buffer)>0){
        if(aux.estado == datoEstado){
            mostrarEstudiante(aux);
        }

    }

    fclose(buffer);
 }else{
 puts("Error en el archivo");
 }


}
int preguntarDatoEntero()
{

    int dato = 0;

    printf("Ingrese el dato solicitado: ");
    fflush(stdin);
    scanf("%i",&dato);

    return dato;
}

///promedio

float calcularPromedioEstudiante(stEstudiante aux)
{
    int sum=0;
    float prom=0;
    for(int i=0; i < aux.cantidadNotas; i++)
    {
        sum+=aux.notas[i];
    }
    return prom=(float)sum/aux.cantidadNotas;
}

float promedioMasBajoDeEstudiante(char archivo[])
{
    stEstudiante aux,alumnoPromBajo;
    float prom=0,promedioBajo=20;

    FILE*buffer=fopen(archivo,"rb");

    if(buffer != NULL)
    {
        while(fread(&aux,sizeof(stEstudiante),1,buffer)>0)
        {
            prom=calcularPromedioEstudiante(aux);
            if(prom < promedioBajo)
            {
                promedioBajo= prom;
                alumnoPromBajo=aux;
            }
        }


        fclose(buffer);
    }
    else
    {
        puts("Error con el archivo");
    }

    mostrarEstudiante(alumnoPromBajo);

    return promedioBajo;
}
float promedioMasAltoDeEstudiante(char archivo[])
{
    stEstudiante aux,alumnoPromAlto;
    float prom=0,promedioAlto=0;

    FILE*buffer=fopen(archivo,"rb");

    if(buffer != NULL)
    {
        while(fread(&aux,sizeof(stEstudiante),1,buffer)>0)
        {
            prom=calcularPromedioEstudiante(aux);
            if(prom > promedioAlto)
            {
                promedioAlto= prom;
                alumnoPromAlto=aux;
            }
        }


        fclose(buffer);
    }
    else
    {
        puts("Error con el archivo");
    }

    mostrarEstudiante(alumnoPromAlto);
    return promedioAlto;
}

void mostrarEstudiantesAprobados(char archivo[])
{
    float aprobado=6,promedio=0;

    stEstudiante aux;
    FILE* buffer= fopen(archivo,"rb");

    if(buffer != NULL)
    {
        while(fread(&aux,sizeof(stEstudiante),1,buffer)>0)
        {
            if(aux.estado == 1)
            {
                promedio= calcularPromedioEstudiante(aux);

                if(promedio >= aprobado)
                {
                    mostrarEstudiante(aux);
                    printf("%s tiene un promedio de: %.2f \n",aux.nombre,promedio);

                }

            }
        }
        fclose(buffer);
    }
    else
    {
        puts("Error con el archivo");
    }
}

void mostrarEstudiantesDesaprobados(char archivo[])
{
    float aprobado=6,promedio=0;

    stEstudiante aux;
    FILE* buffer= fopen(archivo,"rb");

    if(buffer != NULL)
    {
        while(fread(&aux,sizeof(stEstudiante),1,buffer)>0)
        {
            if(aux.estado == 1)
            {
                promedio= calcularPromedioEstudiante(aux);

                if(promedio < aprobado)
                {
                    mostrarEstudiante(aux);
                    printf("%s tiene un promedio de: %.2f \n",aux.nombre,promedio);

                }

            }
        }
        fclose(buffer);
    }
    else
    {
        puts("Error con el archivo");
    }
}

void mostrarEstudiantesPromocionados(char archivo[])
{
    float promocion=8,promedio=0;

    stEstudiante aux;
    FILE* buffer= fopen(archivo,"rb");

    if(buffer != NULL)
    {
        while(fread(&aux,sizeof(stEstudiante),1,buffer)>0)
        {
            if(aux.estado == 1)
            {
                promedio= calcularPromedioEstudiante(aux);

                if(promedio >= promocion)
                {
                    mostrarEstudiante(aux);
                    printf("%s tiene un promedio de: %.2f \n",aux.nombre,promedio);

                }

            }
        }
        fclose(buffer);
    }
    else
    {
        puts("Error con el archivo");
    }
}



