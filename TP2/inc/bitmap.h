/*
 * bitmap.h
 *
 *  Created on: Jun 3, 2012
 *      Author: luckpizza
 */

#ifndef BITMAP_H_
#define BITMAP_H_
/**
 *
 */

typedef struct DIB_header{
	int size;
	int width;
	int height;
	short planes;
	short bitxpixel;
	int nothing[120];
	unsigned char * extra;
}DIB_header_t;

typedef struct simple_8bits_BMP{
	char signature[2];
	int file_size;
	int reserved;
	int file_offset;
	DIB_header_t * dib_header;
	unsigned char** img;

}simple_8bits_BMP_t;


simple_8bits_BMP_t *
load_bmp_from_file( char * file_path);

int
save_bmp_to_file( simple_8bits_BMP_t* img, char * file_path);

#endif /* BITMAP_H_ */
