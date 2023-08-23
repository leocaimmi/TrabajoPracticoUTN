#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "menu.h"
#include "verificaciones.h"

void menu(char archivo[])
{
    int opSw=0;
    char op;
    do
    {
        opSw= opciones();
        limpiarPantalla();
        switch(opSw)
        {
        case 1:
            cargarEstudianteAlArchivo(archivo);
            break;
        case 2:
            menuEditarEstudiante(archivo);
            break;
        case 3:
            menuBuscar(archivo);
            break;
        case 4:
            menuMostrar(archivo);
            break;
        default:
            puts("Por favor ingrese una opcion valida");
            break;
        }
        printf("Desea seguir en el menu principal? s/n: ");
        fflush(stdin);
        scanf("%c",&op);
        limpiarPantalla();

    }
    while(op=='s' || op=='S');


}

int opciones()
{
    int opsw=0;
    puts("Bienvenido.\n");

    puts("1. Cargar estudiante");
    puts("2. Editar estudiante"); //podemos agregar notas,cambiarle el nombre,etc
    puts("3. Buscar estudiante"); // por apellido,nombre o id
    puts("4. Mostrar estudiante"); // todos,promedio mas bajo o mas alto y aprobados(regimen de aprobar es: 6) o desaprobados
    puts("-------------------------------------------------------------");
    printf("Que desea hacer?: ");
    fflush(stdin);
    scanf("%i",&opsw);
    return opsw;
}

void menuEditarEstudiante(char archivo[])
{
    int legajo=0, opSw=0;
    stEstudiante aux;
    do
    {
        mostrarTodosLosEstudiantes(archivo);
        puts("-------------------------------------------------------------");
        printf("Ingrese el legajo del estudiante que quiere modificar o agregar notas: ");
        scanf("%i",&legajo);
    }
    while(validarLegajo(archivo,legajo));

    limpiarPantalla();
    aux=retornarEstudianteXlegajo(archivo,legajo);
    puts("Usted eligio este estudiante:");


    mostrarEstudiante(aux);

    puts("-------------------------------------------------------------");
    opSw= mostrarOpcionesParaModificar();
    modificarEstudiante(opSw,archivo,legajo);


}

int mostrarOpcionesParaModificar()
{
    int dato=0;
    puts("1. Nombre");
    puts("2. Apellido");
    puts("3. Agregar Notas");
    puts("4. Comision");
    puts("5. Estado");
    puts("6. Volver al menu principal");
    puts("-------------------------------------------------------------");
    printf("Que desea hacer?:");
    scanf("%i",&dato);
    return dato;
}


void menuBuscar (char archivo[])
{

    int opSw = 0;
    char op;
    int flag=0;
    do
    {
        opSw = opcionesBuscar();

        switch(opSw)
        {
        case 1:
            flag=1;
            buscarEstudiantePorNombre(archivo);
            break;
        case 2:
            flag=1;
            buscarEstudiantePorApellido(archivo);
            break;
        case 3:
            flag=1;
            buscarPorLegajo(archivo);
            break;
        case 4:
            flag=1;
           buscarXcomi(archivo);
            break;
        case 5:
             flag = 1;
             buscarXestado(archivo);
            break;
        case 6:
            flag=0;
             op='n';
            break;
        default:
            flag=1;
            puts("Ingrese una opcion valida...");
            break;
        }

        if(flag==1)
        {
            printf("Desea seguir buscando estudiantes? s/n: ");
            fflush(stdin);
            scanf("%c",&op);

        }
            limpiarPantalla();

    }
    while(op == 's'||op == 'S');


}

int opcionesBuscar()
{

    int dato = 0;

    puts("1. Buscar por nombre..");
    puts("2. Buscar por apellido..");
    puts("3. Buscar por legajo..");
    puts("4. Buscar por comision..");
    puts("5. Buscar por estado..");
    puts("6. Volver al menu principal");
    puts("-----------------------");
    printf("Que opcion elige?: ");
    fflush(stdin);
    scanf("%i",&dato);

    return dato;
}

void menuMostrar(char archivo[])
{
    char op;
    float promedio=0;
    int flag=0, opsw=0;
    do
    {
        opsw=opcionesMostrar();

        switch(opsw)
        {
        case 1:
            mostrarTodosLosEstudiantes(archivo);
            flag=1;
            break;
        case 2:
            flag=1;
            promedio= promedioMasAltoDeEstudiante(archivo);
            printf("Este es el estudiante con promedio mas alto: %.2f \n",promedio);
            break;
        case 3:
            flag=1;
            promedio= promedioMasBajoDeEstudiante(archivo);
            printf("Este es el estudiante con promedio mas bajo: %.2f \n",promedio);
            break;
        case 4:
            flag=1;
            puts("\n-----------------------APROBADOS-----------------------\n");
            mostrarEstudiantesAprobados(archivo);
            break;
        case 5:
            flag=1;
            puts("\n-----------------------DESAPROBADOS-----------------------\n");
            mostrarEstudiantesDesaprobados(archivo);
            break;
        case 6:
            flag=1;
            puts("\n-----------------------PROMOCIONADOS-----------------------\n");
            mostrarEstudiantesPromocionados(archivo);
            break;
        case 7:
            flag=0;
            op='n';
            break;
        default:
            flag=1;
            puts("Ingrese una opcion valida");
            break;
        }
        if (flag == 1)
        {
            printf("Desea seguir mostrando estudiantes? s/n: ");
            fflush(stdin);
            scanf("%c",&op);
        }
        limpiarPantalla();
    }
    while(op=='s' || op=='S');


}

int opcionesMostrar()
{
    int dato=0;
    puts("1. Mostrar todos los alumnos");
    puts("2. Buscar alumno con promedio mas alto");
    puts("3. Buscar alumno con promedio mas bajo");
    puts("4. Mostrar alumnos aprobados (Prom. mayor o igual a 6)");
    puts("5. Mostrar alumnos desaprobados(Prom. menor a 6)");
    puts("6. Mostrar alumnos promocionados (Prom. mayor o igual a 8)");
    puts("7. Volver al menu principal");
    puts("---------------------------------------------------------");
    printf("Que opcion elige?: ");
    fflush(stdin);
    scanf("%i",&dato);
    return dato;

}



