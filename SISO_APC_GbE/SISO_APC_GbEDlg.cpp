
// SISO_APC_GbEDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SISO_APC_GbE.h"
#include "SISO_APC_GbEDlg.h"
#include "afxdialogex.h"

//Add for Jpeg
#include <sstream>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "os_type.h"
#include "jpeg/JPEGEncoder.h"
#include "jpeg/HUFFTABLES.h"
#include "nanojpeg/nanojpeg.c"
#include "frameGrabberInit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CSISO_APC_GbEDlg* m_pthis;

/**********创建一个指定的文件目录 fromPengxiao**************/
BOOL CreateNDir(CString strDesPath) 
{ 
	int rt=0; 
	int ks; 
	CString exdir,newdir; 
	exdir=strDesPath; 
	while(rt==0) 
	{ 
		ks=exdir.ReverseFind('\\'); 
		exdir=exdir.Left(ks); 
		if(ks<0)break; 
		rt=PathFileExists(exdir); 
	} 
	rt=1; 
	while(ks>1 && rt==1) 
	{ 
		ks=strDesPath.Find('\\',ks+1); 
		if(ks>0) 
		{ 
			newdir=strDesPath.Left(ks); 
		}else 
			newdir=strDesPath; 
		rt=CreateDirectory(newdir,NULL);	
	} 
	return rt; 
}

const unsigned char QTableStd[64] = 
{
	16,  11,  10,  16,  24,  40,  51,  61,
	12,  12,  14,  19,  26,  58,  60,  55,
	14,  13,  16,  24,  40,  57,  69,  56,
	14,  17,  22,  29,  51,  87,  80,  62,
	18,  22,  37,  56,  68, 109, 103,  77,
	24,  35,  55,  64,  81, 104, 113,  92,
	49,  64,  78,  87, 103, 121, 120, 101,
	72,  92,  95,  98, 112, 100, 103,  99
}; 
/********JPEG Header files*********/
//JPEGEncoder jpe; //appends the jpeg header and writes JPEG files to HDD
JPEGEncoder jpe0, jpe1, jpe2, jpe3, jpe4, jpe5;
//for jpe0
unsigned long dc_data[256],dc_len[256];
unsigned long ac_data[256],ac_len[256];

//for jpe1
unsigned long dc_data1[256],dc_len1[256];
unsigned long ac_data1[256],ac_len1[256];

//for jpe2
unsigned long dc_data2[256],dc_len2[256];
unsigned long ac_data2[256],ac_len2[256];

//for jpe3
unsigned long dc_data3[256],dc_len3[256];
unsigned long ac_data3[256],ac_len3[256];

//for jpe4
unsigned long dc_data4[256],dc_len4[256];
unsigned long ac_data4[256],ac_len4[256];

//for jpe5
unsigned long dc_data5[256],dc_len5[256];
unsigned long ac_data5[256],ac_len5[256];

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////
// Asynchronous procedure call
// Callback function 
int ApcFunc(frameindex_t picNr, struct fg_apc_data *data)
{
	if(!data->fg)
		return -1;
	//Calculate fps
	LONG64 dmalenJPEG = 0;
	SYSTEMTIME st;
	char strFile[255];
	GetLocalTime(&st);
	m_pthis->statusJPEG = picNr;

	//For Jpeg 
	setJPEGQuality(data->fg,m_pthis->JPEGQuality);// transfer JPEG Quality to operator
	m_pthis->getQuantizationTable( m_pthis->fg);
	jpe0.SetQuantTable(m_pthis->QTable);	

	sprintf(strFile,"%s%d%s%d_%d_%d_%d_%d_%d_%d_%d_%d_%d.jpg",m_pthis->m_cDirPrefix, m_pthis->m_iStartIndex, "\\Cam",m_pthis->m_iStartIndex, 
		st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond, st.wMilliseconds, m_pthis->JPEGQuality,picNr);

	//*****************Get TansferLen of the current DMA channel***************//
	Fg_getParameterEx(data->fg,FG_TRANSFER_LEN,&dmalenJPEG,data->port,data->mem,picNr); 
	unsigned long* iPtrJPEG = (unsigned long*)Fg_getImagePtrEx(data->fg, picNr, data->port, data->mem);//Get the Pointer of the Jpeg files
	m_pthis->DealJPEG(dmalenJPEG,iPtrJPEG,strFile,m_pthis->width,m_pthis->height,m_pthis->writeToFile,m_pthis->ShowImage,IDC_ImgDisplay,&jpe0);
	//////////////////////////////
	/*********用于统计进回调的次数和进出回调的时间*************/
	if (m_pthis->writeToFile)
	{
		m_pthis->fileWriteCount++;
	}
	
	if (m_pthis->fileWriteCount>100)
	{
		m_pthis->ticks_b= GetTickCount();
		TRACE("ticks_b-ticks_a=%d\n",(m_pthis->ticks_b-m_pthis->ticks_a));
		m_pthis->ticks_a = m_pthis->ticks_b;
		m_pthis->fileWriteCount =0;
	}

	return 0;
}

int ApcFunc1(frameindex_t picNr, struct fg_apc_data *data)
{
	if(data->fg == NULL)
		return -1;

	LONG64 dmalenJPEG = 0;
	SYSTEMTIME st;
	char strFile[255];
	GetLocalTime(&st);

	/////For Jpeg 1
	setJPEGQuality(data->fg,m_pthis->JPEGQuality);// transfer JPEG Quality to operator
	m_pthis->getQuantizationTable1( data->fg);
	jpe1.SetQuantTable( m_pthis->QTable1);	

	sprintf(strFile, "%s%d%s%d_%d_%d_%d_%d_%d_%d_%d_%d_%d.jpg",m_pthis->m_cDirPrefix, m_pthis->m_iStartIndex +1, "\\Cam",m_pthis->m_iStartIndex +1, 
		st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond, st.wMilliseconds, m_pthis->JPEGQuality,picNr);

	//*****************Get TansferLen of the current DMA channel***************//
	Fg_getParameterEx(data->fg,FG_TRANSFER_LEN,&dmalenJPEG,data->port,data->mem,picNr); 
	void* iPtrJPEG = Fg_getImagePtrEx(data->fg, picNr, data->port, data->mem);//Get the Pointer of the Jpeg files
	m_pthis->DealJPEG(dmalenJPEG, iPtrJPEG,strFile,m_pthis->width1,m_pthis->height1,m_pthis->writeToFile,m_pthis->ShowImage,IDC_ImgDisplay1,&jpe1);

	//Calculate fps
	m_pthis->statusJPEG1 = picNr;
	//if (GetTickCount() > m_pthis->ticks1 + 1000)
	//{
	//	m_pthis->fps1 = 1000.0 * (m_pthis->statusJPEG1 - m_pthis->oldStatusJPEG1) / (GetTickCount() - m_pthis->ticks1);
	//	m_pthis->oldStatusJPEG1 = m_pthis->statusJPEG1;
	//	m_pthis->ticks1 = GetTickCount();
	//}

	//////////////////////////////
	/*********用于统计进回调的次数和进出回调的时间*************/
	if (m_pthis->writeToFile)
	{
		m_pthis->fileWriteCount1++;
	}
	
	if (m_pthis->fileWriteCount1>100)
	{
		m_pthis->ticks_d= GetTickCount();
		TRACE("ticks_d-ticks_c=%d\n",(m_pthis->ticks_d-m_pthis->ticks_c));
		m_pthis->ticks_c = m_pthis->ticks_d;
		m_pthis->fileWriteCount1 =0;
	}
	return 0;
}

int ApcFunc2(frameindex_t picNr, struct fg_apc_data *data)
{
	if(data->fg == NULL)
		return -1;

	LONG64 dmalenJPEG = 0;
	SYSTEMTIME st;
	char strFile[255];
	GetLocalTime(&st);

	/////For Jpeg 1
	setJPEGQuality(data->fg,m_pthis->JPEGQuality);// transfer JPEG Quality to operator
	m_pthis->getQuantizationTable2( data->fg);
	jpe2.SetQuantTable( m_pthis->QTable2);	

	sprintf(strFile, "%s%d%s%d_%d_%d_%d_%d_%d_%d_%d_%d_%d.jpg",m_pthis->m_cDirPrefix, m_pthis->m_iStartIndex +2, "\\Cam",m_pthis->m_iStartIndex +2, 
		st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond, st.wMilliseconds, m_pthis->JPEGQuality,picNr);

	//*****************Get TansferLen of the current DMA channel***************//
	Fg_getParameterEx(data->fg,FG_TRANSFER_LEN,&dmalenJPEG,data->port,data->mem,picNr); 
	void* iPtrJPEG = Fg_getImagePtrEx(data->fg, picNr, data->port, data->mem);//Get the Pointer of the Jpeg files
	m_pthis->DealJPEG(dmalenJPEG, iPtrJPEG,strFile,m_pthis->width2,m_pthis->height2,m_pthis->writeToFile,m_pthis->ShowImage,IDC_ImgDisplay2,&jpe2);

	//Calculate fps
	m_pthis->statusJPEG2 = picNr;
	//if (GetTickCount() > m_pthis->ticks2 + 1000)
	//{
	//	m_pthis->fps2 = 1000.0 * (m_pthis->statusJPEG2 - m_pthis->oldStatusJPEG2) / (GetTickCount() - m_pthis->ticks2);
	//	m_pthis->oldStatusJPEG2 = m_pthis->statusJPEG2;
	//	m_pthis->ticks2 = GetTickCount();
	//}
	return 0;
}

int ApcFunc3(frameindex_t picNr, struct fg_apc_data *data)
{
	if(data->fg == NULL)
		return -1;

	LONG64 dmalenJPEG = 0;
	SYSTEMTIME st;
	char strFile[255];
	GetLocalTime(&st);

	/////For Jpeg 1
	setJPEGQuality(data->fg,m_pthis->JPEGQuality);// transfer JPEG Quality to operator
	m_pthis->getQuantizationTable3( data->fg);
	jpe3.SetQuantTable( m_pthis->QTable3);	

	sprintf(strFile, "%s%d%s%d_%d_%d_%d_%d_%d_%d_%d_%d_%d.jpg",m_pthis->m_cDirPrefix, m_pthis->m_iStartIndex + 3, "\\Cam",m_pthis->m_iStartIndex + 3, 
		st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond, st.wMilliseconds, m_pthis->JPEGQuality,picNr);

	//*****************Get TansferLen of the current DMA channel***************//
	Fg_getParameterEx(data->fg,FG_TRANSFER_LEN,&dmalenJPEG,data->port,data->mem,picNr); 
	void* iPtrJPEG = Fg_getImagePtrEx(data->fg, picNr, data->port, data->mem);//Get the Pointer of the Jpeg files
	m_pthis->DealJPEG(dmalenJPEG, iPtrJPEG,strFile,m_pthis->width3,m_pthis->height3,m_pthis->writeToFile,m_pthis->ShowImage,IDC_ImgDisplay3,&jpe3);

	//Calculate fps
	m_pthis->statusJPEG3 = picNr;
	//if (GetTickCount() > m_pthis->ticks3 + 1000)
	//{
	//	m_pthis->fps3 = 1000.0 * (m_pthis->statusJPEG3 - m_pthis->oldStatusJPEG3) / (GetTickCount() - m_pthis->ticks3);
	//	m_pthis->oldStatusJPEG3 = m_pthis->statusJPEG3;
	//	m_pthis->ticks3 = GetTickCount();
	//}
	return 0;
}

int ApcFunc4(frameindex_t picNr, struct fg_apc_data *data)
{
	if(data->fg == NULL)
		return -1;

	LONG64 dmalenJPEG = 0;
	SYSTEMTIME st;
	char strFile[255];
	GetLocalTime(&st);

	/////For Jpeg 1
	setJPEGQuality(data->fg,m_pthis->JPEGQuality);// transfer JPEG Quality to operator
	m_pthis->getQuantizationTable4( data->fg);
	jpe4.SetQuantTable( m_pthis->QTable4);	

	sprintf(strFile, "%s%d%s%d_%d_%d_%d_%d_%d_%d_%d_%d_%d.jpg",m_pthis->m_cDirPrefix, m_pthis->m_iStartIndex + 4, "\\Cam",m_pthis->m_iStartIndex + 4, 
		st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond, st.wMilliseconds, m_pthis->JPEGQuality,picNr);

	//*****************Get TansferLen of the current DMA channel***************//
	Fg_getParameterEx(data->fg,FG_TRANSFER_LEN,&dmalenJPEG,data->port,data->mem,picNr); 
	void* iPtrJPEG = Fg_getImagePtrEx(data->fg, picNr, data->port, data->mem);//Get the Pointer of the Jpeg files
	m_pthis->DealJPEG(dmalenJPEG, iPtrJPEG,strFile,m_pthis->width4,m_pthis->height4,m_pthis->writeToFile,m_pthis->ShowImage,IDC_ImgDisplay4,&jpe4);

	//Calculate fps
	m_pthis->statusJPEG4 = picNr;
	//if (GetTickCount() > m_pthis->ticks4 + 1000)
	//{
	//	m_pthis->fps4 = 1000.0 * (m_pthis->statusJPEG4 - m_pthis->oldStatusJPEG4) / (GetTickCount() - m_pthis->ticks4);
	//	m_pthis->oldStatusJPEG4 = m_pthis->statusJPEG4;
	//	m_pthis->ticks4 = GetTickCount();
	//}
	return 0;
}

int ApcFunc5(frameindex_t picNr, struct fg_apc_data *data)
{
	if(data->fg == NULL)
		return -1;

	LONG64 dmalenJPEG = 0;
	SYSTEMTIME st;
	char strFile[255];
	GetLocalTime(&st);

	/////For Jpeg 1
	setJPEGQuality(data->fg,m_pthis->JPEGQuality);// transfer JPEG Quality to operator
	m_pthis->getQuantizationTable5( data->fg);
	jpe5.SetQuantTable( m_pthis->QTable5);	

	sprintf(strFile, "%s%d%s%d_%d_%d_%d_%d_%d_%d_%d_%d_%d.jpg",m_pthis->m_cDirPrefix, m_pthis->m_iStartIndex + 5, "\\Cam",m_pthis->m_iStartIndex + 5, 
		st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond, st.wMilliseconds, m_pthis->JPEGQuality,picNr);

	//*****************Get TansferLen of the current DMA channel***************//
	Fg_getParameterEx(data->fg,FG_TRANSFER_LEN,&dmalenJPEG,data->port,data->mem,picNr); 
	void* iPtrJPEG = Fg_getImagePtrEx(data->fg, picNr, data->port, data->mem);//Get the Pointer of the Jpeg files
	m_pthis->DealJPEG(dmalenJPEG, iPtrJPEG,strFile,m_pthis->width5,m_pthis->height5,m_pthis->writeToFile,m_pthis->ShowImage,IDC_ImgDisplay5,&jpe5);

	//Calculate fps
	m_pthis->statusJPEG5 = picNr;
	//if (GetTickCount() > m_pthis->ticks5 + 1000)
	//{
	//	m_pthis->fps5 = 1000.0 * (m_pthis->statusJPEG5 - m_pthis->oldStatusJPEG5) / (GetTickCount() - m_pthis->ticks5);
	//	m_pthis->oldStatusJPEG5 = m_pthis->statusJPEG5;
	//	m_pthis->ticks5 = GetTickCount();
	//}
	return 0;
}

DWORD WINAPI thfuncshow(LPVOID param)
{
	CSISO_APC_GbEDlg* m_pthis=(CSISO_APC_GbEDlg*)param;;
	while(m_pthis->m_CpState>0)
	{
		if(m_pthis->fg != NULL){
			if(WaitForSingleObject(m_pthis->m_PutEvent0,10)==WAIT_OBJECT_0)//等待Jpeg存储并缓冲完毕
			{
				ResetEvent(m_pthis->m_PutEvent0);//存储置零
				m_pthis->DecodeImg(m_pthis->bufferJPEGfile0,m_pthis->lengthJPEGfile0,IDC_ImgDisplay,m_pthis->width,m_pthis->height);//图像显示
				SetEvent(m_pthis->m_DrawEvent0);//显示之后将显示线程置零
			}

			if(WaitForSingleObject(m_pthis->m_PutEvent1,10)==WAIT_OBJECT_0)
			{
				ResetEvent(m_pthis->m_PutEvent1);
				m_pthis->DecodeImg(m_pthis->bufferJPEGfile1,m_pthis->lengthJPEGfile1,IDC_ImgDisplay1,m_pthis->width1,m_pthis->height1);
				SetEvent(m_pthis->m_DrawEvent1);
			}
		}
		if(m_pthis->fg1 != NULL){
			if(WaitForSingleObject(m_pthis->m_PutEvent2,10)==WAIT_OBJECT_0)
			{
				ResetEvent(m_pthis->m_PutEvent2);
				m_pthis->DecodeImg(m_pthis->bufferJPEGfile2,m_pthis->lengthJPEGfile2,IDC_ImgDisplay2,m_pthis->width2,m_pthis->height2);
				SetEvent(m_pthis->m_DrawEvent2);
			}
			if(WaitForSingleObject(m_pthis->m_PutEvent3,10)==WAIT_OBJECT_0)
			{
				ResetEvent(m_pthis->m_PutEvent3);
				m_pthis->DecodeImg(m_pthis->bufferJPEGfile3,m_pthis->lengthJPEGfile3,IDC_ImgDisplay3,m_pthis->width3,m_pthis->height3);
				SetEvent(m_pthis->m_DrawEvent3);
			}
		}
		if(m_pthis->fg2 != NULL){
			if(WaitForSingleObject(m_pthis->m_PutEvent4,10)==WAIT_OBJECT_0)
			{
				ResetEvent(m_pthis->m_PutEvent4);
				m_pthis->DecodeImg(m_pthis->bufferJPEGfile4,m_pthis->lengthJPEGfile4,IDC_ImgDisplay4,m_pthis->width4, m_pthis->height4);
				SetEvent(m_pthis->m_DrawEvent4);
			}
			if(WaitForSingleObject(m_pthis->m_PutEvent5,10)==WAIT_OBJECT_0)
			{
				ResetEvent(m_pthis->m_PutEvent5);
				m_pthis->DecodeImg(m_pthis->bufferJPEGfile5, m_pthis->lengthJPEGfile5,IDC_ImgDisplay5,m_pthis->width5,m_pthis->height5);
				SetEvent(m_pthis->m_DrawEvent5);
			}
		}
	}
	return 0;
}


// CSISO_APC_GbEDlg 对话框

CSISO_APC_GbEDlg::CSISO_APC_GbEDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSISO_APC_GbEDlg::IDD, pParent)
	, M_JpegQuality(_T(""))
	, fg(NULL), fg1(NULL), fg2(NULL) 
	, pMem0(NULL), pMem1(NULL), pMem2(NULL), pMem3(NULL), pMem4(NULL), pMem5(NULL)
	, xOffset(0), yOffset(0)
	, width(0), width1(0), width2(0), width3(0), width4(0), width5(0)
	, height(0), height1(0), height2(0), height3(0), height4(0), height5(0)
	, ticks(0), ticks1(0), ticks2(0), ticks3(0), ticks4(0), ticks5(0)
	, ticks_a(0), ticks_b(0), ticks_c(0), ticks_d(0)
	, hThShow(NULL)
	, m_PutEvent0(NULL), m_PutEvent1(NULL), m_PutEvent2(NULL), m_PutEvent3(NULL), m_PutEvent4(NULL), m_PutEvent5(NULL)
	, m_DrawEvent0(NULL), m_DrawEvent1(NULL), m_DrawEvent2(NULL), m_DrawEvent3(NULL), m_DrawEvent4(NULL), m_DrawEvent5(NULL)
	, bufferJPEGfile0(NULL), bufferJPEGfile1(NULL), bufferJPEGfile2(NULL), bufferJPEGfile3(NULL), bufferJPEGfile4(NULL), bufferJPEGfile5(NULL)
	, lengthJPEGfile0(0), lengthJPEGfile1(0), lengthJPEGfile2(0), lengthJPEGfile3(0), lengthJPEGfile4(0), lengthJPEGfile5(0)
	, m_pBmpInfo(NULL)
	, JPEGQuality(70)
	, writeToFile(false)
	, ShowImage(false)
	, fileWriteCount(0), fileWriteCount1(0)
	, m_CpState(0)
	, fps(0), fps1(0), fps2(0), fps3(0), fps4(0), fps5(0)
	, oldStatusJPEG(0), oldStatusJPEG1(0), oldStatusJPEG2(0), oldStatusJPEG3(0), oldStatusJPEG4(0), oldStatusJPEG5(0)
	, statusJPEG(0), statusJPEG1(0), statusJPEG2(0), statusJPEG3(0), statusJPEG4(0), statusJPEG5(0)
	, m_iStartIndex(-1)
	, m_eCollectMode(MODE_NONE)
	, m_iCollectFrequency(40)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pthis = this;
}

void CSISO_APC_GbEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SaveJpeg, M_SaveJpeg);
	DDX_Control(pDX, IDC_ShowImg, M_ShowImg);
	DDX_Text(pDX, IDC_JpegQuality, M_JpegQuality);
	DDX_Control(pDX, IDC_Fps, m_stc_fps);
	DDX_Control(pDX, IDC_Fps1, m_stc_fps1);
	DDX_Control(pDX, IDC_Fps2, m_stc_fps2);
	DDX_Control(pDX, IDC_Fps3, m_stc_fps3);
	DDX_Control(pDX, IDC_Fps4, m_stc_fps4);
	DDX_Control(pDX, IDC_Fps5, m_stc_fps5);
	DDX_Control(pDX, IDC_COMBOCollectMode, m_comboBoxCollectMode);
	//DDX_Control(pDX, IDC_COMBOConnectStatus, m_comboBoxConnectStatus);
	//DDX_Control(pDX, IDC_STATICConnectStatus, m_stc_ConnectStatus);
	DDX_Control(pDX, IDC_COMBO_ExposureTime, m_comboBox_ExposureTime);
	//DDX_Control(pDX, IDC_EDIT_ExposureTime, m_stc_ExposureTime);
	DDX_Control(pDX, IDC_COMBO_Gain, m_comboBox_Gain);
	//DDX_Control(pDX, IDC_EDIT_Gain, m_stc_Gain);
}

BEGIN_MESSAGE_MAP(CSISO_APC_GbEDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BTN_Load, &CSISO_APC_GbEDlg::OnBnClickedBtnLoad)
	//ON_BN_CLICKED(IDC_Grab, &CSISO_APC_GbEDlg::OnBnClickedGrab)
	//ON_BN_CLICKED(IDC_Stop, &CSISO_APC_GbEDlg::OnBnClickedStop)
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_SaveJpeg, &CSISO_APC_GbEDlg::OnBnClickedSavejpeg)
	ON_BN_CLICKED(IDC_ActiveQuality, &CSISO_APC_GbEDlg::OnClickedActivequality)
	//ON_BN_CLICKED(IDC_Exit, &CSISO_APC_GbEDlg::OnClickedExit)
	ON_BN_CLICKED(IDC_ShowImg, &CSISO_APC_GbEDlg::OnClickedShowimg)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBOCollectMode, &CSISO_APC_GbEDlg::OnCbnSelchangeCombocollectmode)
	//ON_CBN_SELCHANGE(IDC_COMBOConnectStatus, &CSISO_APC_GbEDlg::OnCbnSelchangeComboconnectstatus)
	ON_BN_CLICKED(IDC_BUTTONCollectFrequency, &CSISO_APC_GbEDlg::OnBnClickedButtoncollectfrequency)
	ON_BN_CLICKED(IDC_BUTTON_ExposureTime, &CSISO_APC_GbEDlg::OnBnClickedButtonExposuretime)
	ON_BN_CLICKED(IDC_BUTTON_Gain, &CSISO_APC_GbEDlg::OnBnClickedButtonGain)
	ON_CBN_SELCHANGE(IDC_COMBO_ExposureTime, &CSISO_APC_GbEDlg::OnCbnSelchangeComboExposuretime)
	ON_CBN_SELCHANGE(IDC_COMBO_Gain, &CSISO_APC_GbEDlg::OnCbnSelchangeComboGain)
END_MESSAGE_MAP()


// CSISO_APC_GbEDlg 消息处理程序
BOOL CSISO_APC_GbEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MAXIMIZE);

	// TODO: 在此添加额外的初始化代码
	//M_SaveJpeg.SetCheck(BST_CHECKED);

	M_ShowImg.SetCheck(BST_CHECKED);

	//读取配置文件，
	m_cstrIni = L"c:\\TYTunnelTestVehicle.ini";
	char cDirPrefix[256] = {0};

	m_iStartIndex = GetPrivateProfileInt(L"CameraInfo", L"StartIndex", -1, m_cstrIni);
	DWORD iNumber = GetPrivateProfileStringA("Save", "DirPrefix", "", cDirPrefix, 256, "c:\\TYTunnelTestVehicle.ini");
	if(m_iStartIndex < 0 || iNumber ==0){
		MessageBox(CString("找不到文件")+ m_cstrIni);
	}

	SetSaveDir(cDirPrefix);

	M_JpegQuality.Format(L"%d", JPEGQuality);

	// DMA list for All Cards 
	DmaIndex[0] = 0;
	DmaIndex[1] = 1;

	/*********Initialize for JPEG*************/ 
	create_dc_table(dc_data,dc_len);
	jpe0.SetDCHuffTable(dc_data,dc_len);
	create_ac_table(ac_data,ac_len);
	jpe0.SetACHuffTable(ac_data,ac_len);

	create_dc_table(dc_data1,dc_len1);
	jpe1.SetDCHuffTable(dc_data1,dc_len1);
	create_ac_table(ac_data1,ac_len1);
	jpe1.SetACHuffTable(ac_data1,ac_len1);

	create_dc_table(dc_data2,dc_len2);
	jpe2.SetDCHuffTable(dc_data2,dc_len2);
	create_ac_table(ac_data2,ac_len2);
	jpe2.SetACHuffTable(ac_data2,ac_len2);

	create_dc_table(dc_data3,dc_len3);
	jpe3.SetDCHuffTable(dc_data3,dc_len3);
	create_ac_table(ac_data3,ac_len3);
	jpe3.SetACHuffTable(ac_data3,ac_len3);

	create_dc_table(dc_data4,dc_len4);
	jpe4.SetDCHuffTable(dc_data4,dc_len4);
	create_ac_table(ac_data4,ac_len4);
	jpe4.SetACHuffTable(ac_data4,ac_len4);

	create_dc_table(dc_data5,dc_len5);
	jpe5.SetDCHuffTable(dc_data5,dc_len5);
	create_ac_table(ac_data5,ac_len5);
	jpe5.SetACHuffTable(ac_data5,ac_len5);

	njInit(); //nanoJPEG decoder Initialization

	/*********Initialize m_pBmpInfo*************/ 
	//int i;
	//	m_pBmpInfo即指向m_chBmpBuf缓冲区，用户可以自己分配BTIMAPINFO缓冲区	
	m_pBmpInfo								= (BITMAPINFO *)m_chBmpBuf;
	//	初始化BITMAPINFO 结构，此结构在保存bmp文件、显示采集图像时使用
	m_pBmpInfo->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	//	图像宽度，一般为输出窗口宽度
	m_pBmpInfo->bmiHeader.biWidth			= width;
	//	图像宽度，一般为输出窗口高度
    m_pBmpInfo->bmiHeader.biHeight			= height;
	
	/*
	*	以下设置一般相同，
	*	对于低于8位的位图，还应设置相应的位图调色板
	*/
	m_pBmpInfo->bmiHeader.biPlanes			= 1;
	m_pBmpInfo->bmiHeader.biBitCount		= 8;
	m_pBmpInfo->bmiHeader.biCompression		= BI_RGB;
	m_pBmpInfo->bmiHeader.biSizeImage		= 0;
	m_pBmpInfo->bmiHeader.biXPelsPerMeter	= 0;
	m_pBmpInfo->bmiHeader.biYPelsPerMeter	= 0;
	m_pBmpInfo->bmiHeader.biClrUsed			= 0;
	m_pBmpInfo->bmiHeader.biClrImportant	= 0;
		
	//位图调色板
	for (int i = 0; i < 256; i++)
	{
		m_pBmpInfo->bmiColors[i].rgbBlue		= (BYTE)i;
		m_pBmpInfo->bmiColors[i].rgbGreen		= (BYTE)i;
		m_pBmpInfo->bmiColors[i].rgbRed			= (BYTE)i;
		m_pBmpInfo->bmiColors[i].rgbReserved    = 0;	
	}

	m_PutEvent0=CreateEvent(NULL,TRUE,FALSE,NULL);//初始信号状态为无效
	m_DrawEvent0=CreateEvent(NULL,TRUE,TRUE,NULL);//初始信号状态为有效

	m_PutEvent1=CreateEvent(NULL,TRUE,FALSE,NULL);
	m_DrawEvent1=CreateEvent(NULL,TRUE,TRUE,NULL);
	
	m_PutEvent2=CreateEvent(NULL,TRUE,FALSE,NULL);
	m_DrawEvent2=CreateEvent(NULL,TRUE,TRUE,NULL);

	m_PutEvent3=CreateEvent(NULL,TRUE,FALSE,NULL);
	m_DrawEvent3=CreateEvent(NULL,TRUE,TRUE,NULL);

	m_PutEvent4=CreateEvent(NULL,TRUE,FALSE,NULL);
	m_DrawEvent4=CreateEvent(NULL,TRUE,TRUE,NULL);

	m_PutEvent5=CreateEvent(NULL,TRUE,FALSE,NULL);
	m_DrawEvent5=CreateEvent(NULL,TRUE,TRUE,NULL);

	//初始化采集模式
	int iIndex;
	m_comboBoxCollectMode.InsertString(0, L"触发模式");
	m_comboBoxCollectMode.InsertString(1, L"连续模式");
	m_comboBoxCollectMode.SetCurSel(0);
	
	switch(m_comboBoxCollectMode.GetCurSel())
	{
	case 0: m_eCollectMode = MODE_TRIGGER;break;
	case 1: m_eCollectMode = MODE_TIMER;break;
	default: m_eCollectMode = MODE_NONE;break;
	};

	CString cstrCollectFrequency;
	cstrCollectFrequency.Format(L"%d", m_iCollectFrequency);
	((CEdit *)GetDlgItem(IDC_EDITCollectFrequency))->SetWindowTextW(cstrCollectFrequency);

	//初始化连接状态
	//m_comboBoxConnectStatus.InsertString(0, L"相机 0");
	//m_comboBoxConnectStatus.InsertString(1, L"相机 1");
	//m_comboBoxConnectStatus.InsertString(2, L"相机 2");
	//m_comboBoxConnectStatus.InsertString(3, L"相机 3");
	//m_comboBoxConnectStatus.InsertString(4, L"相机 4");
	//m_comboBoxConnectStatus.InsertString(5, L"相机 5");
	//m_comboBoxConnectStatus.SetCurSel(0);

	m_comboBox_ExposureTime.InsertString(0, L"相机 0");
	m_comboBox_ExposureTime.InsertString(1, L"相机 1");
	m_comboBox_ExposureTime.InsertString(2, L"相机 2");
	m_comboBox_ExposureTime.InsertString(3, L"相机 3");
	m_comboBox_ExposureTime.InsertString(4, L"相机 4");
	m_comboBox_ExposureTime.InsertString(5, L"相机 5");
	m_comboBox_ExposureTime.SetCurSel(0);

	m_comboBox_Gain.InsertString(0, L"相机 0");
	m_comboBox_Gain.InsertString(1, L"相机 1");
	m_comboBox_Gain.InsertString(2, L"相机 2");
	m_comboBox_Gain.InsertString(3, L"相机 3");
	m_comboBox_Gain.InsertString(4, L"相机 4");
	m_comboBox_Gain.InsertString(5, L"相机 5");
	m_comboBox_Gain.SetCurSel(0);

	UpdateData(false);
	OnBnClickedBtnLoad();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSISO_APC_GbEDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSISO_APC_GbEDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSISO_APC_GbEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSISO_APC_GbEDlg::OnBnClickedBtnLoad()
{
	/************Board Init*************/ 
	//int BoardIndex = 0;
	switch(m_eCollectMode)
	{
	case MODE_TRIGGER: 
		fg = Fg_InitConfig("Go-5000m-PmCL_onlyJpeg_Exter.mcf", 0);
		fg1 = Fg_InitConfig("Go-5000m-PmCL_onlyJpeg_Exter.mcf", 1);
		fg2 = Fg_InitConfig("Go-5000m-PmCL_onlyJpeg_Exter.mcf", 2);
		break;
	case MODE_TIMER: 
		fg = Fg_InitConfig("Go-5000m-PmCL_onlyJpeg_Generator.mcf", 0);
		fg1 = Fg_InitConfig("Go-5000m-PmCL_onlyJpeg_Generator.mcf", 1);
		fg2 = Fg_InitConfig("Go-5000m-PmCL_onlyJpeg_Generator.mcf", 2);
		break;
	case MODE_NONE:
	default:
		MessageBox(L"采集模式没有被设置。");
		return;
	};

	if(fg == NULL && fg1 == NULL && fg2 == NULL){
		CString cstrMsg(Fg_getLastErrorDescription(NULL));
		MessageBox(cstrMsg);
		return;
	}
	///*******getting  general parameter from DMA0 and DMA1********/
	//int iWidth = 1024, iHeight = 768;
	//int Device1_Process0_Buffer_YLength_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Buffer_YLength");
	//FieldParameterAccess Device1_Process0_Buffer_YLength;
	//unsigned int Device1_Process0_Buffer_YLength_defaults[] = { 768 };
	//Device1_Process0_Buffer_YLength.vtype = FG_PARAM_TYPE_UINT32_T;
	//Device1_Process0_Buffer_YLength.index = 0;
	//Device1_Process0_Buffer_YLength.count = 1;
	//Device1_Process0_Buffer_YLength.p_uint32_t = Device1_Process0_Buffer_YLength_defaults;
	//Fg_setParameterWithType(fg, Device1_Process0_Buffer_YLength_Id, &Device1_Process0_Buffer_YLength, 0, FG_PARAM_TYPE_STRUCT_FIELDPARAMACCESS);
	//
	//int Device1_Process0_Buffer_XLength_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Buffer_XLength");
	//FieldParameterAccess Device1_Process0_Buffer_XLength;
	//unsigned int Device1_Process0_Buffer_XLength_defaults[] = { 1024 };
	//Device1_Process0_Buffer_XLength.vtype = FG_PARAM_TYPE_UINT32_T;
	//Device1_Process0_Buffer_XLength.index = 0;
	//Device1_Process0_Buffer_XLength.count = 1;
	//Device1_Process0_Buffer_XLength.p_uint32_t = Device1_Process0_Buffer_XLength_defaults;
	//Fg_setParameterWithType(fg, Device1_Process0_Buffer_XLength_Id, &Device1_Process0_Buffer_XLength, 0, FG_PARAM_TYPE_STRUCT_FIELDPARAMACCESS);
	
	if(fg){
		Fg_getParameter(fg,FG_WIDTH,&width,DmaIndex[0]);
		Fg_getParameter(fg,FG_HEIGHT,&height,DmaIndex[0]);
	
		Fg_getParameter(fg,FG_WIDTH,&width1,DmaIndex[1]);
		Fg_getParameter(fg,FG_HEIGHT,&height1,DmaIndex[1]);

		//	图像宽度，一般为输出窗口宽度
		m_pBmpInfo->bmiHeader.biWidth			= width;
		//	图像宽度，一般为输出窗口高度
		m_pBmpInfo->bmiHeader.biHeight			= height;
	
		/********Getting  general parameter from DMA*********/
		unsigned int nr_of_buffer = 16;
		size_t bytesPerPixel = 1; 

		 /**************Memory allocation For DMA 0***********/ 
		size_t totalBufSize = width*height*bytesPerPixel;
		if((pMem0 = Fg_AllocMemEx(fg,totalBufSize*nr_of_buffer,nr_of_buffer)) == NULL){
			const char*	err_str = Fg_getLastErrorDescription(fg);
			return;
		} 

		/************************Memory allocation For DMA 1*****************/ 
		size_t totalBufSize1 = width1*height1*bytesPerPixel;
		if((pMem1 = Fg_AllocMemEx(fg,totalBufSize1*nr_of_buffer,nr_of_buffer)) == NULL){
			const char*	err_str = Fg_getLastErrorDescription(fg);
			return;
		}
	
		/******************GetTable and SetTable for Jpeg 0 and Jpeg 1********************/
		setJPEGQuality(fg,m_pthis->JPEGQuality);// transfer JPEG Quality to operator
		/*********Get Matrix table from the board*********/
	
		m_pthis->getQuantizationTable( m_pthis->fg);
		m_pthis->getQuantizationTable1( m_pthis->fg);
	
		jpe0.SetQuantTable( m_pthis->QTable);	
		jpe1.SetQuantTable( m_pthis->QTable1);	

		//For DMA0
		apcdata.fg = m_pthis->fg;
		apcdata.port = m_pthis->DmaIndex[0];
		apcdata.mem = m_pthis->pMem0;

		ctrl.version = 0;
		ctrl.data = &apcdata;
		ctrl.func = ApcFunc;
		ctrl.flags = FG_APC_DEFAULTS;
		ctrl.timeout = 10000;
	
		//For DMA1
		apcdata1.fg = m_pthis->fg;
		apcdata1.port = m_pthis->DmaIndex[1];
		apcdata1.mem = m_pthis->pMem1;

		ctrl1.version = 0;
		ctrl1.data = &apcdata1;
		ctrl1.func = ApcFunc1;
		ctrl1.flags = FG_APC_DEFAULTS;
		ctrl1.timeout = 10000;

		int status = Fg_registerApcHandler(m_pthis->fg, m_pthis->DmaIndex[0], &ctrl, FG_APC_CONTROL_BASIC);
		if (status != FG_OK) {
			Fg_FreeMemEx(m_pthis->fg, pMem0);
			Fg_FreeGrabber(m_pthis->fg);
			return ;
		}
	
		status = Fg_registerApcHandler(m_pthis->fg, m_pthis->DmaIndex[1], &ctrl1, FG_APC_CONTROL_BASIC);
		if (status != FG_OK) {
			Fg_FreeMemEx(m_pthis->fg, pMem1);
			Fg_FreeGrabber(m_pthis->fg);
			return ;
		}
	}

	if(fg1){
		Fg_getParameter(fg1,FG_WIDTH,&width2,DmaIndex[0]);
		Fg_getParameter(fg1,FG_HEIGHT,&height2,DmaIndex[0]);
	
		Fg_getParameter(fg1,FG_WIDTH,&width3,DmaIndex[1]);
		Fg_getParameter(fg1,FG_HEIGHT,&height3,DmaIndex[1]);

		//	图像宽度，一般为输出窗口宽度
		//m_pBmpInfo->bmiHeader.biWidth			= width;
		//	图像宽度，一般为输出窗口高度
		//m_pBmpInfo->bmiHeader.biHeight			= height;
	
		/********Getting  general parameter from DMA*********/
		unsigned int nr_of_buffer = 16;
		size_t bytesPerPixel = 1; 

		 /**************Memory allocation For DMA 0***********/ 
		size_t totalBufSize = width2*height2*bytesPerPixel;
		if((pMem2 = Fg_AllocMemEx(fg1,totalBufSize*nr_of_buffer,nr_of_buffer)) == NULL){
			const char*	err_str = Fg_getLastErrorDescription(fg1);
			return;
		} 

		/************************Memory allocation For DMA 1*****************/ 
		size_t totalBufSize1 = width3*height3*bytesPerPixel;
		if((pMem3 = Fg_AllocMemEx(fg1,totalBufSize1*nr_of_buffer,nr_of_buffer)) == NULL){
			const char*	err_str = Fg_getLastErrorDescription(fg1);
			return;
		}
	
		/******************GetTable and SetTable for Jpeg 0 and Jpeg 1********************/
		setJPEGQuality(fg1,m_pthis->JPEGQuality);// transfer JPEG Quality to operator
		/*********Get Matrix table from the board*********/
	
		m_pthis->getQuantizationTable2( m_pthis->fg1);
		m_pthis->getQuantizationTable3( m_pthis->fg1);
	
		jpe2.SetQuantTable( m_pthis->QTable2);	
		jpe3.SetQuantTable( m_pthis->QTable3);	

		//For DMA0
		apcdata2.fg = m_pthis->fg1;
		apcdata2.port = m_pthis->DmaIndex[0];
		apcdata2.mem = m_pthis->pMem2;

		ctrl2.version = 0;
		ctrl2.data = &apcdata2;
		ctrl2.func = ApcFunc2;
		ctrl2.flags = FG_APC_DEFAULTS;
		ctrl2.timeout = 10000;
	
		//For DMA1
		apcdata3.fg = m_pthis->fg1;
		apcdata3.port = m_pthis->DmaIndex[1];
		apcdata3.mem = m_pthis->pMem3;

		ctrl3.version = 0;
		ctrl3.data = &apcdata3;
		ctrl3.func = ApcFunc3;
		ctrl3.flags = FG_APC_DEFAULTS;
		ctrl3.timeout = 10000;

		int status = Fg_registerApcHandler(m_pthis->fg1, m_pthis->DmaIndex[0], &ctrl2, FG_APC_CONTROL_BASIC);
		if (status != FG_OK) {
			Fg_FreeMemEx(m_pthis->fg1, pMem2);
			Fg_FreeGrabber(m_pthis->fg1);
			return ;
		}
	
		status = Fg_registerApcHandler(m_pthis->fg1, m_pthis->DmaIndex[1], &ctrl3, FG_APC_CONTROL_BASIC);
		if (status != FG_OK) {
			Fg_FreeMemEx(m_pthis->fg1, pMem3);
			Fg_FreeGrabber(m_pthis->fg1);
			return ;
		}
	}

	if(fg2){
		Fg_getParameter(fg2,FG_WIDTH,&width4,DmaIndex[0]);
		Fg_getParameter(fg2,FG_HEIGHT,&height4,DmaIndex[0]);
	
		Fg_getParameter(fg2,FG_WIDTH,&width5,DmaIndex[1]);
		Fg_getParameter(fg2,FG_HEIGHT,&height5,DmaIndex[1]);

		//	图像宽度，一般为输出窗口宽度
		//m_pBmpInfo->bmiHeader.biWidth			= width;
		//	图像宽度，一般为输出窗口高度
		//m_pBmpInfo->bmiHeader.biHeight			= height;
	
		/********Getting  general parameter from DMA*********/
		unsigned int nr_of_buffer = 16;
		size_t bytesPerPixel = 1; 

		 /**************Memory allocation For DMA 0***********/ 
		size_t totalBufSize = width4*height4*bytesPerPixel;
		if((pMem4 = Fg_AllocMemEx(fg2,totalBufSize*nr_of_buffer,nr_of_buffer)) == NULL){
			const char*	err_str = Fg_getLastErrorDescription(fg2);
			return;
		} 

		/************************Memory allocation For DMA 1*****************/ 
		size_t totalBufSize1 = width5*height5*bytesPerPixel;
		if((pMem5 = Fg_AllocMemEx(fg2,totalBufSize1*nr_of_buffer,nr_of_buffer)) == NULL){
			const char*	err_str = Fg_getLastErrorDescription(fg2);
			return;
		}
	
		/******************GetTable and SetTable for Jpeg 0 and Jpeg 1********************/
		setJPEGQuality(fg2,m_pthis->JPEGQuality);// transfer JPEG Quality to operator
		/*********Get Matrix table from the board*********/
	
		m_pthis->getQuantizationTable( m_pthis->fg2);
		m_pthis->getQuantizationTable1( m_pthis->fg2);
	
		jpe4.SetQuantTable( m_pthis->QTable4);	
		jpe5.SetQuantTable( m_pthis->QTable5);	

		//For DMA0
		apcdata4.fg = m_pthis->fg2;
		apcdata4.port = m_pthis->DmaIndex[0];
		apcdata4.mem = m_pthis->pMem4;

		ctrl4.version = 0;
		ctrl4.data = &apcdata4;
		ctrl4.func = ApcFunc4;
		ctrl4.flags = FG_APC_DEFAULTS;
		ctrl4.timeout = 10000;
	
		//For DMA1
		apcdata5.fg = m_pthis->fg2;
		apcdata5.port = m_pthis->DmaIndex[1];
		apcdata5.mem = m_pthis->pMem5;

		ctrl5.version = 0;
		ctrl5.data = &apcdata5;
		ctrl5.func = ApcFunc5;
		ctrl5.flags = FG_APC_DEFAULTS;
		ctrl5.timeout = 10000;

		int status = Fg_registerApcHandler(m_pthis->fg2, m_pthis->DmaIndex[0], &ctrl4, FG_APC_CONTROL_BASIC);
		if (status != FG_OK) {
			Fg_FreeMemEx(m_pthis->fg2, pMem4);
			Fg_FreeGrabber(m_pthis->fg2);
			return ;
		}
	
		status = Fg_registerApcHandler(m_pthis->fg2, m_pthis->DmaIndex[1], &ctrl5, FG_APC_CONTROL_BASIC);
		if (status != FG_OK) {
			Fg_FreeMemEx(m_pthis->fg2, pMem5);
			Fg_FreeGrabber(m_pthis->fg2);
			return ;
		}
	}
	//m_pthis -> GetDlgItem(IDC_Grab)->EnableWindow(TRUE);
	//m_pthis -> GetDlgItem(IDC_BTN_Load)->EnableWindow(FALSE);
	OnBnClickedGrab();
}


void CSISO_APC_GbEDlg::OnBnClickedGrab()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!M_SaveJpeg.GetCheck())
	{
		writeToFile =false;
	} 
	else
	{
		writeToFile =true;
	}

	if (M_ShowImg.GetCheck())
	{
		ShowImage =true;
	} 
	else
	{
		ShowImage =false;
	}
	if(fg){
		if ((Fg_AcquireEx(m_pthis->fg, m_pthis->DmaIndex[0], GRAB_INFINITE, ACQ_STANDARD,m_pthis-> pMem0)) < 0) 
		{
			const char*	err_str1 = Fg_getLastErrorDescription(m_pthis->fg);
			Fg_FreeMemEx(m_pthis->fg, pMem0);
			Fg_FreeGrabber(m_pthis->fg);
			return ;
		}

		if ((Fg_AcquireEx(m_pthis->fg, m_pthis->DmaIndex[1], GRAB_INFINITE, ACQ_STANDARD,m_pthis-> pMem1)) < 0) {
			const char*	err_str1 = Fg_getLastErrorDescription(m_pthis->fg);
			Fg_FreeMemEx(m_pthis->fg, pMem1);
			Fg_FreeGrabber(m_pthis->fg);
			return ;
		}
	}

	if(fg1){
		if ((Fg_AcquireEx(m_pthis->fg1, m_pthis->DmaIndex[0], GRAB_INFINITE, ACQ_STANDARD,m_pthis-> pMem2)) < 0) 
		{
			const char*	err_str1 = Fg_getLastErrorDescription(m_pthis->fg1);
			Fg_FreeMemEx(m_pthis->fg1, pMem2);
			Fg_FreeGrabber(m_pthis->fg1);
			return ;
		}

		if ((Fg_AcquireEx(m_pthis->fg1, m_pthis->DmaIndex[1], GRAB_INFINITE, ACQ_STANDARD,m_pthis-> pMem3)) < 0) {
			const char*	err_str1 = Fg_getLastErrorDescription(m_pthis->fg1);
			Fg_FreeMemEx(m_pthis->fg1, pMem3);
			Fg_FreeGrabber(m_pthis->fg1);
			return ;
		}
	}

	if(fg2){
		if ((Fg_AcquireEx(m_pthis->fg2, m_pthis->DmaIndex[0], GRAB_INFINITE, ACQ_STANDARD,m_pthis-> pMem4)) < 0) 
		{
			const char*	err_str1 = Fg_getLastErrorDescription(m_pthis->fg2);
			Fg_FreeMemEx(m_pthis->fg2, pMem4);
			Fg_FreeGrabber(m_pthis->fg2);
			return ;
		}

		if ((Fg_AcquireEx(m_pthis->fg2, m_pthis->DmaIndex[1], GRAB_INFINITE, ACQ_STANDARD,m_pthis-> pMem5)) < 0) {
			const char*	err_str1 = Fg_getLastErrorDescription(m_pthis->fg2);
			Fg_FreeMemEx(m_pthis->fg2, pMem5);
			Fg_FreeGrabber(m_pthis->fg2);
			return ;
		}
	}
	
	////Create Thread
	DWORD id;
	m_CpState=1;
	SetTimer(0,1000,NULL);//ID为0，定时间隔1000ms,相应函数Ontimer()
	ticks_a=GetTickCount();
	ticks = GetTickCount();
	ticks2= GetTickCount();
	ticks_c=GetTickCount();

	hThShow=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)thfuncshow,this,0,&id);

	//m_pthis -> GetDlgItem(IDC_Stop)->EnableWindow(TRUE);
	//m_pthis -> GetDlgItem(IDC_Grab)->EnableWindow(FALSE);
}

void CSISO_APC_GbEDlg::OnBnClickedStop()
{
	// TODO: 在此添加控件通知处理程序代码
	m_CpState=0;
	KillTimer(0);
	WaitForSingleObject(hThShow,100);
	
	if(fg){	
		ResetEvent(m_PutEvent0);
		SetEvent(m_DrawEvent0);

		ResetEvent(m_PutEvent1);
		SetEvent(m_DrawEvent1);

		Fg_registerApcHandler(m_pthis->fg, DmaIndex[0], NULL, FG_APC_CONTROL_BASIC);
		Fg_stopAcquireEx(m_pthis->fg,DmaIndex[0],pMem0,0);
		Fg_FreeMemEx(m_pthis->fg, pMem0);

		Fg_registerApcHandler(m_pthis->fg, DmaIndex[1], NULL, FG_APC_CONTROL_BASIC);
		Fg_stopAcquireEx(m_pthis->fg,DmaIndex[1],pMem1,0);
		Fg_FreeMemEx(m_pthis->fg, pMem1);

		Fg_FreeGrabber(fg);
		fg = NULL;
	}

	if(fg1){	
		ResetEvent(m_PutEvent2);
		SetEvent(m_DrawEvent2);

		ResetEvent(m_PutEvent3);
		SetEvent(m_DrawEvent3);

		Fg_registerApcHandler(m_pthis->fg1, DmaIndex[0], NULL, FG_APC_CONTROL_BASIC);
		Fg_stopAcquireEx(m_pthis->fg1,DmaIndex[0],pMem2,0);
		Fg_FreeMemEx(m_pthis->fg1, pMem2);

		Fg_registerApcHandler(m_pthis->fg1, DmaIndex[1], NULL, FG_APC_CONTROL_BASIC);
		Fg_stopAcquireEx(m_pthis->fg1,DmaIndex[1],pMem3,0);
		Fg_FreeMemEx(m_pthis->fg1, pMem3);

		Fg_FreeGrabber(fg1);
		fg1 = NULL;
	}

	if(fg2){	
		ResetEvent(m_PutEvent4);
		SetEvent(m_DrawEvent4);

		ResetEvent(m_PutEvent5);
		SetEvent(m_DrawEvent5);

		Fg_registerApcHandler(m_pthis->fg2, DmaIndex[0], NULL, FG_APC_CONTROL_BASIC);
		Fg_stopAcquireEx(m_pthis->fg2,DmaIndex[0],pMem4,0);
		Fg_FreeMemEx(m_pthis->fg2, pMem4);

		Fg_registerApcHandler(m_pthis->fg2, DmaIndex[1], NULL, FG_APC_CONTROL_BASIC);
		Fg_stopAcquireEx(m_pthis->fg2,DmaIndex[1],pMem5,0);
		Fg_FreeMemEx(m_pthis->fg2, pMem5);

		Fg_FreeGrabber(fg2);
		fg2 = NULL;
	}

	if(bufferJPEGfile0)delete []bufferJPEGfile0;
	if(bufferJPEGfile1)delete []bufferJPEGfile1;
	if(bufferJPEGfile2)delete []bufferJPEGfile2;
	if(bufferJPEGfile3)delete []bufferJPEGfile3;
	if(bufferJPEGfile4)delete []bufferJPEGfile4;
	if(bufferJPEGfile5)delete []bufferJPEGfile5;
	bufferJPEGfile0 = NULL;
	bufferJPEGfile1 = NULL;
	bufferJPEGfile2 = NULL;
	bufferJPEGfile3 = NULL;
	bufferJPEGfile4 = NULL;
	bufferJPEGfile5 = NULL;
	lengthJPEGfile0 = 0;
	lengthJPEGfile1 = 0;
	lengthJPEGfile2 = 0;
	lengthJPEGfile3 = 0;
	lengthJPEGfile4 = 0;
	lengthJPEGfile5 = 0;
	
	fps = 0; fps1 = 0;fps2 = 0; fps3 = 0;fps4 = 0; fps5 = 0;
	CString strtmp,strtmp1,strtmp2,strtmp3,strtmp4,strtmp5;
	strtmp.Format(_T("fps:%.3f"), fps);
	strtmp1.Format(_T("fps:%.3f"), fps1);
	strtmp2.Format(_T("fps:%.3f"), fps2);
	strtmp3.Format(_T("fps:%.3f"), fps3);
	strtmp4.Format(_T("fps:%.3f"), fps4);
	strtmp5.Format(_T("fps:%.3f"), fps5);
	m_stc_fps.SetWindowTextW(strtmp);
	m_stc_fps1.SetWindowTextW(strtmp1);
	m_stc_fps2.SetWindowTextW(strtmp2);
	m_stc_fps3.SetWindowTextW(strtmp3);
	m_stc_fps4.SetWindowTextW(strtmp4);
	m_stc_fps5.SetWindowTextW(strtmp5);
	
	//m_pthis -> GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
	//m_pthis -> GetDlgItem(IDC_BTN_Load)->EnableWindow(TRUE);
	return;
}

//DealJpeg 
void CSISO_APC_GbEDlg::DealJPEG(LONG64 dmalenJPEG,void* iPtrJPEG
	,char* filename,int w,int h,bool bIsSave
	,bool bIsShow,int DrawItemID,void* pjpe) 

{
	JPEGEncoder* ptjpe=(JPEGEncoder*)pjpe;
	ptjpe->InitOutputWriter(filename, bIsSave);
	//	jpe0.SetQuantTable(QTable);
	ptjpe->SetPicSize(w,h,0,0,w,h);
	unsigned char lastWordNoOfBytesUsed = ((unsigned char*) iPtrJPEG)[dmalenJPEG - 2];
	dmalenJPEG -= 4; //minus info word from data stream
	if (lastWordNoOfBytesUsed != 0)
		dmalenJPEG -= 4 - lastWordNoOfBytesUsed;
	ptjpe->SetVLCBitstream((unsigned char*)iPtrJPEG,dmalenJPEG);
	ptjpe->EncodePic((unsigned char*)iPtrJPEG);

	// ---------------------------------------------------------------------------
	//decode JPEG file for display
	if(bIsShow)
	{		
		unsigned char* bufferJPEGfile = NULL;
		int* lengthJPEGfile = NULL;

		switch(DrawItemID)
		{
		case IDC_ImgDisplay:
			if(WaitForSingleObject(m_DrawEvent0,1)==WAIT_OBJECT_0)//等待显示完毕
			{
				ResetEvent(m_DrawEvent0);
				if(bufferJPEGfile0!=NULL)delete []bufferJPEGfile0;
				ptjpe->GetBuffer(&bufferJPEGfile, &lengthJPEGfile);
				lengthJPEGfile0=*lengthJPEGfile;
				bufferJPEGfile0=new unsigned char[lengthJPEGfile0];
				memcpy(bufferJPEGfile0,bufferJPEGfile,lengthJPEGfile0);
				SetEvent(m_PutEvent0);
			}
			break;

		case IDC_ImgDisplay1:
			if(WaitForSingleObject(m_DrawEvent1,1)==WAIT_OBJECT_0)
			{
				ResetEvent(m_DrawEvent1);
				if(bufferJPEGfile1!=NULL)delete []bufferJPEGfile1;
				ptjpe->GetBuffer(&bufferJPEGfile, &lengthJPEGfile);
				lengthJPEGfile1=*lengthJPEGfile;
				bufferJPEGfile1=new unsigned char[lengthJPEGfile1];
				memcpy(bufferJPEGfile1,bufferJPEGfile,lengthJPEGfile1);
				SetEvent(m_PutEvent1);
			}
			break;
		case IDC_ImgDisplay2:
			if(WaitForSingleObject(m_DrawEvent2,1)==WAIT_OBJECT_0)//等待显示完毕
			{
				ResetEvent(m_DrawEvent2);
				if(bufferJPEGfile2!=NULL)delete []bufferJPEGfile2;
				ptjpe->GetBuffer(&bufferJPEGfile, &lengthJPEGfile);
				lengthJPEGfile2=*lengthJPEGfile;
				bufferJPEGfile2=new unsigned char[lengthJPEGfile2];
				memcpy(bufferJPEGfile2,bufferJPEGfile,lengthJPEGfile2);
				SetEvent(m_PutEvent2);
			}
			break;

		case IDC_ImgDisplay3:
			if(WaitForSingleObject(m_DrawEvent3,1)==WAIT_OBJECT_0)
			{
				ResetEvent(m_DrawEvent3);
				if(bufferJPEGfile3!=NULL)delete []bufferJPEGfile3;
				ptjpe->GetBuffer(&bufferJPEGfile, &lengthJPEGfile);
				lengthJPEGfile3=*lengthJPEGfile;
				bufferJPEGfile3=new unsigned char[lengthJPEGfile3];
				memcpy(bufferJPEGfile3,bufferJPEGfile,lengthJPEGfile3);
				SetEvent(m_PutEvent3);
			}
			break;
		case IDC_ImgDisplay4:
			if(WaitForSingleObject(m_DrawEvent4,1)==WAIT_OBJECT_0)//等待显示完毕
			{
				ResetEvent(m_DrawEvent4);
				if(bufferJPEGfile4!=NULL)delete []bufferJPEGfile4;
				ptjpe->GetBuffer(&bufferJPEGfile, &lengthJPEGfile);
				lengthJPEGfile4=*lengthJPEGfile;
				bufferJPEGfile4=new unsigned char[lengthJPEGfile4];
				memcpy(bufferJPEGfile4,bufferJPEGfile,lengthJPEGfile4);
				SetEvent(m_PutEvent4);
			}
			break;

		case IDC_ImgDisplay5:
			if(WaitForSingleObject(m_DrawEvent5,1)==WAIT_OBJECT_0)
			{
				ResetEvent(m_DrawEvent5);
				if(bufferJPEGfile5!=NULL)delete []bufferJPEGfile5;
				ptjpe->GetBuffer(&bufferJPEGfile, &lengthJPEGfile);
				lengthJPEGfile5=*lengthJPEGfile;
				bufferJPEGfile5=new unsigned char[lengthJPEGfile5];
				memcpy(bufferJPEGfile5,bufferJPEGfile,lengthJPEGfile5);
				SetEvent(m_PutEvent5);
			}
			break;
		}
	}
}


void CSISO_APC_GbEDlg::DrawImage(int itemID,unsigned char* buf,int w,int h)
{
	CWnd* pwnd=m_pthis->GetDlgItem(itemID);
	CDC* pdc=pwnd->GetDC();
	CRect srect;
	pwnd->GetWindowRect(&srect);
	m_pBmpInfo->bmiHeader.biWidth=w;
	m_pBmpInfo->bmiHeader.biHeight=h;
	::SetStretchBltMode(pdc->GetSafeHdc(), COLORONCOLOR);
	::StretchDIBits(pdc->GetSafeHdc(),
		0,						
		srect.Height(),//0,
		srect.Width(),
		-srect.Height(),//srect.Height(),
		0,
		0,
		w,h,
		buf,
		m_pthis->m_pBmpInfo,
		DIB_RGB_COLORS,
		SRCCOPY
		);
	pwnd->ReleaseDC(pdc);
}

void CSISO_APC_GbEDlg::DecodeImg(unsigned char* bufferJPEGfile,int lengthJPEGfile,int itemID,int w,int h)
{
	if(bufferJPEGfile == NULL)
		return;

	njDecode(bufferJPEGfile, lengthJPEGfile);
	int widthDecoded = njGetWidth();
	int heightDecoded = njGetHeight();
	bool isColor = njIsColor() == 1;
	unsigned char* decodedDrawImage = new unsigned char[w * h];
	unsigned char* decodedImage = njGetImage();
	//		DrawBuffer(id0,decodedImage,jpgimg0,0);

	if (widthDecoded * heightDecoded != w * h)
	{
		for (int cnt_decodedCopy = 0; cnt_decodedCopy < w * h; cnt_decodedCopy++)
		{
			if (cnt_decodedCopy < widthDecoded * heightDecoded)
				decodedDrawImage[cnt_decodedCopy] = decodedImage[cnt_decodedCopy];
			else
				decodedDrawImage[cnt_decodedCopy] = 0;
		}
		DrawImage(itemID,decodedDrawImage,w,h);
	}
	else
	{
		DrawImage(itemID,decodedImage,w,h);
	}
	njDone();
	delete []decodedDrawImage;
}

// ---------------------------------------------------------------------------
unsigned char CSISO_APC_GbEDlg::calcQuantizationMatrixFromPercent(int p_percent)
{

	unsigned __int16 QTable1[64];

	if (p_percent < 1 || p_percent > 100)
		return -1;

	int i = 0;

	if (p_percent >= 50)
		for (i = 0; i < 8*8; i++)
			QTable1[i] = QTableStd[i] * (100 - p_percent) / 50;
	else
		for (i = 0; i < 8*8; i++)
			QTable1[i] = QTableStd[i] * 50 / p_percent;

	for (i = 0; i < 8*8; i++)
	{
		if (QTable1[i] == 0)
			QTable1[i] = 1;
		if (QTable1[i] > 255)
			QTable1[i] = 255;

		if (QTable[i] != QTable1[i])
			printf("Error QTable not equal i = %d, %d != %d\n", i, QTable[i], QTable1[i]);
	}
	return 0;
};


int CSISO_APC_GbEDlg::getQuantizationTable(Fg_Struct* fg) 
{
	int Device1_Process0_Encoder_quantization_matrix_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Encoder_quantization_matrix");
	FieldParameterInt readQuantizationValue;
	printf("New QTable:");
	for (int i = 0; i < 64; i++)
	{
		readQuantizationValue.index = i;
		readQuantizationValue.value = 0;
		 Fg_getParameter(fg, Device1_Process0_Encoder_quantization_matrix_Id, &readQuantizationValue, 0); 
		QTable[i] = readQuantizationValue.value;
		if (i % 8 == 0)
			printf("\n");
		printf("%d ", readQuantizationValue.value);

	}
	return 0;
}

int CSISO_APC_GbEDlg::getQuantizationTable1(Fg_Struct* fg) 
{
	int Device1_Process1_Encoder_quantization_matrix_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Encoder_quantization_matrix");
	FieldParameterInt readQuantizationValue;
	printf("New QTable:");
	for (int i = 0; i < 64; i++)
	{
		readQuantizationValue.index = i;
		readQuantizationValue.value = 0;
		 Fg_getParameter(fg, Device1_Process1_Encoder_quantization_matrix_Id, &readQuantizationValue, 0); 
		QTable1[i] = readQuantizationValue.value;
		if (i % 8 == 0)
			printf("\n");
		printf("%d ", readQuantizationValue.value);
	}
	return 0;
}

int CSISO_APC_GbEDlg::getQuantizationTable2(Fg_Struct* fg) 
{
	int Device1_Process0_Encoder_quantization_matrix_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Encoder_quantization_matrix");
	FieldParameterInt readQuantizationValue;
	printf("New QTable:");
	for (int i = 0; i < 64; i++)
	{
		readQuantizationValue.index = i;
		readQuantizationValue.value = 0;
		 Fg_getParameter(fg, Device1_Process0_Encoder_quantization_matrix_Id, &readQuantizationValue, 0); 
		QTable2[i] = readQuantizationValue.value;
		if (i % 8 == 0)
			printf("\n");
		printf("%d ", readQuantizationValue.value);

	}
	return 0;
}

int CSISO_APC_GbEDlg::getQuantizationTable3(Fg_Struct* fg) 
{
	int Device1_Process1_Encoder_quantization_matrix_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Encoder_quantization_matrix");
	FieldParameterInt readQuantizationValue;
	printf("New QTable:");
	for (int i = 0; i < 64; i++)
	{
		readQuantizationValue.index = i;
		readQuantizationValue.value = 0;
		 Fg_getParameter(fg, Device1_Process1_Encoder_quantization_matrix_Id, &readQuantizationValue, 0); 
		QTable3[i] = readQuantizationValue.value;
		if (i % 8 == 0)
			printf("\n");
		printf("%d ", readQuantizationValue.value);
	}
	return 0;
}

int CSISO_APC_GbEDlg::getQuantizationTable4(Fg_Struct* fg) 
{
	int Device1_Process0_Encoder_quantization_matrix_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Encoder_quantization_matrix");
	FieldParameterInt readQuantizationValue;
	printf("New QTable:");
	for (int i = 0; i < 64; i++)
	{
		readQuantizationValue.index = i;
		readQuantizationValue.value = 0;
		 Fg_getParameter(fg, Device1_Process0_Encoder_quantization_matrix_Id, &readQuantizationValue, 0); 
		QTable4[i] = readQuantizationValue.value;
		if (i % 8 == 0)
			printf("\n");
		printf("%d ", readQuantizationValue.value);

	}
	return 0;
}

int CSISO_APC_GbEDlg::getQuantizationTable5(Fg_Struct* fg) 
{
	int Device1_Process1_Encoder_quantization_matrix_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Encoder_quantization_matrix");
	FieldParameterInt readQuantizationValue;
	printf("New QTable:");
	for (int i = 0; i < 64; i++)
	{
		readQuantizationValue.index = i;
		readQuantizationValue.value = 0;
		 Fg_getParameter(fg, Device1_Process1_Encoder_quantization_matrix_Id, &readQuantizationValue, 0); 
		QTable5[i] = readQuantizationValue.value;
		if (i % 8 == 0)
			printf("\n");
		printf("%d ", readQuantizationValue.value);
	}
	return 0;
}

bool CSISO_APC_GbEDlg::checkROIconsistency(int maxWidth, int maxHeight, int xOffset, int xLength, int yOffset, int yLength)
{
	if ((xLength > maxWidth)	
		|| (xLength < 16)	
		|| (xLength % 16 != 0)	
		|| (xLength + xOffset > maxWidth) 
		|| (xOffset > maxWidth - 16)
		|| (xOffset < 0)
		|| (xOffset % 8 != 0)
		|| (yLength > maxHeight)	
		|| (yLength < 8)	
		|| (yLength % 8 != 0)	
		|| (yLength + yOffset > maxHeight) 
		|| (yOffset > maxHeight - 8)
		|| (yOffset < 0))
		return false;
	else
		return true;
};

void CSISO_APC_GbEDlg::OnBnClickedSavejpeg()
{
	// TODO: 在此添加控件通知处理程序代码
	//ichk= M_SaveJpeg.GetCheck();
	
	if (!M_SaveJpeg.GetCheck())
	{
		writeToFile =false;
	} 
	else
	{
		writeToFile =true;
	}
}

void CSISO_APC_GbEDlg::OnClickedActivequality()
{
	
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//s = M_JpegQuality.GetString();
	// n= _tstoi(s);
	JPEGQuality = _tstoi(M_JpegQuality.GetString());
}

//void CSISO_APC_GbEDlg::OnClickedExit()
//{
//	// TODO: 在此添加控件通知处理程序代码
//    if(m_pthis->m_CpState == 1)
//		OnBnClickedStop();
//	CDialogEx::OnOK();
//}

void CSISO_APC_GbEDlg::OnClickedShowimg()
{
	// TODO: 在此添加控件通知处理程序代码
	//Is_show = M_ShowImg.GetCheck();
	if (M_ShowImg.GetCheck())
	{
		ShowImage =true;
	} 
	else
	{
		ShowImage =false;
	}

}

void CSISO_APC_GbEDlg::OnTimer(UINT_PTR nIDEvent)
{
	fps = 1000.0 * (statusJPEG - oldStatusJPEG) / (GetTickCount() - ticks);
	oldStatusJPEG = statusJPEG;
	ticks = GetTickCount();

	fps1 = 1000.0 * (statusJPEG1 - oldStatusJPEG1) / (GetTickCount() - ticks1);
	oldStatusJPEG1 = statusJPEG1;
	ticks1 = GetTickCount();

	fps2 = 1000.0 * (statusJPEG2 - oldStatusJPEG2) / (GetTickCount() - ticks2);
	oldStatusJPEG2 = statusJPEG2;
	ticks2 = GetTickCount();

	fps3 = 1000.0 * (statusJPEG3 - oldStatusJPEG3) / (GetTickCount() - ticks3);
	oldStatusJPEG3 = m_pthis->statusJPEG3;
	ticks3 = GetTickCount();

	fps4 = 1000.0 * (statusJPEG4 - oldStatusJPEG4) / (GetTickCount() - ticks4);
	oldStatusJPEG4 = statusJPEG4;
	ticks4 = GetTickCount();

	fps5 = 1000.0 * (statusJPEG5 - oldStatusJPEG5) / (GetTickCount() - ticks5);
	oldStatusJPEG5 = statusJPEG5;
	ticks5 = GetTickCount();

	CString strtmp, strtmp1, strtmp2, strtmp3, strtmp4, strtmp5;
	strtmp.Format(_T("fps:%.3f"), fps);
	strtmp1.Format(_T("fps:%.3f"), fps1);
	strtmp2.Format(_T("fps:%.3f"), fps2);
	strtmp3.Format(_T("fps:%.3f"), fps3);
	strtmp4.Format(_T("fps:%.3f"), fps4);
	strtmp5.Format(_T("fps:%.3f"), fps5);
	
	m_stc_fps.SetWindowTextW(strtmp);
	m_stc_fps1.SetWindowTextW(strtmp1);
	m_stc_fps2.SetWindowTextW(strtmp2);
	m_stc_fps3.SetWindowTextW(strtmp3);
	m_stc_fps4.SetWindowTextW(strtmp4);
	m_stc_fps5.SetWindowTextW(strtmp5);
	CDialogEx::OnTimer(nIDEvent);
}

void CSISO_APC_GbEDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_CpState == 1)
		OnBnClickedStop();
	CDialogEx::OnClose();
}

void CSISO_APC_GbEDlg::OnCbnSelchangeCombocollectmode()
{
	// TODO: 在此添加控件通知处理程序代码

	COLLECT_MODE eCollectMode;
	switch(m_comboBoxCollectMode.GetCurSel())
	{
	case 0: eCollectMode = MODE_TRIGGER;break;
	case 1: eCollectMode = MODE_TIMER;break;
	default: eCollectMode = MODE_NONE;break;
	};

	SetCollectMode(eCollectMode);
}

//void CSISO_APC_GbEDlg::OnCbnSelchangeComboconnectstatus()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	if (!fg && !fg1 && !fg2)
//		return;
//
//	int iStatus = -1, iReturn;
//	switch(m_comboBoxConnectStatus.GetCurSel())
//	{
//	case 0:
//		if(fg)
//			iReturn = Fg_getParameter(fg,FG_CAMSTATUS,&iStatus, PORT_A);
//		break;
//	case 1:
//		if(fg)
//			iReturn = Fg_getParameter(fg,FG_CAMSTATUS,&iStatus, PORT_B);
//		break;
//	case 2: 
//		if(fg1)
//			iReturn = Fg_getParameter(fg1,FG_CAMSTATUS,&iStatus, PORT_A);
//		break;
//	case 3: 
//		if(fg1)
//			iReturn = Fg_getParameter(fg1,FG_CAMSTATUS,&iStatus, PORT_B);
//		break;
//	case 4: 
//		if(fg2)
//			iReturn = Fg_getParameter(fg2,FG_CAMSTATUS,&iStatus, PORT_A);
//		break;
//	case 5:
//		if(fg2)
//			iReturn = Fg_getParameter(fg2,FG_CAMSTATUS,&iStatus, PORT_B);
//		break;
//	default:;
//	};
//
//	switch (iStatus)
//	{
//	case 0:
//		m_stc_ConnectStatus.SetWindowTextW(L"Unconnected");
//		break;
//	case 1:
//		m_stc_ConnectStatus.SetWindowTextW(L"Connected");
//		break;
//	case -1:
//	default:
//		m_stc_ConnectStatus.SetWindowTextW(L"Uninitialized");
//		break;
//	}
//	
//}


void CSISO_APC_GbEDlg::OnBnClickedButtoncollectfrequency()
{
	// TODO: 在此添加控件通知处理程序代码
	int iCollectFrequency = GetDlgItemInt(IDC_EDITCollectFrequency);
	TY_STATUS eStatus = SetCollectFrequency(iCollectFrequency);
	if (TY_OK == eStatus){
		MessageBox(L"设置采集频率成功");
	}
	else{
		MessageBox(L"设置采集频率失败");
	}
}


void CSISO_APC_GbEDlg::OnBnClickedButtonExposuretime()
{
	unsigned int iExposureTime = GetDlgItemInt(IDC_EDIT_ExposureTime);
	if(iExposureTime < 10 || iExposureTime > 8000000) {
		MessageBox(L"相机曝光时间必须介于10~8000000之间");
		return;
	}
	int iPortNr = m_comboBox_ExposureTime.GetCurSel();
	
	TY_STATUS eStatus = SetExposureTime(iPortNr, iExposureTime);
	if (TY_OK == eStatus){
		MessageBox(L"设置相机曝光时间成功");
	}
	else{
		MessageBox(L"设置相机曝光时间失败");
	}
}


void CSISO_APC_GbEDlg::OnBnClickedButtonGain()
{
	unsigned int iGain = GetDlgItemInt(IDC_EDIT_Gain);
	if(iGain < 100 || iGain > 1600) {
		MessageBox(L"相机增益必须介于100~1600之间");
		return;
	}

	int iPortNr = m_comboBox_Gain.GetCurSel();
	
	TY_STATUS eStatus = SetGain(iPortNr, iGain);
	if (TY_OK == eStatus){
		MessageBox(L"设置相机增益成功");
	}
	else{
		MessageBox(L"设置相机增益失败");
	}
}


void CSISO_APC_GbEDlg::OnCbnSelchangeComboExposuretime()
{
	int iPortNr = m_comboBox_ExposureTime.GetCurSel();
	unsigned int iExposureTime = 0;
	TY_STATUS eStatus = GetExposureTime(iPortNr, iExposureTime);
	if (TY_OK == eStatus){
		CString cstrExposureTime;
		cstrExposureTime.Format(L"%d", iExposureTime);
		((CEdit *)GetDlgItem(IDC_EDIT_ExposureTime))->SetWindowTextW(cstrExposureTime);
	}
	else{
		MessageBox(L"获取相机曝光时间失败");
	}
}


void CSISO_APC_GbEDlg::OnCbnSelchangeComboGain()
{
	int iPortNr = m_comboBox_Gain.GetCurSel();
	unsigned int iGain = 0;
	TY_STATUS eStatus = GetGain(iPortNr, iGain);
	if (TY_OK == eStatus){
		CString cstrGain;
		cstrGain.Format(L"%d", iGain);
		((CEdit *)GetDlgItem(IDC_EDIT_Gain))->SetWindowTextW(cstrGain);
	}
	else{
		MessageBox(L"获取相机增益失败");
	}
}

TY_STATUS CSISO_APC_GbEDlg::SetCollectMode(COLLECT_MODE eCollectMode)
{
	if(	m_eCollectMode != eCollectMode)
	{
		m_eCollectMode = eCollectMode;

		unsigned int Trigger_TriggerMode_Select;
		switch(m_eCollectMode)
		{
		case MODE_TRIGGER: 
			Trigger_TriggerMode_Select = 0;
			break;
		case MODE_TIMER: 
			Trigger_TriggerMode_Select = 1;
			break;
		default:;
		};

		if(fg != NULL)
		{
			int Device1_Process0_Trigger_TriggerMode_Select_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_TriggerMode_Select");
			Fg_setParameterWithType(fg, Device1_Process0_Trigger_TriggerMode_Select_Id, Trigger_TriggerMode_Select, 0);

			int Device1_Process1_Trigger_TriggerMode_Select_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_TriggerMode_Select");
			Fg_setParameterWithType(fg, Device1_Process1_Trigger_TriggerMode_Select_Id, Trigger_TriggerMode_Select, 0);
		}
		if(fg1 != NULL)
		{
			int Device1_Process0_Trigger_TriggerMode_Select_Id = Fg_getParameterIdByName(fg1, "Device1_Process0_Trigger_TriggerMode_Select");
			Fg_setParameterWithType(fg1, Device1_Process0_Trigger_TriggerMode_Select_Id, Trigger_TriggerMode_Select, 0);

			int Device1_Process1_Trigger_TriggerMode_Select_Id = Fg_getParameterIdByName(fg1, "Device1_Process1_Trigger_TriggerMode_Select");
			Fg_setParameterWithType(fg1, Device1_Process1_Trigger_TriggerMode_Select_Id, Trigger_TriggerMode_Select, 0);
		}
		if(fg2 != NULL)
		{
			int Device1_Process0_Trigger_TriggerMode_Select_Id = Fg_getParameterIdByName(fg2, "Device1_Process0_Trigger_TriggerMode_Select");
			Fg_setParameterWithType(fg2, Device1_Process0_Trigger_TriggerMode_Select_Id, Trigger_TriggerMode_Select, 0);

			int Device1_Process1_Trigger_TriggerMode_Select_Id = Fg_getParameterIdByName(fg2, "Device1_Process1_Trigger_TriggerMode_Select");
			Fg_setParameterWithType(fg2, Device1_Process1_Trigger_TriggerMode_Select_Id, Trigger_TriggerMode_Select, 0);
		}
	}
	return TY_OK;
}

TY_STATUS CSISO_APC_GbEDlg::SetJpegQuality(unsigned int iQuality)
{
	if(iQuality < 1 || iQuality > 100)
		return TY_ERROR;
	
	JPEGQuality = iQuality;
	return TY_OK;
}

TY_STATUS CSISO_APC_GbEDlg::SetSaveDir(char* cSaveDir)
{
	if(!cSaveDir)
		return TY_ERROR;

	memset(m_cDirPrefix, 0, sizeof(m_cDirPrefix));
	strcpy_s(m_cDirPrefix, cSaveDir);
	//创建存储的目录。
	if(m_cDirPrefix[strlen(m_cDirPrefix) -1] != '\\')
		strcat(m_cDirPrefix, "\\");
	CString cDir(m_cDirPrefix), cDir1, cDir2, cDir3, cDir4, cDir5, cDir6;
	cDir1.Format(L"%s%d\\", cDir, m_iStartIndex);
	cDir2.Format(L"%s%d\\", cDir, m_iStartIndex + 1);
	cDir3.Format(L"%s%d\\", cDir, m_iStartIndex + 2);
	cDir4.Format(L"%s%d\\", cDir, m_iStartIndex + 3);
	cDir5.Format(L"%s%d\\", cDir, m_iStartIndex + 4);
	cDir6.Format(L"%s%d\\", cDir, m_iStartIndex + 5);
	CreateNDir(cDir1);
	CreateNDir(cDir2);
	CreateNDir(cDir3);
	CreateNDir(cDir4);
	CreateNDir(cDir5);
	CreateNDir(cDir6);
	return TY_OK;
}
	
TY_STATUS CSISO_APC_GbEDlg::SetPreviewMode(PREVIEW_MODE eMode)
{
	if (PREVIEW_OPEN == eMode){
		ShowImage =true;
	} 
	else{
		ShowImage =false;
	}
	return TY_OK;
}

TY_STATUS CSISO_APC_GbEDlg::BeginCollect()
{
	writeToFile = true;
	return TY_OK;
}

TY_STATUS CSISO_APC_GbEDlg::StopCollect()
{
	writeToFile = false;
	return TY_OK;
}

TY_STATUS CSISO_APC_GbEDlg::GetGain(unsigned int iIndexCamera, unsigned int &iGain)
{
	if(0 > iIndexCamera || iIndexCamera > 5)
		return TY_ERROR;
	void *hSer = NULL;  // reference to serial port
	int iRet = CL_ERR_NO_ERR;
	// initialize serial port
	if((iRet = clSerialInit(iIndexCamera, &hSer)) != CL_ERR_NO_ERR){
		//CString cstrMsg;
		//cstrMsg.Format(L"不能打开相机%d", iPortNr);
		//MessageBox(cstrMsg);
		return TY_ERROR;
	}

	unsigned int clSerBaudRate = CL_BAUDRATE_9600;	// baud rate of serial port, normally 9600
    if((iRet = clSetBaudRate(hSer, clSerBaudRate)) != CL_ERR_NO_ERR) {
		//MessageBox(L"无法设置波特率");
		return TY_ERROR;
	}

	char line[256]= "FGA?";
	TY_STATUS eStatus = TY_ERROR;
	
	unsigned int len = strlen(line);
	line[len] = 10;
	len = strlen(line);
	int error = clSerialWrite(hSer, line, &len, 500);

	len = 256;
	error = clSerialRead(hSer, line, &len, 256);
	if(error == CL_ERR_NO_ERR)
	{
		CString cst(line);
		iGain = _tstoi(cst.Mid(4, len-6).GetString());
		eStatus = TY_OK;
	}
	// clean up the serial port reference
	clSerialClose(hSer);
	return eStatus;
}

TY_STATUS CSISO_APC_GbEDlg::SetGain(unsigned int iIndexCamera, unsigned int iGain)
{
	if(iGain < 100 || iGain > 1600) {
		return TY_ERROR;
	}

	if(0 > iIndexCamera || iIndexCamera > 5)
		return TY_ERROR;

	void *hSer = NULL;  // reference to serial port
	int iRet = CL_ERR_NO_ERR;
	// initialize serial port
	if((iRet = clSerialInit(iIndexCamera, &hSer)) != CL_ERR_NO_ERR){
		return TY_ERROR;
	}

	unsigned int clSerBaudRate = CL_BAUDRATE_9600;	// baud rate of serial port, normally 9600
    if((iRet = clSetBaudRate(hSer, clSerBaudRate)) != CL_ERR_NO_ERR) {
		//MessageBox(L"无法设置波特率");
		return TY_ERROR;
	}

	char line[256]= {0};
	sprintf(line, "FGA=%d", iGain);
	unsigned int len = strlen(line);
	line[len] = 10;
	len = strlen(line);
	
	int error = clSerialWrite(hSer, line, &len, 500);
	TY_STATUS eStatus = TY_ERROR;
	if (CL_ERR_NO_ERR == error ) {
		eStatus = TY_OK;
	}
	// clean up the serial port reference
	clSerialClose(hSer);
	return eStatus;
}

TY_STATUS CSISO_APC_GbEDlg::GetExposureTime(unsigned int iIndexCamera, unsigned int &iExposureTime)
{
	if(0 > iIndexCamera || iIndexCamera > 5)
		return TY_ERROR;
	
	void *hSer = NULL;  // reference to serial port
	int iRet = CL_ERR_NO_ERR;
	// initialize serial port
	if((iRet = clSerialInit(iIndexCamera, &hSer)) != CL_ERR_NO_ERR){
		return TY_ERROR;
	}

	unsigned int clSerBaudRate = CL_BAUDRATE_9600;	// baud rate of serial port, normally 9600
    if((iRet = clSetBaudRate(hSer, clSerBaudRate)) != CL_ERR_NO_ERR) {
		return TY_ERROR;
	}

	char line[256]= "PE?";
	unsigned int len = strlen(line);
	line[len] = 10;
	len = strlen(line);
	
	int error = clSerialWrite(hSer, line, &len, 500);

	len = 256;
	error = clSerialRead(hSer, line, &len, 256);
	
	TY_STATUS eStatus = TY_ERROR;
	if(error == CL_ERR_NO_ERR)
	{
		CString cst(line);
		iExposureTime = _tstoi(cst.Mid(3, len-5).GetString());
		eStatus = TY_OK;
	}
	
	// clean up the serial port reference
	clSerialClose(hSer);
	return eStatus;
}

TY_STATUS CSISO_APC_GbEDlg::SetExposureTime(unsigned int iIndexCamera, unsigned int iExposureTime)
{
	if(iExposureTime < 10 || iExposureTime > 8000000) {
		return TY_ERROR;
	}

	if(0 > iIndexCamera || iIndexCamera > 5)
		return TY_ERROR;
	
	void *hSer = NULL;  // reference to serial port
	int iRet = CL_ERR_NO_ERR;
	// initialize serial port
	if((iRet = clSerialInit(iIndexCamera, &hSer)) != CL_ERR_NO_ERR){
		return TY_ERROR;
	}

	unsigned int clSerBaudRate = CL_BAUDRATE_9600;	// baud rate of serial port, normally 9600
    if((iRet = clSetBaudRate(hSer, clSerBaudRate)) != CL_ERR_NO_ERR) {
		return TY_ERROR;
	}

	char line[256]= {0};
	sprintf(line, "PE=%d", iExposureTime);
	unsigned int len = strlen(line);
	line[len] = 10;
	len = strlen(line);

	TY_STATUS eStatus = TY_ERROR;
	int error = clSerialWrite(hSer, line, &len, 500);
	if (CL_ERR_NO_ERR == error) {
		eStatus = TY_OK;
	}
	// clean up the serial port reference
	clSerialClose(hSer);
	return eStatus;
}

TY_STATUS CSISO_APC_GbEDlg::SetCollectFrequency(unsigned int iCollectFrequency)
{
	if (!fg && !fg1 && !fg2)
		return TY_ERROR;

	if (iCollectFrequency < 1 || iCollectFrequency > 47)
		return TY_ERROR;

	m_iCollectFrequency = iCollectFrequency;
	uint64_t Trigger_Generator_Period_Period = 1000000000/(8*m_iCollectFrequency);
	if(fg != NULL)
	{
		int Device1_Process0_Trigger_Generator_Period_Period_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_Generator_Period_Period");
		Fg_setParameterWithType(fg, Device1_Process0_Trigger_Generator_Period_Period_Id, Trigger_Generator_Period_Period, 0);

		int Device1_Process1_Trigger_Generator_Period_Period_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_Generator_Period_Period");
		Fg_setParameterWithType(fg, Device1_Process1_Trigger_Generator_Period_Period_Id, Trigger_Generator_Period_Period, 0);
	}
	if(fg1 != NULL)
	{
		int Device1_Process0_Trigger_Generator_Period_Period_Id = Fg_getParameterIdByName(fg1, "Device1_Process0_Trigger_Generator_Period_Period");
		Fg_setParameterWithType(fg1, Device1_Process0_Trigger_Generator_Period_Period_Id, Trigger_Generator_Period_Period, 0);

		int Device1_Process1_Trigger_Generator_Period_Period_Id = Fg_getParameterIdByName(fg1, "Device1_Process1_Trigger_Generator_Period_Period");
		Fg_setParameterWithType(fg1, Device1_Process1_Trigger_Generator_Period_Period_Id, Trigger_Generator_Period_Period, 0);
	}
	if(fg2 != NULL)
	{
		int Device1_Process0_Trigger_Generator_Period_Period_Id = Fg_getParameterIdByName(fg2, "Device1_Process0_Trigger_Generator_Period_Period");
		Fg_setParameterWithType(fg2, Device1_Process0_Trigger_Generator_Period_Period_Id, Trigger_Generator_Period_Period, 0);

		int Device1_Process1_Trigger_Generator_Period_Period_Id = Fg_getParameterIdByName(fg2, "Device1_Process1_Trigger_Generator_Period_Period");
		Fg_setParameterWithType(fg2, Device1_Process1_Trigger_Generator_Period_Period_Id, Trigger_Generator_Period_Period, 0);
	}
	return TY_OK;
}