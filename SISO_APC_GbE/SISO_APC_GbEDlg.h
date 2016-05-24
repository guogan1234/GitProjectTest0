
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
#include <afxwin.h>
#include <clser.h>

#include "jpeg/JPEGEncoder.h"
#include "SDrawInterface.h"



using namespace std; 

struct fg_apc_data {
	Fg_Struct *fg;
	unsigned int port;
	dma_mem *mem;
//	int displayid;
};
enum TY_STATUS {TY_ERROR =-1, TY_OK = 0};


// CSISO_APC_GbEDlg 对话框
class CSISO_APC_GbEDlg : public CDialogEx
{
// 构造
public:
	CSISO_APC_GbEDlg(CWnd* pParent = NULL);	// 标准构造函数
	// APC  Data Struct

	Fg_Struct *fg, *fg1, *fg2;
	dma_mem *pMem0, *pMem1, *pMem2, *pMem3, *pMem4, *pMem5;
	
	unsigned int DmaIndex[2];
	struct fg_apc_data apcdata, apcdata1, apcdata2, apcdata3, apcdata4, apcdata5;
	struct FgApcControl ctrl, ctrl1, ctrl2, ctrl3, ctrl4, ctrl5;
	
	int xOffset;
	int yOffset;
	LONG64 width, width1, width2, width3, width4, width5;
	LONG64 height, height1, height2, height3, height4, height5;
	
	unsigned int ticks, ticks1, ticks2, ticks3, ticks4, ticks5;
	unsigned int ticks_a, ticks_b,ticks_c,ticks_d;

	HANDLE	hThShow;
	HANDLE m_PutEvent0, m_PutEvent1, m_PutEvent2, m_PutEvent3, m_PutEvent4, m_PutEvent5;
	HANDLE m_DrawEvent0, m_DrawEvent1, m_DrawEvent2, m_DrawEvent3, m_DrawEvent4, m_DrawEvent5;
	unsigned char *bufferJPEGfile0, *bufferJPEGfile1, *bufferJPEGfile2, *bufferJPEGfile3, *bufferJPEGfile4, *bufferJPEGfile5;
	int lengthJPEGfile0, lengthJPEGfile1, lengthJPEGfile2, lengthJPEGfile3, lengthJPEGfile4, lengthJPEGfile5;
	
	BITMAPINFO *m_pBmpInfo;	      ///< BITMAPINFO 结构指针，显示图像时使用
	char       m_chBmpBuf[4096];  ///< BIMTAPINFO 存储缓冲区，m_pBmpInfo即指向此缓冲区
	int JPEGQuality;
	bool writeToFile;
	
	unsigned int fileWriteCount;
	unsigned int fileWriteCount1;
	int		m_CpState;

	/***********QTable***********/
	unsigned char QTable[64], QTable1[64], QTable2[64], QTable3[64], QTable4[64], QTable5[64];
	unsigned char calcQuantizationMatrixFromPercent(int p_percent);
	int getQuantizationTable(Fg_Struct* fg);
	int getQuantizationTable1(Fg_Struct* fg);
	int getQuantizationTable2(Fg_Struct* fg);
	int getQuantizationTable3(Fg_Struct* fg);
	int getQuantizationTable4(Fg_Struct* fg);
	int getQuantizationTable5(Fg_Struct* fg);
	void DealJPEG(LONG64 dmalenJPEG,void* iPtrJPEG,char* filename,int w,int h,bool bIsSave,bool bIsShow,int DrawItemID,void* pjpe);
	void DecodeImg(unsigned char* bufferJPEGfile,int lengthJPEGfile,int itemID,int w,int h);
	void DrawImage(int itemID,unsigned char* buf,int w,int h);
	bool checkROIconsistency(int maxWidth, int maxHeight, int xOffset, int xLength, int yOffset, int YLength);
	/*********Cacluate Fps************/
	double fps, fps1, fps2, fps3, fps4, fps5;
	int oldStatusJPEG, oldStatusJPEG1, oldStatusJPEG2, oldStatusJPEG3, oldStatusJPEG4, oldStatusJPEG5;
	int statusJPEG, statusJPEG1, statusJPEG2, statusJPEG3, statusJPEG4, statusJPEG5;
	
	CString m_cstrIni;
	char m_cDirPrefix[256]; //存储路径的前缀。
	int   m_iStartIndex;     //摄像头的起始序列号。

	CButton M_SaveJpeg;
	
	CString M_JpegQuality;
	CStatic m_stc_fps, m_stc_fps1, m_stc_fps2, m_stc_fps3, m_stc_fps4, m_stc_fps5;
	
	//采集模式的变量
	enum COLLECT_MODE {MODE_TRIGGER, MODE_TIMER, MODE_NONE};

	enum PREVIEW_MODE {PREVIEW_OPEN, PREVIEW_CLOSE};
	COLLECT_MODE m_eCollectMode;
	CComboBox m_comboBoxCollectMode;

	//采集频率
	unsigned int m_iCollectFrequency;
	
	//连接状态的变量
	//CComboBox m_comboBoxConnectStatus;
	//CStatic m_stc_ConnectStatus;

	//相机曝光时间
	CComboBox m_comboBox_ExposureTime;

	//相机增益
	CComboBox m_comboBox_Gain;

	//预览
	bool m_bPreview[6];
	CButton m_buttonPreview;
	CComboBox m_comboBoxPreview;

	//以下接口需要被实现
	TY_STATUS SetCollectMode(COLLECT_MODE eMode);
	COLLECT_MODE GetCollectMode(){return m_eCollectMode;}

	TY_STATUS SetJpegQuality(unsigned int iQuality);
	unsigned int GetJpegQuality(){return JPEGQuality;}

	TY_STATUS SetSaveDir(char* cSaveDir);
	
	TY_STATUS SetPreviewMode(unsigned int iIndexCamera, PREVIEW_MODE eMode);
	TY_STATUS GetPreviewMode(unsigned int iIndexCamera, PREVIEW_MODE &eMode);

	TY_STATUS BeginCollect();
	TY_STATUS StopCollect();

	TY_STATUS GetGain(unsigned int iIndexCamera, unsigned int &iGain);
	TY_STATUS SetGain(unsigned int iIndexCamera, unsigned int iGain);

	TY_STATUS GetExposureTime(unsigned int iIndexCamera, unsigned int &iExposureTime);
	TY_STATUS SetExposureTime(unsigned int iIndexCamera, unsigned int iExposureTime);

	unsigned int GetCollectFrequency(){return m_iCollectFrequency;}
	TY_STATUS SetCollectFrequency(unsigned int iCollectFrequency);

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
	void OnBnClickedBtnLoad();
	void OnBnClickedGrab();
	void OnBnClickedStop();
	afx_msg void OnBnClickedSavejpeg();
	afx_msg void OnClickedActivequality();
	//afx_msg void OnClickedExit();
	afx_msg void OnClickedShowimg();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnCbnSelchangeCombocollectmode();
	afx_msg void OnCbnSelchangeComboconnectstatus();

	afx_msg void OnBnClickedButtoncollectfrequency();
	afx_msg void OnBnClickedButtonExposuretime();
	afx_msg void OnBnClickedButtonGain();
	afx_msg void OnCbnSelchangeComboExposuretime();
	afx_msg void OnCbnSelchangeComboGain();
	afx_msg void OnCbnSelchangeComboPreview();
};
