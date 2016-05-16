#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <os_type.h>
#include "vasFgProject.h"

int main ()
{
	// ---------------------------------------------------------------------------
	// Frame Grabber: Initialization
	// ---------------------------------------------------------------------------

	int nrOfCycles = 5000; // Acquire 5000 frames, TODO: insert the number according to your needs
	unsigned int boardIndex = 0; // TODO: Use the correct board index at multi frame grabber systems
	int rc = 0; // return code

	Fg_Struct* fg = Fg_Init("BaseAreaGray8_MVCL.hap", boardIndex);
	if(fg == NULL){
		fprintf(stderr, "Error in Fg_Init(): %s\n", Fg_getLastErrorDescription(NULL));
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
		return -1;
	}

	int nrOfParameter = Fg_getNrOfParameter(fg);
	fprintf(stderr, "No. of Parameter: %d\n", nrOfParameter);

	int i;
	for (i = 0; i < nrOfParameter; i++) {
		const char *name = Fg_getParameterName(fg,i);
		fprintf(stderr," Param %d: %s,%x\n",i,name,Fg_getParameterId(fg,i));
	}


	// ---------------------------------------------------------------------------
	// Frame Grabber: Allocate memory for buffer(s)
	// ---------------------------------------------------------------------------

	// Feature Cnt 0,0 
	int width0 = 2560;
	int height0 = 2048;
	int byteWidth0 = 1;
	size_t bufSize0 = width0 * height0 * (size_t)byteWidth0;
	const unsigned int mem0_bufs = 4;
	dma_mem *pmem0 = Fg_AllocMemEx(fg, bufSize0 * mem0_bufs, mem0_bufs);
	if(pmem0 == NULL){
		fprintf(stderr, "Error in Fg_AllocMemEx(): %s\n", Fg_getLastErrorDescription(fg));
		Fg_FreeGrabber(fg);
		fg = NULL;
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
		return -1;
	}


	// ---------------------------------------------------------------------------
	// Frame Grabber: Get* and Set* parameters for Process0
	// ---------------------------------------------------------------------------

	/*============ ImageBuffer : Buffer ============== */ 
	int Device1_Process0_Buffer_XOffset_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Buffer_XOffset");
	if(Device1_Process0_Buffer_XOffset_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Buffer_XOffset): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Buffer_XOffset_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Buffer_XOffset;
	Device1_Process0_Buffer_XOffset = 0;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Buffer_XOffset_Id, Device1_Process0_Buffer_XOffset, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Buffer_XOffset_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Buffer_XLength_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Buffer_XLength");
	if(Device1_Process0_Buffer_XLength_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Buffer_XLength): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Buffer_XLength_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Buffer_XLength;
	Device1_Process0_Buffer_XLength = 2560;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Buffer_XLength_Id, Device1_Process0_Buffer_XLength, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Buffer_XLength_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Buffer_YOffset_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Buffer_YOffset");
	if(Device1_Process0_Buffer_YOffset_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Buffer_YOffset): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Buffer_YOffset_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Buffer_YOffset;
	Device1_Process0_Buffer_YOffset = 0;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Buffer_YOffset_Id, Device1_Process0_Buffer_YOffset, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Buffer_YOffset_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Buffer_YLength_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Buffer_YLength");
	if(Device1_Process0_Buffer_YLength_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Buffer_YLength): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Buffer_YLength_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Buffer_YLength;
	Device1_Process0_Buffer_YLength = 2048;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Buffer_YLength_Id, Device1_Process0_Buffer_YLength, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Buffer_YLength_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Buffer_FillLevel_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Buffer_FillLevel");
	if(Device1_Process0_Buffer_FillLevel_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Buffer_FillLevel): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Buffer_FillLevel_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	uint64_t Device1_Process0_Buffer_FillLevel = 0;
	rc = Fg_getParameterWithType(fg, Device1_Process0_Buffer_FillLevel_Id, &Device1_Process0_Buffer_FillLevel, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_Buffer_FillLevel_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_Buffer_FillLevel = %I64d\n", Device1_Process0_Buffer_FillLevel);
	}

	int Device1_Process0_Buffer_Overflow_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Buffer_Overflow");
	if(Device1_Process0_Buffer_Overflow_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Buffer_Overflow): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Buffer_Overflow_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	unsigned int Device1_Process0_Buffer_Overflow = 0;
	rc = Fg_getParameterWithType(fg, Device1_Process0_Buffer_Overflow_Id, &Device1_Process0_Buffer_Overflow, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_Buffer_Overflow_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_Buffer_Overflow = %d\n", Device1_Process0_Buffer_Overflow);
	}

	int Device1_Process0_Buffer_InfiniteSource_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Buffer_InfiniteSource");
	if(Device1_Process0_Buffer_InfiniteSource_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Buffer_InfiniteSource): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Buffer_InfiniteSource_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ DmaToPC : DMA ============== */ 
	int Device1_Process0_DMA_CurrentTransferLength_Id = Fg_getParameterIdByName(fg, "Device1_Process0_DMA_CurrentTransferLength");
	if(Device1_Process0_DMA_CurrentTransferLength_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_DMA_CurrentTransferLength): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_DMA_CurrentTransferLength_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	uint64_t Device1_Process0_DMA_CurrentTransferLength = 0;
	rc = Fg_getParameterWithType(fg, Device1_Process0_DMA_CurrentTransferLength_Id, &Device1_Process0_DMA_CurrentTransferLength, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_DMA_CurrentTransferLength_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_DMA_CurrentTransferLength = %I64d\n", Device1_Process0_DMA_CurrentTransferLength);
	}

	/*============ AppletProperties : AppletProperties ============== */ 
	int Device1_Process0_AppletProperties_VisualAppletsVersion_Id = Fg_getParameterIdByName(fg, "Device1_Process0_AppletProperties_VisualAppletsVersion");
	if(Device1_Process0_AppletProperties_VisualAppletsVersion_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_AppletProperties_VisualAppletsVersion): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_AppletProperties_VisualAppletsVersion_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	char Device1_Process0_AppletProperties_VisualAppletsVersion[6] = {'\0'}; //be careful: the length of the string parameter is determined dynamically by the current stored value plus 1
	rc = Fg_getParameterWithType(fg, Device1_Process0_AppletProperties_VisualAppletsVersion_Id, Device1_Process0_AppletProperties_VisualAppletsVersion, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_AppletProperties_VisualAppletsVersion_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_AppletProperties_VisualAppletsVersion = %s\n", Device1_Process0_AppletProperties_VisualAppletsVersion);
	}

	int Device1_Process0_AppletProperties_ProjectName_Id = Fg_getParameterIdByName(fg, "Device1_Process0_AppletProperties_ProjectName");
	if(Device1_Process0_AppletProperties_ProjectName_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_AppletProperties_ProjectName): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_AppletProperties_ProjectName_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	char Device1_Process0_AppletProperties_ProjectName[19] = {'\0'}; //be careful: the length of the string parameter is determined dynamically by the current stored value plus 1
	rc = Fg_getParameterWithType(fg, Device1_Process0_AppletProperties_ProjectName_Id, Device1_Process0_AppletProperties_ProjectName, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_AppletProperties_ProjectName_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_AppletProperties_ProjectName = %s\n", Device1_Process0_AppletProperties_ProjectName);
	}

	int Device1_Process0_AppletProperties_AppletVersion_Id = Fg_getParameterIdByName(fg, "Device1_Process0_AppletProperties_AppletVersion");
	if(Device1_Process0_AppletProperties_AppletVersion_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_AppletProperties_AppletVersion): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_AppletProperties_AppletVersion_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	char Device1_Process0_AppletProperties_AppletVersion[2] = {'\0'}; //be careful: the length of the string parameter is determined dynamically by the current stored value plus 1
	rc = Fg_getParameterWithType(fg, Device1_Process0_AppletProperties_AppletVersion_Id, Device1_Process0_AppletProperties_AppletVersion, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_AppletProperties_AppletVersion_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_AppletProperties_AppletVersion = %s\n", Device1_Process0_AppletProperties_AppletVersion);
	}

	int Device1_Process0_AppletProperties_AppletVendor_Id = Fg_getParameterIdByName(fg, "Device1_Process0_AppletProperties_AppletVendor");
	if(Device1_Process0_AppletProperties_AppletVendor_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_AppletProperties_AppletVendor): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_AppletProperties_AppletVendor_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	char Device1_Process0_AppletProperties_AppletVendor[4] = {'\0'}; //be careful: the length of the string parameter is determined dynamically by the current stored value plus 1
	rc = Fg_getParameterWithType(fg, Device1_Process0_AppletProperties_AppletVendor_Id, Device1_Process0_AppletProperties_AppletVendor, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_AppletProperties_AppletVendor_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_AppletProperties_AppletVendor = %s\n", Device1_Process0_AppletProperties_AppletVendor);
	}

	int Device1_Process0_AppletProperties_AppletAuthor_Id = Fg_getParameterIdByName(fg, "Device1_Process0_AppletProperties_AppletAuthor");
	if(Device1_Process0_AppletProperties_AppletAuthor_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_AppletProperties_AppletAuthor): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_AppletProperties_AppletAuthor_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	char Device1_Process0_AppletProperties_AppletAuthor[4] = {'\0'}; //be careful: the length of the string parameter is determined dynamically by the current stored value plus 1
	rc = Fg_getParameterWithType(fg, Device1_Process0_AppletProperties_AppletAuthor_Id, Device1_Process0_AppletProperties_AppletAuthor, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_AppletProperties_AppletAuthor_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_AppletProperties_AppletAuthor = %s\n", Device1_Process0_AppletProperties_AppletAuthor);
	}

	int Device1_Process0_AppletProperties_DesignClock_Id = Fg_getParameterIdByName(fg, "Device1_Process0_AppletProperties_DesignClock");
	if(Device1_Process0_AppletProperties_DesignClock_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_AppletProperties_DesignClock): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_AppletProperties_DesignClock_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	char Device1_Process0_AppletProperties_DesignClock[4] = {'\0'}; //be careful: the length of the string parameter is determined dynamically by the current stored value plus 1
	rc = Fg_getParameterWithType(fg, Device1_Process0_AppletProperties_DesignClock_Id, Device1_Process0_AppletProperties_DesignClock, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_AppletProperties_DesignClock_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_AppletProperties_DesignClock = %s\n", Device1_Process0_AppletProperties_DesignClock);
	}

	int Device1_Process0_AppletProperties_BuildTime_Id = Fg_getParameterIdByName(fg, "Device1_Process0_AppletProperties_BuildTime");
	if(Device1_Process0_AppletProperties_BuildTime_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_AppletProperties_BuildTime): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_AppletProperties_BuildTime_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	char Device1_Process0_AppletProperties_BuildTime[20] = {'\0'}; //be careful: the length of the string parameter is determined dynamically by the current stored value plus 1
	rc = Fg_getParameterWithType(fg, Device1_Process0_AppletProperties_BuildTime_Id, Device1_Process0_AppletProperties_BuildTime, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_AppletProperties_BuildTime_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_AppletProperties_BuildTime = %s\n", Device1_Process0_AppletProperties_BuildTime);
	}

	int Device1_Process0_AppletProperties_AppletUid_Id = Fg_getParameterIdByName(fg, "Device1_Process0_AppletProperties_AppletUid");
	if(Device1_Process0_AppletProperties_AppletUid_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_AppletProperties_AppletUid): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_AppletProperties_AppletUid_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	char Device1_Process0_AppletProperties_AppletUid[37] = {'\0'}; //be careful: the length of the string parameter is determined dynamically by the current stored value plus 1
	rc = Fg_getParameterWithType(fg, Device1_Process0_AppletProperties_AppletUid_Id, Device1_Process0_AppletProperties_AppletUid, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_AppletProperties_AppletUid_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_AppletProperties_AppletUid = %s\n", Device1_Process0_AppletProperties_AppletUid);
	}

	int Device1_Process0_AppletProperties_GpioType_Id = Fg_getParameterIdByName(fg, "Device1_Process0_AppletProperties_GpioType");
	if(Device1_Process0_AppletProperties_GpioType_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_AppletProperties_GpioType): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_AppletProperties_GpioType_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_AppletProperties_GpioType;
	Device1_Process0_AppletProperties_GpioType = AppletProperties::OpenDrain;
	rc = Fg_setParameterWithType(fg, Device1_Process0_AppletProperties_GpioType_Id, Device1_Process0_AppletProperties_GpioType, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_AppletProperties_GpioType_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ BoardStatus : BoardStatus ============== */ 
	int Device1_Process0_BoardStatus_FpgaDNA_Id = Fg_getParameterIdByName(fg, "Device1_Process0_BoardStatus_FpgaDNA");
	if(Device1_Process0_BoardStatus_FpgaDNA_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_BoardStatus_FpgaDNA): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_BoardStatus_FpgaDNA_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	uint64_t Device1_Process0_BoardStatus_FpgaDNA = 0;
	rc = Fg_getParameterWithType(fg, Device1_Process0_BoardStatus_FpgaDNA_Id, &Device1_Process0_BoardStatus_FpgaDNA, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_BoardStatus_FpgaDNA_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_BoardStatus_FpgaDNA = %I64d\n", Device1_Process0_BoardStatus_FpgaDNA);
	}

	int Device1_Process0_BoardStatus_FpgaTemperature_Id = Fg_getParameterIdByName(fg, "Device1_Process0_BoardStatus_FpgaTemperature");
	if(Device1_Process0_BoardStatus_FpgaTemperature_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_BoardStatus_FpgaTemperature): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_BoardStatus_FpgaTemperature_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	double Device1_Process0_BoardStatus_FpgaTemperature = .0;
	rc = Fg_getParameterWithType(fg, Device1_Process0_BoardStatus_FpgaTemperature_Id, &Device1_Process0_BoardStatus_FpgaTemperature, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_BoardStatus_FpgaTemperature_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_BoardStatus_FpgaTemperature = %f\n", Device1_Process0_BoardStatus_FpgaTemperature);
	}

	int Device1_Process0_BoardStatus_FpgaVccInt_Id = Fg_getParameterIdByName(fg, "Device1_Process0_BoardStatus_FpgaVccInt");
	if(Device1_Process0_BoardStatus_FpgaVccInt_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_BoardStatus_FpgaVccInt): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_BoardStatus_FpgaVccInt_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	double Device1_Process0_BoardStatus_FpgaVccInt = .0;
	rc = Fg_getParameterWithType(fg, Device1_Process0_BoardStatus_FpgaVccInt_Id, &Device1_Process0_BoardStatus_FpgaVccInt, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_BoardStatus_FpgaVccInt_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_BoardStatus_FpgaVccInt = %f\n", Device1_Process0_BoardStatus_FpgaVccInt);
	}

	int Device1_Process0_BoardStatus_FpgaVccAux_Id = Fg_getParameterIdByName(fg, "Device1_Process0_BoardStatus_FpgaVccAux");
	if(Device1_Process0_BoardStatus_FpgaVccAux_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_BoardStatus_FpgaVccAux): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_BoardStatus_FpgaVccAux_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	double Device1_Process0_BoardStatus_FpgaVccAux = .0;
	rc = Fg_getParameterWithType(fg, Device1_Process0_BoardStatus_FpgaVccAux_Id, &Device1_Process0_BoardStatus_FpgaVccAux, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_BoardStatus_FpgaVccAux_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_BoardStatus_FpgaVccAux = %f\n", Device1_Process0_BoardStatus_FpgaVccAux);
	}

	int Device1_Process0_BoardStatus_FpgaVccBram_Id = Fg_getParameterIdByName(fg, "Device1_Process0_BoardStatus_FpgaVccBram");
	if(Device1_Process0_BoardStatus_FpgaVccBram_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_BoardStatus_FpgaVccBram): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_BoardStatus_FpgaVccBram_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	double Device1_Process0_BoardStatus_FpgaVccBram = .0;
	rc = Fg_getParameterWithType(fg, Device1_Process0_BoardStatus_FpgaVccBram_Id, &Device1_Process0_BoardStatus_FpgaVccBram, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_BoardStatus_FpgaVccBram_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_BoardStatus_FpgaVccBram = %f\n", Device1_Process0_BoardStatus_FpgaVccBram);
	}

	int Device1_Process0_BoardStatus_PcieCurrentLinkWidth_Id = Fg_getParameterIdByName(fg, "Device1_Process0_BoardStatus_PcieCurrentLinkWidth");
	if(Device1_Process0_BoardStatus_PcieCurrentLinkWidth_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_BoardStatus_PcieCurrentLinkWidth): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_BoardStatus_PcieCurrentLinkWidth_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	unsigned int Device1_Process0_BoardStatus_PcieCurrentLinkWidth = 0;
	rc = Fg_getParameterWithType(fg, Device1_Process0_BoardStatus_PcieCurrentLinkWidth_Id, &Device1_Process0_BoardStatus_PcieCurrentLinkWidth, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_BoardStatus_PcieCurrentLinkWidth_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_BoardStatus_PcieCurrentLinkWidth = %d\n", Device1_Process0_BoardStatus_PcieCurrentLinkWidth);
	}

	int Device1_Process0_BoardStatus_PcieCurrentLinkSpeed_Id = Fg_getParameterIdByName(fg, "Device1_Process0_BoardStatus_PcieCurrentLinkSpeed");
	if(Device1_Process0_BoardStatus_PcieCurrentLinkSpeed_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_BoardStatus_PcieCurrentLinkSpeed): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_BoardStatus_PcieCurrentLinkSpeed_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	double Device1_Process0_BoardStatus_PcieCurrentLinkSpeed = .0;
	rc = Fg_getParameterWithType(fg, Device1_Process0_BoardStatus_PcieCurrentLinkSpeed_Id, &Device1_Process0_BoardStatus_PcieCurrentLinkSpeed, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_BoardStatus_PcieCurrentLinkSpeed_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_BoardStatus_PcieCurrentLinkSpeed = %f\n", Device1_Process0_BoardStatus_PcieCurrentLinkSpeed);
	}

	int Device1_Process0_BoardStatus_PcieLinkGen2Capable_Id = Fg_getParameterIdByName(fg, "Device1_Process0_BoardStatus_PcieLinkGen2Capable");
	if(Device1_Process0_BoardStatus_PcieLinkGen2Capable_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_BoardStatus_PcieLinkGen2Capable): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_BoardStatus_PcieLinkGen2Capable_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	unsigned int Device1_Process0_BoardStatus_PcieLinkGen2Capable = -1;
	rc = Fg_getParameterWithType(fg, Device1_Process0_BoardStatus_PcieLinkGen2Capable_Id, &Device1_Process0_BoardStatus_PcieLinkGen2Capable, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_BoardStatus_PcieLinkGen2Capable_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_BoardStatus_PcieLinkGen2Capable = %d\n", Device1_Process0_BoardStatus_PcieLinkGen2Capable);
	}

	int Device1_Process0_BoardStatus_PcieLinkPartnerGen2Capable_Id = Fg_getParameterIdByName(fg, "Device1_Process0_BoardStatus_PcieLinkPartnerGen2Capable");
	if(Device1_Process0_BoardStatus_PcieLinkPartnerGen2Capable_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_BoardStatus_PcieLinkPartnerGen2Capable): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_BoardStatus_PcieLinkPartnerGen2Capable_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	unsigned int Device1_Process0_BoardStatus_PcieLinkPartnerGen2Capable = -1;
	rc = Fg_getParameterWithType(fg, Device1_Process0_BoardStatus_PcieLinkPartnerGen2Capable_Id, &Device1_Process0_BoardStatus_PcieLinkPartnerGen2Capable, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_BoardStatus_PcieLinkPartnerGen2Capable_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_BoardStatus_PcieLinkPartnerGen2Capable = %d\n", Device1_Process0_BoardStatus_PcieLinkPartnerGen2Capable);
	}

	int Device1_Process0_BoardStatus_PcieTrainedPayloadSize_Id = Fg_getParameterIdByName(fg, "Device1_Process0_BoardStatus_PcieTrainedPayloadSize");
	if(Device1_Process0_BoardStatus_PcieTrainedPayloadSize_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_BoardStatus_PcieTrainedPayloadSize): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_BoardStatus_PcieTrainedPayloadSize_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	unsigned int Device1_Process0_BoardStatus_PcieTrainedPayloadSize = 0;
	rc = Fg_getParameterWithType(fg, Device1_Process0_BoardStatus_PcieTrainedPayloadSize_Id, &Device1_Process0_BoardStatus_PcieTrainedPayloadSize, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_BoardStatus_PcieTrainedPayloadSize_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_BoardStatus_PcieTrainedPayloadSize = %d\n", Device1_Process0_BoardStatus_PcieTrainedPayloadSize);
	}

	int Device1_Process0_BoardStatus_ExtensionConnectorPresent_Id = Fg_getParameterIdByName(fg, "Device1_Process0_BoardStatus_ExtensionConnectorPresent");
	if(Device1_Process0_BoardStatus_ExtensionConnectorPresent_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_BoardStatus_ExtensionConnectorPresent): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_BoardStatus_ExtensionConnectorPresent_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	unsigned int Device1_Process0_BoardStatus_ExtensionConnectorPresent = -1;
	rc = Fg_getParameterWithType(fg, Device1_Process0_BoardStatus_ExtensionConnectorPresent_Id, &Device1_Process0_BoardStatus_ExtensionConnectorPresent, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_BoardStatus_ExtensionConnectorPresent_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_BoardStatus_ExtensionConnectorPresent = %d\n", Device1_Process0_BoardStatus_ExtensionConnectorPresent);
	}

	int Device1_Process0_BoardStatus_PoCLStatePortA_Id = Fg_getParameterIdByName(fg, "Device1_Process0_BoardStatus_PoCLStatePortA");
	if(Device1_Process0_BoardStatus_PoCLStatePortA_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_BoardStatus_PoCLStatePortA): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_BoardStatus_PoCLStatePortA_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	unsigned int Device1_Process0_BoardStatus_PoCLStatePortA = -1;
	rc = Fg_getParameterWithType(fg, Device1_Process0_BoardStatus_PoCLStatePortA_Id, &Device1_Process0_BoardStatus_PoCLStatePortA, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_BoardStatus_PoCLStatePortA_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_BoardStatus_PoCLStatePortA = %d\n", Device1_Process0_BoardStatus_PoCLStatePortA);
	}

	int Device1_Process0_BoardStatus_PoCLStatePortB_Id = Fg_getParameterIdByName(fg, "Device1_Process0_BoardStatus_PoCLStatePortB");
	if(Device1_Process0_BoardStatus_PoCLStatePortB_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_BoardStatus_PoCLStatePortB): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_BoardStatus_PoCLStatePortB_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	unsigned int Device1_Process0_BoardStatus_PoCLStatePortB = -1;
	rc = Fg_getParameterWithType(fg, Device1_Process0_BoardStatus_PoCLStatePortB_Id, &Device1_Process0_BoardStatus_PoCLStatePortB, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_BoardStatus_PoCLStatePortB_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_BoardStatus_PoCLStatePortB = %d\n", Device1_Process0_BoardStatus_PoCLStatePortB);
	}

	/*============ BaseGrayCamera : Camera ============== */ 
	int Device1_Process0_Camera_DvalMode_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Camera_DvalMode");
	if(Device1_Process0_Camera_DvalMode_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Camera_DvalMode): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Camera_DvalMode_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Camera_DvalMode;
	Device1_Process0_Camera_DvalMode = BaseGrayCamera::DVAL_Enabled;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Camera_DvalMode_Id, Device1_Process0_Camera_DvalMode, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Camera_DvalMode_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Camera_BaseMode_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Camera_BaseMode");
	if(Device1_Process0_Camera_BaseMode_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Camera_BaseMode): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Camera_BaseMode_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Camera_BaseMode;
	Device1_Process0_Camera_BaseMode = BaseGrayCamera::Tap3x8bit;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Camera_BaseMode_Id, Device1_Process0_Camera_BaseMode, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Camera_BaseMode_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Camera_CameraStatus_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Camera_CameraStatus");
	if(Device1_Process0_Camera_CameraStatus_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Camera_CameraStatus): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Camera_CameraStatus_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	unsigned int Device1_Process0_Camera_CameraStatus = 0;
	rc = Fg_getParameterWithType(fg, Device1_Process0_Camera_CameraStatus_Id, &Device1_Process0_Camera_CameraStatus, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_Camera_CameraStatus_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_Camera_CameraStatus = %d\n", Device1_Process0_Camera_CameraStatus);
	}

	/*============ Polarity : Invert ============== */ 
	int Device1_Process0_Trigger_Invert_Invert_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_Invert_Invert");
	if(Device1_Process0_Trigger_Invert_Invert_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_Invert_Invert): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_Invert_Invert_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Trigger_Invert_Invert;
	Device1_Process0_Trigger_Invert_Invert = Polarity::Invert;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Trigger_Invert_Invert_Id, Device1_Process0_Trigger_Invert_Invert, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Trigger_Invert_Invert_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ Select : TriggerMode ============== */ 
	int Device1_Process0_Trigger_TriggerMode_Select_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_TriggerMode_Select");
	if(Device1_Process0_Trigger_TriggerMode_Select_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_TriggerMode_Select): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_TriggerMode_Select_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Trigger_TriggerMode_Select;
	Device1_Process0_Trigger_TriggerMode_Select = 1;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Trigger_TriggerMode_Select_Id, Device1_Process0_Trigger_TriggerMode_Select, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Trigger_TriggerMode_Select_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ SignalWidth : Width ============== */ 
	int Device1_Process0_Trigger_Width_WidthBits_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_Width_WidthBits");
	if(Device1_Process0_Trigger_Width_WidthBits_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_Width_WidthBits): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_Width_WidthBits_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Trigger_Width_Width_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_Width_Width");
	if(Device1_Process0_Trigger_Width_Width_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_Width_Width): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_Width_Width_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	uint64_t Device1_Process0_Trigger_Width_Width;
	Device1_Process0_Trigger_Width_Width = 0x186a;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Trigger_Width_Width_Id, Device1_Process0_Trigger_Width_Width, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Trigger_Width_Width_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ SetSignalStatus : SoftwareTrigger ============== */ 
	int Device1_Process0_Trigger_SoftwareTrigger_Mode_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_SoftwareTrigger_Mode");
	if(Device1_Process0_Trigger_SoftwareTrigger_Mode_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_SoftwareTrigger_Mode): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_SoftwareTrigger_Mode_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Trigger_SoftwareTrigger_Mode;
	Device1_Process0_Trigger_SoftwareTrigger_Mode = SetSignalStatus::Pulse;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Trigger_SoftwareTrigger_Mode_Id, Device1_Process0_Trigger_SoftwareTrigger_Mode, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Trigger_SoftwareTrigger_Mode_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ SignalDebounce : Debounce ============== */ 
	int Device1_Process0_Trigger_ExternalInput_Debounce_DebounceBits_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_ExternalInput_Debounce_DebounceBits");
	if(Device1_Process0_Trigger_ExternalInput_Debounce_DebounceBits_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_ExternalInput_Debounce_DebounceBits): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_ExternalInput_Debounce_DebounceBits_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Trigger_ExternalInput_Debounce_Debounce_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_ExternalInput_Debounce_Debounce");
	if(Device1_Process0_Trigger_ExternalInput_Debounce_Debounce_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_ExternalInput_Debounce_Debounce): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_ExternalInput_Debounce_Debounce_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Trigger_ExternalInput_Debounce_Debounce;
	Device1_Process0_Trigger_ExternalInput_Debounce_Debounce = 125;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Trigger_ExternalInput_Debounce_Debounce_Id, Device1_Process0_Trigger_ExternalInput_Debounce_Debounce, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Trigger_ExternalInput_Debounce_Debounce_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ Select : SelectInput ============== */ 
	int Device1_Process0_Trigger_ExternalInput_SelectInput_Select_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_ExternalInput_SelectInput_Select");
	if(Device1_Process0_Trigger_ExternalInput_SelectInput_Select_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_ExternalInput_SelectInput_Select): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_ExternalInput_SelectInput_Select_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Trigger_ExternalInput_SelectInput_Select;
	Device1_Process0_Trigger_ExternalInput_SelectInput_Select = 0;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Trigger_ExternalInput_SelectInput_Select_Id, Device1_Process0_Trigger_ExternalInput_SelectInput_Select, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Trigger_ExternalInput_SelectInput_Select_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ GPI : FrontGPI1 ============== */ 
	int Device1_Process0_Trigger_ExternalInput_FrontGPI1_Pin_ID_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_ExternalInput_FrontGPI1_Pin_ID");
	if(Device1_Process0_Trigger_ExternalInput_FrontGPI1_Pin_ID_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_ExternalInput_FrontGPI1_Pin_ID): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_ExternalInput_FrontGPI1_Pin_ID_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Trigger_ExternalInput_FrontGPI1_ConnectorType_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_ExternalInput_FrontGPI1_ConnectorType");
	if(Device1_Process0_Trigger_ExternalInput_FrontGPI1_ConnectorType_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_ExternalInput_FrontGPI1_ConnectorType): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_ExternalInput_FrontGPI1_ConnectorType_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ GPI : FrontGPI0 ============== */ 
	int Device1_Process0_Trigger_ExternalInput_FrontGPI0_Pin_ID_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_ExternalInput_FrontGPI0_Pin_ID");
	if(Device1_Process0_Trigger_ExternalInput_FrontGPI0_Pin_ID_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_ExternalInput_FrontGPI0_Pin_ID): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_ExternalInput_FrontGPI0_Pin_ID_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Trigger_ExternalInput_FrontGPI0_ConnectorType_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_ExternalInput_FrontGPI0_ConnectorType");
	if(Device1_Process0_Trigger_ExternalInput_FrontGPI0_ConnectorType_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_ExternalInput_FrontGPI0_ConnectorType): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_ExternalInput_FrontGPI0_ConnectorType_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ GPI : GPI1 ============== */ 
	int Device1_Process0_Trigger_ExternalInput_GPI1_Pin_ID_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_ExternalInput_GPI1_Pin_ID");
	if(Device1_Process0_Trigger_ExternalInput_GPI1_Pin_ID_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_ExternalInput_GPI1_Pin_ID): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_ExternalInput_GPI1_Pin_ID_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Trigger_ExternalInput_GPI1_ConnectorType_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_ExternalInput_GPI1_ConnectorType");
	if(Device1_Process0_Trigger_ExternalInput_GPI1_ConnectorType_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_ExternalInput_GPI1_ConnectorType): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_ExternalInput_GPI1_ConnectorType_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ GPI : GPI0 ============== */ 
	int Device1_Process0_Trigger_ExternalInput_GPI0_Pin_ID_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_ExternalInput_GPI0_Pin_ID");
	if(Device1_Process0_Trigger_ExternalInput_GPI0_Pin_ID_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_ExternalInput_GPI0_Pin_ID): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_ExternalInput_GPI0_Pin_ID_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Trigger_ExternalInput_GPI0_ConnectorType_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_ExternalInput_GPI0_ConnectorType");
	if(Device1_Process0_Trigger_ExternalInput_GPI0_ConnectorType_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_ExternalInput_GPI0_ConnectorType): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_ExternalInput_GPI0_ConnectorType_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ Generate : Period ============== */ 
	int Device1_Process0_Trigger_Generator_Period_PeriodBits_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_Generator_Period_PeriodBits");
	if(Device1_Process0_Trigger_Generator_Period_PeriodBits_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_Generator_Period_PeriodBits): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_Generator_Period_PeriodBits_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Trigger_Generator_Period_Period_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_Generator_Period_Period");
	if(Device1_Process0_Trigger_Generator_Period_Period_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_Generator_Period_Period): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_Generator_Period_Period_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	uint64_t Device1_Process0_Trigger_Generator_Period_Period;
	Device1_Process0_Trigger_Generator_Period_Period = 0x2faf08;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Trigger_Generator_Period_Period_Id, Device1_Process0_Trigger_Generator_Period_Period, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Trigger_Generator_Period_Period_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Trigger_Generator_Period_SequenceBits_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_Generator_Period_SequenceBits");
	if(Device1_Process0_Trigger_Generator_Period_SequenceBits_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_Generator_Period_SequenceBits): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_Generator_Period_SequenceBits_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Trigger_Generator_Period_Sequence_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_Generator_Period_Sequence");
	if(Device1_Process0_Trigger_Generator_Period_Sequence_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_Generator_Period_Sequence): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_Generator_Period_Sequence_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Trigger_Generator_Period_PulsePosition_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_Generator_Period_PulsePosition");
	if(Device1_Process0_Trigger_Generator_Period_PulsePosition_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_Generator_Period_PulsePosition): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_Generator_Period_PulsePosition_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ CameraControl : CamA ============== */ 
	/*============ GPO : GPO0 ============== */ 
	int Device1_Process0_Trigger_GPO0_Pin_ID_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_GPO0_Pin_ID");
	if(Device1_Process0_Trigger_GPO0_Pin_ID_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_GPO0_Pin_ID): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_GPO0_Pin_ID_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Trigger_GPO0_ConnectorType_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Trigger_GPO0_ConnectorType");
	if(Device1_Process0_Trigger_GPO0_ConnectorType_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Trigger_GPO0_ConnectorType): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Trigger_GPO0_ConnectorType_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */


	// ---------------------------------------------------------------------------
	// Frame Grabber: Create the display(s)
	// ---------------------------------------------------------------------------

	int id0 = CreateDisplay(8 * byteWidth0, width0, height0);
	if(id0 < 0) {
		fprintf(stderr, "Error in CreateDisplay(): %s (%d)\n", Fg_getLastErrorDescription(fg), id0);
		Fg_FreeMemEx(fg, pmem0);
		pmem0 = NULL;
		Fg_FreeGrabber(fg);
		fg = NULL;
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
		return id0;
	}
	SetBufferWidth(id0, width0, height0);


	// ---------------------------------------------------------------------------
	// Frame Grabber: Start acquisition at applet and camera for each present port
	// ---------------------------------------------------------------------------

	rc = Fg_AcquireEx(fg, 0, nrOfCycles, ACQ_STANDARD, pmem0);
	if(rc != 0) {
		fprintf(stderr, "Error in Fg_AcquireEx() for channel 0: %s\n", Fg_getErrorDescription(fg, rc));
		CloseDisplay(id0);
		Fg_FreeMemEx(fg, pmem0);
		pmem0 = NULL;
		Fg_FreeGrabber(fg);
		fg = NULL;
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
		return rc;
	}


	// ---------------------------------------------------------------------------
	// Frame Grabber: Grab images
	// ---------------------------------------------------------------------------

	frameindex_t frameNo0 = 0;
	for(i = 1; i <= nrOfCycles; ++i){
		frameNo0 = Fg_getLastPicNumberBlockingEx(fg, frameNo0 + 1, 0, 5, pmem0);
		if(frameNo0 < 0) {
			fprintf(stderr, "Error in Fg_getLastPicNumberBlockingEx(): %s (%d)\n", Fg_getLastErrorDescription(fg), frameNo0);
			fprintf(stderr, "Press any key to continue...\n");
			_getch();
			break;
		} else {
			fprintf(stderr, "grabbed image %d\n", frameNo0 );
		}

		void *iPtr0 = Fg_getImagePtrEx(fg, frameNo0, 0, pmem0);
		if(iPtr0 == NULL) {
			fprintf(stderr, "Error in Fg_getImagePtrEx(): %s\n", Fg_getLastErrorDescription(fg));
			Fg_stopAcquireEx(fg, 0, pmem0, 0);
			CloseDisplay(id0);
			Fg_FreeMemEx(fg, pmem0);
			pmem0 = NULL;
			Fg_FreeGrabber(fg);
			fg = NULL;
			fprintf(stderr, "Press any key to continue...\n");
			_getch();
			return -1;
		}
		DrawBuffer(id0, iPtr0, frameNo0, 0);
	}


	// ---------------------------------------------------------------------------
	// Frame Grabber: Stop acquisition
	// ---------------------------------------------------------------------------

	rc = Fg_stopAcquireEx(fg, 0, pmem0, 0);
	if(rc < 0) {
		fprintf(stderr, "Error in Fg_stopAcquireEx(): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}


	// ---------------------------------------------------------------------------
	// Frame Grabber: Close the display
	// ---------------------------------------------------------------------------

	CloseDisplay(id0);


	// ---------------------------------------------------------------------------
	// Frame Grabber: Release the memory for buffer(s)
	// ---------------------------------------------------------------------------

	rc = Fg_FreeMemEx(fg, pmem0);
	if(rc < 0) {
		fprintf(stderr, "Error in Fg_FreeMemEx(): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}
	pmem0 = NULL;


	// ---------------------------------------------------------------------------
	// Frame Grabber: Uninitialization
	// ---------------------------------------------------------------------------

	rc = Fg_FreeGrabber(fg);
	if(rc < 0) {
		fprintf(stderr, "Error in Fg_FreeGrabber(): %s\n", Fg_getLastErrorDescription(NULL));
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}
	fg = NULL;


	fprintf(stderr, "Press any key to exit...\n");
	_getch();

	return (0);
}
