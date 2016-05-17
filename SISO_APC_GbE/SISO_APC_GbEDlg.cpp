
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
//CSISO_APC_GbEDlg *pMainDlg; 

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
JPEGEncoder jpe0,jpe1;
//for jpe0
unsigned long dc_data[256],dc_len[256];
unsigned long ac_data[256],ac_len[256];

//for jpe1
unsigned long dc_data1[256],dc_len1[256];
unsigned long ac_data1[256],ac_len1[256];



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
  
	
	//Calculate fps
	LONG64 dmalenJPEG = 0;
	SYSTEMTIME st;
	TCHAR strFile0[255];
	GetLocalTime(&st);
	m_pthis->statusJPEG = picNr;
	if (GetTickCount() > m_pthis->ticks + 1000)
	{
		m_pthis->fps = 1000.0 * (m_pthis->statusJPEG - m_pthis->oldStatusJPEG) / (GetTickCount() - m_pthis->ticks);
		m_pthis->oldStatusJPEG = m_pthis->statusJPEG;
		m_pthis->ticks = GetTickCount();
	}

	//For Jpeg 
	m_pthis->retCode += setJPEGQuality(data->fg,m_pthis->JPEGQuality);// transfer JPEG Quality to operator
	m_pthis->getQuantizationTable( m_pthis->fg);
	jpe0.SetQuantTable(m_pthis->QTable);	

	wsprintf(strFile0,L"%s%d%s%d_%d_%d_%d_%d_%d_%d_%d_%d_%d.jpg",m_pthis->m_cDirPrefix, m_pthis->m_iStartIndex, L"\\Cam",m_pthis->m_iStartIndex, 
		st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond, st.wMilliseconds, m_pthis->JPEGQuality,picNr);
	//sprintf(strFile0,"F:\\Img0\\Cam0%d_%d_%d_%d_%d_%d_%d.jpg",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,m_pthis->fileWriteCount);

	//*****************Get TansferLen of the current DMA channel***************//
	Fg_getParameterEx(data->fg,FG_TRANSFER_LEN,&dmalenJPEG,data->port,data->mem,picNr); 
	unsigned long* iPtrJPEG = (unsigned long*)Fg_getImagePtrEx(data->fg, picNr, data->port, data->mem);//Get the Pointer of the Jpeg files
	m_pthis->actualYLength = m_pthis->height;
	m_pthis->DealJPEG(dmalenJPEG,iPtrJPEG,strFile0,m_pthis->width,m_pthis->actualYLength,m_pthis->writeToFile,m_pthis->ShowImage,IDC_ImgDisplay,&jpe0);
	//m_pthis->DealJPEG(dmalenJPEG,iPtrJPEG,strFile0,1024,768,m_pthis->writeToFile,m_pthis->ShowImage,IDC_ImgDisplay,&jpe0);
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
  
	LONG64 dmalenJPEG1 = 0;
	SYSTEMTIME st;
	TCHAR strFile1[255];
	GetLocalTime(&st);

	/////For Jpeg 1
	m_pthis->retCode += setJPEGQuality(data->fg,m_pthis->JPEGQuality);// transfer JPEG Quality to operator
	m_pthis->getQuantizationTable1( m_pthis->fg);
	jpe1.SetQuantTable( m_pthis->QTable1);	

	//sprintf(strFile1,"f:\\Img1\\Cam1%d_%d_%d_%d_%d_%d_%d.jpg",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,m_pthis->fileWriteCount1);
	wsprintf(strFile1,L"%s%d%s%d_%d_%d_%d_%d_%d_%d_%d_%d_%d.jpg",m_pthis->m_cDirPrefix, m_pthis->m_iStartIndex +1, L"\\Cam",m_pthis->m_iStartIndex +1, 
		st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond, st.wMilliseconds, m_pthis->JPEGQuality,picNr);
	//sprintf(strFile1,"f:\\Img1\\Cam1%d_%d_%d_%d_%d_%d_%d_%d_%d.jpg",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds, m_pthis->JPEGQuality, picNr);

	//*****************Get TansferLen of the current DMA channel***************//
	Fg_getParameterEx(data->fg,FG_TRANSFER_LEN,&dmalenJPEG1,data->port,data->mem,picNr); 
	void* iPtrJPEG1 = Fg_getImagePtrEx(data->fg, picNr, data->port, data->mem);//Get the Pointer of the Jpeg files
	m_pthis->actualYLength1 = m_pthis->height1;
	m_pthis->DealJPEG(dmalenJPEG1,iPtrJPEG1,strFile1,m_pthis->width1,m_pthis->actualYLength1,m_pthis->writeToFile,m_pthis->ShowImage,IDC_ImgDisplay1,&jpe1);

	//Calculate fps
	m_pthis->statusJPEG1 = picNr;
	if (GetTickCount() > m_pthis->ticks2 + 1000)
	{
		m_pthis->fps1 = 1000.0 * (m_pthis->statusJPEG1 - m_pthis->oldStatusJPEG1) / (GetTickCount() - m_pthis->ticks2);
		m_pthis->oldStatusJPEG1 = m_pthis->statusJPEG1;
		m_pthis->ticks2 = GetTickCount();
	}

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



DWORD WINAPI thfuncshow(LPVOID param)
{
	CSISO_APC_GbEDlg* m_pthis=(CSISO_APC_GbEDlg*)param;;
	while(m_pthis->m_CpState>0)
	{
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
	return 0;
}


// CSISO_APC_GbEDlg 对话框

CSISO_APC_GbEDlg::CSISO_APC_GbEDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSISO_APC_GbEDlg::IDD, pParent)
	, JpegQuality(0)
	, M_JpegQuality(_T(""))
	, m_eCollectMode(MODE_NONE)
	, fg(NULL)

	//, M_Fps(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pthis = this;

}

void CSISO_APC_GbEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SaveJpeg, M_SaveJpeg);
	DDX_Control(pDX, IDC_ShowImg, M_ShowImg);
	DDV_MinMaxUInt(pDX, JpegQuality, 0, 100);
	DDX_Text(pDX, IDC_JpegQuality, M_JpegQuality);
	DDX_Control(pDX, IDC_Fps, m_stc_fps);
	DDX_Control(pDX, IDC_Fps1, m_stc_fps1);
	DDX_Control(pDX, IDC_COMBOCollectMode, m_comboBoxCollectMode);
	DDX_Control(pDX, IDC_COMBOConnectStatus, m_comboBoxConnectStatus);
	DDX_Control(pDX, IDC_STATICConnectStatus, m_stc_ConnectStatus);
}

BEGIN_MESSAGE_MAP(CSISO_APC_GbEDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_Load, &CSISO_APC_GbEDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_Grab, &CSISO_APC_GbEDlg::OnBnClickedGrab)
	ON_BN_CLICKED(IDC_Stop, &CSISO_APC_GbEDlg::OnBnClickedStop)
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_SaveJpeg, &CSISO_APC_GbEDlg::OnBnClickedSavejpeg)
	ON_BN_CLICKED(IDC_ActiveQuality, &CSISO_APC_GbEDlg::OnClickedActivequality)
	ON_BN_CLICKED(IDC_Exit, &CSISO_APC_GbEDlg::OnClickedExit)
	ON_BN_CLICKED(IDC_ShowImg, &CSISO_APC_GbEDlg::OnClickedShowimg)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBOCollectMode, &CSISO_APC_GbEDlg::OnCbnSelchangeCombocollectmode)
	ON_CBN_SELCHANGE(IDC_COMBOConnectStatus, &CSISO_APC_GbEDlg::OnCbnSelchangeComboconnectstatus)
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

	ShowWindow(SW_MAXIMIZE);

	// TODO: 在此添加额外的初始化代码
	M_SaveJpeg.SetCheck(BST_CHECKED);
	//M_SaveJpeg1.SetCheck(BST_CHECKED);
	M_ShowImg.SetCheck(BST_CHECKED);

	//读取配置文件，
	m_cstrIni = L"c:\\TYTunnelTestVehicle.ini";

	m_iStartIndex = GetPrivateProfileInt(L"CameraInfo", L"StartIndex", -1, m_cstrIni);
	DWORD iNumber = GetPrivateProfileString(L"Save", L"DirPrefix", L"", m_cDirPrefix, 256, m_cstrIni);
	if(m_iStartIndex < 0 || iNumber ==0){
		MessageBox(CString("找不到文件")+ m_cstrIni);
	}

	//创建存储的目录。
	if(m_cDirPrefix[iNumber -1] != L'\\')
		lstrcat(m_cDirPrefix, L"\\");
	CString cDir1, cDir2;
	cDir1.Format(L"%s%d\\", m_cDirPrefix, m_iStartIndex);
	cDir2.Format(L"%s%d\\", m_cDirPrefix, m_iStartIndex + 1);
	CreateNDir(cDir1);
	CreateNDir(cDir2);
	// Initi Board
	BoardIndex = 0;
    const char*	err_st   =NULL;
    nCamPort		=	PORT_A;		// Port (PORT_A / PORT_B)
	/*Cam_width = 2048;
	Cam_height = 504;*/
	ch= NULL;
	format =  1;
	status =  0;
	width = 0;
	height = 0;
	width1 = 0;
	height1 = 0;
    //dmalenJPEG =0;
	actualYLength =2048;
	actualYLength1 =2048;
	xOffset = 0;
	yOffset = 0;
	ticks = GetTickCount();

	//ticks_a=GetTickCount();
	writeToFile = false;
	//writeToFile1 =false;
	ShowImage = false;
	fileWriteCount = 0;
	 JPEGQuality = 70;
	 M_JpegQuality.Format(L"%d", JPEGQuality);
	 ichk = 0;
	 ichk1=0;
	 Is_show = 0;
	 ticks = 0;
	 ticks2= 0;
	 ticks_a=0;
	 ticks_b=0;
	 ticks_c=0;
	 ticks_d=0;
	 ticks_a1=0;
	 ticks_b1=0;
	 ticks_c1=0;
	 ticks_d1=0;
	 fps =0;
	 fps1=0;
	 oldStatusJPEG =0;
	 statusJPEG =0;
	// DMA list for All Cards 
	  DmaIndex[0] = 0;
	  DmaIndex[1] = 1;
	  DmaIndex[2] = 2;
	  DmaIndex[3] = 3;
	  DmaIndex[4] = 4;
	  DmaIndex[5] = 5;
	  DmaIndex[6] = 6;
      DmaIndex[7] = 7;
	  retCode = 0;
	   /*********Initialize for JPEG*************/ 
	  create_dc_table(dc_data,dc_len);
	  jpe0.SetDCHuffTable(dc_data,dc_len);
	  create_ac_table(ac_data,ac_len);
	  jpe0.SetACHuffTable(ac_data,ac_len);

	  create_dc_table(dc_data1,dc_len1);
	  jpe1.SetDCHuffTable(dc_data1,dc_len1);
	  create_ac_table(ac_data1,ac_len1);
	  jpe1.SetACHuffTable(ac_data1,ac_len1);

	  njInit(); //nanoJPEG decoder Initialization

	 /*********Initialize m_pBmpInfo*************/ 
	  int i;
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
	for (i = 0; i < 256; i++)
	{
		m_pBmpInfo->bmiColors[i].rgbBlue		= (BYTE)i;
		m_pBmpInfo->bmiColors[i].rgbGreen		= (BYTE)i;
		m_pBmpInfo->bmiColors[i].rgbRed			= (BYTE)i;
		m_pBmpInfo->bmiColors[i].rgbReserved    = 0;	
	}

	bufferJPEGfile0=NULL;
	bufferJPEGfile1=NULL;

	m_PutEvent0=CreateEvent(NULL,TRUE,FALSE,NULL);//初始信号状态为无效
	m_DrawEvent0=CreateEvent(NULL,TRUE,TRUE,NULL);//初始信号状态为有效

	m_PutEvent1=CreateEvent(NULL,TRUE,FALSE,NULL);
	m_DrawEvent1=CreateEvent(NULL,TRUE,TRUE,NULL);
	// For Image Process and Display

	//初始化画图
	//CDC* pdc=m_staticTitle.GetDC();
	//m_ImgPinter.SetDrawDC(pdc);
	//m_ImgPinter.LoadCDBP("./Title.bmp",&m_srcTitle);
	//CRect wrect;
	//m_staticTitle.GetWindowRect(&wrect);
	//m_ImgPinter.DrawCDBP(m_srcTitle,pdc,0,0,wrect.Width(),wrect.Height(),true);
	//m_staticTitle.ReleaseDC(pdc);
	
	//初始化采集模式
	int iIndex;
	iIndex = m_comboBoxCollectMode.InsertString(0, L"trigger");
	iIndex = m_comboBoxCollectMode.InsertString(1, L"timer");
	iIndex = m_comboBoxCollectMode.SetCurSel(0);
	
	switch(m_comboBoxCollectMode.GetCurSel())
	{
	case 0: m_eCollectMode = MODE_TRIGGER;break;
	case 1: m_eCollectMode = MODE_TIMER;break;
	default: m_eCollectMode = MODE_NONE;break;
	};

	//初始化连接状态
	m_comboBoxConnectStatus.InsertString(0, L"Camera 0");
	m_comboBoxConnectStatus.InsertString(1, L"Camera 1");
	m_comboBoxConnectStatus.InsertString(2, L"Camera 2");
	m_comboBoxConnectStatus.InsertString(3, L"Camera 3");
	m_comboBoxConnectStatus.InsertString(4, L"Camera 4");
	m_comboBoxConnectStatus.InsertString(5, L"Camera 5");

	UpdateData(false);
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
	// TODO: 在此添加控件通知处理程序代码

	//再画一遍图
	//CDC* pdc=m_staticTitle.GetDC();
	////	m_ImgPinter.SetDrawDC(pdc);
	////	m_ImgPinter.LoadCDBP("./titleimg.bmp",&m_srcTitle);
	//CRect wrect;
	//m_staticTitle.GetWindowRect(&wrect);
	//m_ImgPinter.DrawCDBP(m_srcTitle,pdc,0,0,wrect.Width(),wrect.Height(),true);
	//m_staticTitle.ReleaseDC(pdc);


	/************Board Init*************/ 
	switch(m_eCollectMode)
	{
	case MODE_TRIGGER: 
		fg = Fg_InitConfig("Go-5000m-PmCL_onlyJpeg_Exter.mcf",BoardIndex);
		break;
	case MODE_TIMER: 
		fg = Fg_InitConfig("Go-5000m-PmCL_onlyJpeg_Generator.mcf",BoardIndex);
		break;
	case MODE_NONE:
	default:
		MessageBox(L"采集模式没有被设置。");
		exit(-1);
	};
//load *.mcf
	 //fg = Fg_InitConfig("Go-5000m-PmCL_onlyJpeg_Exter.mcf",BoardIndex);//load *.mcf
	 
	//fg = Fg_InitConfig("F:\\Gbe_1Pro2DMA_jpeg.mcf",BoardIndex);//load *.mcf 
	 //fg = Fg_Init("Sg14-02K-Jpeg.hap",BoardIndex);
	 //fg = Fg_Init("Sg14-02K-Jpeg_Windows_AMD64.hap",BoardIndex);
	if(fg == NULL){
		MessageBox(L"采集卡正在被其他程序使用。");
		exit(-1);
	}
	int iStatus0, iStatus1, iReturn;
	iReturn = Fg_getParameter(fg,FG_CAMSTATUS,&iStatus1, PORT_B);
	iReturn = Fg_getParameter(fg,FG_CAMSTATUS,&iStatus0, PORT_A);
	                             
	//int Device1_Process0_Trigger_TriggerMode_Select_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_TriggerMode_Select");
	//unsigned int Device1_Process0_Trigger_TriggerMode_Select;
	//Device1_Process0_Trigger_TriggerMode_Select = 1;
	//Fg_setParameterWithType(fg, Device1_Process0_Trigger_TriggerMode_Select_Id, Device1_Process0_Trigger_TriggerMode_Select, 0);


	//int Device1_Process1_Trigger_TriggerMode_Select_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_TriggerMode_Select");
	//unsigned int Device1_Process1_Trigger_TriggerMode_Select;
	//Device1_Process1_Trigger_TriggerMode_Select = 1;
	//Fg_setParameterWithType(fg, Device1_Process1_Trigger_TriggerMode_Select_Id, Device1_Process1_Trigger_TriggerMode_Select, 0);

	//int Device1_Process0_Trigger_Generator_Period_Period_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_Generator_Period_Period");
	//uint64_t Device1_Process0_Trigger_Generator_Period_Period;
	//Device1_Process0_Trigger_Generator_Period_Period = 0x2faf080;
	//Fg_setParameterWithType(fg, Device1_Process0_Trigger_Generator_Period_Period_Id, Device1_Process0_Trigger_Generator_Period_Period, 0);
	//
	//int Device1_Process1_Trigger_Generator_Period_Period_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_Generator_Period_Period");
	//uint64_t Device1_Process1_Trigger_Generator_Period_Period;
	//Device1_Process1_Trigger_Generator_Period_Period = 0x2faf080;
	//Fg_setParameterWithType(fg, Device1_Process1_Trigger_Generator_Period_Period_Id, Device1_Process1_Trigger_Generator_Period_Period, 0);

	/********Getting  general parameter from DMA*********/
	unsigned int nr_of_buffer = 16;
	size_t bytesPerPixel = 1; 

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
	
	Fg_getParameter(fg,FG_WIDTH,&width,DmaIndex[0]);
	Fg_getParameter(fg,FG_HEIGHT,&height,DmaIndex[0]);
	
	Fg_getParameter(fg,FG_WIDTH,&width1,DmaIndex[1]);
	Fg_getParameter(fg,FG_HEIGHT,&height1,DmaIndex[1]);

	//	图像宽度，一般为输出窗口宽度
	m_pBmpInfo->bmiHeader.biWidth			= width;
	//	图像宽度，一般为输出窗口高度
	m_pBmpInfo->bmiHeader.biHeight			= height;
	

	 /**************Memory allocation For DMA 0***********/ 
	size_t totalBufSize = width*height*bytesPerPixel;
	if((pMem0 = Fg_AllocMemEx(fg,totalBufSize*nr_of_buffer,nr_of_buffer)) == NULL){
		const char*	err_str = Fg_getLastErrorDescription(fg);
		return;
	} else {

	}

	/************************Memory allocation For DMA 1*****************/ 
	size_t totalBufSize1 = width1*height1*bytesPerPixel;
	if((pMem1 = Fg_AllocMemEx(fg,totalBufSize1*nr_of_buffer,nr_of_buffer)) == NULL){
		const char*	err_str = Fg_getLastErrorDescription(fg);
		return;
	} else {

	}


	/******************GetTable and SetTable for Jpeg 0 and Jpeg 1********************/
	m_pthis->retCode += setJPEGQuality(fg,m_pthis->JPEGQuality);// transfer JPEG Quality to operator
	/*********Get Matrix table from the board*********/
	
	m_pthis->getQuantizationTable( m_pthis->fg);
	m_pthis->getQuantizationTable1( m_pthis->fg);
	
	jpe0.SetQuantTable( m_pthis->QTable);	
	jpe1.SetQuantTable( m_pthis->QTable1);	

	//For DMA0
	apcdata.fg = m_pthis->fg;
	apcdata.port = m_pthis->DmaIndex[0];
	apcdata.mem = m_pthis->pMem0;
	apcdata.displayid =m_pthis->nId;

	ctrl.version = 0;
	ctrl.data = &apcdata;
	ctrl.func = ApcFunc;
	ctrl.flags = FG_APC_DEFAULTS;
	ctrl.timeout = 10000;
	
	//For DMA1
	apcdata1.fg = m_pthis->fg;
	apcdata1.port = m_pthis->DmaIndex[1];
	apcdata1.mem = m_pthis->pMem1;
	apcdata1.displayid =m_pthis->nId1;

	ctrl1.version = 0;
	ctrl1.data = &apcdata1;
	ctrl1.func = ApcFunc1;
	ctrl1.flags = FG_APC_DEFAULTS;
	ctrl1.timeout = 10000;



	status = Fg_registerApcHandler(m_pthis->fg, m_pthis->DmaIndex[0], &ctrl, FG_APC_CONTROL_BASIC);
	if (status != FG_OK) {
		Fg_FreeMemEx(m_pthis->fg, pMem0);
		Fg_FreeGrabber(m_pthis->fg);
		return ;
	}
	
	status1 = Fg_registerApcHandler(m_pthis->fg, m_pthis->DmaIndex[1], &ctrl1, FG_APC_CONTROL_BASIC);
	if (status != FG_OK) {
		//fprintf(stderr, "registering APC handler failed: %s\n", Fg_getErrorDescription(fg, status));
		Fg_FreeMemEx(m_pthis->fg, pMem1);
		Fg_FreeGrabber(m_pthis->fg);
		//	CloseDisplay(nId);
		return ;
	}


	m_pthis -> GetDlgItem(IDC_Grab)->EnableWindow(TRUE);
	m_pthis -> GetDlgItem(IDC_BTN_Load)->EnableWindow(FALSE);
	//m_pthis -> GetDlgItem(IDC_stop)->EnableWindow(TRUE);

}


void CSISO_APC_GbEDlg::OnBnClickedGrab()
{
	// TODO: 在此添加控件通知处理程序代码
	// ====================================================
	ichk =M_SaveJpeg.GetCheck();
	//ichk1 =M_SaveJpeg1.GetCheck();

	if (!ichk)
	{
		writeToFile =false;
		//writeToFile1 =false;
	} 
	else
	{
		writeToFile =true;
		//writeToFile1 =true;
	}


	//if (!ichk1)
	//{
	//	writeToFile1 =false;
	//} 
	//else
	//{
	//	writeToFile1 =true;
	//}



	Is_show = M_ShowImg.GetCheck();
	if (Is_show)
	{
		ShowImage =true;
	} 
	else
	{
		ShowImage =false;
	}



	if ((Fg_AcquireEx(m_pthis->fg, m_pthis->DmaIndex[0], GRAB_INFINITE, ACQ_STANDARD,m_pthis-> pMem0)) < 0) 
	{
		const char*	err_str1 = Fg_getLastErrorDescription(m_pthis->fg);
		Fg_FreeMemEx(m_pthis->fg, pMem0);
		Fg_FreeGrabber(m_pthis->fg);

		return ;
	}


	if ((Fg_AcquireEx(m_pthis->fg, m_pthis->DmaIndex[1], GRAB_INFINITE, ACQ_STANDARD,m_pthis-> pMem1)) < 0) {
		//status = ErrorMessageWait(fg);
		const char*	err_str1 = Fg_getLastErrorDescription(m_pthis->fg);
		Fg_FreeMemEx(m_pthis->fg, pMem1);
		Fg_FreeGrabber(m_pthis->fg);

		return ;
	}

	///***********Starts the grabbing within the camera***********/
	//if((Gbe_startAcquisition(ch_PORT_A)) < 0) {
	//	exit(-1);
	//}

	//if((Gbe_startAcquisition(ch_PORT_B)) < 0) {
	//	exit(-1);
	//}

	////Create Thread
	DWORD id;
	m_CpState=1;
	SetTimer(0,1000,NULL);//ID为0，定时间隔1000ms,相应函数Ontimer()
	ticks_a=GetTickCount();
	ticks = GetTickCount();
	ticks2= GetTickCount();
	ticks_c=GetTickCount();
	ticks_a1=GetTickCount();
	ticks_c1=GetTickCount();

	hThShow=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)thfuncshow,this,0,&id);
	//SetTimer(0,1000,NULL);

	m_pthis -> GetDlgItem(IDC_Stop)->EnableWindow(TRUE);
	m_pthis -> GetDlgItem(IDC_Grab)->EnableWindow(FALSE);

}


void CSISO_APC_GbEDlg::OnBnClickedStop()
{
	// TODO: 在此添加控件通知处理程序代码
	m_CpState=0;
	KillTimer(0);
	WaitForSingleObject(hThShow,100);
	ResetEvent(m_PutEvent0);
	SetEvent(m_DrawEvent0);
	ResetEvent(m_PutEvent1);
	SetEvent(m_DrawEvent1);

	// Freeing the grabber resource
	//Gbe_stopAcquisition(ch_PORT_A);
	//Gbe_disconnectCamera(ch_PORT_A);
	//Gbe_freeCamera(ch_PORT_A);
	//Gbe_stopAcquisition(ch_PORT_B);
	//Gbe_disconnectCamera(ch_PORT_B);
	//Gbe_freeCamera(ch_PORT_B);
	//Gbe_freeBoard(board_handle_ptr);

	Fg_registerApcHandler(m_pthis->fg, DmaIndex[0], NULL, FG_APC_CONTROL_BASIC);
	Fg_stopAcquireEx(m_pthis->fg,DmaIndex[0],pMem0,0);
	Fg_FreeMemEx(m_pthis->fg, pMem0);

	Fg_registerApcHandler(m_pthis->fg, DmaIndex[1], NULL, FG_APC_CONTROL_BASIC);
	Fg_stopAcquireEx(m_pthis->fg,DmaIndex[1],pMem1,0);
	Fg_FreeMemEx(m_pthis->fg, pMem1);

	Fg_FreeGrabber(fg);

	if(bufferJPEGfile0)delete []bufferJPEGfile0;
	if(bufferJPEGfile1)delete []bufferJPEGfile1;
	bufferJPEGfile0 = NULL;
	bufferJPEGfile1 = NULL;
	lengthJPEGfile0 = 0;
	lengthJPEGfile1 = 0;
	
	fps = 0; fps1 = 0;
	CString strtmp,strtmp1;
	strtmp.Format(_T("fps:%.3f"), fps);
	strtmp1.Format(_T("fps:%.3f"), fps1);
	m_pthis->m_stc_fps.SetWindowTextW(strtmp);
	m_pthis->m_stc_fps1.SetWindowTextW(strtmp1);
	
	m_pthis -> GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
	m_pthis -> GetDlgItem(IDC_BTN_Load)->EnableWindow(TRUE);
	return;
}

//DealJpeg 
void CSISO_APC_GbEDlg::DealJPEG(LONG64 dmalenJPEG,void* iPtrJPEG
	,TCHAR* filename,int w,int h,bool bIsSave
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
		}


	}


}


void CSISO_APC_GbEDlg::DrawImage(int itemID,unsigned char* buf,int w,int h)
{
	
	//////////////////////////////////////////////////////////////////////////
	//uint8_t* image_memory0  = static_cast<uint8_t*>(decodedImage);
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
	//int Device1_Process0_JPEG_Encoder_quantization_matrix_Id = Fg_getParameterIdByName(fg, "Device1_Process0_JPEG_Encoder_quantization_matrix");
	int Device1_Process0_Encoder_quantization_matrix_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Encoder_quantization_matrix");
	FieldParameterInt readQuantizationValue;
	printf("New QTable:");
	for (int i = 0; i < 64; i++)
	{
		readQuantizationValue.index = i;
		readQuantizationValue.value = 0;
		//Fg_getParameter(fg, Device1_Process0_JPEG_Encoder_quantization_matrix_Id, &readQuantizationValue, 0);
		 Fg_getParameter(fg, Device1_Process0_Encoder_quantization_matrix_Id, &readQuantizationValue, 0); 
		QTable[i] = readQuantizationValue.value;
		if (i % 8 == 0)
			printf("\n");
		printf("%d ", readQuantizationValue.value);

	}

	//------------For marathron VCL Board








	return 0;

}

int CSISO_APC_GbEDlg::getQuantizationTable1(Fg_Struct* fg) 
{
	//int Device1_Process0_JPEG_Encoder_quantization_matrix_Id = Fg_getParameterIdByName(fg, "Device1_Process0_JPEG_Encoder_quantization_matrix");
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
	ichk= M_SaveJpeg.GetCheck();
	
	if (!ichk)
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
	   s = M_JpegQuality.GetString();
	   n=_tstoi(s);
       JPEGQuality = n;
}



void CSISO_APC_GbEDlg::OnClickedExit()
{
	// TODO: 在此添加控件通知处理程序代码
    if(m_pthis->m_CpState == 1)
		OnBnClickedStop();
	CDialogEx::OnOK();
}


void CSISO_APC_GbEDlg::OnClickedShowimg()
{
	// TODO: 在此添加控件通知处理程序代码
	Is_show = M_ShowImg.GetCheck();
	if (Is_show)
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString strtmp,strtmp1;
	strtmp.Format(_T("fps:%.3f"), m_pthis->fps);
	strtmp1.Format(_T("fps:%.3f"), m_pthis->fps1);
	m_pthis->m_stc_fps.SetWindowTextW(strtmp);
	m_pthis->m_stc_fps1.SetWindowTextW(strtmp1);
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

	if(	m_eCollectMode != eCollectMode)
	{
		m_eCollectMode = eCollectMode;
		if(fg != NULL)
		{
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

			int Device1_Process0_Trigger_TriggerMode_Select_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_TriggerMode_Select");
			Fg_setParameterWithType(fg, Device1_Process0_Trigger_TriggerMode_Select_Id, Trigger_TriggerMode_Select, 0);

			int Device1_Process1_Trigger_TriggerMode_Select_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_TriggerMode_Select");
			Fg_setParameterWithType(fg, Device1_Process1_Trigger_TriggerMode_Select_Id, Trigger_TriggerMode_Select, 0);
		}
	}
}

void CSISO_APC_GbEDlg::OnCbnSelchangeComboconnectstatus()
{
	// TODO: 在此添加控件通知处理程序代码
	if(fg != NULL)
	{
		int iStatus, iReturn;
		switch(m_comboBoxConnectStatus.GetCurSel())
		{
		case 0:
			iReturn = Fg_getParameter(fg,FG_CAMSTATUS,&iStatus, PORT_A);
			break;
		case 1:
			iReturn = Fg_getParameter(fg,FG_CAMSTATUS,&iStatus, PORT_B);
			break;
		case 2: case 3: case 4: case 5:
		default:;
		};

		switch (iStatus)
		{
		case 0:
			m_stc_ConnectStatus.SetWindowTextW(L"Unconnected");
			break;
		case 1:
			m_stc_ConnectStatus.SetWindowTextW(L"Connected");
			break;
		}
	}
	else
	{
		m_stc_ConnectStatus.SetWindowTextW(L"Uninitialized");
	}
}
