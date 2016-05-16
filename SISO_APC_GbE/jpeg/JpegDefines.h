#pragma once

#include <wtypes.h>

typedef struct pic_header_s {
	int xdim,ydim;
	int xoff,yoff;
	int width,height;
	int color;
	int Horiz_Sample_Y;
	int Vert_Sample_Y;
	int Horiz_Sample_C;
	int Vert_Sample_C;
	int row_len; 
	int col_len;

} pic_header_t;

typedef struct buffer_s {
	unsigned char *data;
	int size;
	int position;
} buffer_t;

typedef struct huff_list {
	CHAR Class;
	CHAR BITS[17];
	int sum;
	CHAR HUFFVAL[255];
	long HUFFSIZE[255];
	long HUFFCODE[255];
	unsigned long *huff_code;
	unsigned long *huff_size;
	signed int VALPTR[16+1];
	long MINCODE[16+1];
	long MAXCODE[16+1];
	int LASTK;
	struct huff_list *next;
} huff_t;
