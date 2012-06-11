#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "bitmap.h"
#include "share_secret.h"

#define TRUE 1
#define FALSE 0

#define DISTRIBUTE 0
#define RECOVER 1

typedef struct
{
    const char* name;
    int         has_arg;
    int*        flag;
    int         val;
} option;

struct option* InitOptionStruct(void);

unsigned int IsValid(unsigned int distribute,
                     unsigned int recover,
                     const char* secret,
                     unsigned int min_shadows,
                     unsigned int shadows);

unsigned int preprocess(unsigned int action,
                        char* secret,
                        unsigned int min_shadows,
                        unsigned int shadows,
                        const char* directory);

unsigned int readDirectoryFiles(simple_8bits_BMP_t** secret,
				const char* directory,
				simple_8bits_BMP_t** shadowFiles,
				unsigned int shadows,
				unsigned int action);

unsigned int validImages(simple_8bits_BMP_t* image,
			 simple_8bits_BMP_t** shadowFiles,
			 int readFileAmount);

void PrintHelp(void);

int
main(int argc, char* argv[])
{
    int indexptr = 0;
    int opt = 0;

    unsigned int distribute = FALSE;
    unsigned int recover = FALSE;
    unsigned int min_shadows = 0;
    unsigned int shadows = 0;
    unsigned int help = FALSE;
    unsigned int error = FALSE;

    char* secret = NULL;
    char* directory = NULL;

    static struct option options[8] =
    {
        {"d", no_argument, 0, 'd'},
        {"r", no_argument, 0, 'r'},
        {"secret", required_argument, 0, 's'},
        {"k", required_argument, 0, 'k'},
        {"n", required_argument, 0, 'n'},
        {"dir", required_argument, 0, 'e'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    /*Uso getopt para parsear los argumentos pasados por lines de comando.*/
    while (!error && !help && (opt = getopt_long_only(argc, argv,
                                     "drs:k:n:e:h", options, &indexptr)) != -1)
    {
        switch (opt)
        {
            case 'd':
                distribute = TRUE;
                break;
            case 'r':
                recover = TRUE;
                break;
            case 's':
                secret = optarg;
                break;
            case 'k':
                min_shadows = atoi(optarg);
                break;
            case 'n':
                shadows = atoi(optarg);
                break;
            case 'e':
                directory = optarg;
                break;
            case 'h':
                help = TRUE;
                break;
            case -1 :
            case ':':
            case '?':
                printf("La opcion %s requiere que ingrese un parametro.\n",
                       options[optind].name);
                error = TRUE;
                break;
        }
    }

    if (!error && !help)
    {
        /*Verifico que la combinacion de parametros sea correcta*/
        if (IsValid(distribute, recover, secret, min_shadows, shadows))
        {
            unsigned int action = distribute == 1 ? DISTRIBUTE : RECOVER;
            if (preprocess(action, secret, min_shadows, shadows, directory))
                printf("Listo!\n");
            else
                exit(EXIT_FAILURE);
        }
        else
        {
            PrintHelp();
            exit(EXIT_FAILURE);
        }
    }
    else if (help)
    {
        /*El usuario uso pidio que se imprima el menu de ayuda*/
        PrintHelp();
        exit(EXIT_SUCCESS);
    }
    else
    {
        /*Se producjo un error en el parseo de los comandos*/
        PrintHelp();
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

unsigned int
IsValid(unsigned int distribute,
        unsigned int recover,
        const char* secret,
        unsigned int min_shadows,
        unsigned int shadows)
{
    if ((distribute && recover) || (!distribute && !recover))
    {
        printf("Se debe especificar si se desea recuperar el secreto (r) o " \
               "distribuirlo (d). No ambos.\n");
        return FALSE;
    }

    if (secret == NULL)
    {
        printf("Se debe especificar una imagen como parametro para el " \
               "parametro secret.\n");
        return FALSE;
    }

    if (!(1 < min_shadows && min_shadows < 5))
    {
        printf("La cantidad minima de sombras (k) debe ser un valor entre " \
               "2 y 4.\n");
        return FALSE;
    }

    if (!distribute && shadows != 0)
    {
        printf("La cantidad de sombras (n) solo debe ser especificada si se " \
               "desea distribuir el secreto.\n");
        return FALSE;
    }

    if (shadows != 0 && !(2 < shadows && shadows < 9))
    {
        printf("La cantidad total de sombras (n) debe ser un valor entre " \
               "2 y 8.\n");
        return FALSE;
    }

    if(shadows!=0 && min_shadows>shadows)
    {
	printf("La cantidad minima de sombras necesarias para recuperar el " \
	       "secreto no puede ser mayor que la cantidad total de sombras " \
	       "a utilizar.\n");
	return FALSE;
    }

    return TRUE;
}

unsigned int
preprocess(unsigned int action,
           char* secret,
           unsigned int min_shadows,
           unsigned int shadows,
           const char* directory)
{
    unsigned int readFileAmount = 0,i=0;
    int j=0;
    unsigned int shadowsAux=shadows;
    shadows = shadows==0?min_shadows:shadows;
    unsigned int shadowsAmount = shadows == 0 ? 8 : shadows;
    simple_8bits_BMP_t** shadowFiles;
    simple_8bits_BMP_t* image = NULL;

    shadowFiles = calloc(8+1, sizeof(simple_8bits_BMP_t*));
    if (shadowFiles == NULL)
    {
        printf("Se ha producido un error al alocar memoria.\n");
        return FALSE;
    }

    if (strstr(secret, ".bmp") != NULL || strstr(secret, ".BMP") != NULL)
    {
	if(action==DISTRIBUTE)
	{
	    image = load_bmp_from_file(secret);
	    if(image==NULL)
	    {
		free(shadowFiles);
		return FALSE;
	    }
	}
    }
    else
    {
        printf("El archivo especificado con -secret no tiene extension .bmp.\n");
        return FALSE;
    }

    readFileAmount = readDirectoryFiles(&image, directory == NULL ? "." : directory, shadowFiles, shadowsAux==0?8:shadowsAmount,action);

    if ((shadows != 0 && readFileAmount < shadows) || (shadows == 0 && !(2 < readFileAmount && readFileAmount < 9)))
    {
        printf("No se pudo leer la cantidad especificada de archivos para ser usados como sombras.\n");
        return FALSE;
    }

    if(validImages(image,shadowFiles,readFileAmount))
    {
	if (action == DISTRIBUTE)
	{
	    share_secret(min_shadows,readFileAmount,image,shadowFiles);

	    while(shadowFiles[i]!=NULL)
	    {
		char outname[256];
		sprintf(outname,"shadow_%d.bmp",i);
		save_bmp_to_file(shadowFiles[i], outname);
		++i;
	    }
	}
	else
	{
	    for(j=0;j<image->dib_header->height;++j)
	    {
		image->img[i]=calloc(1,image->dib_header->width);
	    }
	    get_secret(shadows==0?readFileAmount:shadows,shadowFiles,image);
	    save_bmp_to_file(image, secret);
	}
    }
    else
    {
	return FALSE;
    }

    return TRUE;
}

/*Abre los archivos .BMP de un directorio*/
unsigned int
readDirectoryFiles(simple_8bits_BMP_t** secret,
                   const char* directory,
                   simple_8bits_BMP_t** shadowFiles,
                   unsigned int shadows,
		   unsigned int action)
{
    DIR* dir = NULL, * aux = NULL;
    simple_8bits_BMP_t* shadowImage = NULL;
    struct dirent* file = NULL;
    unsigned int amount = 0;
    if ((dir = opendir(directory)) != NULL)
    {
        while ((file = readdir(dir)) != NULL && amount < shadows)
        {
            /*Aloco y armo un string con el path completo al archivo.*/
            char* fullPath = calloc(strlen(directory) + strlen(file->d_name) + 2, sizeof(char));
            if (fullPath == NULL)
            {
                printf("Se ha producido un error al alocar memoria.\n");
                return 0;
            }
            strncat(fullPath, directory, strlen(directory));
            if (directory[strlen(directory) - 1] != '/')
                strncat(fullPath, "/", 1);
            strncat(fullPath, file->d_name, strlen(file->d_name));
            if ((aux = opendir(fullPath)) == NULL )
            {
                if (strstr(file->d_name, ".bmp") != NULL || strstr(file->d_name, ".BMP") != NULL)
                {
                    /*Si no es un directorio se trata de un archivos*/
		    shadowImage = load_bmp_from_file(fullPath);
		    if(action!=DISTRIBUTE && amount==0)
		    {
			*secret = load_bmp_from_file(fullPath);
		    }
                    shadowFiles[amount] = shadowImage;
                    ++amount;
                }
            }
            else
                closedir(aux);
        }
        closedir(dir);
    }
    else
    {
        printf("El directorio especificado no existe.\n");
        return 0;
    }

    return amount;
}

unsigned int
validImages(simple_8bits_BMP_t* image,simple_8bits_BMP_t** shadowFiles,int readFileAmount)
{
    int height=0,width=0;
    unsigned int i=1;

    if(shadowFiles[0]->dib_header->bitxpixel==8)
    {
	height=shadowFiles[0]->dib_header->height;
	width=shadowFiles[0]->dib_header->width;
    }
    else
    {
	printf("La imagen no es de 8 bits por pixel.\n");
	return FALSE;
    }

    while(i<readFileAmount)
    {
	if(shadowFiles[i]->dib_header->bitxpixel==8)
	{
	    if(width!=shadowFiles[i]->dib_header->width ||
	      height!=shadowFiles[i]->dib_header->height)
	    {
		printf("La dimension de las imagenes es incorrecta.\n");
		return FALSE;
	    }
	}
	else
	{
	    printf("La imagen no es de 8 bits por pixel.\n");
	    return FALSE;
	}
	++i;
    }

    if(image!=NULL)
    {
	if(image->dib_header->bitxpixel==8)
	{
	    if(width!=image->dib_header->width ||
	      height!=image->dib_header->height)
	    {
		printf("La dimension de las imagenes es incorrecta.\n");
		return FALSE;
	    }
	}
	else
	{
	    printf("La imagen no es de 8 bits por pixel.\n");
	    return FALSE;
	}
    }
    return TRUE;
}

void
PrintHelp(void)
{
}
