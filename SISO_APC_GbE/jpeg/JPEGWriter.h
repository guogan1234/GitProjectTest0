#pragma once

#include <stdio.h>
#include "JpegDefines.h"

//-----------------------------------JPEGWriter-----------------------------

class JPEGWriter
{
public:
	JPEGWriter(bool fileAccessEnabled = true);
	~JPEGWriter();
	int OpenFile(const char* FileName);
	void CloseFile();
	int Buf2File();
	void ClearBuf();
	int GetBufPos();
	int GetBufSize();
	unsigned char* GetBufPosPtr();
	int GetBuffer(unsigned char** buffer, int** length);
	void IncBufPosPtr(int Incs);
	int put_word(WORD w);
	int put_jchar(char *c,int len);

private:
	FILE* writefile;
	char fname[255];
	buffer_t buffer;
	bool m_fileAccessEnabled;
};
