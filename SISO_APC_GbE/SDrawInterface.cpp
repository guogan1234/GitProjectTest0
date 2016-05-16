// SDrawInterface.cpp: implementation of the SDrawInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "DrawPic.h"
#include "SDrawInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SDrawInterface::SDrawInterface()
{

}

SDrawInterface::~SDrawInterface()
{
	
}
void SDrawInterface::ReleaseCDBP(CDBP* pcdbp)
{
	if(pcdbp->bmp)delete pcdbp->bmp;
	if(pcdbp->dc)delete pcdbp->dc;
}
int SDrawInterface::LoadCDBP(char* path,CDBP* pcdbp)
{
	FREE_IMAGE_FORMAT m_fif = FreeImage_GetFileType(path);                           //获取Image类型 
	
	//如果没有文件签名，试着从文件扩展名判断文件类型
	if(m_fif == FIF_UNKNOWN)
		m_fif = FreeImage_GetFIFFromFilename(path); 
	
	//检查插件是否具有读取该格式的能力
	if((m_fif != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(m_fif))
	{ 		
		FIBITMAP *dib = FreeImage_Load(m_fif, path, 0);	
		if(dib){
			//创建兼容位图
			pcdbp->width=FreeImage_GetWidth(dib);
			pcdbp->height=FreeImage_GetHeight(dib);
			pcdbp->bmp=new CBitmap;
			pcdbp->dc=new CDC;
			pcdbp->bmp->DeleteObject();
			pcdbp->dc->DeleteDC();
			pcdbp->dc->CreateCompatibleDC(m_DrawDC);
			pcdbp->bmp->CreateCompatibleBitmap(m_DrawDC,pcdbp->width,pcdbp->height);
			pcdbp->dc->SelectObject(*pcdbp->bmp);

			//画图
			//设置指定设备环境中的位图拉伸模式
			pcdbp->dc->SetStretchBltMode(COLORONCOLOR);
			
			//绘制位图
			::StretchDIBits
				(
				pcdbp->dc->GetSafeHdc(), 
				0, 
				0, 
				pcdbp->width,
				pcdbp->height,
				0,
				0, 
				pcdbp->width,
				pcdbp->height,
				FreeImage_GetBits(dib), 
				FreeImage_GetInfo(dib), 
				DIB_RGB_COLORS, 
				SRCCOPY
			); 
			FreeImage_Unload(dib);
			return 0;
		}
		return -2; 
	}
	return -1;
}
/*void SDrawInterface::DrawCDBP(CDBP scdbp,CDC* pdc,int x,int y)

{
	pdc->SetStretchBltMode(COLORONCOLOR);
	pdc->StretchBlt(x,y,scdbp.width,scdbp.height
		,&scdbp.dc,0,0,scdbp.width,scdbp.height,SRCCOPY);
}*/
void SDrawInterface::DrawCDBP(CDBP scdbp,CDC* pdc,int x,int y,int w,int h,bool tile)
//绘制图像到指定区域
//CDBP	scdbp		原图
//CDC*	pdc			目标DC
//int	x,int y		绘制坐标
//int	w,int h		绘制大小
//bool	tile		是否平铺	
{
	pdc->SetStretchBltMode(COLORONCOLOR);
	if(tile)
	{
		pdc->StretchBlt(x,y,w,h,scdbp.dc,0,0,scdbp.width,scdbp.height,SRCCOPY);
	}else
	{
		int rx,ry,rw,rh;
		if(w/(float)h>scdbp.width/(float)scdbp.height)
		{
			rw=scdbp.width*h/scdbp.height;
			rh=h;
			rx=(w-rw)/2;
			ry=0;
		}else
		{
			rw=w;
			rh=scdbp.height*w/scdbp.width;
			rx=0;
			ry=(h-rh)/2;
		}
		pdc->StretchBlt(rx,ry,rw,rh,scdbp.dc,0,0,scdbp.width,scdbp.height,SRCCOPY);
	}

}
