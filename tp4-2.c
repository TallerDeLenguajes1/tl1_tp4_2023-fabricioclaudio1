#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Tarea {
int TareaID; //Numerado en ciclo iterativo
char *Descripcion;
int Duracion; // entre 10 – 100
}typedef Tarea;

void inicializarTareas(Tarea** tareas, Tarea** tareasRealizadas, int cantTareas);
void cargarTareas(Tarea** tareas, int cantTareas);
void listarTareas(Tarea** tareas,Tarea** tareasRealizadas, int cantTareas);
void mostrarTareas(Tarea** tareas,Tarea** tareasRealizadas, int cantTareas);
void BuscarTareaPorPalabra(Tarea** tareas,Tarea** tareasRealizadas, int cantTareas);

void liberarMemoria(Tarea** tareas,Tarea** tareasRealizadas,int cantTareas);

int main(){
    int cantTareas;

    printf("Ingrese la cantidad de tareas para cargar: \n");
    scanf("%d",&cantTareas);

    Tarea** tareas= (Tarea**) malloc(cantTareas*sizeof(Tarea*));
    Tarea** tareasRealizadas= (Tarea**) malloc(cantTareas*sizeof(Tarea*));

    inicializarTareas(tareas, tareasRealizadas, cantTareas);
    cargarTareas(tareas, cantTareas);
    listarTareas(tareas, tareasRealizadas, cantTareas);
    mostrarTareas(tareas, tareasRealizadas, cantTareas);
    BuscarTareaPorPalabra(tareas, tareasRealizadas, cantTareas);

    liberarMemoria(tareas, tareasRealizadas, cantTareas);

    return 0;
}

void inicializarTareas(Tarea** tareas, Tarea** tareasRealizadas, int cantTareas){
    for (int i = 0; i < cantTareas; i++)
    {
        tareas[i]=NULL;
        tareasRealizadas[i]=NULL;
    }
    
}

void cargarTareas(Tarea** tareas, int cantTareas){
    srand(time(NULL));
    for (int i = 0; i < cantTareas; i++)
    {
        //Reserva de memoria para cada tarea
        tareas[i]=(Tarea*) malloc(sizeof(Tarea));

        //ID
        tareas[i]->TareaID=i+1;

        //Descripcion
        char descrip[200];
        printf("Ingrese la descripcion de tarea Nro %d: \n", i+1);
        fflush(stdin);

        gets(descrip);
        /* "gets(descrip)" o lo siguiente:
        fgets(descrip,sizeof(descrip),stdin);
        strtok(descrip, "\n"); // elimina el caracter de nueva línea
        scanf("%s",descrip); //va el &?
        */
        tareas[i]->Descripcion=malloc((strlen(descrip)+1)*sizeof(char)); //Reservo memoria para la descripcion. El tamaño es igual a 'descrip' + un char más para guardar el caracter de fin de linea
        strcpy(tareas[i]->Descripcion,descrip);

        //Duracion
        tareas[i]->Duracion=rand()% 91 + 10;

    }
}

void listarTareas(Tarea** tareas,Tarea** tareasRealizadas, int cantTareas){
    int resp=0;
    printf("|Listado de tareas| \n");
    for (int i = 0; i < cantTareas; i++)
    {
        puts("---------------");
        printf("ID %d\n",tareas[i]->TareaID);

        printf("Descripcion: ");
        puts(tareas[i]->Descripcion);

        printf("Duracion %d\n",tareas[i]->Duracion);

        printf("Esta tarea esta realizada? (1:SI, 0:NO)\n");
        fflush(stdin);
        scanf("%d",&resp);
        if (resp==1)
        {
            tareasRealizadas[i]=tareas[i];
            tareas[i]=NULL;
        }
        puts("---------------");
    }
}

void mostrarTareas(Tarea** tareas,Tarea** tareasRealizadas, int cantTareas){
    printf("|Tareas Realizadas|\n");
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareasRealizadas[i]!=NULL)
        {
            puts("---------------");
            puts(tareasRealizadas[i]->Descripcion);
            puts("---------------");
        }
        
        

    }
    
    printf("|Tareas Pendientes|\n");
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareas[i]!=NULL)
        {
            puts("---------------");
            puts(tareas[i]->Descripcion);
            puts("---------------");
        }
        
        
    }
}

void BuscarTareaPorPalabra(Tarea** tareas,Tarea** tareasRealizadas, int cantTareas){
    char *palabra=(char*) malloc(50*sizeof(char));

    printf("Ingresa una palabra clave para encontrar alguna tarea: \n");
    fflush(stdin);
    gets(palabra);

    puts("|Tareas encontradas|");
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareasRealizadas[i]!=NULL)
        {
            char *resultado= strstr(tareasRealizadas[i]->Descripcion, palabra);
            if (resultado!=NULL)
            {
                puts("---------------");
                puts(tareasRealizadas[i]->Descripcion);
                puts("---------------");
            }

        }
    }
    
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareas[i]!=NULL)
        {
            char *resultado= strstr(tareas[i]->Descripcion, palabra);
            if (resultado!=NULL)
            {
                puts("---------------");
                puts(tareas[i]->Descripcion);
                puts("---------------");
            }
        }
    }

    free(palabra);
}

void liberarMemoria(Tarea** tareas,Tarea** tareasRealizadas,int cantTareas){

    free(tareas);
    free(tareasRealizadas);
    for (int i = 0; i < cantTareas; i++)
    {
        free(tareas[i]);
        free(tareas[i]->Descripcion);
        free(tareasRealizadas[i]);
        free(tareasRealizadas[i]->Descripcion);
    }  
}