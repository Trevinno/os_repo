/* PROGRAMA: estado1.c (basado en programa 3.10 en tercera edicion.)
   DESCRIPCION:
                 Presenta por pantalla la informacion estadistica de nombre_archivo.
   FORMA DE USO:
                 estado <nombre_archivo> [<nombre_archivo> ...]
   VALOR DE RETORNO:
               0: si se ejecuta satisfactoriamente.
              -1: si se da alguna condicion de error.       
*/
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <sys/stat.h>
 
char permisos[]={'x','y','r'};
 
int estado(char *archivo)
{
   struct stat buf;
   struct passwd *pw;
   struct group *gr;
   int i;
  
   if (stat(archivo, &buf)== -1) /* Lee informacion del tipo archivo. */
   {
      perror(archivo);
      exit(-1);
   }
 
   fprintf(stdout,"  Archivo: %s\n", archivo);
   fprintf(stdout,"  Nro. de inode: %d\n", buf.st_ino);
 
   fprintf(stdout,"  Tipo:");
   /* Analisis del tipo de dispositivo*/
   /* Para concer el tipo de archivo, se utilizan unas constantes definidas*/
   /* en sys/stat.h*/
   /* S_IFMT= 0170000 */
   /* S_IFREG=0100000 */
   /* S_IFDIR=0040000 */
   /* S_IFCHR=0020000 */
   /* S_IFBLK=0060000 */
   /* S_IFIFO=0010000 */
   switch (buf.st_mode & S_IFMT) /* mascara para obtener el tipo de archivo*/
   {
      case S_IFREG:
         printf("ordinario\n");
                            break;
      case S_IFDIR:
         printf("directorio\n");
                            break;
      case S_IFCHR:
         printf("especial modo de caracter\n");
                            break;
      case S_IFBLK:
         printf("especial modo bloque\n");
                            break;
      case S_IFIFO:
         printf("FIFO");
                            break;
   }
}
 
int main(int argc, char *argv[])
{
  int i;
 
  /*Analisis de los argumentos de la linea de comandos. */
  fprintf(stderr,"argc=%d\n",argc);
  if (argc < 2)
  {
     fprintf(stderr,"Forma de uso: %s nombre_archivo\n", argv[0]);
     exit(-1);
  }
  
  /* Ciclo de conteo */
  for (i=1; i<argc; i++)
  {
     estado(argv[i]);
  }
  exit(0);
  return 0;
}
