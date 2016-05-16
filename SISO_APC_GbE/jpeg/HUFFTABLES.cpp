//+-------------------------------------------------------------------
//
//  JPEG Encoder
//  Copyright (C) Silicon Software GmbH, 1997.
//
//
//--------------------------------------------------------------------

/* ------------------------------------------------------------------------ 
 *
 *
 *  SUBROUTINE create_huffman_dc_table()
 *
 *  purpose: generates the input of the DC table for the Huffman encoder
 *
 *  para   : unsigned long dc_data[12] : 
 *           huffman codeword for the DC table: [size] = 0 .. 0xb
 *           unsigned long dc_len[12] :
 *           length of the huffman DC table codeword: [size] = 0 .. 0xb
 *  return : no return value
 *
 */

void create_dc_table(unsigned long dc_data[], unsigned long dc_len[])
{
	int i;

  dc_data[0]  = 0x0;
  dc_data[1]  = 0x2;
  dc_data[2]  = 0x3;
  dc_data[3]  = 0x4;
  dc_data[4]  = 0x5;
  dc_data[5]  = 0x6;
  dc_data[6]  = 0xe;
  dc_data[7]  = 0x1e;
  dc_data[8]  = 0x3e;
  dc_data[9]  = 0x7e;
  dc_data[10] = 0xfe;
  dc_data[11] = 0x1fe;

  dc_len[0]   = 2;
  dc_len[1]   = 3;
  dc_len[2]   = 3;
  dc_len[3]   = 3;
  dc_len[4]   = 3;
  dc_len[5]   = 3;
  dc_len[6]   = 4;
  dc_len[7]   = 5;
  dc_len[8]   = 6;
  dc_len[9]   = 7;
  dc_len[10]  = 8;
  dc_len[11]  = 9;

  for(i=12;i<256;i++){
	dc_len[i] = 0;
	dc_data[i] = 0;
  }

}


/* ------------------------------------------------------------------------ 
 *
 *
 *  SUBROUTINE create_huffman_ac_table()
 *
 *  file   : huff_data.c
 *  purpose: generates the input of the AC table for the Huffman encoder
 *
 *  para   : unsigned long huff_data[16*16+11] : 
 *           huffman codeword for the AC table: [run*16+size] =[0..0xf*16+0 .. 0xb]
 *           unsigned long huff_len[16*16+11] :
 *           length of the huffman AC table codeword: [run*16+size] =[0..0xf*16+0 .. 0xb]
 *  return : no return value
 *
 */


void create_ac_table(unsigned long huff_data[256], unsigned long huff_len[256])
{
int i;
for(i=0;i<256;i++){
	huff_data[i] = 0;
	huff_len[i]=0;
}

huff_data[0*16+0]= 0xa;
huff_data[0*16+1]= 0x0;
huff_data[0*16+2]= 0x1;
huff_data[0*16+3]= 0x4;
huff_data[0*16+4]= 0xb;
huff_data[0*16+5]= 0x1a;
huff_data[0*16+6]= 0x78;
huff_data[0*16+7]= 0xf8;
huff_data[0*16+8]= 0x3f6;
huff_data[0*16+9]= 0xff82;
huff_data[0*16+10]= 0xff83;

huff_data[1*16+1]= 0xc;
huff_data[1*16+2]= 0x1b;
huff_data[1*16+3]= 0x79;
huff_data[1*16+4]= 0x1f6;
huff_data[1*16+5]= 0x7f6;
huff_data[1*16+6]= 0xff84;
huff_data[1*16+7]= 0xff85;
huff_data[1*16+8]= 0xff86;
huff_data[1*16+9]= 0xff87;
huff_data[1*16+10]= 0xff88;

huff_data[2*16+1]= 0x1c;
huff_data[2*16+2]= 0xf9;
huff_data[2*16+3]= 0x3f7;
huff_data[2*16+4]= 0xff4;
huff_data[2*16+5]= 0xff89;
huff_data[2*16+6]= 0xff8a;
huff_data[2*16+7]= 0xff8b;
huff_data[2*16+8]= 0xff8c;
huff_data[2*16+9]= 0xff8d;
huff_data[2*16+10]= 0xff8e;

huff_data[3*16+1]= 0x3a;
huff_data[3*16+2]= 0x1f7;
huff_data[3*16+3]= 0xff5;
huff_data[3*16+4]= 0xff8f;
huff_data[3*16+5]= 0xff90;
huff_data[3*16+6]= 0xff91;
huff_data[3*16+7]= 0xff92;
huff_data[3*16+8]= 0xff93;
huff_data[3*16+9]= 0xff94;
huff_data[3*16+10]= 0xff95;

huff_data[4*16+1]= 0x3b;
huff_data[4*16+2]= 0x3f8;
huff_data[4*16+3]= 0xff96;
huff_data[4*16+4]= 0xff97;
huff_data[4*16+5]= 0xff98;
huff_data[4*16+6]= 0xff99;
huff_data[4*16+7]= 0xff9a;
huff_data[4*16+8]= 0xff9b;
huff_data[4*16+9]= 0xff9c;
huff_data[4*16+10]= 0xff9d;

huff_data[5*16+1]= 0x7a;
huff_data[5*16+2]= 0x7f7;
huff_data[5*16+3]= 0xff9e;
huff_data[5*16+4]= 0xff9f;
huff_data[5*16+5]= 0xffa0;
huff_data[5*16+6]= 0xffa1;
huff_data[5*16+7]= 0xffa2;
huff_data[5*16+8]= 0xffa3;
huff_data[5*16+9]= 0xffa4;
huff_data[5*16+10]= 0xffa5;

huff_data[6*16+1]= 0x7b;
huff_data[6*16+2]= 0xff6;
huff_data[6*16+3]= 0xffa6;
huff_data[6*16+4]= 0xffa7;
huff_data[6*16+5]= 0xffa8;
huff_data[6*16+6]= 0xffa9;
huff_data[6*16+7]= 0xffaa;
huff_data[6*16+8]= 0xffab;
huff_data[6*16+9]= 0xffac;
huff_data[6*16+10]= 0xffad;

huff_data[7*16+1]= 0xfa;
huff_data[7*16+2]= 0xff7;
huff_data[7*16+3]= 0xffae;
huff_data[7*16+4]= 0xffaf;
huff_data[7*16+5]= 0xffb0;
huff_data[7*16+6]= 0xffb1;
huff_data[7*16+7]= 0xffb2;
huff_data[7*16+8]= 0xffb3;
huff_data[7*16+9]= 0xffb4;
huff_data[7*16+10]= 0xffb5;

huff_data[8*16+1]= 0x1f8;
huff_data[8*16+2]= 0x7fc0;
huff_data[8*16+3]= 0xffb6;
huff_data[8*16+4]= 0xffb7;
huff_data[8*16+5]= 0xffb8;
huff_data[8*16+6]= 0xffb9;
huff_data[8*16+7]= 0xffba;
huff_data[8*16+8]= 0xffbb;
huff_data[8*16+9]= 0xffbc;
huff_data[8*16+10]= 0xffbd;

huff_data[9*16+1]= 0x1f9;
huff_data[9*16+2]= 0xffbe;
huff_data[9*16+3]= 0xffbf;
huff_data[9*16+4]= 0xffc0;
huff_data[9*16+5]= 0xffc1;
huff_data[9*16+6]= 0xffc2;
huff_data[9*16+7]= 0xffc3;
huff_data[9*16+8]= 0xffc4;
huff_data[9*16+9]= 0xffc5;
huff_data[9*16+10]= 0xffc6;

huff_data[10*16+1]= 0x1fa;
huff_data[10*16+2]= 0xffc7;
huff_data[10*16+3]= 0xffc8;
huff_data[10*16+4]= 0xffc9;
huff_data[10*16+5]= 0xffca;
huff_data[10*16+6]= 0xffcb;
huff_data[10*16+7]= 0xffcc;
huff_data[10*16+8]= 0xffcd;
huff_data[10*16+9]= 0xffce;
huff_data[10*16+10]= 0xffcf;

huff_data[11*16+1]= 0x3f9;
huff_data[11*16+2]= 0xffd0;
huff_data[11*16+3]= 0xffd1;
huff_data[11*16+4]= 0xffd2;
huff_data[11*16+5]= 0xffd3;
huff_data[11*16+6]= 0xffd4;
huff_data[11*16+7]= 0xffd5;
huff_data[11*16+8]= 0xffd6;
huff_data[11*16+9]= 0xffd7;
huff_data[11*16+10]= 0xffd8;

huff_data[12*16+1]= 0x3fa;
huff_data[12*16+2]= 0xffd9;
huff_data[12*16+3]= 0xffda;
huff_data[12*16+4]= 0xffdb;
huff_data[12*16+5]= 0xffdc;
huff_data[12*16+6]= 0xffdd;
huff_data[12*16+7]= 0xffde;
huff_data[12*16+8]= 0xffdf;
huff_data[12*16+9]= 0xffe0;
huff_data[12*16+10]= 0xffe1;

huff_data[13*16+1]= 0x7f8;

huff_data[13*16+2]= 0xffe2;
huff_data[13*16+3]= 0xffe3;
huff_data[13*16+4]= 0xffe4;
huff_data[13*16+5]= 0xffe5;
huff_data[13*16+6]= 0xffe6;
huff_data[13*16+7]= 0xffe7;
huff_data[13*16+8]= 0xffe8;
huff_data[13*16+9]= 0xffe9;
huff_data[13*16+10]= 0xffea;

huff_data[14*16+1]= 0xffeb;
huff_data[14*16+2]= 0xffec;
huff_data[14*16+3]= 0xffed;
huff_data[14*16+4]= 0xffee;
huff_data[14*16+5]= 0xffef;
huff_data[14*16+6]= 0xfff0;
huff_data[14*16+7]= 0xfff1;
huff_data[14*16+8]= 0xfff2;
huff_data[14*16+9]= 0xfff3;
huff_data[14*16+10]= 0xfff4;

huff_data[15*16+0]= 0x7f9;
huff_data[15*16+1]= 0xfff5;
huff_data[15*16+2]= 0xfff6;
huff_data[15*16+3]= 0xfff7;
huff_data[15*16+4]= 0xfff8;
huff_data[15*16+5]= 0xfff9;
huff_data[15*16+6]= 0xfffa;
huff_data[15*16+7]= 0xfffb;
huff_data[15*16+8]= 0xfffc;
huff_data[15*16+9]= 0xfffd;
huff_data[15*16+10]= 0xfffe;

huff_len[0*16+0]= 0x4;

huff_len[0*16+1]= 0x2;
huff_len[0*16+2]= 0x2;
huff_len[0*16+3]= 0x3;
huff_len[0*16+4]= 0x4;
huff_len[0*16+5]= 0x5;
huff_len[0*16+6]= 0x7;
huff_len[0*16+7]= 0x8;
huff_len[0*16+8]= 0xa;
huff_len[0*16+9]= 0x10;
huff_len[0*16+10]= 0x10;

huff_len[1*16+1]= 0x4;
huff_len[1*16+2]= 0x5;
huff_len[1*16+3]= 0x7;
huff_len[1*16+4]= 0x9;
huff_len[1*16+5]= 0xb;
huff_len[1*16+6]= 0x10;
huff_len[1*16+7]= 0x10;
huff_len[1*16+8]= 0x10;
huff_len[1*16+9]= 0x10;
huff_len[1*16+10]= 0x10;

huff_len[2*16+1]= 0x5;
huff_len[2*16+2]= 0x8;
huff_len[2*16+3]= 0xa;
huff_len[2*16+4]= 0xc;
huff_len[2*16+5]= 0x10;
huff_len[2*16+6]= 0x10;
huff_len[2*16+7]= 0x10;
huff_len[2*16+8]= 0x10;
huff_len[2*16+9]= 0x10;
huff_len[2*16+10]= 0x10;

huff_len[3*16+1]= 0x6;
huff_len[3*16+2]= 0x9;
huff_len[3*16+3]= 0xc;
huff_len[3*16+4]= 0x10;
huff_len[3*16+5]= 0x10;
huff_len[3*16+6]= 0x10;
huff_len[3*16+7]= 0x10;
huff_len[3*16+8]= 0x10;
huff_len[3*16+9]= 0x10;
huff_len[3*16+10]= 0x10;

huff_len[4*16+1]= 0x6;
huff_len[4*16+2]= 0xa;
huff_len[4*16+3]= 0x10;
huff_len[4*16+4]= 0x10;
huff_len[4*16+5]= 0x10;
huff_len[4*16+6]= 0x10;
huff_len[4*16+7]= 0x10;
huff_len[4*16+8]= 0x10;
huff_len[4*16+9]= 0x10;
huff_len[4*16+10]= 0x10;

huff_len[5*16+1]= 0x7;
huff_len[5*16+2]= 0xb;
huff_len[5*16+3]= 0x10;
huff_len[5*16+4]= 0x10;
huff_len[5*16+5]= 0x10;
huff_len[5*16+6]= 0x10;
huff_len[5*16+7]= 0x10;
huff_len[5*16+8]= 0x10;
huff_len[5*16+9]= 0x10;
huff_len[5*16+10]= 0x10;

huff_len[6*16+1]= 0x7;
huff_len[6*16+2]= 0xc;
huff_len[6*16+3]= 0x10;
huff_len[6*16+4]= 0x10;
huff_len[6*16+5]= 0x10;
huff_len[6*16+6]= 0x10;
huff_len[6*16+7]= 0x10;
huff_len[6*16+8]= 0x10;
huff_len[6*16+9]= 0x10;
huff_len[6*16+10]= 0x10;

huff_len[7*16+1]= 0x8;
huff_len[7*16+2]= 0xc;
huff_len[7*16+3]= 0x10;
huff_len[7*16+4]= 0x10;
huff_len[7*16+5]= 0x10;
huff_len[7*16+6]= 0x10;
huff_len[7*16+7]= 0x10;
huff_len[7*16+8]= 0x10;
huff_len[7*16+9]= 0x10;
huff_len[7*16+10]= 0x10;

huff_len[8*16+1]= 0x9;
huff_len[8*16+2]= 0xf;
huff_len[8*16+3]= 0x10;
huff_len[8*16+4]= 0x10;
huff_len[8*16+5]= 0x10;
huff_len[8*16+6]= 0x10;
huff_len[8*16+7]= 0x10;
huff_len[8*16+8]= 0x10;
huff_len[8*16+9]= 0x10;
huff_len[8*16+10]= 0x10;

huff_len[9*16+1]= 0x9;
huff_len[9*16+2]= 0x10;
huff_len[9*16+3]= 0x10;
huff_len[9*16+4]= 0x10;
huff_len[9*16+5]= 0x10;
huff_len[9*16+6]= 0x10;
huff_len[9*16+7]= 0x10;
huff_len[9*16+8]= 0x10;
huff_len[9*16+9]= 0x10;
huff_len[9*16+10]= 0x10;

huff_len[10*16+1]= 0x9;
huff_len[10*16+2]= 0x10;
huff_len[10*16+3]= 0x10;
huff_len[10*16+4]= 0x10;
huff_len[10*16+5]= 0x10;
huff_len[10*16+6]= 0x10;
huff_len[10*16+7]= 0x10;
huff_len[10*16+8]= 0x10;
huff_len[10*16+9]= 0x10;
huff_len[10*16+10]= 0x10;

huff_len[11*16+1]= 0xa;
huff_len[11*16+2]= 0x10;
huff_len[11*16+3]= 0x10;
huff_len[11*16+4]= 0x10;
huff_len[11*16+5]= 0x10;
huff_len[11*16+6]= 0x10;
huff_len[11*16+7]= 0x10;
huff_len[11*16+8]= 0x10;
huff_len[11*16+9]= 0x10;
huff_len[11*16+10]= 0x10;

huff_len[12*16+1]= 0xa;
huff_len[12*16+2]= 0x10;
huff_len[12*16+3]= 0x10;
huff_len[12*16+4]= 0x10;
huff_len[12*16+5]= 0x10;
huff_len[12*16+6]= 0x10;
huff_len[12*16+7]= 0x10;
huff_len[12*16+8]= 0x10;
huff_len[12*16+9]= 0x10;
huff_len[12*16+10]= 0x10;

huff_len[13*16+1]= 0xb;
huff_len[13*16+2]= 0x10;
huff_len[13*16+3]= 0x10;
huff_len[13*16+4]= 0x10;
huff_len[13*16+5]= 0x10;
huff_len[13*16+6]= 0x10;
huff_len[13*16+7]= 0x10;
huff_len[13*16+8]= 0x10;
huff_len[13*16+9]= 0x10;
huff_len[13*16+10]= 0x10;

huff_len[14*16+1]= 0x10;
huff_len[14*16+2]= 0x10;
huff_len[14*16+3]= 0x10;
huff_len[14*16+4]= 0x10;
huff_len[14*16+5]= 0x10;
huff_len[14*16+6]= 0x10;
huff_len[14*16+7]= 0x10;
huff_len[14*16+8]= 0x10;
huff_len[14*16+9]= 0x10;
huff_len[14*16+10]= 0x10;
huff_len[15*16+0]= 0xb;
huff_len[15*16+1]= 0x10;
huff_len[15*16+2]= 0x10;
huff_len[15*16+3]= 0x10;
huff_len[15*16+4]= 0x10;
huff_len[15*16+5]= 0x10;
huff_len[15*16+6]= 0x10;
huff_len[15*16+7]= 0x10;
huff_len[15*16+8]= 0x10;
huff_len[15*16+9]= 0x10;
huff_len[15*16+10]= 0x10;
}

