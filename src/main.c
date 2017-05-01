#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#define SYS_procinfo_64 326
#define SYS_procinfo_32 377

int main(int argc, char *argv[])
{
    int statusValue = -1;
    int archValue = -1;
    int opt;
    int salida;

    while((opt = getopt(argc, argv, "a:s:"))!= -1){
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

    if(archValue == 32){
        salida = syscall(SYS_procinfo_32, statusValue);
    }else if(archValue == 64){
        salida = syscall(SYS_procinfo_64, statusValue);
    }else{
        printf("Este programa lista en la salida estandar del kernel todos los procesos con estado s y todos sus hijos\n");
        printf("Argumentos:\n");
        printf("-a:\tRecibe la arquitectura de la syscall, puede ser 32 o 64\n");
        printf("-s:\tRecibe el estado de un proceso, puede ser 0,1,2,4,8,16,32,64,128,256,512,1024,2048 o 4096\n");
    }

    printf("La syscall retorno con valor %i\n", salida);

    return 0;
}