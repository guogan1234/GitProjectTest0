#pragma once

#include <windows.h>
#include <stdio.h>
#include "JpegDefines.h"
#include <stdarg.h> 

class JPEGWriter;

#define ERROR_RANGE_EXCEED -16
#define ERROR_ZERO_PTR -256
#define ERROR_NO_VLC -32

//-----------------------------------JPEGEncoder-----------------------------

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


class JPEGEncoder
{
public:
	JPEGEncoder(bool p_textOutput = false);
	~JPEGEncoder();
	void SetPicSize(int xdim, int ydim, int xoff, int yoff, int width, int height);
	void SetDCHuffTable(unsigned long dc_data[], unsigned long dc_len[]);
	void SetACHuffTable(unsigned long ac_data[], unsigned long ac_len[]);
	void SetQuantTable(unsigned char qu_tab[]);
	void Set2ndQuantTable(unsigned char qu_tab[]);
	void SetColSample(unsigned char Color, 
					int Horiz_Samp_Y = 1, int Vert_Samp_Y = 1,
					int Horiz_Samp_C = 1, int Vert_Samp_C = 1);
	void SetVLCBitstream(unsigned char codes[], unsigned long bytes);
	void InitOutputWriter(const TCHAR* FileName, bool fileAccessEnabled = true);
	unsigned int EncodePic(unsigned char* Pic_Data);
	int GetBuffer(unsigned char** buffer, int** length);

private:
	JPEGWriter *Writer;
	pic_header_t HeadInfo;
	huff_t DCHuffTable;
	huff_t ACHuffTable;
	const unsigned char* QUTable;
	const unsigned char* QUTable2;
	unsigned char* Bitstream;
	unsigned long BitstreamLen;
	bool	textOutput;
	
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

	int fprintf( FILE * stream, const char * format, ... );
};


