#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#define MAX 10
#define A 0.6180339887

/************************************************************
Autores: Victor Rillo Martinez / David Martos Grande
Fecha: 12/06/2020
Asignatura: Estructura de Datos y Algoritmos, curso 19/20
Tarea: Actividad práctica UD6
************************************************************/

struct student
{
    int id;
    char name[50];
    char phone[9];
    char email[50];
    int enrolled;
}*students[MAX];

int main()
{
    int option = 1;

    while(option != 0)
    {
        printf("Selecciona una opcion\n");
        printf("1 - Anadir nuevo alumno\n");
        printf("2 - Mostrar listado alumnos\n");
        printf("3 - Modificar valor matriculacion\n");
        printf("4 - Eliminar alumno\n");
        printf("5 - Guardar fichero (alumnos.txt)\n");
        printf("0 - Salir\n");
        printf("Opcion: ");
        scanf("%d", &option);

        switch(option)
        {
        case 1:
            createStudent();
            break;
        case 2:
            showList();
            break;
        case 3:
            updateStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            saveFile();
            break;
        }

    }
    printf("Adios\n");
    return 0;
}

int hash(int k, int m)
{
    return floor(m * (k*A - floor(k*A)));
}

void createStudent()
{
    struct student *aux;
    int arrayIndex=0;

    aux = (struct student*)malloc(sizeof(struct student));

    printf("\tIntroducir id de usuario: ");
    scanf("%d", &aux->id);

    printf("\tIntroduce el nombre: ");
    scanf("%s", &aux->name);

    printf("\tIntroduce el telefono: ");
    scanf("%s", &aux->phone);

    printf("\tIntroduce el email: ");
    scanf("%s", &aux->email);

    printf("\t¿Está matriculado? (Si-> 1/No->0): ");
    scanf("%d", &aux->enrolled);

    arrayIndex = hash(aux->id,11);

    printf("\n");

    if (students[arrayIndex] != 0)
    {
        printf("Ese id de usuario ya existe\n");
    }
    else
    {
        printf("\tid: %d \t -> index hash: %d \n", aux->id, arrayIndex);
        students[arrayIndex] = (struct student *)malloc(sizeof(struct student));
        students[arrayIndex] = aux;
    }

    printf("\n");
}

void updateStudent()
{
    struct student *aux;
    int index=0,key=0;

    printf("\tIntroduce el id del alumno: ");
    scanf("%d", &key);
    index = hash(key,11);

    printf("\n");

    if (students[index] != NULL)
    {
        if (students[index]->id == key)
        {
            aux = students[index];
            printf("\t\tAlumno encontrado. Nombre: %s\n", &aux->name);
            printf("\t\tEsta matriculado? (Si-> 1/No->0): ");
            scanf("%d", &aux->enrolled);
            printf("\t\t->Alumno actualizado\n");
        }

        else
        {
            printf("\t\tEstudiante con id %d no encontrado\n", key);
        }
    }
    else
    {
        printf("\t\tEstudiante con id %d no encontrado\n", key);
    }
    printf("\n");
}

void deleteStudent()
{
    int index=0,key=0;

    printf("\tIntroduce el id del alumno: ");
    scanf("%d", &key);
    index = hash(key,11);

    printf("\n");

    if (students[index] != NULL)
    {

        if (students[index]->id == key)
        {
            printf("\t\tAlumno encontrado. Nombre: %s\n", students[index]->name);
            free(students[index]);
            students[index] = NULL;
            printf("\t\t->Alumno eliminado\n");
        }

        else
        {
            printf("\t\tEstudiante con id %d no encontrado\n", key);
        }
    }
    else
    {
        printf("\t\tEstudiante con id %d no encontrado\n", key);
    }
    printf("\n");
}

void showList()
{
    printf("\n");

    for(int i = 0; i < MAX; i++ )
    {
        if(students[i] != NULL)
        {
            printf("\t\tAlumno con id %d: ", students[i]->id);
            printf("%s\t %s\t %s\t %s\n",
                   students[i]->name, students[i]->phone, students[i]->email, students[i]->enrolled == 1 ? "Si" : "No");
        }
    }

    printf("\n");
}

void saveFile()
{
    FILE *file;

    if((file   = fopen("alumnos.txt", "w"))==NULL)
    {
        printf("No se puede abrir el fichero alumnos.txt\n");
        exit(1);
    };

    for(int i = 0; i < MAX; i++ )
    {
        if(students[i] != NULL)
        {
            fprintf(file, "Alumno id %d\t|\tNombre %s\t|\tEmail %s\t|\tTelefono %s\t|\tMatriculado %s\n", students[i]->id, students[i]->name, students[i]->email, students[i]->phone, students[i]->enrolled == 1 ? "Si" : "No");
        }
    }

    printf("\t\t->alumnos.txt guardado\n");

    fclose(file);
}
