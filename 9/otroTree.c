#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
struct opciones
{
     unsigned mostrar_archivos:1;
};
 
enum Boolean {NO,SI};
void otroTree(char *path, struct opciones opciones);
 
/*** FUNCION: main
   DESCRIPCION
    Funcion principal , se encarga de analizar los argumentos
    De la linea de ordenes y de invocar a la funcion otroTree.***/
int main (int argc, char *argv[])
{
   struct opciones opciones;
   int i, j;
 
   /*Analisis de los argumentos en la linea de ordenes.*/
   if (argc<2)
   {
       fprintf (stderr,"Forma de uso: otroTree [-f] nombre_directorio\n");
       exit (-1);
   }
 
   for (i=1;i<argc;i++)
      if (argv[i][0] =='-')
          for (j=1;argv[i][j]!=0;j++)
              switch (argv[i][j])
              {
                 case 'f':
                    opciones.mostrar_archivos= SI;
                    break;
                 default:    
                    fprintf(stderr, "Opcion [-%c] desconocida \n",argv[i][j]);
              }
 
    /*Analisis de la estructura en arbol de directorios para cada uno
      de los argumentos que aparecen en la linea de ordenes y que no
      son opciones de otroTree.*/
    for (i=1;i<argc;i++)
      if (argv [i][0]!='-')
         otroTree (argv[i],opciones);
 
              return 0;
}


void otroTree(char *path, struct opciones opciones)
{
     DIR *dirp;
     struct dirent *dp;
     static unsigned int nivel = 0;
     struct stat buf;
     int ok;
     int i;
     char archivo [256];
     char tipo_archivo;
 
   /*Apertura de directorio.*/
   if ((dirp=opendir(path)) == NULL)
   {
      perror(path);
      return;
   };
  
   /*Leemos, una por una, las restantes entradas del directorio.*/
   while ((dp=readdir(dirp))!=NULL)
   {
                            /*Formamos el path name correspondiente al archivo de la entrada de
                              directorio que estamos procesando*/
       sprintf(archivo,"%s/%s",path, dp->d_name);
 
       /*Lectura del inode del archivo. */
       ok=stat(archivo,&buf);
      
       /*Si el archivo es un subdirectorio, llamamos nuevamente a otroTree.*/
       if (ok!=-1 && (buf.st_mode & S_IFMT) == S_IFDIR)
       {
              for (i=0;i<nivel;i++)
                  printf("\t");
                 printf ("%s %s \n",dp->d_name, opciones.mostrar_archivos ? "(d)":"");

            /* Si es referencia a "este directorio" (.) o el "directiorio padre" (..), saltar) */
           if (!strcmp(".", dp->d_name) || !strcmp("..", dp->d_name))
                continue;   

                 ++nivel;
                 otroTree(archivo,opciones);
              --nivel;
        }
                  /* Si el archivo no es un directorio y esta activa la opcion
                                Mostrar_archivos (-f), presentamos por pantalla el nombre del
                                archivo y su tipo.*/
         else {
                   if (ok !=-1 && opciones.mostrar_archivos== SI) {
                      for (i=0;i<nivel;i++)
                          printf ("\t");
                      switch (buf.st_mode & S_IFMT)
                      {
                    case S_IFREG:
                           if (buf.st_mode & 0111)
                        tipo_archivo = 'x';
                               else
                               tipo_archivo = 'o';
                            break;
                      case S_IFCHR:
                             tipo_archivo = 'c';
                             break;
                      case S_IFBLK:
                             tipo_archivo = 'b';
                             break;
                      case S_IFIFO:
                             tipo_archivo = 'p';
                             break;
                      default:
                             tipo_archivo = '?';
                     } //switch
                fprintf(stdout,"(%c) %s \n", tipo_archivo, dp->d_name);
            }else 
                    fprintf(stdout," %s \n", dp->d_name);
                }
   } /* while */
   closedir(dirp);
} /* otroTree */
