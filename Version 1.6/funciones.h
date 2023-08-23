#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#define DIM_CHAR 30
#define DIM_NOTAS 6
typedef struct
{
    int legajo; //identificacion
    char nombre[DIM_CHAR];
    char apellido[DIM_CHAR];
    int notas[DIM_NOTAS];
    int cantidadNotas; // validos
    int comision;
    int estado;
}stEstudiante;

///varios
void limpiarPantalla();
int preguntarDatoEntero();

///cargar
stEstudiante crearUnEstdiante(char archivoEstudiante[]);
void cargarEstudianteAlArchivo(char archivo[]);

///mostrar
void mostrarEstudiante(stEstudiante aux);
void mostrarNotas(stEstudiante aux);
void mostrarTodosLosEstudiantes(char archivo[]);


///modificar
stEstudiante retornarEstudianteXlegajo(char archivo[], int legajo);
void modificarEstudiante(int opsw, char archivo[],int legajoSelecto);
void modificarNombreEstudiante(char archivo[], char nuevoNombre[], int legajo);
void modificarApellidoEstudiante(char archivo[], char nuevoApellido[], int legajo);
void agregarNotas(char archivo[],int legajo);
int preguntarMasNotas(int arreglo[], int validos);
void modificarEstado(char archivo[], int nuevoEstado, int legajo);
void cambiarComision(char archivo[],int auxEntero,int legajoSelecto);

///buscar
int retornarPosEstudianteXlegajo(char archivo[], int legajoBuscado);
void buscarEstudiantePorNombre(char archivo[]);
void buscarEstudiantePorApellido(char archivo[]);
void buscarPorLegajo(char archivo[]);
void buscarXcomi(char archivo[]);
void buscarXestado(char archivo[]);

///promedio
float calcularPromedioEstudiante(stEstudiante aux);
float promedioMasBajoDeEstudiante(char archivo[]);
float promedioMasAltoDeEstudiante(char archivo[]);
void mostrarEstudiantesAprobados(char archivo[]);
void mostrarEstudiantesDesaprobados(char archivo[]);
void mostrarEstudiantesPromocionados(char archivo[]);
#endif // FUNCIONES_H_INCLUDED
