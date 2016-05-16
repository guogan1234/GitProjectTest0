//+-------------------------------------------------------------------
//
//  JPEG Encoder
//  Copyright (C) Silicon Software GmbH, 1997.
//
//
//--------------------------------------------------------------------

#include "JPEGEncoder.h"
#include "JPEGWriter.h"
#include "HUFF.h"

//-----------------------------------JPEGEncoder-----------------------------
/*
// JPEG Marker-Definitionen
#define SOI_MARKER (WORD)0xffd8
#define EOI_MARKER (WORD)0xffd9
#define SOS_MARKER (WORD)0xffda

#define SOF0_MARKER (WORD)0xffc0
#define SOF1_MARKER (WORD)0xffc1
#define SOF2_MARKER (WORD)0xffc2
#define SOF3_MARKER (WORD)0xffc3
#define DHT_MARKER (WORD)0xffc4
#define SOF5_MARKER (WORD)0xffc5
#define SOF6_MARKER (WORD)0xffc6
#define SOF7_MARKER (WORD)0xffc7
#define SOF8_MARKER (WORD)0xffc8
#define SOF9_MARKER (WORD)0xffc9
#define SOFa_MARKER (WORD)0xffca
#define SOFb_MARKER (WORD)0xffcb
#define SOFc_MARKER (WORD)0xffcc
#define SOFd_MARKER (WORD)0xffcd
#define SOFe_MARKER (WORD)0xffce
#define SOFf_MARKER (WORD)0xffcf

#define APP0_MARKER (WORD)0xffe0
#define COM_MARKER (WORD)0xfffe
#define DQT_MARKER (WORD)0xffdb

class JPEGEncoder: JPEGHAP
{
public:
	JPEGEncoder();
	~JPEGEncoder();
	SetPicSize(int xdim, int ydim, int xoff, int yoff, int width, int height);
	SetDCHuffTable(unsigned long dc_data[], unsigned long dc_len[]);
	SetACHuffTable(unsigned long ac_data[], unsigned long ac_len[]);
	SetQuantTable(unsigned char qu_tab[]);
	Set2ndQuantTable(unsigned char qu_tab[]);
	SetColSample(unsigned char Color, 
					int Horiz_Samp_Y = 1, int Vert_Samp_Y = 1,
					int Horiz_Samp_C = 1, int Vert_Samp_C = 1);
	InitOutputWriter(const char* FileName);
	EncodePic(char* Pic_Data);

private:
	JPEGWriter *Writer;
	pic_head_t HeadInfo;
	huff_t DCHuffTable;
	huff_t ACHuffTable;
	const unsigned char* QUTable;
	const unsigned char* QUTable2;
	
	int append_soi_marker();
	int append_eoi_marker();
	WORD write_table_misc();
	int append_sof_marker();
	void encode_scan();

	int append_com();
	int append_app0();
	int append_dqt();
	int append_dqt2();
	int append_dc_huffman();
	int append_ac_huffman();
	int append_baseline_dct();
};
*/

//-----------------------------------JPEGEncoder-----------------------------

JPEGEncoder::JPEGEncoder(bool p_textOutput)
{
	Writer = NULL;
	HeadInfo.xdim = 0;
	HeadInfo.ydim = 0;
	HeadInfo.xoff = 0;
	HeadInfo.yoff = 0;
	HeadInfo.width = 0;
	HeadInfo.height = 0;
	HeadInfo.row_len = 0;
	HeadInfo.col_len = 0;
	HeadInfo.color = 0;
	HeadInfo.Horiz_Sample_Y = 1;
	HeadInfo.Vert_Sample_Y = 1;
	HeadInfo.Horiz_Sample_C = 1;
	HeadInfo.Vert_Sample_C = 1;
	QUTable = NULL;
	QUTable2 = NULL;
	Bitstream = NULL;
	BitstreamLen = 0;
	textOutput = p_textOutput;
}

/* ================================================ */

JPEGEncoder::~JPEGEncoder()
{
	if (Writer != NULL) delete(Writer);
}

/* ================================================ */

void JPEGEncoder::InitOutputWriter(const TCHAR* FileName, bool fileAccessEnabled)
{
	if (Writer != NULL) delete(Writer);
	Writer = new JPEGWriter(fileAccessEnabled);
	if (Writer == NULL)
	{
		fprintf(stderr, "ERROR - Allocation of JPEGWriter-object failed\n");
		exit(-1);
	}
	if (Writer->GetBufPosPtr() == NULL) 
	{
		fprintf(stderr, "ERROR - initialization of JPEGWriter failed\n");
		exit(-1);
	}
	Writer->OpenFile(FileName);
}

/* ================================================ */

void JPEGEncoder::SetPicSize(int xdim, int ydim, int xoff, int yoff, 
						int width, int height)
{
	HeadInfo.xdim = xdim;
	HeadInfo.ydim = ydim;
	HeadInfo.xoff = xoff;
	HeadInfo.yoff = yoff;
	HeadInfo.row_len = width / 8;
	HeadInfo.col_len = height / 8;
	HeadInfo.width = HeadInfo.row_len * 8;
	HeadInfo.height = HeadInfo.col_len * 8;
}

void JPEGEncoder::SetColSample(unsigned char Color, 
						  int Horiz_Samp_Y, int Vert_Samp_Y,
						  int Horiz_Samp_C, int Vert_Samp_C)
{
	HeadInfo.color = Color;
	HeadInfo.Horiz_Sample_Y = Horiz_Samp_Y;
	HeadInfo.Vert_Sample_Y = Vert_Samp_Y;
	HeadInfo.Horiz_Sample_C = Horiz_Samp_C;
	HeadInfo.Vert_Sample_C = Vert_Samp_C;
}
/* ================================================ */

void JPEGEncoder::SetDCHuffTable(unsigned long dc_data[], unsigned long dc_len[])
{
	DCHuffTable.huff_code = &(dc_data[0]);
	DCHuffTable.huff_size = &(dc_len[0]);
	create_hufftable(&DCHuffTable);
}

/* ================================================ */
	
void JPEGEncoder::SetACHuffTable(unsigned long ac_data[], unsigned long ac_len[])
{
	ACHuffTable.huff_code = &(ac_data[0]);
	ACHuffTable.huff_size = &(ac_len[0]);
	create_hufftable(&ACHuffTable);
}

/* ================================================ */

void JPEGEncoder::SetQuantTable(unsigned char qu_tab[])
{
	QUTable = &(qu_tab[0]);
}

/* ================================================ */

void JPEGEncoder::Set2ndQuantTable(unsigned char qu_tab[])
{
	QUTable2 = &(qu_tab[0]);
}

void JPEGEncoder::SetVLCBitstream(unsigned char codes[], unsigned long bytes)
{
	Bitstream		= &(codes[0]);
	BitstreamLen	= bytes;
}

/* ================================================ */

unsigned int JPEGEncoder::EncodePic(unsigned char* Pic_Data)
{
	int CodeBytes;

	// Test integrity of parameters
	if(Writer == NULL){
		return ERROR_ZERO_PTR;
	}

	// check for correct image dimensions
	if ((HeadInfo.xdim <0)){
		return ERROR_RANGE_EXCEED;
	}
	if ((HeadInfo.ydim <0)){
		return ERROR_RANGE_EXCEED;
	}

	if ((HeadInfo.xoff <0) || (HeadInfo.xoff >HeadInfo.xdim)){
		return ERROR_RANGE_EXCEED;
	}
	if ((HeadInfo.yoff <0) || (HeadInfo.yoff >HeadInfo.ydim)){
		return ERROR_RANGE_EXCEED;
	}

	// Test width and height
	if((HeadInfo.width < 8 ) || 
		((HeadInfo.width + HeadInfo.xoff) > HeadInfo.xdim))
	{
		return ERROR_RANGE_EXCEED;
	}
	if((HeadInfo.height < 8 ) || 
		((HeadInfo.height + HeadInfo.yoff) > HeadInfo.ydim))
	{
		return ERROR_RANGE_EXCEED;
	}

	// Test, if QuantTables are specified
	if((QUTable == NULL)||((HeadInfo.color!=0)&&(QUTable2 == NULL)))
	{
		return ERROR_ZERO_PTR;
	}

	Writer->ClearBuf();

	// Test if bitstream of variable length codes is provided
	if ((Bitstream == NULL)||(BitstreamLen == 0))
	{
		return ERROR_NO_VLC;
	}

	// generate Jfif header structure

	append_soi_marker();
	write_table_misc();
	append_sof_marker();
	
	encode_scan();

	// code image data
	
	Writer->put_jchar((char*)Bitstream, BitstreamLen);

	// EOI-marker

	append_eoi_marker();

	Pic_Data = Writer->GetBufPosPtr();
	CodeBytes = Writer->GetBufPos();
	Writer->Buf2File();

	Writer->CloseFile();

	return CodeBytes;
}

/* ================================================ */

 //
 //append_soi_marker
 //

int JPEGEncoder::append_soi_marker()
{
 	WORD marker;
	
	marker = SOI_MARKER;
	Writer->put_word(marker);

	return 0;
 }

 /* ================================================ */

 //
 //append_eoi_marker
 //

int JPEGEncoder::append_eoi_marker()
{
 	WORD marker;
	
	marker = EOI_MARKER;
	Writer->put_word(marker);

	return 0;
 }

/* ================================================ */
 
 //
 // WRITE_TABLE_MISC
 //


WORD JPEGEncoder::write_table_misc()
{
  	append_app0();
	append_com();
	append_dqt();
	if (HeadInfo.color) append_dqt2();
	return 0;
 }

 /* ================================================ */

 //
 // APPEND_APP0
 //

int JPEGEncoder::append_app0()
{
   WORD w,len,version,aufh,aufv;
   CHAR c[256],br,ho;
   
   w = APP0_MARKER;
   Writer->put_word(w);

   // length of data block
   len = 2+5+2+1+2+2+1+1;
   Writer->put_word(len);
   fprintf(stdout,"  app0 len : %d\n",len);

   // Identification: JFIF
   sprintf(c,"%c%c%c%c%c",'J','F','I','F',0);
   Writer->put_jchar(c,5);
   fprintf(stdout,"  id %s,%x,%x,%x,%x,%x\n",c,c[0],c[1],c[2],c[3],c[4]);


   // get version number
   version = 0;
   Writer->put_word(version);
   fprintf(stdout,"  version %x\n",version);

   // resolution
   c[0] = 0;
   Writer->put_jchar(c,1);
   fprintf(stdout,"  Resolution: %d\n",c[0]);

   // horizontal resolution
   aufh = 1;
   Writer->put_word(aufh);
   // vertical resolution
   aufv = 1;
   Writer->put_word(aufv);
   fprintf(stdout,"  h,v resolution: %d,%d\n",aufh,aufv);

   //width of thumbnail image
   br = 0;
   Writer->put_jchar(&br,1);
   fprintf(stdout,"  Width of thumbnail: %d\n",br);

   //height of thumbnail image
   ho = 0;
   Writer->put_jchar(&ho,1);
   fprintf(stdout,"  heigth of thumbnail: %d\n",ho);    

	return 0;
}

 /* ================================================ */

int JPEGEncoder::append_com()
{
   WORD w,len;
   CHAR c[256];
   
   sprintf(c,"CREATOR: SISO   \n");

   w = COM_MARKER;
   Writer->put_word(w);
   len = 2+strlen(c);
   Writer->put_word(len);
   
   Writer->put_jchar(c,len-2);
   fprintf(stdout,"  comment : %s\n",c);
   
   return 0;
 }

 /* ================================================ */

int de_zig_zag[64] = {
	0,1,8,16,9,2,3,10,
	17,24,32,25,18,11,4,
	5,12,19,26,33,40,
	48,41,34,27,20,13,6,
	7,14,21,28,35,42,49,
	56,57,50,43,36,29,22,15,
	23,30,37,44,51,58,59,52,
	45,38,31,39,46,53,60,
	61,54,47,55,62,63};

int JPEGEncoder::append_dqt()
{
   WORD w,len;
   CHAR prec_ident;
   int i;

   w = DQT_MARKER;
   Writer->put_word(w);

   len = 2+65;
   Writer->put_word(len);
   fprintf(stdout,"  len of dqt: %d\n",len);

   //precision and identification
   prec_ident = 0;
   Writer->put_jchar(&prec_ident,1);
   fprintf(stdout,"  precison and identifier: %d\n",prec_ident);

   // quant table

   for(i=0;i<64;i++)
	Writer->put_jchar((char*)&(QUTable[de_zig_zag[i]]),1);
   fprintf(stdout,"  got quant table\n");

   return 0;
 }

int JPEGEncoder::append_dqt2()
{
   WORD w,len;
   CHAR prec_ident;
   int i;

   w = DQT_MARKER;
   Writer->put_word(w);

   len = 2+65;
   Writer->put_word(len);
   fprintf(stdout,"  len of dqt: %d\n",len);

   prec_ident = 0x01;
   Writer->put_jchar(&prec_ident,1);
   fprintf(stdout,"  precison and identifier: %d\n",prec_ident);

   // quant table

   for(i=0;i<64;i++)
	Writer->put_jchar((char*)&(QUTable2[de_zig_zag[i]]),1);
   fprintf(stdout,"  got 2nd quant table\n");

   return 0;
 }

 /* ================================================ */

int JPEGEncoder::append_sof_marker()
{
	
	append_baseline_dct();

	append_dc_huffman();
	append_ac_huffman();
	return 0;
 }

 /* ================================================ */


int JPEGEncoder::append_baseline_dct()
{
	WORD len,num_of_lines,num_of_samples_per_lines,w;
	CHAR prec,num_of_cols,col_inf[3];
	int n,i;

	w = SOF0_MARKER;
	Writer->put_word(w);

	// calc len of frame header
	len = 2+1+2+2+1+3*(1+2*HeadInfo.color);
	Writer->put_word(len);
	fprintf(stdout,"  len: %d\n",len);

	// prec
	prec = 8;
	Writer->put_jchar(&prec,1);
	fprintf(stdout,"  precision: %d\n",prec);

	//number of line
	num_of_lines = 8*(HeadInfo.height/8);
	Writer->put_word(num_of_lines);
	fprintf(stdout,"  num of lines %d\n",num_of_lines);

	//number of samples perline
	num_of_samples_per_lines = 8*(HeadInfo.width/8);
	Writer->put_word(num_of_samples_per_lines);
	fprintf(stdout,"  num of samples per line %d\n",num_of_samples_per_lines);

	// number of color components
	num_of_cols = 1 + 2*HeadInfo.color;
	Writer->put_jchar(&num_of_cols ,1);
	fprintf(stdout,"  num of col components: %d\n",num_of_cols);

	n = num_of_cols;

	
	for(i = 0; i < n; i++){
		col_inf[0] = i;
		if(i== 0){
			col_inf[1] = HeadInfo.Horiz_Sample_Y * 0x10 + HeadInfo.Vert_Sample_Y;
			col_inf[2] = 0;
		} else {
			col_inf[1] = HeadInfo.Horiz_Sample_C * 0x10 + HeadInfo.Vert_Sample_C;
			col_inf[2] = 1;
		}

		Writer->put_jchar(col_inf,3);				
	}

	return 0;
 }

 /* ================================================ */


int JPEGEncoder::append_dc_huffman()
{
	WORD len,w;
	int i,sum;
	huff_t *hl= NULL;

	w = DHT_MARKER;
	Writer->put_word(w);
	fprintf(stdout, "DC-Huffman-Table \n");

	for(i=1,sum=0;i<17;i++){
		sum  += DCHuffTable.BITS[i];
	}
	fprintf(stdout,"  sum %d\n",sum);

	// get len of DHT-marker-segment
	len = 2+1+16+sum;
	Writer->put_word(len);
	fprintf(stdout,"  len: %d\n",len);

	DCHuffTable.Class = 0;
	Writer->put_jchar(&(DCHuffTable.Class),1);
	fprintf(stdout,"  Table class: %d\n",DCHuffTable.Class);
	
	// huflen 
	Writer->put_jchar(&(DCHuffTable.BITS[1]),16);
	fprintf(stdout,"  got 16 huff_lens\n");

	DCHuffTable.sum = sum;
	Writer->put_jchar(DCHuffTable.HUFFVAL,sum);

	fprintf(stdout,"  put %d elements\n",sum);

	return 0;
 }

   /* ================================================ */

int JPEGEncoder::append_ac_huffman()
{
	WORD len,w;
	int i,sum;
	huff_t *hl= NULL;

	w = DHT_MARKER;
	Writer->put_word(w);
	fprintf(stdout, "AC-Huffman-Table \n");

	for(i=1,sum=0;i<17;i++){
		sum  += ACHuffTable.BITS[i];
	}
	fprintf(stdout,"  sum %d\n",sum);

	// get len of DHT-marker-segment
	len = 2+1+16+sum;
	Writer->put_word(len);
	fprintf(stdout,"  len: %d\n",len);

	ACHuffTable.Class = 16;
	Writer->put_jchar(&(ACHuffTable.Class),1);
	fprintf(stdout,"  Table class: %d\n",ACHuffTable.Class);
	
	// huflen 
	Writer->put_jchar(&(ACHuffTable.BITS[1]),16);
	fprintf(stdout,"  got 16 huff_lens\n");

	ACHuffTable.sum = sum;
	Writer->put_jchar(ACHuffTable.HUFFVAL,sum);

	fprintf(stdout,"  put %d elements\n",sum);

	return 0;
 }

 /* ================================================ */

void JPEGEncoder::encode_scan()
{
	 WORD len,w;
	 CHAR num_of_comps,comps[2],ss,se,a;
	 int i;

	 w = SOS_MARKER;
	 Writer->put_word(w);

     num_of_comps = 1+2*HeadInfo.color;

	 // get len
	 len = 2 + 1 + 2*(num_of_comps)+ 3 ;
	 Writer->put_word(len);
	 fprintf(stdout,"  len %d\n",len);

	 //number of comps
	
	 Writer->put_jchar(&num_of_comps,1);
	 fprintf(stdout,"  num of comps :%d\n",num_of_comps);

	 // write comps
	 
	 for(i=0;i<num_of_comps;i++){
	   comps[0] = i;
       comps[1] = 0;
	   Writer->put_jchar(comps,2);
	 }

	 // write start of spectral 
	 ss = 0;
	 Writer->put_jchar(&ss,1);
	 fprintf(stdout,"  ss = %d\n",ss);

	 // write end of spectral 
	 se = 63;
	 Writer->put_jchar(&se,1);
	 fprintf(stdout,"  se = %d\n",se);

	 // write successive approximation information
	 a = 0;
	 Writer->put_jchar(&a,1);
	 fprintf(stdout, "  ah/al = %d\n",a);
}


/* ================================================ */

int JPEGEncoder::GetBuffer(unsigned char** p_buffer, int** p_length)
{
	return Writer->GetBuffer(p_buffer, p_length);
}

int JPEGEncoder::fprintf( FILE * stream, const char * format, ... )
{
	if (textOutput)
	{
		va_list arglist;
		va_start(arglist, format); 
		int n = ::vfprintf(stream, format, arglist);
		return n;
	}
	return 0;
};