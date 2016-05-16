#pragma once

//#include "JPEG_Gray.h"
#pragma once

#include "fgrab_prototyp.h"
#include "fgrab_struct.h"
#include "fgrab_define.h"

namespace CameraGrayArea {
	enum PixelFormat {
		MONO8	= 0,
		MONO8_SIGNED	= 1,
		MONO10	= 2,
		MONO10_PACKED	= 3,
		MONO12	= 4,
		MONO12_PACKED	= 5,
		MONO16	= 6
	};

}

namespace ImageBuffer_JPEG_Gray {
	enum me_InfiniteSource {
		ENABLED	= 0,
		DISABLED	= 1
	};

}

namespace ImageBuffer {
	enum mt_InfiniteSource {
		ENABLED	= 0,
		DISABLED	= 1
	};

}


int setBufferROI(Fg_Struct* fg, int xOffset, int xLength, int yOffset, int yLength);

int setJPEGQuality(Fg_Struct* fg, int q);
//int setJPEGQuality1(Fg_Struct* fg, int JPEGQuality1);

int configureCam(Fg_Struct* fg);