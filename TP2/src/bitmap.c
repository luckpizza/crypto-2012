/*
 * bitmap.c
 *
 *  Created on: Jun 3, 2012
 *      Author: luckpizza
 */

#include "bitmap.h"
#include "debug.h"
#include "memory_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define fread_with_error(a,b,c,d) if(fread(a,b,c,d) != c){error("there was an error reading the file"); return NULL;}

#define BMP_SIGNATURE "BM"

simple_8bits_BMP_t *
load_bmp_from_file( char * file_path)
{
	int unused;
	int read;
	int still_to_read = 0;
	//int px_array_offset;
	DIB_header_t * dib_header = my_malloc(sizeof(DIB_header_t));
	simple_8bits_BMP_t * img = my_malloc(sizeof(simple_8bits_BMP_t));
	if(img != NULL)
	{
		memset(img, 0, sizeof(simple_8bits_BMP_t));
	}
	FILE * file = fopen(file_path, "rb");
	if (!file)
		{
			fprintf(stderr, "Unable to open file %s", file_path);
			return NULL;
		}
	fread(&img->signature, 2, 1, file );
	if(strcmp(img->signature, BMP_SIGNATURE))
	{
		error("File seems not to be a BITMAP");
		return NULL;
	}
	fread_with_error(&img->file_size, 4, 1, file);
	fread_with_error(&unused, 4, 1, file);
	fread_with_error(&img->file_offset, 4, 1, file);
	fread_with_error(&dib_header->size,4,1, file );
	fread_with_error(&dib_header->width, dib_header->size, 1, file);
	still_to_read = img->file_offset - ftell(file);
	dib_header->extra = my_malloc(still_to_read );
	memset(dib_header->extra, 0, still_to_read);
	fread_with_error(dib_header->extra, still_to_read, 1, file);
//	fseek(file, img->file_offset, SEEK_SET);
	img->img = my_malloc(dib_header->height * sizeof(char*));
	memset(img->img, 0, dib_header->height * sizeof(char*));
	int i;
	for( i = 0 ; i <dib_header->height; ++i)
	{
		img->img[i] =  malloc(dib_header->width );
		memset(img->img[i], 0, dib_header->width);
		read = fread(img->img[i], ((dib_header->bitxpixel/8) * dib_header->width), 1, file);
		if(read != 1)
		{
			//ERROR
		}else if((((dib_header->bitxpixel/8) * dib_header->width) % 4) != 0)
		{
			fseek(file, (((dib_header->bitxpixel/8) * dib_header->width) % 4), SEEK_CUR);
		}
		if(i == 37){
			printf("asd");
		}
	}
	img->dib_header = dib_header;
	return img;

}
int
save_bmp_to_file( simple_8bits_BMP_t* img, char * file_path)
{
	int unused = 0;
	int read;
	int still_to_read = 0;

	FILE * file = fopen(file_path, "wb");
	if (!file)
		{
			fprintf(stderr, "Unable to open file %s", file_path);
			return NULL;
		}
	fwrite(&img->signature, 2, 1, file );

	fwrite(&img->file_size, 4, 1, file);
	fwrite(&unused, 4, 1, file);
	fwrite(&img->file_offset, 4, 1, file);
	fwrite(&img->dib_header->size,4,1, file );
	fwrite(&img->dib_header->width, img->dib_header->size, 1, file);

	still_to_read = img->file_offset - ftell(file);
	fwrite(img->dib_header->extra, still_to_read, 1, file);

	int i;
	for( i = 0 ; i < img->dib_header->height; ++i)
	{
		read = fwrite(img->img[i], (img->dib_header->bitxpixel/8) * img->dib_header->width, 1, file);
		if(read != 1)
		{
			//ERROR
		}else if((((img->dib_header->bitxpixel/8) * img->dib_header->width) % 4) != 0)
		{
			fwrite(&unused, (((img->dib_header->bitxpixel/8) * img->dib_header->width) % 4), 1, file);
		}
	}
	fflush(file);
	fclose(file);
	return 1;

}
