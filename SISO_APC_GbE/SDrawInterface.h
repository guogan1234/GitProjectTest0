// SDrawInterface.h: interface for the SDrawInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(SDRAWINTERFACE_H)
#define SDRAWINTERFACE_H
#include "FreeImage.h"
#include "SDrawDef.h"
#pragma comment(lib,"FreeImaged.lib")

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SDrawInterface{
public:
	SCtl	m_hSCtl;	//�ؼ��ṹ��
	CDC*	m_DrawDC;	//��ͼDC
//	SetBmpBK(char* path);	
//	void AddCtl(DWORD ID);
	int	 LoadCDBP(char* path,CDBP* pcdbp);			//���ļ�װ��ͼƬ
	void ReleaseCDBP(CDBP* pcdbp);
//	void DrawCDBP(CDBP scdbp,CDC* pdc,int x,int y);	//����ԭ�п�߻���ͼ��
	void SetDrawDC(CDC* pdc){m_DrawDC=pdc;};		//���û���DC
	void DrawCDBP(CDBP scdbp,CDC* pdc,int x,int y,int w,int h,bool tile);	//����ͼ��ָ������
	SDrawInterface();
	virtual ~SDrawInterface();

};

#endif // !defined(AFX_SDRAWINTERFACE_H__F3604E54_89D7_4548_B31D_D85C812262C5__INCLUDED_)
