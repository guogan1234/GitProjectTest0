#include <fgrab_prototyp.h>
#include <fgrab_struct.h>
#include <fgrab_define.h>


namespace ImageBuffer {
enum mt_InfiniteSource {
	ENABLED	= 0,
	DISABLED	= 1
};

}

namespace AppletProperties {
enum mt_GpioType {
	PushPull	= 0,
	OpenDrain	= 1
};

}

namespace BoardStatus {
enum mt_Capability {
	YES	= 1,
	NO	= 0
};
enum mt_PoCLState {
	Initialize	= 0,
	PoCL_Connection_Sense	= 1,
	PoCL_Camera_and_Cable_Detected	= 2,
	PoCL_Camera_Clock_Detected	= 3,
	NonPoCL_Camera_or_Cable_Detected	= 4,
	NonPoCL_Camera_Clock_Detected	= 5
};

}

namespace BaseGrayCamera {
enum mt_DvalMode {
	DVAL_Enabled	= 1,
	DVAL_Disabled	= 0
};
enum mt_CameraBaseMode {
	Tap1x8bit	= 0,
	Tap1x10bit	= 1,
	Tap1x12bit	= 2,
	Tap1x14bit	= 3,
	Tap1x16bit	= 4,
	Tap2x8bit	= 5,
	Tap2x10bit	= 6,
	Tap2x12bit	= 7,
	Tap3x8bit	= 8
};

}

namespace Polarity {
enum mt_Invert {
	NotInvert	= 0,
	Invert	= 1
};

}

namespace SetSignalStatus {
enum mt_ModeType {
	Low	= 0,
	High	= 1,
	Pulse	= 2
};

}

namespace GPI {
enum ConnectorType {
	FrontGPIO	= 1,
	GPIO	= 0
};

}

namespace Generate {
enum mt_PulsePosition {
	AtPeriodStart	= 1,
	AtPeriodEnd	= 0
};

}

namespace GPO {
enum ConnectorType {
	FrontGPIO	= 1,
	GPIO	= 0
};

}
