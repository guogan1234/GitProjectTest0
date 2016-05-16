//+-------------------------------------------------------------------
//
//  JPEG Encoder
//  Copyright (C) Silicon Software GmbH, 1997.
//
//
//--------------------------------------------------------------------

#include "JpegDefines.h"
//#include "stdafx.h"

int generate_size_table(huff_t *hl){
	int i,k,j;

	k=0;i=1;j=1;

	bool repeat = true;

	while(repeat)
	{
		if(j > hl->BITS[i]) 
		{
			i = i+1;
			j = 1;

			if(i>16)
			{
				hl->HUFFSIZE[k] =0;
				hl->LASTK = k;
				repeat = false;
			} 
			else 
			{
			}
		} 
		else 
		{
			hl->HUFFSIZE[k]=i;
			k=k+1;
			j=j+1;
		}
	} //of while
	return 0;
}

int generate_code_table(huff_t *hl){
	long k,code,si;

	k=0; code = 0; si = hl->HUFFSIZE[0];

	bool repeat = true;

	while (repeat)
	{
		hl->HUFFCODE[k] = code;
		code = code +1;
		k = k + 1;

		if(hl->HUFFSIZE[k] == si)
		{
			//
		} 
		else 
		{
			if (hl->HUFFSIZE[k] == 0)
			{
				repeat = false;
			}
			else 
			{
				bool shift = true;
				while(shift)
				{
					code = code << 1;
					si = si + 1;
					if(hl->HUFFSIZE[k] == si ) 
					{
						shift = false;
					} 
					else
					{
						//
					}
				}
			}
		}
	}
	return 0;
}


int decoder_table_(huff_t *hl){
	int i,j;

	i = 0; j= 0;
	bool repeat = true;
	while(repeat)
	{
		i = i+1;
		if (i > 16) 
		{
			repeat = false;
		} 
		else 
		{
			if (hl->BITS[i] == 0)
			{
				hl->MAXCODE[i] = -1;
			} 
			else 
			{
				hl->VALPTR[i] = j;
				hl->MINCODE[i] = hl->HUFFCODE[j];
				j = j + hl->BITS[i] -1;
				hl->MAXCODE[i] = hl->HUFFCODE[j];
				j = j + 1;
			}
		}
	}
	return 0;
}


int huffcode_to_bits(huff_t *huf){
	int i;


	for(i=0;i<17;i++){
		huf->BITS[i] = 0;
	}

	for(i=0;i<256;i++){
		huf->BITS[huf->huff_size[i]] += 1;		
	}

	generate_size_table(huf);
	generate_code_table(huf);
	decoder_table_(huf);

	return 0;
}

int gen_hufval(huff_t* huf){
	int i,j,l;
	unsigned char value;
	long code;

	for(l=255;l>=0;l--){
		huf->HUFFVAL[l]=0;
	}

	for(l=0;l<256;l++)
	{
		i = 1;
		code = huf->huff_code[l];
		if(huf->huff_size[l] == 0) continue;

		bool repeat = true;
		while (repeat)
		{
			if (code > huf->MAXCODE[i]) 
			{
				i = i +1;
			} 
			else 
			{
				j = huf->VALPTR[i];
				j = j + code - huf->MINCODE[i];
				value = l;
				huf->HUFFVAL[j]=value;
				repeat = false;
			}
		}
	}
	return 0;
}

int create_hufftable(huff_t *hufft)
{
	huffcode_to_bits(hufft);
	gen_hufval(hufft);

	return 0;
}

