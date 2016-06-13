
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

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(test_lg, src::severity_logger< >)
src::severity_logger< >& lg = test_lg::get();

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

int ApcFunc(frameindex_t picNr, struct fg_apc_data *data)
{
	if(data->fg == NULL)
		return -1;

	SYSTEMTIME st;
	GetLocalTime(&st);

	char strFile[255];
	sprintf_s(strFile, "%s%d%s%d_%d_%d_%d_%.2d_%.2d_%.2d_%.3d_%d_%d.jpg",m_pthis->m_cDirPrefix, m_pthis->m_iStartIndex + data->iIndex, "\\Cam",m_pthis->m_iStartIndex + data->iIndex, 
		st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond, st.wMilliseconds, m_pthis->JPEGQuality,picNr);

	//*****************Get TansferLen of the current DMA channel***************//
	LONG64 dmalenJPEG = 0;
	Fg_getParameterEx(data->fg,FG_TRANSFER_LEN,&dmalenJPEG,data->port,data->mem,picNr); 
	void* iPtrJPEG = Fg_getImagePtrEx(data->fg, picNr, data->port, data->mem);//Get the Pointer of the Jpeg files
	m_pthis->DealJPEG(dmalenJPEG, iPtrJPEG,strFile,m_pthis->width[data->iIndex],m_pthis->height[data->iIndex],m_pthis->writeToFile,m_pthis->m_bPreview[data->iIndex],data->iDisplayId,&m_pthis->jpe[data->iIndex]);

	//Calculate fps
	m_pthis->statusJPEG[data->iIndex] = picNr;

	m_pthis->m_iTickEnd[data->iIndex] = GetTickCount();
	unsigned itick =m_pthis->m_iTickEnd[data->iIndex] - m_pthis->m_iTickStart[data->iIndex];
	if ( itick > 100 ){
		BOOST_LOG_SEV(lg, info) << "相机 " << data->iIndex << ": " << itick << "。图片序号： " << picNr;
	}
	m_pthis->m_iTickStart[data->iIndex] = m_pthis->m_iTickEnd[data->iIndex];
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
				m_pthis->DecodeImg(m_pthis->bufferJPEGfile0,m_pthis->lengthJPEGfile0,IDC_ImgDisplay,m_pthis->width[0],m_pthis->height[0]);//图像显示
				SetEvent(m_pthis->m_DrawEvent0);//显示之后将显示线程置零
			}

			if(WaitForSingleObject(m_pthis->m_PutEvent1,10)==WAIT_OBJECT_0)
			{
				ResetEvent(m_pthis->m_PutEvent1);
				m_pthis->DecodeImg(m_pthis->bufferJPEGfile1,m_pthis->lengthJPEGfile1,IDC_ImgDisplay1,m_pthis->width[1],m_pthis->height[1]);
				SetEvent(m_pthis->m_DrawEvent1);
			}
		}
		if(m_pthis->fg1 != NULL){
			if(WaitForSingleObject(m_pthis->m_PutEvent2,10)==WAIT_OBJECT_0)
			{
				ResetEvent(m_pthis->m_PutEvent2);
				m_pthis->DecodeImg(m_pthis->bufferJPEGfile2,m_pthis->lengthJPEGfile2,IDC_ImgDisplay2,m_pthis->width[2],m_pthis->height[2]);
				SetEvent(m_pthis->m_DrawEvent2);
			}
			if(WaitForSingleObject(m_pthis->m_PutEvent3,10)==WAIT_OBJECT_0)
			{
				ResetEvent(m_pthis->m_PutEvent3);
				m_pthis->DecodeImg(m_pthis->bufferJPEGfile3,m_pthis->lengthJPEGfile3,IDC_ImgDisplay3,m_pthis->width[3],m_pthis->height[3]);
				SetEvent(m_pthis->m_DrawEvent3);
			}
		}
		if(m_pthis->fg2 != NULL){
			if(WaitForSingleObject(m_pthis->m_PutEvent4,10)==WAIT_OBJECT_0)
			{
				ResetEvent(m_pthis->m_PutEvent4);
				m_pthis->DecodeImg(m_pthis->bufferJPEGfile4,m_pthis->lengthJPEGfile4,IDC_ImgDisplay4,m_pthis->width[4], m_pthis->height[4]);
				SetEvent(m_pthis->m_DrawEvent4);
			}
			if(WaitForSingleObject(m_pthis->m_PutEvent5,10)==WAIT_OBJECT_0)
			{
				ResetEvent(m_pthis->m_PutEvent5);
				m_pthis->DecodeImg(m_pthis->bufferJPEGfile5, m_pthis->lengthJPEGfile5,IDC_ImgDisplay5,m_pthis->width[5],m_pthis->height[5]);
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
	, width(6, 0), height(6, 0), ticks(6, 0), m_iTickStart(6, 0), m_iTickEnd(6, 0)
	, hThShow(NULL)
	, m_PutEvent0(NULL), m_PutEvent1(NULL), m_PutEvent2(NULL), m_PutEvent3(NULL), m_PutEvent4(NULL), m_PutEvent5(NULL)
	, m_DrawEvent0(NULL), m_DrawEvent1(NULL), m_DrawEvent2(NULL), m_DrawEvent3(NULL), m_DrawEvent4(NULL), m_DrawEvent5(NULL)
	, bufferJPEGfile0(NULL), bufferJPEGfile1(NULL), bufferJPEGfile2(NULL), bufferJPEGfile3(NULL), bufferJPEGfile4(NULL), bufferJPEGfile5(NULL)
	, lengthJPEGfile0(0), lengthJPEGfile1(0), lengthJPEGfile2(0), lengthJPEGfile3(0), lengthJPEGfile4(0), lengthJPEGfile5(0)
	, m_pBmpInfo(NULL)
	, JPEGQuality(75)
	, m_CpState(0)
	, DmaIndex(2, 0)
	, m_bPreview(6, true)
	, fps(6, 0)
	, statusJPEG(6, 0)
	, oldStatusJPEG(6, 0)
	, m_iStartIndex(-1)
	, m_eCollectMode(MODE_TRIGGER)
	, m_iCollectFrequency(40)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pthis = this;
}

void CSISO_APC_GbEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SaveJpeg, M_SaveJpeg);
	DDX_Control(pDX, IDC_ShowImg, m_buttonPreview);
	DDX_Text(pDX, IDC_JpegQuality, M_JpegQuality);
	DDX_Control(pDX, IDC_Fps, m_stc_fps);
	DDX_Control(pDX, IDC_Fps1, m_stc_fps1);
	DDX_Control(pDX, IDC_Fps2, m_stc_fps2);
	DDX_Control(pDX, IDC_Fps3, m_stc_fps3);
	DDX_Control(pDX, IDC_Fps4, m_stc_fps4);
	DDX_Control(pDX, IDC_Fps5, m_stc_fps5);
	DDX_Control(pDX, IDC_COMBOCollectMode, m_comboBoxCollectMode);
	DDX_Control(pDX, IDC_COMBOConnectStatus, m_comboBoxConnectStatus);
	//DDX_Control(pDX, IDC_STATICConnectStatus, m_stc_ConnectStatus);
	DDX_Control(pDX, IDC_COMBO_ExposureTime, m_comboBox_ExposureTime);
	//DDX_Control(pDX, IDC_EDIT_ExposureTime, m_stc_ExposureTime);
	DDX_Control(pDX, IDC_COMBO_Gain, m_comboBox_Gain);
	DDX_Control(pDX, IDC_COMBO_Preview, m_comboBoxPreview);
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
	ON_CBN_SELCHANGE(IDC_COMBOConnectStatus, &CSISO_APC_GbEDlg::OnCbnSelchangeComboconnectstatus)
	ON_BN_CLICKED(IDC_BUTTONCollectFrequency, &CSISO_APC_GbEDlg::OnBnClickedButtoncollectfrequency)
	ON_BN_CLICKED(IDC_BUTTON_ExposureTime, &CSISO_APC_GbEDlg::OnBnClickedButtonExposuretime)
	ON_BN_CLICKED(IDC_BUTTON_Gain, &CSISO_APC_GbEDlg::OnBnClickedButtonGain)
	ON_CBN_SELCHANGE(IDC_COMBO_ExposureTime, &CSISO_APC_GbEDlg::OnCbnSelchangeComboExposuretime)
	ON_CBN_SELCHANGE(IDC_COMBO_Gain, &CSISO_APC_GbEDlg::OnCbnSelchangeComboGain)
	ON_CBN_SELCHANGE(IDC_COMBO_Preview, &CSISO_APC_GbEDlg::OnCbnSelchangeComboPreview)
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
	M_SaveJpeg.SetCheck(BST_CHECKED);
	writeToFile = true;

	//读取配置文件，
	prot::ptree pt;
	prot::read_ini("TYConf.ini", pt);
	m_iStartIndex = pt.get<int>("CameraInfo.StartIndex");
	string sDirPrefix = pt.get<string>("Save.DirPrefix");

	if(m_iStartIndex < 0 || sDirPrefix.size() ==0){
		MessageBox(CString("找不到配置文件"));
	}

	SetSaveDir(sDirPrefix.c_str());
	
	//读取log配置文件
	std::ifstream settings("TYLog.ini");
	if (!settings.is_open())
	{
		std::cout << "Could not open settings.txt file" << std::endl;
		return 1;
	}

	// Read the settings and initialize logging library
	logging::init_from_stream(settings);
	logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());

	M_JpegQuality.Format(L"%d", JPEGQuality);
	
	// DMA list for All Cards 
	DmaIndex[0] = 0;
	DmaIndex[1] = 1;

	m_bPreview[0] = m_bPreview[1] = m_bPreview[2] = m_bPreview[3] = m_bPreview[4] = m_bPreview[5] = true;
	m_buttonPreview.SetCheck(BST_CHECKED);

	/*********Initialize for JPEG*************/ 
	create_dc_table(dc_data,dc_len);
	jpe[0].SetDCHuffTable(dc_data,dc_len);
	create_ac_table(ac_data,ac_len);
	jpe[0].SetACHuffTable(ac_data,ac_len);

	create_dc_table(dc_data1,dc_len1);
	jpe[1].SetDCHuffTable(dc_data1,dc_len1);
	create_ac_table(ac_data1,ac_len1);
	jpe[1].SetACHuffTable(ac_data1,ac_len1);

	create_dc_table(dc_data2,dc_len2);
	jpe[2].SetDCHuffTable(dc_data2,dc_len2);
	create_ac_table(ac_data2,ac_len2);
	jpe[2].SetACHuffTable(ac_data2,ac_len2);

	create_dc_table(dc_data3,dc_len3);
	jpe[3].SetDCHuffTable(dc_data3,dc_len3);
	create_ac_table(ac_data3,ac_len3);
	jpe[3].SetACHuffTable(ac_data3,ac_len3);

	create_dc_table(dc_data4,dc_len4);
	jpe[4].SetDCHuffTable(dc_data4,dc_len4);
	create_ac_table(ac_data4,ac_len4);
	jpe[4].SetACHuffTable(ac_data4,ac_len4);

	create_dc_table(dc_data5,dc_len5);
	jpe[5].SetDCHuffTable(dc_data5,dc_len5);
	create_ac_table(ac_data5,ac_len5);
	jpe[5].SetACHuffTable(ac_data5,ac_len5);

	njInit(); //nanoJPEG decoder Initialization

	/*********Initialize m_pBmpInfo*************/ 
	//int i;
	//	m_pBmpInfo即指向m_chBmpBuf缓冲区，用户可以自己分配BTIMAPINFO缓冲区	
	m_pBmpInfo								= (BITMAPINFO *)m_chBmpBuf;
	//	初始化BITMAPINFO 结构，此结构在保存bmp文件、显示采集图像时使用
	m_pBmpInfo->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	//	图像宽度，一般为输出窗口宽度
	m_pBmpInfo->bmiHeader.biWidth			= width[0];
	//	图像宽度，一般为输出窗口高度
    m_pBmpInfo->bmiHeader.biHeight			= height[0];
	
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
	//int iIndex;
	m_comboBoxCollectMode.InsertString(0, L"触发模式");
	m_comboBoxCollectMode.InsertString(1, L"连续模式");
	m_comboBoxCollectMode.SetCurSel(0);
	
	m_eCollectMode = (0 == m_comboBoxCollectMode.GetCurSel()) ? MODE_TRIGGER : MODE_TIMER;

	CString cstrCollectFrequency;
	cstrCollectFrequency.Format(L"%d", m_iCollectFrequency);
	((CEdit *)GetDlgItem(IDC_EDITCollectFrequency))->SetWindowTextW(cstrCollectFrequency);

	//初始化连接状态
	m_comboBoxConnectStatus.InsertString(0, L"相机 0");
	m_comboBoxConnectStatus.InsertString(1, L"相机 1");
	m_comboBoxConnectStatus.InsertString(2, L"相机 2");
	m_comboBoxConnectStatus.InsertString(3, L"相机 3");
	m_comboBoxConnectStatus.InsertString(4, L"相机 4");
	m_comboBoxConnectStatus.InsertString(5, L"相机 5");
	m_comboBoxConnectStatus.SetCurSel(0);

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

	m_comboBoxPreview.InsertString(0, L"相机 0");
	m_comboBoxPreview.InsertString(1, L"相机 1");
	m_comboBoxPreview.InsertString(2, L"相机 2");
	m_comboBoxPreview.InsertString(3, L"相机 3");
	m_comboBoxPreview.InsertString(4, L"相机 4");
	m_comboBoxPreview.InsertString(5, L"相机 5");
	m_comboBoxPreview.SetCurSel(0);

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
		Fg_getParameter(fg,FG_WIDTH,&width[0],DmaIndex[0]);
		Fg_getParameter(fg,FG_HEIGHT,&height[0],DmaIndex[0]);
	
		Fg_getParameter(fg,FG_WIDTH,&width[1],DmaIndex[1]);
		Fg_getParameter(fg,FG_HEIGHT,&height[1],DmaIndex[1]);

		//	图像宽度，一般为输出窗口宽度
		m_pBmpInfo->bmiHeader.biWidth			= width[0];
		//	图像宽度，一般为输出窗口高度
		m_pBmpInfo->bmiHeader.biHeight			= height[0];
	
		/********Getting  general parameter from DMA*********/
		unsigned int nr_of_buffer = 16;
		size_t bytesPerPixel = 1; 

		 /**************Memory allocation For DMA 0***********/ 
		size_t totalBufSize = width[0]*height[0]*bytesPerPixel;
		if((pMem0 = Fg_AllocMemEx(fg,totalBufSize*nr_of_buffer,nr_of_buffer)) == NULL){
			const char*	err_str = Fg_getLastErrorDescription(fg);
			return;
		} 

		/************************Memory allocation For DMA 1*****************/ 
		size_t totalBufSize1 = width[1]*height[1]*bytesPerPixel;
		if((pMem1 = Fg_AllocMemEx(fg,totalBufSize1*nr_of_buffer,nr_of_buffer)) == NULL){
			const char*	err_str = Fg_getLastErrorDescription(fg);
			return;
		}
	
		///******************GetTable and SetTable for Jpeg 0 and Jpeg 1********************/
		//setJPEGQuality(fg,m_pthis->JPEGQuality);// transfer JPEG Quality to operator
		///*********Get Matrix table from the board*********/
	
		//m_pthis->getQuantizationTable( m_pthis->fg);
		//m_pthis->getQuantizationTable1( m_pthis->fg);
	
		//jpe0.SetQuantTable( m_pthis->QTable);	
		//jpe1.SetQuantTable( m_pthis->QTable1);	

		//For DMA0
		apcdata.fg = m_pthis->fg;
		apcdata.port = m_pthis->DmaIndex[0];
		apcdata.mem = m_pthis->pMem0;
		apcdata.iIndex = 0;
		apcdata.iDisplayId = IDC_ImgDisplay;

		ctrl.version = 0;
		ctrl.data = &apcdata;
		ctrl.func = ApcFunc;
		ctrl.flags = FG_APC_HIGH_PRIORITY | FG_APC_IGNORE_TIMEOUTS;
		ctrl.timeout = 100000;
	
		//For DMA1
		apcdata1.fg = m_pthis->fg;
		apcdata1.port = m_pthis->DmaIndex[1];
		apcdata1.mem = m_pthis->pMem1;
		apcdata1.iIndex = 1;
		apcdata1.iDisplayId = IDC_ImgDisplay1;

		ctrl1.version = 0;
		ctrl1.data = &apcdata1;
		ctrl1.func = ApcFunc;
		ctrl1.flags = FG_APC_HIGH_PRIORITY | FG_APC_IGNORE_TIMEOUTS;
		ctrl1.timeout = 100000;

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
		Fg_getParameter(fg1,FG_WIDTH,&width[2],DmaIndex[0]);
		Fg_getParameter(fg1,FG_HEIGHT,&height[2],DmaIndex[0]);
	
		Fg_getParameter(fg1,FG_WIDTH,&width[3],DmaIndex[1]);
		Fg_getParameter(fg1,FG_HEIGHT,&height[3],DmaIndex[1]);

		//	图像宽度，一般为输出窗口宽度
		//m_pBmpInfo->bmiHeader.biWidth			= width;
		//	图像宽度，一般为输出窗口高度
		//m_pBmpInfo->bmiHeader.biHeight			= height;
	
		/********Getting  general parameter from DMA*********/
		unsigned int nr_of_buffer = 16;
		size_t bytesPerPixel = 1; 

		 /**************Memory allocation For DMA 0***********/ 
		size_t totalBufSize = width[2]*height[2]*bytesPerPixel;
		if((pMem2 = Fg_AllocMemEx(fg1,totalBufSize*nr_of_buffer,nr_of_buffer)) == NULL){
			const char*	err_str = Fg_getLastErrorDescription(fg1);
			return;
		} 

		/************************Memory allocation For DMA 1*****************/ 
		size_t totalBufSize1 = width[3]*height[3]*bytesPerPixel;
		if((pMem3 = Fg_AllocMemEx(fg1,totalBufSize1*nr_of_buffer,nr_of_buffer)) == NULL){
			const char*	err_str = Fg_getLastErrorDescription(fg1);
			return;
		}
	
		///******************GetTable and SetTable for Jpeg 0 and Jpeg 1********************/
		//setJPEGQuality(fg1,m_pthis->JPEGQuality);// transfer JPEG Quality to operator
		///*********Get Matrix table from the board*********/
	
		//m_pthis->getQuantizationTable2( m_pthis->fg1);
		//m_pthis->getQuantizationTable3( m_pthis->fg1);
	
		//jpe2.SetQuantTable( m_pthis->QTable2);	
		//jpe3.SetQuantTable( m_pthis->QTable3);	

		//For DMA0
		apcdata2.fg = m_pthis->fg1;
		apcdata2.port = m_pthis->DmaIndex[0];
		apcdata2.mem = m_pthis->pMem2;
		apcdata2.iIndex = 2;
		apcdata2.iDisplayId = IDC_ImgDisplay2;

		ctrl2.version = 0;
		ctrl2.data = &apcdata2;
		ctrl2.func = ApcFunc;
		ctrl2.flags = FG_APC_HIGH_PRIORITY | FG_APC_IGNORE_TIMEOUTS;
		ctrl2.timeout = 100000;
	
		//For DMA1
		apcdata3.fg = m_pthis->fg1;
		apcdata3.port = m_pthis->DmaIndex[1];
		apcdata3.mem = m_pthis->pMem3;
		apcdata3.iIndex = 3;
		apcdata3.iDisplayId = IDC_ImgDisplay3;

		ctrl3.version = 0;
		ctrl3.data = &apcdata3;
		ctrl3.func = ApcFunc;
		ctrl3.flags = FG_APC_HIGH_PRIORITY | FG_APC_IGNORE_TIMEOUTS;
		ctrl3.timeout = 100000;

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
		Fg_getParameter(fg2,FG_WIDTH,&width[4],DmaIndex[0]);
		Fg_getParameter(fg2,FG_HEIGHT,&height[4],DmaIndex[0]);
	
		Fg_getParameter(fg2,FG_WIDTH,&width[5],DmaIndex[1]);
		Fg_getParameter(fg2,FG_HEIGHT,&height[5],DmaIndex[1]);

		//	图像宽度，一般为输出窗口宽度
		//m_pBmpInfo->bmiHeader.biWidth			= width;
		//	图像宽度，一般为输出窗口高度
		//m_pBmpInfo->bmiHeader.biHeight			= height;
	
		/********Getting  general parameter from DMA*********/
		unsigned int nr_of_buffer = 16;
		size_t bytesPerPixel = 1; 

		 /**************Memory allocation For DMA 0***********/ 
		size_t totalBufSize = width[4]*height[4]*bytesPerPixel;
		if((pMem4 = Fg_AllocMemEx(fg2,totalBufSize*nr_of_buffer,nr_of_buffer)) == NULL){
			const char*	err_str = Fg_getLastErrorDescription(fg2);
			return;
		} 

		/************************Memory allocation For DMA 1*****************/ 
		size_t totalBufSize1 = width[5]*height[5]*bytesPerPixel;
		if((pMem5 = Fg_AllocMemEx(fg2,totalBufSize1*nr_of_buffer,nr_of_buffer)) == NULL){
			const char*	err_str = Fg_getLastErrorDescription(fg2);
			return;
		}
	
		///******************GetTable and SetTable for Jpeg 0 and Jpeg 1********************/
		//setJPEGQuality(fg2,m_pthis->JPEGQuality);// transfer JPEG Quality to operator
		///*********Get Matrix table from the board*********/
	
		//m_pthis->getQuantizationTable( m_pthis->fg2);
		//m_pthis->getQuantizationTable1( m_pthis->fg2);
	
		//jpe4.SetQuantTable( m_pthis->QTable4);	
		//jpe5.SetQuantTable( m_pthis->QTable5);	

		//For DMA0
		apcdata4.fg = m_pthis->fg2;
		apcdata4.port = m_pthis->DmaIndex[0];
		apcdata4.mem = m_pthis->pMem4;
		apcdata4.iIndex = 4;
		apcdata4.iDisplayId = IDC_ImgDisplay4;

		ctrl4.version = 0;
		ctrl4.data = &apcdata4;
		ctrl4.func = ApcFunc;
		ctrl4.flags = FG_APC_HIGH_PRIORITY | FG_APC_IGNORE_TIMEOUTS;
		ctrl4.timeout = 100000;
	
		//For DMA1
		apcdata5.fg = m_pthis->fg2;
		apcdata5.port = m_pthis->DmaIndex[1];
		apcdata5.mem = m_pthis->pMem5;
		apcdata5.iIndex = 5;
		apcdata5.iDisplayId = IDC_ImgDisplay5;

		ctrl5.version = 0;
		ctrl5.data = &apcdata5;
		ctrl5.func = ApcFunc;
		ctrl5.flags = FG_APC_HIGH_PRIORITY | FG_APC_IGNORE_TIMEOUTS;
		ctrl5.timeout = 100000;

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
	//if (!M_SaveJpeg.GetCheck())
	//{
	//	writeToFile =false;
	//} 
	//else
	//{
	//	writeToFile =true;
	//}

	//if (M_ShowImg.GetCheck())
	//{
	//	ShowImage =true;
	//} 
	//else
	//{
	//	ShowImage =false;
	//}
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

	SetJpegQuality(JPEGQuality);

	m_CpState=1;
	SetTimer(0,1000,NULL);//ID为0，定时间隔1000ms,相应函数Ontimer()

	////Create Thread
	DWORD id;
	hThShow=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)thfuncshow,this,0,&id);

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
	
	fps[0] = fps[1] = fps[2] = fps[3] = fps[4] = fps[5] = 0;
	CString strtmp,strtmp1,strtmp2,strtmp3,strtmp4,strtmp5;
	strtmp.Format(_T("fps:%.3f"), fps[0]);
	strtmp1.Format(_T("fps:%.3f"), fps[1]);
	strtmp2.Format(_T("fps:%.3f"), fps[2]);
	strtmp3.Format(_T("fps:%.3f"), fps[3]);
	strtmp4.Format(_T("fps:%.3f"), fps[4]);
	strtmp5.Format(_T("fps:%.3f"), fps[5]);
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
	ptjpe->SetVLCBitstream((unsigned char*)iPtrJPEG,(unsigned long)dmalenJPEG);
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


int CSISO_APC_GbEDlg::getQuantizationTable(Fg_Struct* fg, const char *cMatrix_ID, unsigned char (*Qtable)[64]) 
{
	int Device1_Process0_Encoder_quantization_matrix_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Encoder_quantization_matrix");
	FieldParameterInt readQuantizationValue;
	//printf("New QTable:");
	for (int i = 0; i < 64; i++)
	{
		readQuantizationValue.index = i;
		readQuantizationValue.value = 0;
		 Fg_getParameter(fg, Device1_Process0_Encoder_quantization_matrix_Id, &readQuantizationValue, 0); 
		(*Qtable)[i] = readQuantizationValue.value;
		//if (i % 8 == 0)
			//printf("\n");
		//printf("%d ", readQuantizationValue.value);

	}
	return 0;
}

void CSISO_APC_GbEDlg::OnBnClickedSavejpeg()
{
	// TODO: 在此添加控件通知处理程序代码
	writeToFile = M_SaveJpeg.GetCheck() ? true : false;
}

void CSISO_APC_GbEDlg::OnClickedActivequality()
{
	UpdateData(TRUE);
	SetJpegQuality(_tstoi(M_JpegQuality.GetString()));
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
	int iCameraIndex = m_comboBoxPreview.GetCurSel();

	m_bPreview[iCameraIndex] = m_buttonPreview.GetCheck() ? true : false;
}

void CSISO_APC_GbEDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString strtmp[6];
	for (unsigned i = 0; i < 6 ; ++i)
	{
		fps[i] = 1000.0 * (statusJPEG[i] - oldStatusJPEG[i]) / (GetTickCount() - ticks[i]);
		oldStatusJPEG[i] = statusJPEG[i];
		ticks[i] = GetTickCount();
		strtmp[i].Format(_T("fps:%.3f"), fps[i]);
	}

	m_stc_fps.SetWindowTextW(strtmp[0]);
	m_stc_fps1.SetWindowTextW(strtmp[1]);
	m_stc_fps2.SetWindowTextW(strtmp[2]);
	m_stc_fps3.SetWindowTextW(strtmp[3]);
	m_stc_fps4.SetWindowTextW(strtmp[4]);
	m_stc_fps5.SetWindowTextW(strtmp[5]);
	CDialogEx::OnTimer(nIDEvent);
}

void CSISO_APC_GbEDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_CpState == 1)
		OnBnClickedStop();

	CDialogEx::OnClose();
}

void CSISO_APC_GbEDlg::OnCbnSelchangeComboPreview()
{
	int iCameraIndex = m_comboBoxPreview.GetCurSel();

	if(m_bPreview[iCameraIndex])
		m_buttonPreview.SetCheck(BST_CHECKED);
	else
		m_buttonPreview.SetCheck(BST_UNCHECKED);
}

void CSISO_APC_GbEDlg::OnCbnSelchangeCombocollectmode()
{
	// TODO: 在此添加控件通知处理程序代码

	COLLECT_MODE eCollectMode;
	eCollectMode = (0 == m_comboBoxCollectMode.GetCurSel()) ? MODE_TRIGGER : MODE_TIMER;

	SetCollectMode(eCollectMode);
}

void CSISO_APC_GbEDlg::OnCbnSelchangeComboconnectstatus()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!fg && !fg1 && !fg2)
		return;

	bool bConnect;
	GetConnectStatus(m_comboBoxConnectStatus.GetCurSel(), bConnect);
	
	wstring strStatus;
	strStatus = (true == bConnect) ? L"已连接" : L"未连接";
	GetDlgItem(IDC_STATICConnectStatus)->SetWindowTextW(strStatus.c_str());
}


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
		Trigger_TriggerMode_Select = (MODE_TRIGGER == m_eCollectMode) ? 0 : 1; 

		if(fg != NULL)
		{
			int Device1_Process0_Trigger_TriggerMode_Select_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_TriggerMode_Select");
			if (Device1_Process0_Trigger_TriggerMode_Select_Id < 0){
				cout << "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_TriggerMode_Select) " << Fg_getLastErrorDescription(fg) << Device1_Process0_Trigger_TriggerMode_Select_Id << endl;
			}

			int rc = Fg_setParameterWithType(fg, Device1_Process0_Trigger_TriggerMode_Select_Id, Trigger_TriggerMode_Select, 0);
			if(rc < 0) {
				cout << "Error in Fg_setParameterWithType(Device1_Process0_Trigger_TriggerMode_Select_Id) " << Fg_getLastErrorDescription(fg) << rc << endl;
			}

			int Device1_Process1_Trigger_TriggerMode_Select_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_TriggerMode_Select");
			if (Device1_Process1_Trigger_TriggerMode_Select_Id < 0){
				cout << "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_TriggerMode_Select) " << Fg_getLastErrorDescription(fg) << Device1_Process1_Trigger_TriggerMode_Select_Id << endl;
			}
			
			rc = Fg_setParameterWithType(fg, Device1_Process1_Trigger_TriggerMode_Select_Id, Trigger_TriggerMode_Select, 0);
			if(rc < 0) {
				cout << "Error in Fg_setParameterWithType(Device1_Process1_Trigger_TriggerMode_Select_Id) " << Fg_getLastErrorDescription(fg) << rc << endl;
			}
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

	setJPEGQuality(fg,JPEGQuality);// transfer JPEG Quality to operator
	getQuantizationTable(fg, "Device1_Process0_Encoder_quantization_matrix", &QTable);
	jpe[0].SetQuantTable(QTable);

	getQuantizationTable(fg, "Device1_Process1_Encoder_quantization_matrix", &QTable1);
	jpe[1].SetQuantTable(QTable1);

	setJPEGQuality(fg1,JPEGQuality);// transfer JPEG Quality to operator
	getQuantizationTable(fg1, "Device1_Process0_Encoder_quantization_matrix", &QTable2);
	jpe[2].SetQuantTable(QTable2);

	getQuantizationTable(fg1, "Device1_Process1_Encoder_quantization_matrix", &QTable3);
	jpe[3].SetQuantTable(QTable3);

	setJPEGQuality(fg2,JPEGQuality);// transfer JPEG Quality to operator
	getQuantizationTable(fg2, "Device1_Process0_Encoder_quantization_matrix", &QTable4);
	jpe[4].SetQuantTable(QTable4);

	getQuantizationTable(fg2, "Device1_Process1_Encoder_quantization_matrix", &QTable5);
	jpe[5].SetQuantTable(QTable5);

	return TY_OK;
}

TY_STATUS CSISO_APC_GbEDlg::SetSaveDir(const char* cSaveDir)
{
	if(!cSaveDir)
		return TY_ERROR;

	memset(m_cDirPrefix, 0, sizeof(m_cDirPrefix));
	strcpy_s(m_cDirPrefix, cSaveDir);
	//创建存储的目录。
	if(m_cDirPrefix[strlen(m_cDirPrefix) -1] != '\\')
		strcat_s(m_cDirPrefix, "\\");
	std::string sDir(m_cDirPrefix), sDir0, sDir1, sDir2, sDir3, sDir4, sDir5;
	sDir0 = sDir + boost::lexical_cast<std::string>(m_iStartIndex) + std::string("\\");
	sDir1 = sDir + boost::lexical_cast<std::string>(m_iStartIndex+1) + std::string("\\");
	sDir2 = sDir + boost::lexical_cast<std::string>(m_iStartIndex+2) + std::string("\\");
	sDir3 = sDir + boost::lexical_cast<std::string>(m_iStartIndex+3) + std::string("\\");
	sDir4 = sDir + boost::lexical_cast<std::string>(m_iStartIndex+4) + std::string("\\");
	sDir5 = sDir + boost::lexical_cast<std::string>(m_iStartIndex+5) + std::string("\\");
	fs::create_directories(sDir0);
	fs::create_directories(sDir1);
	fs::create_directories(sDir2);
	fs::create_directories(sDir3);
	fs::create_directories(sDir4);
	fs::create_directories(sDir5);

	return TY_OK;
}
	
TY_STATUS CSISO_APC_GbEDlg::SetPreviewMode(unsigned int iIndexCamera, PREVIEW_MODE eMode)
{
	if(0 > iIndexCamera || iIndexCamera > 5)
		return TY_ERROR;
	
	m_bPreview[iIndexCamera] = (PREVIEW_OPEN == eMode) ? true : false;
	return TY_OK;
}

TY_STATUS CSISO_APC_GbEDlg::GetPreviewMode(unsigned int iIndexCamera, PREVIEW_MODE &eMode)
{
	if(0 > iIndexCamera || iIndexCamera > 5)
		return TY_ERROR;

	eMode = m_bPreview[iIndexCamera] ? PREVIEW_OPEN : PREVIEW_CLOSE;
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

TY_STATUS CSISO_APC_GbEDlg::clSerialOperator(unsigned int iIndexCamera, char *line, char *cReturn)
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
		
	TY_STATUS eStatus = TY_ERROR;
	
	size_t len = strlen(line);
	line[len] = 10;
	line[len+1] = 0;
	len = strlen(line);
	int error = clSerialWrite(hSer, line, (unsigned int*)&len, 500);
	
	if (CString("SA=3")==CString(line).Trim())
		Sleep(2000);

	len = 256;
	error = clSerialRead(hSer, cReturn, (unsigned int*)&len, 256);
	
	if(error == CL_ERR_NO_ERR)
	{
		eStatus = TY_OK;
	}
	// clean up the serial port reference
	clSerialClose(hSer);
	return eStatus;
}

TY_STATUS CSISO_APC_GbEDlg::GetGain(unsigned int iIndexCamera, unsigned int &iGain)
{
	char line[256]= "FGA?";
	char cReturn[256] = {0};

	TY_STATUS eStatus = clSerialOperator(iIndexCamera, line, cReturn);
	if(TY_OK == eStatus) {
		string cst(cReturn, 4, (int)strlen(cReturn)-6);
		iGain = stoi(cst);
	}
	return eStatus;
}

TY_STATUS CSISO_APC_GbEDlg::SetGain(unsigned int iIndexCamera, unsigned int iGain)
{
	if(iGain < 100 || iGain > 1600) {
		return TY_ERROR;
	}

	char line[256] = {0};
	sprintf_s(line, "FGA=%d", iGain);
	char cReturn[256] = {0};

	TY_STATUS eStatus = clSerialOperator(iIndexCamera, line, cReturn);
	if(TY_OK == eStatus) {
		CString cst(cReturn);
		if(cst.Trim() != CString("COMPLETE"))
			eStatus = TY_ERROR;
	}

	eStatus = SaveUserSet(iIndexCamera);

	return eStatus;
}

TY_STATUS CSISO_APC_GbEDlg::GetExposureTime(unsigned int iIndexCamera, unsigned int &iExposureTime)
{
	char line[256]= "PE?";
	char cReturn[256] = {0};

	TY_STATUS eStatus = clSerialOperator(iIndexCamera, line, cReturn);
	if(TY_OK == eStatus) {
		CString cst(cReturn);
		iExposureTime = _tstoi(cst.Mid(3, (int)strlen(cReturn)-5).GetString());
	}
	return eStatus;
}

TY_STATUS CSISO_APC_GbEDlg::SetExposureTime(unsigned int iIndexCamera, unsigned int iExposureTime)
{
	if(iExposureTime < 10 || iExposureTime > 8000000) {
		return TY_ERROR;
	}

	char line[256] = {0};
	sprintf_s(line, "PE=%d", iExposureTime);
	char cReturn[256] = {0};

	TY_STATUS eStatus = clSerialOperator(iIndexCamera, line, cReturn);
	if(TY_OK == eStatus) {
		CString cst(cReturn);
		if(cst.Trim() != CString("COMPLETE"))
			eStatus = TY_ERROR;
	}

	eStatus = SaveUserSet(iIndexCamera);
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

TY_STATUS CSISO_APC_GbEDlg::GetConnectStatus(unsigned iIndexCamera, bool &bConnect)
{
	if(0 > iIndexCamera || iIndexCamera > 5)
		return TY_ERROR;

	unsigned iGain;
	TY_STATUS status;
	status = GetGain(m_comboBoxConnectStatus.GetCurSel(), iGain);
	bConnect = (TY_OK == status) ? true : false;

	return TY_OK;
}

TY_STATUS CSISO_APC_GbEDlg::SaveUserSet(unsigned iIndexCamera)
{
	char line[256] = {0};
	strcpy_s(line, "SA=3");
	char cReturn[256] = {0};

	TY_STATUS eStatus = clSerialOperator(iIndexCamera, line, cReturn);
	if(TY_OK == eStatus) {
		CString cst(cReturn);
		if(cst.Trim() != CString("COMPLETE"))
			eStatus = TY_ERROR;
	}
	return eStatus;
}