/* PROGRAMA: copiar.c
              FORMA DE USO:
                            ./copiar origen destino
              VALOR DE RETORNO:
              0: si se ejecuta satisfactoriamente.
                                       -1: si se da alguna condicion de error
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
 
char buffer[BUFSIZ];
 
int main(int argc, char *argv[])
{
                 int fd_origen;
                              int fd_destino;
                 int nbytes;
 
                 /*Analisis de los argumentos de la linea de comandos*/
                 if (argc != 3)
                 {
                                fprintf(stderr,"Forma de uso: %s origen destino\n", argv[0]);
                                exit(-1);
                 }
 
                               /*Apertura del archivo en modo solo lectura*/
                 if ((fd_origen=open(argv[1],O_RDONLY))== -1)
                 {
                                 perror(argv[1]);
                                 exit(-1);
                 }
 
                 /* Apertura o creacion de archivos en modo solo escritura*/
                 if ((fd_destino=open(argv[2],O_WRONLY|O_TRUNC|O_CREAT, 0666))== -1)
                 {
                                 perror(argv[2]);
                                 exit(-1);
                 }
                 fprintf(stdout,"Num. descriptor del origen %d\n", fd_origen);
                 fprintf(stdout,"Num. descriptor del destino %d\n", fd_destino);
 
                 /* copiamos el archivo origen en el archivo destino. */
                 while ((nbytes=fread(fd_origen, buffer, sizeof buffer))> 0)
                                 fwrite(fd_destino, buffer, nbytes);
 
                 close(fd_origen);
                 close(fd_destino);
                            return 0;
}
