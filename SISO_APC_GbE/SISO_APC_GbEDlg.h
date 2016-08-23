
// SISO_APC_GbEDlg.h : ͷ�ļ�
//

#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/regex.hpp>
#include <boost/log/common.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/utility/setup/from_stream.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

/********SISO******/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <vector>

#include <fgrab_struct.h>
#include <fgrab_prototyp.h>
#include <fgrab_define.h>
#include <SisoDisplay.h>
#include <gbe.h>
#include <afxwin.h>
#include <clser.h>

#include "jpeg/JPEGEncoder.h"

namespace prot = boost::property_tree;
namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace fs = boost::filesystem;

using namespace std; 

enum severity_level
{
	trace,
	debug,
	info,
	warning,
	error,
	critical
};

struct fg_apc_data {
	Fg_Struct *fg;
	unsigned int port;
	dma_mem *mem;
	unsigned iIndex;
	unsigned iDisplayId;
};
enum TY_STATUS {TY_ERROR =-1, TY_OK = 0};


// CSISO_APC_GbEDlg �Ի���
class CSISO_APC_GbEDlg : public CDialogEx
{
// ����
public:
	CSISO_APC_GbEDlg(CWnd* pParent = NULL);	// ��׼���캯��
	
	JPEGEncoder jpe[6];
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
	// APC  Data Struct
	Fg_Struct *fg, *fg1, *fg2;
	dma_mem *pMem0, *pMem1, *pMem2, *pMem3, *pMem4, *pMem5;
	
	vector<unsigned> DmaIndex;
	struct fg_apc_data apcdata, apcdata1, apcdata2, apcdata3, apcdata4, apcdata5;
	struct FgApcControl ctrl, ctrl1, ctrl2, ctrl3, ctrl4, ctrl5;
	
	int xOffset;
	int yOffset;
	vector<unsigned> width;
	vector<unsigned> height;
	
	vector<unsigned> ticks;
	vector<unsigned> m_iTickStart, m_iTickEnd;         //Ϊ�˼���ÿ100֡�ĺķ�ʱ�䡣

	HANDLE	hThShow;
	HANDLE m_PutEvent0, m_PutEvent1, m_PutEvent2, m_PutEvent3, m_PutEvent4, m_PutEvent5;
	HANDLE m_DrawEvent0, m_DrawEvent1, m_DrawEvent2, m_DrawEvent3, m_DrawEvent4, m_DrawEvent5;
	unsigned char *bufferJPEGfile0, *bufferJPEGfile1, *bufferJPEGfile2, *bufferJPEGfile3, *bufferJPEGfile4, *bufferJPEGfile5;
	int lengthJPEGfile0, lengthJPEGfile1, lengthJPEGfile2, lengthJPEGfile3, lengthJPEGfile4, lengthJPEGfile5;
	
	BITMAPINFO *m_pBmpInfo;	      ///< BITMAPINFO �ṹָ�룬��ʾͼ��ʱʹ��
	char       m_chBmpBuf[4096];  ///< BIMTAPINFO �洢��������m_pBmpInfo��ָ��˻�����
	int JPEGQuality;
	bool writeToFile;
	int		m_CpState;

	/***********QTable***********/
	unsigned char QTable[64], QTable1[64], QTable2[64], QTable3[64], QTable4[64], QTable5[64];
	unsigned char calcQuantizationMatrixFromPercent(int p_percent);
	int getQuantizationTable(Fg_Struct* fg, const char *cMatrix_ID, unsigned char (*Qtable)[64]); 
	void DealJPEG(LONG64 dmalenJPEG,void* iPtrJPEG,char* filename,int w,int h,bool bIsSave,bool bIsShow,int DrawItemID,void* pjpe);
	void DecodeImg(unsigned char* bufferJPEGfile,int lengthJPEGfile,int itemID,int w,int h);
	void DrawImage(int itemID,unsigned char* buf,int w,int h);
	/*********Cacluate Fps************/
	vector<double> fps;
	vector<uint64_t> oldStatusJPEG;
	vector<uint64_t> statusJPEG;
	
	char m_cDirPrefix[256]; //�洢·����ǰ׺��
	vector<int>   m_iCameraIndex;     //����ͷ����ʼ���кš�

	CButton M_SaveJpeg;
	
	CString M_JpegQuality;
	CStatic m_stc_fps, m_stc_fps1, m_stc_fps2, m_stc_fps3, m_stc_fps4, m_stc_fps5;
	
	//�ɼ�ģʽ�ı���
	enum COLLECT_MODE {MODE_TRIGGER, MODE_TIMER};

	enum PREVIEW_MODE {PREVIEW_OPEN, PREVIEW_CLOSE};
	COLLECT_MODE m_eCollectMode;
	CComboBox m_comboBoxCollectMode;

	//�ɼ�Ƶ��
	unsigned int m_iCollectFrequency;
	
	//����״̬�ı���
	CComboBox m_comboBoxConnectStatus;

	//����ع�ʱ��
	CComboBox m_comboBox_ExposureTime;

	//�������
	CComboBox m_comboBox_Gain;

	//ͼƬ��ʾģʽ������
	CComboBox m_comboBox_DisplayMode;
	CComboBox m_comboBox_CameraIndex;
	//Ԥ��
	vector<bool> m_bPreview;
	CButton m_buttonPreview;
	CComboBox m_comboBoxPreview;

	TY_STATUS SaveUserSet(unsigned iIndexCamera);
	//���½ӿ���Ҫ��ʵ��
	//5.�ɼ�ģʽ
	TY_STATUS SetCollectMode(COLLECT_MODE eMode);
	COLLECT_MODE GetCollectMode(){return m_eCollectMode;}

	//7.ͼ��ѹ����
	TY_STATUS SetJpegQuality(unsigned int iQuality);
	unsigned int GetJpegQuality(){return JPEGQuality;}
	//8.�ļ��洢·��
	TY_STATUS SetSaveDir(const char* cSaveDir);
	//9.Ԥ��
	TY_STATUS SetPreviewMode(unsigned int iIndexCamera, PREVIEW_MODE eMode);
	TY_STATUS GetPreviewMode(unsigned int iIndexCamera, PREVIEW_MODE &eMode);
	//a.��ʼ/�����ɼ�
	TY_STATUS BeginCollect();
	TY_STATUS StopCollect();
	//4.�������
	TY_STATUS GetGain(unsigned int iIndexCamera, unsigned int &iGain);
	TY_STATUS SetGain(unsigned int iIndexCamera, unsigned int iGain);
	//3.��������ٶ�
	TY_STATUS GetExposureTime(unsigned int iIndexCamera, unsigned int &iExposureTime);
	TY_STATUS SetExposureTime(unsigned int iIndexCamera, unsigned int iExposureTime);
	//6.�ɼ�Ƶ��
	unsigned int GetCollectFrequency(){return m_iCollectFrequency;}
	TY_STATUS SetCollectFrequency(unsigned int iCollectFrequency);
	//c.��ȡ����״̬
	TY_STATUS GetConnectStatus(unsigned iIndexCamera, bool &bConnect);
	//b.��ȡʵʱFPS
	double    GetFPS(unsigned iIndexCamera);
// �Ի�������
	enum { IDD = IDD_SISO_APC_GBE_DIALOG };

	CWinThread *m_pWinThread;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	TY_STATUS clSerialOperator(unsigned int iIndexCamera, char *line, char *cReturn);
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	afx_msg void OnCbnSelchangeComboDisplaymode0();
	afx_msg void OnBnClickedImgdisplay();

	TY_STATUS Y_Control_1(char* recvData, CSISO_APC_GbEDlg* dlg);
	TY_STATUS Y_Control_2(char* recvData, CSISO_APC_GbEDlg* dlg);
	TY_STATUS Y_Control_3(char* recvData, CSISO_APC_GbEDlg* dlg);
	TY_STATUS Y_Control_4(char* recvData, CSISO_APC_GbEDlg* dlg);
	TY_STATUS Y_Control_5(char* recvData, CSISO_APC_GbEDlg* dlg);
	TY_STATUS Y_Control_6(char* recvData, CSISO_APC_GbEDlg* dlg);
	TY_STATUS Y_Control_7(char* recvData, CSISO_APC_GbEDlg* dlg);
	TY_STATUS Y_Control_8(char* recvData, CSISO_APC_GbEDlg* dlg);
	TY_STATUS Y_Control_9(char* recvData, CSISO_APC_GbEDlg* dlg);
	TY_STATUS Y_Control_a(char* recvData, CSISO_APC_GbEDlg* dlg);
};

TY_STATUS praseRecvData(char* recvData, CSISO_APC_GbEDlg* dlg);
