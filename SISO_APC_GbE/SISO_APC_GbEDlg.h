
// SISO_APC_GbEDlg.h : 头文件
//

#pragma once


/********SISO******/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//#include "board_and_dll_chooser.h"

#include <fgrab_struct.h>
#include <fgrab_prototyp.h>
#include <fgrab_define.h>
#include <SisoDisplay.h>
#include <gbe.h>
#include "jpeg/JPEGEncoder.h"
#include "afxwin.h"
#include "SDrawInterface.h"

using namespace std; 

struct fg_apc_data {
	Fg_Struct *fg;
	unsigned int port;
	dma_mem *mem;
	int displayid;
};

// CSISO_APC_GbEDlg 对话框
class CSISO_APC_GbEDlg : public CDialogEx
{
// 构造
public:
	CSISO_APC_GbEDlg(CWnd* pParent = NULL);	// 标准构造函数
	// APC  Data Struct

	Fg_Struct *fg;
	dma_mem *pMem0;
	dma_mem *pMem1;
	//dma_mem *pMem1;
	int nId;
	int nId1;
	int status ;
	int status1;
	int retCode ;
	unsigned int DmaIndex[8];
	struct fg_apc_data apcdata;
	struct fg_apc_data apcdata1;
	struct FgApcControl ctrl;
	struct FgApcControl ctrl1;
	unsigned int BoardIndex;
	CameraHandle *ch_PORT_A,*ch_PORT_B;
	int nCamPort;
	int format;
	/*int Cam_width ;	
	int Cam_height;*/
	int xOffset;
	int yOffset;
	LONG64 width;
	LONG64 height;
	LONG64 height1;
	LONG64 width1;
	unsigned int ticks,ticks2;
	unsigned int ticks_a, ticks_b,ticks_c,ticks_d;
	unsigned int ticks_a1,ticks_b1,ticks_c1,ticks_d1;
	int Bits;
	CView*	m_pview;
	CRect	m_Img0;
	 unsigned int actualYLength;
	 unsigned int actualYLength1;

	 HANDLE	hThShow;
	 HANDLE m_PutEvent0,m_DrawEvent0;
	 HANDLE m_PutEvent1,m_DrawEvent1;
	 unsigned char* bufferJPEGfile0;// = NULL;
	 int lengthJPEGfile0;// = NULL;
	 unsigned char* bufferJPEGfile1;// = NULL;
	 int lengthJPEGfile1;// = NULL;

	 int ichk,ichk1;
	 
	 CString s;
	 CString yy;
	 int n;
	BITMAPINFO *m_pBmpInfo;	      ///< BITMAPINFO 结构指针，显示图像时使用
	char       m_chBmpBuf[4096];  ///< BIMTAPINFO 存储缓冲区，m_pBmpInfo即指向此缓冲区
	BoardHandle *board_handle_ptr;
	CameraHandle *ch; 
	int JPEGQuality;
	//int JPEGQuality1;
	bool writeToFile;
	//bool writeToFile1;
	bool ShowImage;
	int Is_show;
	unsigned int fileWriteCount;
	unsigned int fileWriteCount1;
	int		m_CpState;
	/***********QTable***********/
	unsigned char QTable[64];
	unsigned char QTable1[64];
	unsigned char calcQuantizationMatrixFromPercent(int p_percent);
	int getQuantizationTable(Fg_Struct* fg);
	int getQuantizationTable1(Fg_Struct* fg);
	void DealJPEG(LONG64 dmalenJPEG,void* iPtrJPEG,TCHAR* filename,int w,int h,bool bIsSave,bool bIsShow,int DrawItemID,void* pjpe);
	void	DecodeImg(unsigned char* bufferJPEGfile,int lengthJPEGfile,int itemID,int w,int h);
	void	DrawImage(int itemID,unsigned char* buf,int w,int h);
	bool checkROIconsistency(int maxWidth, int maxHeight, int xOffset, int xLength, int yOffset, int YLength);
	/*********Cacluate Fps************/
	double fps;
	double fps1;
	int oldStatusJPEG;
	int oldStatusJPEG1;
	int statusJPEG;
	int statusJPEG1;

	CString m_cstrIni;
	TCHAR m_cDirPrefix[256]; //存储路径的前缀。
	int   m_iStartIndex;     //摄像头的起始序列号。
// 对话框数据
	enum { IDD = IDD_SISO_APC_GBE_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedGrab();
	afx_msg void OnBnClickedStop();
	//afx_msg void OnClickedSavejpe();
	//afx_msg void OnDoubleclickedSavejpe();
	//afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	CButton M_SaveJpeg;
	//CButton M_SaveJpeg1;
	CButton M_ShowImg;
	afx_msg void OnBnClickedSavejpeg();
	afx_msg void OnClickedActivequality();
	UINT JpegQuality;
	CString M_JpegQuality;
	CStatic m_stc_fps;
	CStatic m_stc_fps1;

	//采集模式的变量
	enum COLLECT_MODE {MODE_TRIGGER, MODE_TIMER, MODE_NONE};
	COLLECT_MODE m_eCollectMode;
	CComboBox m_comboBoxCollectMode;

	//连接状态的变量
	CComboBox m_comboBoxConnectStatus;
	CStatic m_stc_ConnectStatus;
	//CString M_Fps;
	//CStatic m_staticTitle;
	
	//画图
	//CDBP m_srcTitle;
	//SDrawInterface	m_ImgPinter;

	afx_msg void OnClickedExit();
	afx_msg void OnClickedShowimg();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnCbnSelchangeCombocollectmode();
	afx_msg void OnCbnSelchangeComboconnectstatus();
};
