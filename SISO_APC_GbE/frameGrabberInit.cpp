#include "stdafx.h"
#include "frameGrabberInit.h"
#include <stdlib.h>
#include <stdio.h>

int setBufferROI(Fg_Struct* fg, int xOffset, int xLength, int yOffset, int yLength)
{
	int retCode = 0;

	/*******For Gbe LineScan Camera********/
	/*============ ImageBuffer : ImageBuffer ============== */ 

	int Device1_Process0_ImageBuffer_XOffset_Id = Fg_getParameterIdByName(fg, "Device1_Process0_ImageBuffer_XOffset");
	unsigned int Device1_Process0_ImageBuffer_XOffset;
	Device1_Process0_ImageBuffer_XOffset = xOffset;
	retCode += Fg_setParameterWithType(fg, Device1_Process0_ImageBuffer_XOffset_Id, &Device1_Process0_ImageBuffer_XOffset, 0, FG_PARAM_TYPE_UINT32_T);

	int Device1_Process0_ImageBuffer_XLength_Id = Fg_getParameterIdByName(fg, "Device1_Process0_ImageBuffer_XLength");
	unsigned int Device1_Process0_ImageBuffer_XLength;
	Device1_Process0_ImageBuffer_XLength = xLength;
	retCode += Fg_setParameterWithType(fg, Device1_Process0_ImageBuffer_XLength_Id, &Device1_Process0_ImageBuffer_XLength, 0, FG_PARAM_TYPE_UINT32_T);

	int Device1_Process0_ImageBuffer_YOffset_Id = Fg_getParameterIdByName(fg, "Device1_Process0_ImageBuffer_YOffset");
	unsigned int Device1_Process0_ImageBuffer_YOffset;
	Device1_Process0_ImageBuffer_YOffset = yOffset;
	retCode += Fg_setParameterWithType(fg, Device1_Process0_ImageBuffer_YOffset_Id, &Device1_Process0_ImageBuffer_YOffset, 0, FG_PARAM_TYPE_UINT32_T);

	int Device1_Process0_ImageBuffer_YLength_Id = Fg_getParameterIdByName(fg, "Device1_Process0_ImageBuffer_YLength");
	unsigned int Device1_Process0_ImageBuffer_YLength;
	Device1_Process0_ImageBuffer_YLength = yLength;
	retCode += Fg_setParameterWithType(fg, Device1_Process0_ImageBuffer_YLength_Id, &Device1_Process0_ImageBuffer_YLength, 0, FG_PARAM_TYPE_UINT32_T);
	
	/*============ ImageBuffer_JPEG_Gray : JPEG_Buffer ============== */ 

	int Device1_Process0_JPEG_Buffer_XOffset_Id = Fg_getParameterIdByName(fg, "Device1_Process0_JPEG_Buffer_XOffset");
	unsigned int Device1_Process0_JPEG_Buffer_XOffset;
	Device1_Process0_JPEG_Buffer_XOffset = xOffset;
	retCode += Fg_setParameterWithType(fg, Device1_Process0_JPEG_Buffer_XOffset_Id, &Device1_Process0_JPEG_Buffer_XOffset, 0, FG_PARAM_TYPE_UINT32_T);

	int Device1_Process0_JPEG_Buffer_XLength_Id = Fg_getParameterIdByName(fg, "Device1_Process0_JPEG_Buffer_XLength");
	unsigned int Device1_Process0_JPEG_Buffer_XLength;
	Device1_Process0_JPEG_Buffer_XLength = xLength;
	retCode += Fg_setParameterWithType(fg, Device1_Process0_JPEG_Buffer_XLength_Id, &Device1_Process0_JPEG_Buffer_XLength, 0, FG_PARAM_TYPE_UINT32_T);

	int Device1_Process0_JPEG_Buffer_YOffset_Id = Fg_getParameterIdByName(fg, "Device1_Process0_JPEG_Buffer_YOffset");
	unsigned int Device1_Process0_JPEG_Buffer_YOffset;
	Device1_Process0_JPEG_Buffer_YOffset = yOffset;
	retCode += Fg_setParameterWithType(fg, Device1_Process0_JPEG_Buffer_YOffset_Id, &Device1_Process0_JPEG_Buffer_YOffset, 0, FG_PARAM_TYPE_UINT32_T);

	int Device1_Process0_JPEG_Buffer_YLength_Id = Fg_getParameterIdByName(fg, "Device1_Process0_JPEG_Buffer_YLength");
	unsigned int Device1_Process0_JPEG_Buffer_YLength;
	Device1_Process0_JPEG_Buffer_YLength = yLength;
	retCode += Fg_setParameterWithType(fg, Device1_Process0_JPEG_Buffer_YLength_Id, &Device1_Process0_JPEG_Buffer_YLength, 0, FG_PARAM_TYPE_UINT32_T);

	return retCode;
};

int setJPEGQuality(Fg_Struct* fg, int q)
{
	

		/*============ JPEG_Encoder_Gray : JPEG_Encoder ============== */ //  Marathron VCL Camera1
	
	int Device1_Process0_Encoder_quality_in_percent_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Encoder_quality_in_percent");
	int Device1_Process0_Encoder_quality_in_percent;
	Device1_Process0_Encoder_quality_in_percent = q;
    Fg_setParameterWithType(fg, Device1_Process0_Encoder_quality_in_percent_Id, Device1_Process0_Encoder_quality_in_percent, 0);
	
	/*============ JPEG_Encoder_Gray : JPEG_Encoder ============== */ // Marathron VCL  Camera2
	int Device1_Process1_Encoder_quality_in_percent_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Encoder_quality_in_percent");
    int Device1_Process1_Encoder_quality_in_percent;
	Device1_Process1_Encoder_quality_in_percent = q;
	return Fg_setParameterWithType(fg, Device1_Process1_Encoder_quality_in_percent_Id, Device1_Process1_Encoder_quality_in_percent, 0);
	

}



int configureCam(Fg_Struct* fg)
{
	/*============ CameraGrayAreaBase : Cam ============== */ 

	/*
	int Device1_Process0_Cam_UseDval_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Cam_UseDval");
	int Device1_Process0_Cam_UseDval;
	Device1_Process0_Cam_UseDval = CameraGrayAreaBase::DVAL_Enabled;
	retCode += Fg_setParameter(fg, Device1_Process0_Cam_UseDval_Id, &Device1_Process0_Cam_UseDval, 0);

	int Device1_Process0_Cam_Format_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Cam_Format");
	int Device1_Process0_Cam_Format;
	Device1_Process0_Cam_Format = CameraGrayAreaBase::SingleTap8Bit;
	retCode += Fg_setParameter(fg, Device1_Process0_Cam_Format_Id, &Device1_Process0_Cam_Format, 0);*/

	/*******Add For Gbe LineScan Camera********/

	/*============ CameraGrayArea : Camera ============== */ 
	int retCode = 0;
	int Device1_Process0_Camera_PixelFormat_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Camera_PixelFormat");
	unsigned int Device1_Process0_Camera_PixelFormat;
	Device1_Process0_Camera_PixelFormat = CameraGrayArea::MONO8;
	retCode += Fg_setParameterWithType(fg, Device1_Process0_Camera_PixelFormat_Id, &Device1_Process0_Camera_PixelFormat, 0, FG_PARAM_TYPE_UINT32_T);

	return retCode;
}
