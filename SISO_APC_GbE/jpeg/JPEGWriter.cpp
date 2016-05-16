//+-------------------------------------------------------------------
//
//  JPEG Encoder
//  Copyright (C) Silicon Software GmbH, 1997.
//
//
//--------------------------------------------------------------------

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "JPEGWriter.h"

//-----------------------------------JPEGWriter-----------------------------
const unsigned int StdBufSize(16*1024*1024);

JPEGWriter::JPEGWriter(bool fileAccessEnabled)
{
	m_fileAccessEnabled = fileAccessEnabled;
	strcpy(fname, "");
	writefile = NULL;
	if ((buffer.data = (unsigned char *)malloc(sizeof(char)*StdBufSize)) == NULL) 
	{
		fprintf(stderr,"Couldn't allocate memory to image\n");
		exit(-1);
	}
	buffer.size = StdBufSize;
	buffer.position = 0;
}

JPEGWriter::~JPEGWriter()
{
	if (buffer.data != NULL) free(buffer.data);
	if (writefile != NULL && m_fileAccessEnabled) CloseFile();
}

int JPEGWriter::OpenFile(const char* FileName)
{
	if (m_fileAccessEnabled)
	{
		if (writefile != NULL) CloseFile();
		strcpy(fname, FileName);
		if ((writefile = fopen(fname,"wb")) == NULL) 
		{
			fprintf(stderr,"Error in opening file: %s\n",fname);
			exit(-1);
		}
	}
	return 0;
}

void JPEGWriter::CloseFile()
{
	if (m_fileAccessEnabled)
	{
		if (writefile != NULL) fclose(writefile);
		writefile = NULL;
	}
	return;
}

int JPEGWriter::Buf2File()
{
	int status;
	if (m_fileAccessEnabled)
	{
		if (writefile == NULL)
		{
			fprintf(stderr, "File not opened: %s", fname);
			exit(-1);
		}
		if ((status = fwrite(buffer.data,sizeof(char),buffer.position,writefile)) 
			!= buffer.position) 
		{
			fprintf(stderr,"%s%s\n","Error in writing to file: ",fname);
			exit(-1);
		}
	}
	return 0;
}

void JPEGWriter::ClearBuf()
{
	buffer.position = 0;
}

int JPEGWriter::GetBufPos()
{
	return buffer.position;
}

int JPEGWriter::GetBufSize()
{
	return buffer.size;
}

unsigned char* JPEGWriter::GetBufPosPtr()
{
	if (buffer.data!=NULL)
		return &(buffer.data[buffer.position]);
	else return NULL;
}

int JPEGWriter::GetBuffer(unsigned char** p_buffer, int** length)
{
	if (buffer.data!=NULL)
	{
		*p_buffer = buffer.data;
		*length = &buffer.position;
	}
	else 
		return -1;
	return 0;
}

void JPEGWriter::IncBufPosPtr(int Incs)
{
	buffer.position+=Incs;
	if (buffer.position >= buffer.size)
	{
		fprintf(stderr, "ERROR - JPEGWriter: buffer-overflow\n");
		buffer.position = buffer.size - 1;
	}
}

int JPEGWriter::put_jchar(char *c,int len)
{
	int i;

	if ((buffer.position+len) < buffer.size)
		for(i=0;i<len;i++)
		buffer.data[buffer.position++] = (unsigned char )c[i];

	return 0;
}

int JPEGWriter::put_word(WORD w)
{
	static CHAR *c,tmp;

	c = (CHAR*)&w;
	tmp=c[0];
	c[0] = c[1];
	c[1] = tmp;

	if ((buffer.position + 2 ) < buffer.size)
	{
		buffer.data[buffer.position++]=c[0];
		buffer.data[buffer.position++]=c[1];
	}
	
	return 0;
}