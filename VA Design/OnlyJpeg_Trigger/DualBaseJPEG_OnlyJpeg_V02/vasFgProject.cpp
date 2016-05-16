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

	Fg_Struct* fg = Fg_Init("DualBaseJPEG_OnlyJpeg_V02.hap", boardIndex);
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
	int width0 = 1000;
	int height0 = 4000;
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

	// Feature Cnt 1,1 
	int width1 = 1000;
	int height1 = 4000;
	int byteWidth1 = 1;
	size_t bufSize1 = width1 * height1 * (size_t)byteWidth1;
	const unsigned int mem1_bufs = 4;
	dma_mem *pmem1 = Fg_AllocMemEx(fg, bufSize1 * mem1_bufs, mem1_bufs);
	if(pmem1 == NULL){
		fprintf(stderr, "Error in Fg_AllocMemEx(): %s\n", Fg_getLastErrorDescription(fg));
		Fg_FreeMemEx(fg, pmem0);
		pmem0 = NULL;
		Fg_FreeGrabber(fg);
		fg = NULL;
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
		return -1;
	}


	// ---------------------------------------------------------------------------
	// Frame Grabber: Get* and Set* parameters for Process0
	// ---------------------------------------------------------------------------

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

	char Device1_Process0_AppletProperties_ProjectName[26] = {'\0'}; //be careful: the length of the string parameter is determined dynamically by the current stored value plus 1
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

	char Device1_Process0_AppletProperties_AppletVersion[4] = {'\0'}; //be careful: the length of the string parameter is determined dynamically by the current stored value plus 1
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

	/*============ JPEG_Encoder_Gray : Encoder ============== */ 
	int Device1_Process0_Encoder_quality_in_percent_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Encoder_quality_in_percent");
	if(Device1_Process0_Encoder_quality_in_percent_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Encoder_quality_in_percent): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Encoder_quality_in_percent_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Encoder_quality_in_percent;
	Device1_Process0_Encoder_quality_in_percent = 50;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Encoder_quality_in_percent_Id, Device1_Process0_Encoder_quality_in_percent, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Encoder_quality_in_percent_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Encoder_quantization_matrix_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Encoder_quantization_matrix");
	if(Device1_Process0_Encoder_quantization_matrix_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Encoder_quantization_matrix): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Encoder_quantization_matrix_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	FieldParameterAccess Device1_Process0_Encoder_quantization_matrix;
	unsigned int Device1_Process0_Encoder_quantization_matrix_values[64] = { 0 };
	Device1_Process0_Encoder_quantization_matrix.vtype = FG_PARAM_TYPE_UINT32_T;
	Device1_Process0_Encoder_quantization_matrix.index = 0;
	Device1_Process0_Encoder_quantization_matrix.count = 64;
	Device1_Process0_Encoder_quantization_matrix.p_uint32_t = Device1_Process0_Encoder_quantization_matrix_values;
	rc = Fg_getParameterWithType(fg, Device1_Process0_Encoder_quantization_matrix_Id, &Device1_Process0_Encoder_quantization_matrix, 0, FG_PARAM_TYPE_STRUCT_FIELDPARAMACCESS);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_Encoder_quantization_matrix_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		for( int j = 0; j < 64; ++j ) {
			fprintf(stderr, "Device1_Process0_Encoder_quantization_matrix_values[%d] = %d\n", j, Device1_Process0_Encoder_quantization_matrix_values[j]);
		}
	}

	/*============ DmaToPC : DMA_JPEG ============== */ 
	int Device1_Process0_DMA_JPEG_CurrentTransferLength_Id = Fg_getParameterIdByName(fg, "Device1_Process0_DMA_JPEG_CurrentTransferLength");
	if(Device1_Process0_DMA_JPEG_CurrentTransferLength_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_DMA_JPEG_CurrentTransferLength): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_DMA_JPEG_CurrentTransferLength_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	uint64_t Device1_Process0_DMA_JPEG_CurrentTransferLength = 0;
	rc = Fg_getParameterWithType(fg, Device1_Process0_DMA_JPEG_CurrentTransferLength_Id, &Device1_Process0_DMA_JPEG_CurrentTransferLength, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process0_DMA_JPEG_CurrentTransferLength_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process0_DMA_JPEG_CurrentTransferLength = %I64d\n", Device1_Process0_DMA_JPEG_CurrentTransferLength);
	}

	/*============ AppendLine : Append8 ============== */ 
	int Device1_Process0_Sorter_Append8_AppendNumber_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Sorter_Append8_AppendNumber");
	if(Device1_Process0_Sorter_Append8_AppendNumber_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Sorter_Append8_AppendNumber): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Sorter_Append8_AppendNumber_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Sorter_Append8_AppendNumber;
	Device1_Process0_Sorter_Append8_AppendNumber = 8;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Sorter_Append8_AppendNumber_Id, Device1_Process0_Sorter_Append8_AppendNumber, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Sorter_Append8_AppendNumber_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ LineMemory : module21 ============== */ 
	int Device1_Process0_Sorter_module21_Implementation_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Sorter_module21_Implementation");
	if(Device1_Process0_Sorter_module21_Implementation_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Sorter_module21_Implementation): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Sorter_module21_Implementation_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Sorter_module21_FrameWidth_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Sorter_module21_FrameWidth");
	if(Device1_Process0_Sorter_module21_FrameWidth_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Sorter_module21_FrameWidth): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Sorter_module21_FrameWidth_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Sorter_module21_XOffset_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Sorter_module21_XOffset");
	if(Device1_Process0_Sorter_module21_XOffset_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Sorter_module21_XOffset): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Sorter_module21_XOffset_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Sorter_module21_XOffset;
	Device1_Process0_Sorter_module21_XOffset = 0;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Sorter_module21_XOffset_Id, Device1_Process0_Sorter_module21_XOffset, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Sorter_module21_XOffset_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Sorter_module21_XLength_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Sorter_module21_XLength");
	if(Device1_Process0_Sorter_module21_XLength_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Sorter_module21_XLength): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Sorter_module21_XLength_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Sorter_module21_XLength;
	Device1_Process0_Sorter_module21_XLength = 2560;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Sorter_module21_XLength_Id, Device1_Process0_Sorter_module21_XLength, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Sorter_module21_XLength_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ SplitLine : Width ============== */ 
	int Device1_Process0_Sorter_Width_LineLength_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Sorter_Width_LineLength");
	if(Device1_Process0_Sorter_Width_LineLength_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Sorter_Width_LineLength): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Sorter_Width_LineLength_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Sorter_Width_LineLength;
	Device1_Process0_Sorter_Width_LineLength = 2560;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Sorter_Width_LineLength_Id, Device1_Process0_Sorter_Width_LineLength, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Sorter_Width_LineLength_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ CONST : Write ============== */ 
	int Device1_Process0_Sorter_Write_Value_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Sorter_Write_Value");
	if(Device1_Process0_Sorter_Write_Value_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Sorter_Write_Value): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Sorter_Write_Value_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ SCALE : By8 ============== */ 
	int Device1_Process0_Sorter_AddrGen_By8_ScaleFactorMaxBits_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Sorter_AddrGen_By8_ScaleFactorMaxBits");
	if(Device1_Process0_Sorter_AddrGen_By8_ScaleFactorMaxBits_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Sorter_AddrGen_By8_ScaleFactorMaxBits): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Sorter_AddrGen_By8_ScaleFactorMaxBits_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Sorter_AddrGen_By8_ScaleFactor_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Sorter_AddrGen_By8_ScaleFactor");
	if(Device1_Process0_Sorter_AddrGen_By8_ScaleFactor_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Sorter_AddrGen_By8_ScaleFactor): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Sorter_AddrGen_By8_ScaleFactor_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ ModuloCount : Modx ============== */ 
	int Device1_Process0_Sorter_AddrGen_Modx_Divisor_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Sorter_AddrGen_Modx_Divisor");
	if(Device1_Process0_Sorter_AddrGen_Modx_Divisor_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Sorter_AddrGen_Modx_Divisor): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Sorter_AddrGen_Modx_Divisor_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Sorter_AddrGen_Modx_Divisor;
	Device1_Process0_Sorter_AddrGen_Modx_Divisor = 320;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Sorter_AddrGen_Modx_Divisor_Id, Device1_Process0_Sorter_AddrGen_Modx_Divisor, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Sorter_AddrGen_Modx_Divisor_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Sorter_AddrGen_Modx_CountEntity_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Sorter_AddrGen_Modx_CountEntity");
	if(Device1_Process0_Sorter_AddrGen_Modx_CountEntity_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Sorter_AddrGen_Modx_CountEntity): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Sorter_AddrGen_Modx_CountEntity_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Sorter_AddrGen_Modx_AutoClear_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Sorter_AddrGen_Modx_AutoClear");
	if(Device1_Process0_Sorter_AddrGen_Modx_AutoClear_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Sorter_AddrGen_Modx_AutoClear): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Sorter_AddrGen_Modx_AutoClear_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ CONST : 320 ============== */ 
	int Device1_Process0_Sorter_AddrGen_320_Value_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Sorter_AddrGen_320_Value");
	if(Device1_Process0_Sorter_AddrGen_320_Value_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Sorter_AddrGen_320_Value): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Sorter_AddrGen_320_Value_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Sorter_AddrGen_320_Value;
	Device1_Process0_Sorter_AddrGen_320_Value = 320;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Sorter_AddrGen_320_Value_Id, Device1_Process0_Sorter_AddrGen_320_Value, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Sorter_AddrGen_320_Value_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ ImageBufferMultiRoI : Buffer ============== */ 
	int Device1_Process0_Buffer_Mode_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Buffer_Mode");
	if(Device1_Process0_Buffer_Mode_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Buffer_Mode): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Buffer_Mode_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Buffer_MaxNumRoI_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Buffer_MaxNumRoI");
	if(Device1_Process0_Buffer_MaxNumRoI_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Buffer_MaxNumRoI): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Buffer_MaxNumRoI_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Buffer_NumRoI_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Buffer_NumRoI");
	if(Device1_Process0_Buffer_NumRoI_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Buffer_NumRoI): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Buffer_NumRoI_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Buffer_NumRoI;
	Device1_Process0_Buffer_NumRoI = 1;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Buffer_NumRoI_Id, Device1_Process0_Buffer_NumRoI, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Buffer_NumRoI_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Buffer_XOffset_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Buffer_XOffset");
	if(Device1_Process0_Buffer_XOffset_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Buffer_XOffset): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Buffer_XOffset_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	FieldParameterAccess Device1_Process0_Buffer_XOffset;
	unsigned int Device1_Process0_Buffer_XOffset_defaults[] = { 0 };
	Device1_Process0_Buffer_XOffset.vtype = FG_PARAM_TYPE_UINT32_T;
	Device1_Process0_Buffer_XOffset.index = 0;
	Device1_Process0_Buffer_XOffset.count = 1;
	Device1_Process0_Buffer_XOffset.p_uint32_t = Device1_Process0_Buffer_XOffset_defaults;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Buffer_XOffset_Id, &Device1_Process0_Buffer_XOffset, 0, FG_PARAM_TYPE_STRUCT_FIELDPARAMACCESS);
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

	FieldParameterAccess Device1_Process0_Buffer_XLength;
	unsigned int Device1_Process0_Buffer_XLength_defaults[] = { 2560 };
	Device1_Process0_Buffer_XLength.vtype = FG_PARAM_TYPE_UINT32_T;
	Device1_Process0_Buffer_XLength.index = 0;
	Device1_Process0_Buffer_XLength.count = 1;
	Device1_Process0_Buffer_XLength.p_uint32_t = Device1_Process0_Buffer_XLength_defaults;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Buffer_XLength_Id, &Device1_Process0_Buffer_XLength, 0, FG_PARAM_TYPE_STRUCT_FIELDPARAMACCESS);
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

	FieldParameterAccess Device1_Process0_Buffer_YOffset;
	unsigned int Device1_Process0_Buffer_YOffset_defaults[] = { 0 };
	Device1_Process0_Buffer_YOffset.vtype = FG_PARAM_TYPE_UINT32_T;
	Device1_Process0_Buffer_YOffset.index = 0;
	Device1_Process0_Buffer_YOffset.count = 1;
	Device1_Process0_Buffer_YOffset.p_uint32_t = Device1_Process0_Buffer_YOffset_defaults;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Buffer_YOffset_Id, &Device1_Process0_Buffer_YOffset, 0, FG_PARAM_TYPE_STRUCT_FIELDPARAMACCESS);
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

	FieldParameterAccess Device1_Process0_Buffer_YLength;
	unsigned int Device1_Process0_Buffer_YLength_defaults[] = { 2048 };
	Device1_Process0_Buffer_YLength.vtype = FG_PARAM_TYPE_UINT32_T;
	Device1_Process0_Buffer_YLength.index = 0;
	Device1_Process0_Buffer_YLength.count = 1;
	Device1_Process0_Buffer_YLength.p_uint32_t = Device1_Process0_Buffer_YLength_defaults;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Buffer_YLength_Id, &Device1_Process0_Buffer_YLength, 0, FG_PARAM_TYPE_STRUCT_FIELDPARAMACCESS);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Buffer_YLength_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Buffer_Unlock_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Buffer_Unlock");
	if(Device1_Process0_Buffer_Unlock_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Buffer_Unlock): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Buffer_Unlock_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Buffer_Unlock;
	Device1_Process0_Buffer_Unlock = 1;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Buffer_Unlock_Id, Device1_Process0_Buffer_Unlock, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Buffer_Unlock_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Buffer_InfiniteSource_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Buffer_InfiniteSource");
	if(Device1_Process0_Buffer_InfiniteSource_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Buffer_InfiniteSource): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Buffer_InfiniteSource_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

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

	/*============ SourceSelector : EnableSimulator ============== */ 
	int Device1_Process0_EnableSimulator_SelectSource_Id = Fg_getParameterIdByName(fg, "Device1_Process0_EnableSimulator_SelectSource");
	if(Device1_Process0_EnableSimulator_SelectSource_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_EnableSimulator_SelectSource): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_EnableSimulator_SelectSource_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_EnableSimulator_SelectSource;
	Device1_Process0_EnableSimulator_SelectSource = 1;
	rc = Fg_setParameterWithType(fg, Device1_Process0_EnableSimulator_SelectSource_Id, Device1_Process0_EnableSimulator_SelectSource, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_EnableSimulator_SelectSource_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_EnableSimulator_InfiniteSource_Id = Fg_getParameterIdByName(fg, "Device1_Process0_EnableSimulator_InfiniteSource");
	if(Device1_Process0_EnableSimulator_InfiniteSource_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_EnableSimulator_InfiniteSource): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_EnableSimulator_InfiniteSource_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ CreateBlankImage : Size ============== */ 
	int Device1_Process0_Simulator_Size_ImageWidth_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_Size_ImageWidth");
	if(Device1_Process0_Simulator_Size_ImageWidth_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_Size_ImageWidth): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_Size_ImageWidth_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Simulator_Size_ImageWidth;
	Device1_Process0_Simulator_Size_ImageWidth = 2560;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Simulator_Size_ImageWidth_Id, Device1_Process0_Simulator_Size_ImageWidth, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Simulator_Size_ImageWidth_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Simulator_Size_ImageHeight_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_Size_ImageHeight");
	if(Device1_Process0_Simulator_Size_ImageHeight_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_Size_ImageHeight): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_Size_ImageHeight_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Simulator_Size_ImageHeight;
	Device1_Process0_Simulator_Size_ImageHeight = 2048;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Simulator_Size_ImageHeight_Id, Device1_Process0_Simulator_Size_ImageHeight, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Simulator_Size_ImageHeight_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ ModuloCount : module61 ============== */ 
	int Device1_Process0_Simulator_module61_Divisor_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_module61_Divisor");
	if(Device1_Process0_Simulator_module61_Divisor_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_module61_Divisor): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_module61_Divisor_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Simulator_module61_Divisor;
	Device1_Process0_Simulator_module61_Divisor = 256;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Simulator_module61_Divisor_Id, Device1_Process0_Simulator_module61_Divisor, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Simulator_module61_Divisor_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Simulator_module61_CountEntity_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_module61_CountEntity");
	if(Device1_Process0_Simulator_module61_CountEntity_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_module61_CountEntity): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_module61_CountEntity_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Simulator_module61_AutoClear_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_module61_AutoClear");
	if(Device1_Process0_Simulator_module61_AutoClear_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_module61_AutoClear): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_module61_AutoClear_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ ModuloCount : module62 ============== */ 
	int Device1_Process0_Simulator_module62_Divisor_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_module62_Divisor");
	if(Device1_Process0_Simulator_module62_Divisor_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_module62_Divisor): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_module62_Divisor_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Simulator_module62_Divisor;
	Device1_Process0_Simulator_module62_Divisor = 256;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Simulator_module62_Divisor_Id, Device1_Process0_Simulator_module62_Divisor, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Simulator_module62_Divisor_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Simulator_module62_CountEntity_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_module62_CountEntity");
	if(Device1_Process0_Simulator_module62_CountEntity_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_module62_CountEntity): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_module62_CountEntity_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Simulator_module62_AutoClear_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_module62_AutoClear");
	if(Device1_Process0_Simulator_module62_AutoClear_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_module62_AutoClear): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_module62_AutoClear_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ ModuloCount : module63 ============== */ 
	int Device1_Process0_Simulator_module63_Divisor_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_module63_Divisor");
	if(Device1_Process0_Simulator_module63_Divisor_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_module63_Divisor): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_module63_Divisor_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Simulator_module63_Divisor;
	Device1_Process0_Simulator_module63_Divisor = 256;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Simulator_module63_Divisor_Id, Device1_Process0_Simulator_module63_Divisor, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Simulator_module63_Divisor_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Simulator_module63_CountEntity_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_module63_CountEntity");
	if(Device1_Process0_Simulator_module63_CountEntity_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_module63_CountEntity): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_module63_CountEntity_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Simulator_module63_AutoClear_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_module63_AutoClear");
	if(Device1_Process0_Simulator_module63_AutoClear_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_module63_AutoClear): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_module63_AutoClear_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ ImageValve : Valve ============== */ 
	int Device1_Process0_Simulator_Valve_Mode_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_Valve_Mode");
	if(Device1_Process0_Simulator_Valve_Mode_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_Valve_Mode): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_Valve_Mode_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Simulator_Valve_Mode;
	Device1_Process0_Simulator_Valve_Mode = ImageValve::LINE;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Simulator_Valve_Mode_Id, Device1_Process0_Simulator_Valve_Mode, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Simulator_Valve_Mode_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Simulator_Valve_SequenceLengthBits_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_Valve_SequenceLengthBits");
	if(Device1_Process0_Simulator_Valve_SequenceLengthBits_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_Valve_SequenceLengthBits): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_Valve_SequenceLengthBits_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Simulator_Valve_SequenceLength_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_Valve_SequenceLength");
	if(Device1_Process0_Simulator_Valve_SequenceLength_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_Valve_SequenceLength): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_Valve_SequenceLength_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Simulator_Valve_SequenceLength;
	Device1_Process0_Simulator_Valve_SequenceLength = 1;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Simulator_Valve_SequenceLength_Id, Device1_Process0_Simulator_Valve_SequenceLength, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Simulator_Valve_SequenceLength_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ Generate : LinePeriod ============== */ 
	int Device1_Process0_Simulator_LinePeriod_PeriodBits_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_LinePeriod_PeriodBits");
	if(Device1_Process0_Simulator_LinePeriod_PeriodBits_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_LinePeriod_PeriodBits): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_LinePeriod_PeriodBits_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Simulator_LinePeriod_Period_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_LinePeriod_Period");
	if(Device1_Process0_Simulator_LinePeriod_Period_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_LinePeriod_Period): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_LinePeriod_Period_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Simulator_LinePeriod_Period;
	Device1_Process0_Simulator_LinePeriod_Period = 1356;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Simulator_LinePeriod_Period_Id, Device1_Process0_Simulator_LinePeriod_Period, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Simulator_LinePeriod_Period_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Simulator_LinePeriod_SequenceBits_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_LinePeriod_SequenceBits");
	if(Device1_Process0_Simulator_LinePeriod_SequenceBits_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_LinePeriod_SequenceBits): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_LinePeriod_SequenceBits_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process0_Simulator_LinePeriod_Sequence_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_LinePeriod_Sequence");
	if(Device1_Process0_Simulator_LinePeriod_Sequence_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_LinePeriod_Sequence): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_LinePeriod_Sequence_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Simulator_LinePeriod_Sequence;
	Device1_Process0_Simulator_LinePeriod_Sequence = 0;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Simulator_LinePeriod_Sequence_Id, Device1_Process0_Simulator_LinePeriod_Sequence, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Simulator_LinePeriod_Sequence_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process0_Simulator_LinePeriod_PulsePosition_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_LinePeriod_PulsePosition");
	if(Device1_Process0_Simulator_LinePeriod_PulsePosition_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_LinePeriod_PulsePosition): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_LinePeriod_PulsePosition_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ Select : EnableGenerate ============== */ 
	int Device1_Process0_Simulator_EnableGenerate_Select_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_EnableGenerate_Select");
	if(Device1_Process0_Simulator_EnableGenerate_Select_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_EnableGenerate_Select): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_EnableGenerate_Select_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Simulator_EnableGenerate_Select;
	Device1_Process0_Simulator_EnableGenerate_Select = 0;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Simulator_EnableGenerate_Select_Id, Device1_Process0_Simulator_EnableGenerate_Select, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Simulator_EnableGenerate_Select_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ SetSignalStatus : OpenValve ============== */ 
	int Device1_Process0_Simulator_OpenValve_Mode_Id = Fg_getParameterIdByName(fg, "Device1_Process0_Simulator_OpenValve_Mode");
	if(Device1_Process0_Simulator_OpenValve_Mode_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process0_Simulator_OpenValve_Mode): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process0_Simulator_OpenValve_Mode_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process0_Simulator_OpenValve_Mode;
	Device1_Process0_Simulator_OpenValve_Mode = SetSignalStatus::High;
	rc = Fg_setParameterWithType(fg, Device1_Process0_Simulator_OpenValve_Mode_Id, Device1_Process0_Simulator_OpenValve_Mode, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process0_Simulator_OpenValve_Mode_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
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
	// Frame Grabber: Get* and Set* parameters for Process1
	// ---------------------------------------------------------------------------

	/*============ BaseGrayCamera : Camera ============== */ 
	int Device1_Process1_Camera_DvalMode_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Camera_DvalMode");
	if(Device1_Process1_Camera_DvalMode_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Camera_DvalMode): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Camera_DvalMode_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Camera_DvalMode;
	Device1_Process1_Camera_DvalMode = BaseGrayCamera::DVAL_Enabled;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Camera_DvalMode_Id, Device1_Process1_Camera_DvalMode, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Camera_DvalMode_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Camera_BaseMode_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Camera_BaseMode");
	if(Device1_Process1_Camera_BaseMode_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Camera_BaseMode): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Camera_BaseMode_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Camera_BaseMode;
	Device1_Process1_Camera_BaseMode = BaseGrayCamera::Tap3x8bit;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Camera_BaseMode_Id, Device1_Process1_Camera_BaseMode, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Camera_BaseMode_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Camera_CameraStatus_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Camera_CameraStatus");
	if(Device1_Process1_Camera_CameraStatus_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Camera_CameraStatus): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Camera_CameraStatus_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	unsigned int Device1_Process1_Camera_CameraStatus = 0;
	rc = Fg_getParameterWithType(fg, Device1_Process1_Camera_CameraStatus_Id, &Device1_Process1_Camera_CameraStatus, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process1_Camera_CameraStatus_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process1_Camera_CameraStatus = %d\n", Device1_Process1_Camera_CameraStatus);
	}

	/*============ CreateBlankImage : Size ============== */ 
	int Device1_Process1_Simulator_Size_ImageWidth_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_Size_ImageWidth");
	if(Device1_Process1_Simulator_Size_ImageWidth_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_Size_ImageWidth): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_Size_ImageWidth_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Simulator_Size_ImageWidth;
	Device1_Process1_Simulator_Size_ImageWidth = 2560;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Simulator_Size_ImageWidth_Id, Device1_Process1_Simulator_Size_ImageWidth, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Simulator_Size_ImageWidth_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Simulator_Size_ImageHeight_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_Size_ImageHeight");
	if(Device1_Process1_Simulator_Size_ImageHeight_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_Size_ImageHeight): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_Size_ImageHeight_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Simulator_Size_ImageHeight;
	Device1_Process1_Simulator_Size_ImageHeight = 2048;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Simulator_Size_ImageHeight_Id, Device1_Process1_Simulator_Size_ImageHeight, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Simulator_Size_ImageHeight_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ ModuloCount : module61 ============== */ 
	int Device1_Process1_Simulator_module61_Divisor_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_module61_Divisor");
	if(Device1_Process1_Simulator_module61_Divisor_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_module61_Divisor): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_module61_Divisor_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Simulator_module61_Divisor;
	Device1_Process1_Simulator_module61_Divisor = 256;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Simulator_module61_Divisor_Id, Device1_Process1_Simulator_module61_Divisor, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Simulator_module61_Divisor_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Simulator_module61_CountEntity_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_module61_CountEntity");
	if(Device1_Process1_Simulator_module61_CountEntity_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_module61_CountEntity): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_module61_CountEntity_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Simulator_module61_AutoClear_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_module61_AutoClear");
	if(Device1_Process1_Simulator_module61_AutoClear_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_module61_AutoClear): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_module61_AutoClear_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ ModuloCount : module62 ============== */ 
	int Device1_Process1_Simulator_module62_Divisor_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_module62_Divisor");
	if(Device1_Process1_Simulator_module62_Divisor_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_module62_Divisor): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_module62_Divisor_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Simulator_module62_Divisor;
	Device1_Process1_Simulator_module62_Divisor = 256;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Simulator_module62_Divisor_Id, Device1_Process1_Simulator_module62_Divisor, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Simulator_module62_Divisor_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Simulator_module62_CountEntity_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_module62_CountEntity");
	if(Device1_Process1_Simulator_module62_CountEntity_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_module62_CountEntity): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_module62_CountEntity_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Simulator_module62_AutoClear_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_module62_AutoClear");
	if(Device1_Process1_Simulator_module62_AutoClear_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_module62_AutoClear): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_module62_AutoClear_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ ModuloCount : module63 ============== */ 
	int Device1_Process1_Simulator_module63_Divisor_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_module63_Divisor");
	if(Device1_Process1_Simulator_module63_Divisor_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_module63_Divisor): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_module63_Divisor_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Simulator_module63_Divisor;
	Device1_Process1_Simulator_module63_Divisor = 256;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Simulator_module63_Divisor_Id, Device1_Process1_Simulator_module63_Divisor, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Simulator_module63_Divisor_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Simulator_module63_CountEntity_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_module63_CountEntity");
	if(Device1_Process1_Simulator_module63_CountEntity_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_module63_CountEntity): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_module63_CountEntity_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Simulator_module63_AutoClear_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_module63_AutoClear");
	if(Device1_Process1_Simulator_module63_AutoClear_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_module63_AutoClear): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_module63_AutoClear_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ ImageValve : Valve ============== */ 
	int Device1_Process1_Simulator_Valve_Mode_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_Valve_Mode");
	if(Device1_Process1_Simulator_Valve_Mode_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_Valve_Mode): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_Valve_Mode_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Simulator_Valve_Mode;
	Device1_Process1_Simulator_Valve_Mode = ImageValve::LINE;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Simulator_Valve_Mode_Id, Device1_Process1_Simulator_Valve_Mode, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Simulator_Valve_Mode_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Simulator_Valve_SequenceLengthBits_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_Valve_SequenceLengthBits");
	if(Device1_Process1_Simulator_Valve_SequenceLengthBits_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_Valve_SequenceLengthBits): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_Valve_SequenceLengthBits_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Simulator_Valve_SequenceLength_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_Valve_SequenceLength");
	if(Device1_Process1_Simulator_Valve_SequenceLength_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_Valve_SequenceLength): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_Valve_SequenceLength_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Simulator_Valve_SequenceLength;
	Device1_Process1_Simulator_Valve_SequenceLength = 1;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Simulator_Valve_SequenceLength_Id, Device1_Process1_Simulator_Valve_SequenceLength, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Simulator_Valve_SequenceLength_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ Generate : LinePeriod ============== */ 
	int Device1_Process1_Simulator_LinePeriod_PeriodBits_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_LinePeriod_PeriodBits");
	if(Device1_Process1_Simulator_LinePeriod_PeriodBits_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_LinePeriod_PeriodBits): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_LinePeriod_PeriodBits_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Simulator_LinePeriod_Period_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_LinePeriod_Period");
	if(Device1_Process1_Simulator_LinePeriod_Period_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_LinePeriod_Period): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_LinePeriod_Period_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Simulator_LinePeriod_Period;
	Device1_Process1_Simulator_LinePeriod_Period = 1356;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Simulator_LinePeriod_Period_Id, Device1_Process1_Simulator_LinePeriod_Period, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Simulator_LinePeriod_Period_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Simulator_LinePeriod_SequenceBits_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_LinePeriod_SequenceBits");
	if(Device1_Process1_Simulator_LinePeriod_SequenceBits_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_LinePeriod_SequenceBits): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_LinePeriod_SequenceBits_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Simulator_LinePeriod_Sequence_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_LinePeriod_Sequence");
	if(Device1_Process1_Simulator_LinePeriod_Sequence_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_LinePeriod_Sequence): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_LinePeriod_Sequence_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Simulator_LinePeriod_Sequence;
	Device1_Process1_Simulator_LinePeriod_Sequence = 0;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Simulator_LinePeriod_Sequence_Id, Device1_Process1_Simulator_LinePeriod_Sequence, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Simulator_LinePeriod_Sequence_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Simulator_LinePeriod_PulsePosition_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_LinePeriod_PulsePosition");
	if(Device1_Process1_Simulator_LinePeriod_PulsePosition_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_LinePeriod_PulsePosition): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_LinePeriod_PulsePosition_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ Select : EnableGenerate ============== */ 
	int Device1_Process1_Simulator_EnableGenerate_Select_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_EnableGenerate_Select");
	if(Device1_Process1_Simulator_EnableGenerate_Select_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_EnableGenerate_Select): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_EnableGenerate_Select_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Simulator_EnableGenerate_Select;
	Device1_Process1_Simulator_EnableGenerate_Select = 0;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Simulator_EnableGenerate_Select_Id, Device1_Process1_Simulator_EnableGenerate_Select, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Simulator_EnableGenerate_Select_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ SetSignalStatus : OpenValve ============== */ 
	int Device1_Process1_Simulator_OpenValve_Mode_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Simulator_OpenValve_Mode");
	if(Device1_Process1_Simulator_OpenValve_Mode_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Simulator_OpenValve_Mode): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Simulator_OpenValve_Mode_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Simulator_OpenValve_Mode;
	Device1_Process1_Simulator_OpenValve_Mode = SetSignalStatus::High;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Simulator_OpenValve_Mode_Id, Device1_Process1_Simulator_OpenValve_Mode, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Simulator_OpenValve_Mode_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ ImageBufferMultiRoI : Buffer ============== */ 
	int Device1_Process1_Buffer_Mode_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Buffer_Mode");
	if(Device1_Process1_Buffer_Mode_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Buffer_Mode): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Buffer_Mode_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Buffer_MaxNumRoI_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Buffer_MaxNumRoI");
	if(Device1_Process1_Buffer_MaxNumRoI_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Buffer_MaxNumRoI): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Buffer_MaxNumRoI_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Buffer_NumRoI_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Buffer_NumRoI");
	if(Device1_Process1_Buffer_NumRoI_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Buffer_NumRoI): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Buffer_NumRoI_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Buffer_NumRoI;
	Device1_Process1_Buffer_NumRoI = 1;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Buffer_NumRoI_Id, Device1_Process1_Buffer_NumRoI, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Buffer_NumRoI_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Buffer_XOffset_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Buffer_XOffset");
	if(Device1_Process1_Buffer_XOffset_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Buffer_XOffset): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Buffer_XOffset_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	FieldParameterAccess Device1_Process1_Buffer_XOffset;
	unsigned int Device1_Process1_Buffer_XOffset_defaults[] = { 0 };
	Device1_Process1_Buffer_XOffset.vtype = FG_PARAM_TYPE_UINT32_T;
	Device1_Process1_Buffer_XOffset.index = 0;
	Device1_Process1_Buffer_XOffset.count = 1;
	Device1_Process1_Buffer_XOffset.p_uint32_t = Device1_Process1_Buffer_XOffset_defaults;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Buffer_XOffset_Id, &Device1_Process1_Buffer_XOffset, 0, FG_PARAM_TYPE_STRUCT_FIELDPARAMACCESS);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Buffer_XOffset_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Buffer_XLength_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Buffer_XLength");
	if(Device1_Process1_Buffer_XLength_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Buffer_XLength): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Buffer_XLength_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	FieldParameterAccess Device1_Process1_Buffer_XLength;
	unsigned int Device1_Process1_Buffer_XLength_defaults[] = { 2560 };
	Device1_Process1_Buffer_XLength.vtype = FG_PARAM_TYPE_UINT32_T;
	Device1_Process1_Buffer_XLength.index = 0;
	Device1_Process1_Buffer_XLength.count = 1;
	Device1_Process1_Buffer_XLength.p_uint32_t = Device1_Process1_Buffer_XLength_defaults;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Buffer_XLength_Id, &Device1_Process1_Buffer_XLength, 0, FG_PARAM_TYPE_STRUCT_FIELDPARAMACCESS);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Buffer_XLength_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Buffer_YOffset_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Buffer_YOffset");
	if(Device1_Process1_Buffer_YOffset_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Buffer_YOffset): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Buffer_YOffset_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	FieldParameterAccess Device1_Process1_Buffer_YOffset;
	unsigned int Device1_Process1_Buffer_YOffset_defaults[] = { 0 };
	Device1_Process1_Buffer_YOffset.vtype = FG_PARAM_TYPE_UINT32_T;
	Device1_Process1_Buffer_YOffset.index = 0;
	Device1_Process1_Buffer_YOffset.count = 1;
	Device1_Process1_Buffer_YOffset.p_uint32_t = Device1_Process1_Buffer_YOffset_defaults;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Buffer_YOffset_Id, &Device1_Process1_Buffer_YOffset, 0, FG_PARAM_TYPE_STRUCT_FIELDPARAMACCESS);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Buffer_YOffset_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Buffer_YLength_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Buffer_YLength");
	if(Device1_Process1_Buffer_YLength_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Buffer_YLength): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Buffer_YLength_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	FieldParameterAccess Device1_Process1_Buffer_YLength;
	unsigned int Device1_Process1_Buffer_YLength_defaults[] = { 2048 };
	Device1_Process1_Buffer_YLength.vtype = FG_PARAM_TYPE_UINT32_T;
	Device1_Process1_Buffer_YLength.index = 0;
	Device1_Process1_Buffer_YLength.count = 1;
	Device1_Process1_Buffer_YLength.p_uint32_t = Device1_Process1_Buffer_YLength_defaults;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Buffer_YLength_Id, &Device1_Process1_Buffer_YLength, 0, FG_PARAM_TYPE_STRUCT_FIELDPARAMACCESS);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Buffer_YLength_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Buffer_Unlock_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Buffer_Unlock");
	if(Device1_Process1_Buffer_Unlock_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Buffer_Unlock): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Buffer_Unlock_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Buffer_Unlock;
	Device1_Process1_Buffer_Unlock = 1;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Buffer_Unlock_Id, Device1_Process1_Buffer_Unlock, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Buffer_Unlock_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Buffer_InfiniteSource_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Buffer_InfiniteSource");
	if(Device1_Process1_Buffer_InfiniteSource_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Buffer_InfiniteSource): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Buffer_InfiniteSource_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Buffer_FillLevel_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Buffer_FillLevel");
	if(Device1_Process1_Buffer_FillLevel_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Buffer_FillLevel): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Buffer_FillLevel_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	uint64_t Device1_Process1_Buffer_FillLevel = 0;
	rc = Fg_getParameterWithType(fg, Device1_Process1_Buffer_FillLevel_Id, &Device1_Process1_Buffer_FillLevel, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process1_Buffer_FillLevel_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process1_Buffer_FillLevel = %I64d\n", Device1_Process1_Buffer_FillLevel);
	}

	int Device1_Process1_Buffer_Overflow_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Buffer_Overflow");
	if(Device1_Process1_Buffer_Overflow_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Buffer_Overflow): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Buffer_Overflow_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	unsigned int Device1_Process1_Buffer_Overflow = 0;
	rc = Fg_getParameterWithType(fg, Device1_Process1_Buffer_Overflow_Id, &Device1_Process1_Buffer_Overflow, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process1_Buffer_Overflow_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process1_Buffer_Overflow = %d\n", Device1_Process1_Buffer_Overflow);
	}

	/*============ JPEG_Encoder_Gray : Encoder ============== */ 
	int Device1_Process1_Encoder_quality_in_percent_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Encoder_quality_in_percent");
	if(Device1_Process1_Encoder_quality_in_percent_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Encoder_quality_in_percent): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Encoder_quality_in_percent_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Encoder_quality_in_percent;
	Device1_Process1_Encoder_quality_in_percent = 50;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Encoder_quality_in_percent_Id, Device1_Process1_Encoder_quality_in_percent, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Encoder_quality_in_percent_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Encoder_quantization_matrix_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Encoder_quantization_matrix");
	if(Device1_Process1_Encoder_quantization_matrix_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Encoder_quantization_matrix): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Encoder_quantization_matrix_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	FieldParameterAccess Device1_Process1_Encoder_quantization_matrix;
	unsigned int Device1_Process1_Encoder_quantization_matrix_values[64] = { 0 };
	Device1_Process1_Encoder_quantization_matrix.vtype = FG_PARAM_TYPE_UINT32_T;
	Device1_Process1_Encoder_quantization_matrix.index = 0;
	Device1_Process1_Encoder_quantization_matrix.count = 64;
	Device1_Process1_Encoder_quantization_matrix.p_uint32_t = Device1_Process1_Encoder_quantization_matrix_values;
	rc = Fg_getParameterWithType(fg, Device1_Process1_Encoder_quantization_matrix_Id, &Device1_Process1_Encoder_quantization_matrix, 0, FG_PARAM_TYPE_STRUCT_FIELDPARAMACCESS);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process1_Encoder_quantization_matrix_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		for( int j = 0; j < 64; ++j ) {
			fprintf(stderr, "Device1_Process1_Encoder_quantization_matrix_values[%d] = %d\n", j, Device1_Process1_Encoder_quantization_matrix_values[j]);
		}
	}

	/*============ AppendLine : Append8 ============== */ 
	int Device1_Process1_Sorter_Append8_AppendNumber_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Sorter_Append8_AppendNumber");
	if(Device1_Process1_Sorter_Append8_AppendNumber_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Sorter_Append8_AppendNumber): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Sorter_Append8_AppendNumber_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Sorter_Append8_AppendNumber;
	Device1_Process1_Sorter_Append8_AppendNumber = 8;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Sorter_Append8_AppendNumber_Id, Device1_Process1_Sorter_Append8_AppendNumber, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Sorter_Append8_AppendNumber_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ LineMemory : module21 ============== */ 
	int Device1_Process1_Sorter_module21_Implementation_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Sorter_module21_Implementation");
	if(Device1_Process1_Sorter_module21_Implementation_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Sorter_module21_Implementation): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Sorter_module21_Implementation_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Sorter_module21_FrameWidth_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Sorter_module21_FrameWidth");
	if(Device1_Process1_Sorter_module21_FrameWidth_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Sorter_module21_FrameWidth): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Sorter_module21_FrameWidth_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Sorter_module21_XOffset_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Sorter_module21_XOffset");
	if(Device1_Process1_Sorter_module21_XOffset_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Sorter_module21_XOffset): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Sorter_module21_XOffset_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Sorter_module21_XOffset;
	Device1_Process1_Sorter_module21_XOffset = 0;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Sorter_module21_XOffset_Id, Device1_Process1_Sorter_module21_XOffset, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Sorter_module21_XOffset_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Sorter_module21_XLength_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Sorter_module21_XLength");
	if(Device1_Process1_Sorter_module21_XLength_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Sorter_module21_XLength): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Sorter_module21_XLength_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Sorter_module21_XLength;
	Device1_Process1_Sorter_module21_XLength = 2560;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Sorter_module21_XLength_Id, Device1_Process1_Sorter_module21_XLength, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Sorter_module21_XLength_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ SplitLine : Width ============== */ 
	int Device1_Process1_Sorter_Width_LineLength_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Sorter_Width_LineLength");
	if(Device1_Process1_Sorter_Width_LineLength_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Sorter_Width_LineLength): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Sorter_Width_LineLength_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Sorter_Width_LineLength;
	Device1_Process1_Sorter_Width_LineLength = 2560;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Sorter_Width_LineLength_Id, Device1_Process1_Sorter_Width_LineLength, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Sorter_Width_LineLength_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ CONST : Write ============== */ 
	int Device1_Process1_Sorter_Write_Value_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Sorter_Write_Value");
	if(Device1_Process1_Sorter_Write_Value_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Sorter_Write_Value): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Sorter_Write_Value_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ SCALE : By8 ============== */ 
	int Device1_Process1_Sorter_AddrGen_By8_ScaleFactorMaxBits_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Sorter_AddrGen_By8_ScaleFactorMaxBits");
	if(Device1_Process1_Sorter_AddrGen_By8_ScaleFactorMaxBits_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Sorter_AddrGen_By8_ScaleFactorMaxBits): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Sorter_AddrGen_By8_ScaleFactorMaxBits_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Sorter_AddrGen_By8_ScaleFactor_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Sorter_AddrGen_By8_ScaleFactor");
	if(Device1_Process1_Sorter_AddrGen_By8_ScaleFactor_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Sorter_AddrGen_By8_ScaleFactor): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Sorter_AddrGen_By8_ScaleFactor_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ ModuloCount : Modx ============== */ 
	int Device1_Process1_Sorter_AddrGen_Modx_Divisor_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Sorter_AddrGen_Modx_Divisor");
	if(Device1_Process1_Sorter_AddrGen_Modx_Divisor_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Sorter_AddrGen_Modx_Divisor): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Sorter_AddrGen_Modx_Divisor_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Sorter_AddrGen_Modx_Divisor;
	Device1_Process1_Sorter_AddrGen_Modx_Divisor = 320;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Sorter_AddrGen_Modx_Divisor_Id, Device1_Process1_Sorter_AddrGen_Modx_Divisor, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Sorter_AddrGen_Modx_Divisor_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Sorter_AddrGen_Modx_CountEntity_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Sorter_AddrGen_Modx_CountEntity");
	if(Device1_Process1_Sorter_AddrGen_Modx_CountEntity_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Sorter_AddrGen_Modx_CountEntity): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Sorter_AddrGen_Modx_CountEntity_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Sorter_AddrGen_Modx_AutoClear_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Sorter_AddrGen_Modx_AutoClear");
	if(Device1_Process1_Sorter_AddrGen_Modx_AutoClear_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Sorter_AddrGen_Modx_AutoClear): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Sorter_AddrGen_Modx_AutoClear_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ CONST : 320 ============== */ 
	int Device1_Process1_Sorter_AddrGen_320_Value_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Sorter_AddrGen_320_Value");
	if(Device1_Process1_Sorter_AddrGen_320_Value_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Sorter_AddrGen_320_Value): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Sorter_AddrGen_320_Value_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Sorter_AddrGen_320_Value;
	Device1_Process1_Sorter_AddrGen_320_Value = 320;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Sorter_AddrGen_320_Value_Id, Device1_Process1_Sorter_AddrGen_320_Value, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Sorter_AddrGen_320_Value_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ SourceSelector : EnableSimulator ============== */ 
	int Device1_Process1_EnableSimulator_SelectSource_Id = Fg_getParameterIdByName(fg, "Device1_Process1_EnableSimulator_SelectSource");
	if(Device1_Process1_EnableSimulator_SelectSource_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_EnableSimulator_SelectSource): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_EnableSimulator_SelectSource_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_EnableSimulator_SelectSource;
	Device1_Process1_EnableSimulator_SelectSource = 0;
	rc = Fg_setParameterWithType(fg, Device1_Process1_EnableSimulator_SelectSource_Id, Device1_Process1_EnableSimulator_SelectSource, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_EnableSimulator_SelectSource_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_EnableSimulator_InfiniteSource_Id = Fg_getParameterIdByName(fg, "Device1_Process1_EnableSimulator_InfiniteSource");
	if(Device1_Process1_EnableSimulator_InfiniteSource_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_EnableSimulator_InfiniteSource): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_EnableSimulator_InfiniteSource_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ DmaToPC : DMA_JPEG ============== */ 
	int Device1_Process1_DMA_JPEG_CurrentTransferLength_Id = Fg_getParameterIdByName(fg, "Device1_Process1_DMA_JPEG_CurrentTransferLength");
	if(Device1_Process1_DMA_JPEG_CurrentTransferLength_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_DMA_JPEG_CurrentTransferLength): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_DMA_JPEG_CurrentTransferLength_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* dynamic read only parameter */

	uint64_t Device1_Process1_DMA_JPEG_CurrentTransferLength = 0;
	rc = Fg_getParameterWithType(fg, Device1_Process1_DMA_JPEG_CurrentTransferLength_Id, &Device1_Process1_DMA_JPEG_CurrentTransferLength, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterWithType(Device1_Process1_DMA_JPEG_CurrentTransferLength_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}else{
		fprintf(stderr, "Device1_Process1_DMA_JPEG_CurrentTransferLength = %I64d\n", Device1_Process1_DMA_JPEG_CurrentTransferLength);
	}

	/*============ Polarity : Invert ============== */ 
	int Device1_Process1_Trigger_Invert_Invert_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_Invert_Invert");
	if(Device1_Process1_Trigger_Invert_Invert_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_Invert_Invert): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_Invert_Invert_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Trigger_Invert_Invert;
	Device1_Process1_Trigger_Invert_Invert = Polarity::Invert;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Trigger_Invert_Invert_Id, Device1_Process1_Trigger_Invert_Invert, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Trigger_Invert_Invert_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ Select : TriggerMode ============== */ 
	int Device1_Process1_Trigger_TriggerMode_Select_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_TriggerMode_Select");
	if(Device1_Process1_Trigger_TriggerMode_Select_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_TriggerMode_Select): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_TriggerMode_Select_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Trigger_TriggerMode_Select;
	Device1_Process1_Trigger_TriggerMode_Select = 1;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Trigger_TriggerMode_Select_Id, Device1_Process1_Trigger_TriggerMode_Select, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Trigger_TriggerMode_Select_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ SignalWidth : Width ============== */ 
	int Device1_Process1_Trigger_Width_WidthBits_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_Width_WidthBits");
	if(Device1_Process1_Trigger_Width_WidthBits_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_Width_WidthBits): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_Width_WidthBits_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Trigger_Width_Width_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_Width_Width");
	if(Device1_Process1_Trigger_Width_Width_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_Width_Width): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_Width_Width_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	uint64_t Device1_Process1_Trigger_Width_Width;
	Device1_Process1_Trigger_Width_Width = 0x186a;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Trigger_Width_Width_Id, Device1_Process1_Trigger_Width_Width, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Trigger_Width_Width_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ SetSignalStatus : SoftwareTrigger ============== */ 
	int Device1_Process1_Trigger_SoftwareTrigger_Mode_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_SoftwareTrigger_Mode");
	if(Device1_Process1_Trigger_SoftwareTrigger_Mode_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_SoftwareTrigger_Mode): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_SoftwareTrigger_Mode_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Trigger_SoftwareTrigger_Mode;
	Device1_Process1_Trigger_SoftwareTrigger_Mode = SetSignalStatus::Pulse;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Trigger_SoftwareTrigger_Mode_Id, Device1_Process1_Trigger_SoftwareTrigger_Mode, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Trigger_SoftwareTrigger_Mode_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ SignalDebounce : Debounce ============== */ 
	int Device1_Process1_Trigger_ExternalInput_Debounce_DebounceBits_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_ExternalInput_Debounce_DebounceBits");
	if(Device1_Process1_Trigger_ExternalInput_Debounce_DebounceBits_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_ExternalInput_Debounce_DebounceBits): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_ExternalInput_Debounce_DebounceBits_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Trigger_ExternalInput_Debounce_Debounce_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_ExternalInput_Debounce_Debounce");
	if(Device1_Process1_Trigger_ExternalInput_Debounce_Debounce_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_ExternalInput_Debounce_Debounce): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_ExternalInput_Debounce_Debounce_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Trigger_ExternalInput_Debounce_Debounce;
	Device1_Process1_Trigger_ExternalInput_Debounce_Debounce = 125;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Trigger_ExternalInput_Debounce_Debounce_Id, Device1_Process1_Trigger_ExternalInput_Debounce_Debounce, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Trigger_ExternalInput_Debounce_Debounce_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ Select : SelectInput ============== */ 
	int Device1_Process1_Trigger_ExternalInput_SelectInput_Select_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_ExternalInput_SelectInput_Select");
	if(Device1_Process1_Trigger_ExternalInput_SelectInput_Select_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_ExternalInput_SelectInput_Select): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_ExternalInput_SelectInput_Select_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	unsigned int Device1_Process1_Trigger_ExternalInput_SelectInput_Select;
	Device1_Process1_Trigger_ExternalInput_SelectInput_Select = 0;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Trigger_ExternalInput_SelectInput_Select_Id, Device1_Process1_Trigger_ExternalInput_SelectInput_Select, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Trigger_ExternalInput_SelectInput_Select_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	/*============ GPI : FrontGPI1 ============== */ 
	int Device1_Process1_Trigger_ExternalInput_FrontGPI1_Pin_ID_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_ExternalInput_FrontGPI1_Pin_ID");
	if(Device1_Process1_Trigger_ExternalInput_FrontGPI1_Pin_ID_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_ExternalInput_FrontGPI1_Pin_ID): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_ExternalInput_FrontGPI1_Pin_ID_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Trigger_ExternalInput_FrontGPI1_ConnectorType_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_ExternalInput_FrontGPI1_ConnectorType");
	if(Device1_Process1_Trigger_ExternalInput_FrontGPI1_ConnectorType_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_ExternalInput_FrontGPI1_ConnectorType): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_ExternalInput_FrontGPI1_ConnectorType_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ GPI : FrontGPI0 ============== */ 
	int Device1_Process1_Trigger_ExternalInput_FrontGPI0_Pin_ID_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_ExternalInput_FrontGPI0_Pin_ID");
	if(Device1_Process1_Trigger_ExternalInput_FrontGPI0_Pin_ID_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_ExternalInput_FrontGPI0_Pin_ID): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_ExternalInput_FrontGPI0_Pin_ID_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Trigger_ExternalInput_FrontGPI0_ConnectorType_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_ExternalInput_FrontGPI0_ConnectorType");
	if(Device1_Process1_Trigger_ExternalInput_FrontGPI0_ConnectorType_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_ExternalInput_FrontGPI0_ConnectorType): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_ExternalInput_FrontGPI0_ConnectorType_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ GPI : GPI1 ============== */ 
	int Device1_Process1_Trigger_ExternalInput_GPI1_Pin_ID_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_ExternalInput_GPI1_Pin_ID");
	if(Device1_Process1_Trigger_ExternalInput_GPI1_Pin_ID_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_ExternalInput_GPI1_Pin_ID): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_ExternalInput_GPI1_Pin_ID_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Trigger_ExternalInput_GPI1_ConnectorType_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_ExternalInput_GPI1_ConnectorType");
	if(Device1_Process1_Trigger_ExternalInput_GPI1_ConnectorType_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_ExternalInput_GPI1_ConnectorType): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_ExternalInput_GPI1_ConnectorType_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ GPI : GPI0 ============== */ 
	int Device1_Process1_Trigger_ExternalInput_GPI0_Pin_ID_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_ExternalInput_GPI0_Pin_ID");
	if(Device1_Process1_Trigger_ExternalInput_GPI0_Pin_ID_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_ExternalInput_GPI0_Pin_ID): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_ExternalInput_GPI0_Pin_ID_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Trigger_ExternalInput_GPI0_ConnectorType_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_ExternalInput_GPI0_ConnectorType");
	if(Device1_Process1_Trigger_ExternalInput_GPI0_ConnectorType_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_ExternalInput_GPI0_ConnectorType): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_ExternalInput_GPI0_ConnectorType_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ Generate : Period ============== */ 
	int Device1_Process1_Trigger_Generator_Period_PeriodBits_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_Generator_Period_PeriodBits");
	if(Device1_Process1_Trigger_Generator_Period_PeriodBits_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_Generator_Period_PeriodBits): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_Generator_Period_PeriodBits_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Trigger_Generator_Period_Period_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_Generator_Period_Period");
	if(Device1_Process1_Trigger_Generator_Period_Period_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_Generator_Period_Period): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_Generator_Period_Period_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	uint64_t Device1_Process1_Trigger_Generator_Period_Period;
	Device1_Process1_Trigger_Generator_Period_Period = 0x2faf08;
	rc = Fg_setParameterWithType(fg, Device1_Process1_Trigger_Generator_Period_Period_Id, Device1_Process1_Trigger_Generator_Period_Period, 0);
	if(rc < 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_setParameterWithType(Device1_Process1_Trigger_Generator_Period_Period_Id): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}

	int Device1_Process1_Trigger_Generator_Period_SequenceBits_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_Generator_Period_SequenceBits");
	if(Device1_Process1_Trigger_Generator_Period_SequenceBits_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_Generator_Period_SequenceBits): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_Generator_Period_SequenceBits_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Trigger_Generator_Period_Sequence_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_Generator_Period_Sequence");
	if(Device1_Process1_Trigger_Generator_Period_Sequence_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_Generator_Period_Sequence): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_Generator_Period_Sequence_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Trigger_Generator_Period_PulsePosition_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_Generator_Period_PulsePosition");
	if(Device1_Process1_Trigger_Generator_Period_PulsePosition_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_Generator_Period_PulsePosition): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_Generator_Period_PulsePosition_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	/*============ CameraControl : CamA ============== */ 
	/*============ GPO : GPO1 ============== */ 
	int Device1_Process1_Trigger_GPO1_Pin_ID_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_GPO1_Pin_ID");
	if(Device1_Process1_Trigger_GPO1_Pin_ID_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_GPO1_Pin_ID): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_GPO1_Pin_ID_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */

	int Device1_Process1_Trigger_GPO1_ConnectorType_Id = Fg_getParameterIdByName(fg, "Device1_Process1_Trigger_GPO1_ConnectorType");
	if(Device1_Process1_Trigger_GPO1_ConnectorType_Id <= 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error in Fg_getParameterIdByName(Device1_Process1_Trigger_GPO1_ConnectorType): %s (%d)\n", Fg_getLastErrorDescription(fg), Device1_Process1_Trigger_GPO1_ConnectorType_Id);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	} /* static parameter */


	// ---------------------------------------------------------------------------
	// Frame Grabber: Create the display(s)
	// ---------------------------------------------------------------------------

	int id0 = CreateDisplay(8 * byteWidth0, width0, height0);
	if(id0 < 0) {
		fprintf(stderr, "Error in CreateDisplay(): %s (%d)\n", Fg_getLastErrorDescription(fg), id0);
		Fg_FreeMemEx(fg, pmem1);
		pmem1 = NULL;
		Fg_FreeMemEx(fg, pmem0);
		pmem0 = NULL;
		Fg_FreeGrabber(fg);
		fg = NULL;
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
		return id0;
	}
	SetBufferWidth(id0, width0, height0);

	int id1 = CreateDisplay(8 * byteWidth1, width1, height1);
	if(id1 < 0) {
		fprintf(stderr, "Error in CreateDisplay(): %s (%d)\n", Fg_getLastErrorDescription(fg), id1);
		CloseDisplay(id0);
		Fg_FreeMemEx(fg, pmem1);
		pmem1 = NULL;
		Fg_FreeMemEx(fg, pmem0);
		pmem0 = NULL;
		Fg_FreeGrabber(fg);
		fg = NULL;
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
		return id1;
	}
	SetBufferWidth(id1, width1, height1);


	// ---------------------------------------------------------------------------
	// Frame Grabber: Start acquisition at applet and camera for each present port
	// ---------------------------------------------------------------------------

	rc = Fg_AcquireEx(fg, 0, nrOfCycles, ACQ_STANDARD, pmem0);
	if(rc != 0) {
		fprintf(stderr, "Error in Fg_AcquireEx() for channel 0: %s\n", Fg_getErrorDescription(fg, rc));
		CloseDisplay(id1);
		CloseDisplay(id0);
		Fg_FreeMemEx(fg, pmem1);
		pmem1 = NULL;
		Fg_FreeMemEx(fg, pmem0);
		pmem0 = NULL;
		Fg_FreeGrabber(fg);
		fg = NULL;
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
		return rc;
	}

	rc = Fg_AcquireEx(fg, 1, nrOfCycles, ACQ_STANDARD, pmem1);
	if(rc != 0) {
		fprintf(stderr, "Error in Fg_AcquireEx() for channel 1: %s\n", Fg_getErrorDescription(fg, rc));
		Fg_stopAcquireEx(fg, 0, pmem0, 0);
		CloseDisplay(id1);
		CloseDisplay(id0);
		Fg_FreeMemEx(fg, pmem1);
		pmem1 = NULL;
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
	frameindex_t frameNo1 = 0;
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
		frameNo1 = Fg_getLastPicNumberBlockingEx(fg, frameNo1 + 1, 1, 5, pmem1);
		if(frameNo1 < 0) {
			fprintf(stderr, "Error in Fg_getLastPicNumberBlockingEx(): %s (%d)\n", Fg_getLastErrorDescription(fg), frameNo1);
			fprintf(stderr, "Press any key to continue...\n");
			_getch();
			break;
		} else {
			fprintf(stderr, "grabbed image %d\n", frameNo1 );
		}

		void *iPtr0 = Fg_getImagePtrEx(fg, frameNo0, 0, pmem0);
		if(iPtr0 == NULL) {
			fprintf(stderr, "Error in Fg_getImagePtrEx(): %s\n", Fg_getLastErrorDescription(fg));
			Fg_stopAcquireEx(fg, 1, pmem1, 0);
			Fg_stopAcquireEx(fg, 0, pmem0, 0);
			CloseDisplay(id1);
			CloseDisplay(id0);
			Fg_FreeMemEx(fg, pmem1);
			pmem1 = NULL;
			Fg_FreeMemEx(fg, pmem0);
			pmem0 = NULL;
			Fg_FreeGrabber(fg);
			fg = NULL;
			fprintf(stderr, "Press any key to continue...\n");
			_getch();
			return -1;
		}
		DrawBuffer(id0, iPtr0, frameNo0, 0);

		void *iPtr1 = Fg_getImagePtrEx(fg, frameNo1, 0, pmem1);
		if(iPtr1 == NULL) {
			fprintf(stderr, "Error in Fg_getImagePtrEx(): %s\n", Fg_getLastErrorDescription(fg));
			Fg_stopAcquireEx(fg, 1, pmem1, 0);
			Fg_stopAcquireEx(fg, 0, pmem0, 0);
			CloseDisplay(id1);
			CloseDisplay(id0);
			Fg_FreeMemEx(fg, pmem1);
			pmem1 = NULL;
			Fg_FreeMemEx(fg, pmem0);
			pmem0 = NULL;
			Fg_FreeGrabber(fg);
			fg = NULL;
			fprintf(stderr, "Press any key to continue...\n");
			_getch();
			return -1;
		}
		DrawBuffer(id1, iPtr1, frameNo1, 0);
	}


	// ---------------------------------------------------------------------------
	// Frame Grabber: Stop acquisition
	// ---------------------------------------------------------------------------

	rc = Fg_stopAcquireEx(fg, 1, pmem1, 0);
	if(rc < 0) {
		fprintf(stderr, "Error in Fg_stopAcquireEx(): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
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

	CloseDisplay(id1);


	// ---------------------------------------------------------------------------
	// Frame Grabber: Close the display
	// ---------------------------------------------------------------------------

	CloseDisplay(id0);


	// ---------------------------------------------------------------------------
	// Frame Grabber: Release the memory for buffer(s)
	// ---------------------------------------------------------------------------

	rc = Fg_FreeMemEx(fg, pmem1);
	if(rc < 0) {
		fprintf(stderr, "Error in Fg_FreeMemEx(): %s (%d)\n", Fg_getLastErrorDescription(fg), rc);
		fprintf(stderr, "Press any key to continue...\n");
		_getch();
	}
	pmem1 = NULL;


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
