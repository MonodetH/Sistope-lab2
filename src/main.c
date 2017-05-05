#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

/* Definicion de syscall number*/
#define SYS_procinfo_64 326
#define SYS_procinfo_32 377
#define SYS_procstate_64 327
#define SYS_procstate_32 378

int main(int argc, char *argv[])
{
    int statusValue = 0;
    int archValue = 64;
    int listProcesos = 0;
    int opt;
    int salida;

    /* Obtener opciones y sus argumentos */
    while((opt = getopt(argc, argv, "la:s:"))!= -1){
        switch (opt) {
            case 'a':
                if(!sscanf(optarg, "%i", &archValue)){
                    fprintf (stderr, "ERROR: Argumento de -a no valido, se requiere un entero.\n");
                    return 1;
                }
                break;
            case 's':
                if(!sscanf(optarg, "%i", &statusValue)){
                    fprintf (stderr, "ERROR: Argumento de -s no valido, se requiere un entero.\n");
                    return 1;
                }
                break;
            case 'l':
                listProcesos = 1;
                break;
            case '?':
                if(optopt == 'a'){
                    fprintf(stderr, "ERROR: La opcion -a debe ser seguida de una arquitectura valida (32 o 64)\n");
                }
                else if(optopt == 's'){
                    fprintf(stderr, "ERROR: La opcion -s debe ser seguida de un estado valido\n");
                }
                else{
                    fprintf(stderr, "ERROR: Argumentos no validos\n");
                }
                return 1;
            default:
                return 1;
        }
    }


    /**
     *  Hacer llamada a syscall
     */
    if (listProcesos){
        if(archValue == 32){
            printf("Listando procesos y sus estados con syscall 32 bits\n");
            salida = syscall(SYS_procstate_32, statusValue);
        }else if(archValue == 64){
            printf("Listando procesos y sus estados con syscall 64 bits\n");
            salida = syscall(SYS_procstate_64, statusValue);
        }else{
            printf("Argumentos:\n");
            printf("-a:\tRecibe la arquitectura de la syscall, puede ser 32 o 64\n");
        }
    }else{
        if(archValue == 32){
            printf("Listando procesos en estado %i con syscall 32 bits\n",statusValue);
            salida = syscall(SYS_procinfo_32, statusValue);
        }else if(archValue == 64){
            printf("Listando procesos en estado %i con syscall 64 bits\n",statusValue);
            salida = syscall(SYS_procinfo_64, statusValue);
        }else{
            printf("Este programa lista en la salida estandar del kernel todos los procesos con estado s y todos sus hijos\n");
            printf("Argumentos:\n");
            printf("-a:\tRecibe la arquitectura de la syscall, puede ser 32 o 64\n");
            printf("-s:\tRecibe el estado de un proceso, puede ser 0,1,2,4,8,16,32,64,128,256,512,1024,2048 o 4096\n");
        }
    }

    printf("La syscall retorno con valor %i\n", salida);

    return 0;
}