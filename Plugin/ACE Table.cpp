// Include StdAfx
#include "StdAfx.h"

// Include any used common ACE definitions.
#ifdef RUN_ONLY
#include "..\Common\CommonAceDef.hpp"
#endif

//////////////////////////////////////////////////////////////////////////////////
// ACE table
//////////////////////////////////////////////////////////////////////////////////

void DefineACES(MicroAceTime* at)
{
	// Define your ACE tables here.
	// Use ADDPARAM before each ADDACT/ADDCND/ADDEXP to add parameters.
	// See the documentation for full details.

	// Note in the display string, %o is your object icon and %0-%9 make up parameters.
	// Note the script name should be a name suitable for the routine as if it were a member function in a
	// scripting language, eg. "Clear Stored Items" -> "ClearStoredItems"

	/////////////////////////////
	// Conditions
	// Format:
	// ADDCND(List name, Category, Display string, Function address, Script name, Flags)

	ADDCND("Connected", "Connection", "%o Remote connected", &ExtObject::cConnected, "Connected", 0);
	ADDCND("Connection lost", "Connection", "%o Connection lost", &ExtObject::cConnectionLost, "ConnectionLost", 0);

	ADDPARAMCOMBO("Button", "Remote button", WIIBUTTONSTRING);
	ADDCND("Button pressed", "Buttons", "%o %0 pressed", &ExtObject::cButtonPressed, "ButtonPressed", 0);
	ADDPARAMCOMBO("Button", "Remote button", WIIBUTTONSTRING);
	ADDCND("Button down", "Buttons", "%o %0 is down", &ExtObject::cButtonDown, "ButtonDown", 0);
	ADDPARAMCOMBO("Button", "Remote button", WIIBUTTONSTRING);
	ADDCND("Button released", "Buttons", "%o %0 released", &ExtObject::cButtonReleased, "ButtonReleased", 0);

	/////////////////////////////
	// Actions
	// Format:
	// ADDCND(List name, Category, Display string, Function address, Script name, Flags)
	//ADDPARAM(PARAM_VALUE, "Example parameter", "Here is an example parameter.");
	//ADDACT("My action", "My category", "Example action (%0)", &ExtObject::aMyAction, "MyAction", 0);

	ADDACT("Connect", "Connection", "Connect remote", &ExtObject::aConnect, "Connect", 0);
	ADDACT("Disconnect", "Connection", "Disconnect remote", &ExtObject::aDisconnect, "Disconnect", 0);

	ADDPARAMCOMBO("Report level", "Set features to report. Accelerometer and Infrared increase power consumption.", "Buttons only|Accelerometer|Acc + Infrared");
	ADDACT("Set report level", "Remote", "Set report level to %0", &ExtObject::aSetReportType, "SetReportType", 0);

	ADDPARAMCOMBO("Rumble", "Turn rumble off or on", "Off|On");
	ADDACT("Set rumble", "Remote", "Set rumble %0", &ExtObject::aSetRumble, "SetRumble", 0);

	ADDPARAM(PARAM_VALUE, "Led 1", "0 = off, 1 = on.");
	ADDPARAM(PARAM_VALUE, "Led 2", "0 = off, 1 = on.");
	ADDPARAM(PARAM_VALUE, "Led 3", "0 = off, 1 = on.");
	ADDPARAM(PARAM_VALUE, "Led 3", "0 = off, 1 = on.");
	ADDACT("Set LEDs", "Remote", "Set LEDs to %0 %1 %2 %3", &ExtObject::aSetLeds, "SetLEDs", 0);

	/////////////////////////////
	// Expressions
	// ADDEXP(List name, Category, Display string, Function address, Flags)
	ADDEXP("Pitch", "Orientation", "Pitch", &ExtObject::ePitch, RETURN_INTEGER);
	ADDEXP("Roll", "Orientation", "Roll", &ExtObject::eRoll, RETURN_INTEGER);
	ADDEXP("Orientation X", "Orientation", "OriX", &ExtObject::eOriX, RETURN_FLOAT);
	ADDEXP("Orientation Y", "Orientation", "OriY", &ExtObject::eOriY, RETURN_FLOAT);
	ADDEXP("Orientation Z", "Orientation", "OriZ", &ExtObject::eOriZ, RETURN_FLOAT);
	ADDEXP("Acceleration X", "Acceleration", "AccX", &ExtObject::eAccX, RETURN_FLOAT);
	ADDEXP("Acceleration Y", "Acceleration", "AccY", &ExtObject::eAccY, RETURN_FLOAT);
	ADDEXP("Acceleration Z", "Acceleration", "AccZ", &ExtObject::eAccZ, RETURN_FLOAT);
	ADDEXP("Battery level", "Status", "BatteryLevel", &ExtObject::eBatteryPercent, RETURN_INTEGER);
	ADDEXP("IR X", "Infrared", "IrX", &ExtObject::eIrX, RETURN_FLOAT);
	ADDEXP("IR Y", "Infrared", "IrY", &ExtObject::eIrY, RETURN_FLOAT);
	ADDEXP("IR Z", "Infrared", "IrZ", &ExtObject::eIrZ, RETURN_FLOAT);
	ADDPARAM(PARAM_VALUE, "1", "Sensor bar led to read from");
	ADDEXP("Raw IR X", "Infrared", "RawIrX", &ExtObject::eRawX, RETURN_INTEGER);
	ADDPARAM(PARAM_VALUE, "1", "Sensor bar led to read from");
	ADDEXP("Raw IR Y", "Infrared", "RawIrY", &ExtObject::eRawY, RETURN_INTEGER);
	ADDEXP("IR Report level", "Status", "ReportLevel", &ExtObject::eReportLevel, RETURN_STRING);
	ADDEXP("Led status", "Status", "LedStatus", &ExtObject::eLedStatus, RETURN_STRING);
	ADDEXP("Update age", "Status", "UpdateAge", &ExtObject::eUpdateAge, RETURN_INTEGER);

	//Nunchuk actions
	ADDPARAM(PARAM_VALUE, "X axis", "0.0 - 1.0, default 0.03");
	ADDPARAM(PARAM_VALUE, "Y axis", "0.0 - 1.0, default 0.03");
	ADDACT("Set joystick deadzone", "Nunchuk", "Set joystick X, Y deadzone to %0, %0", &ExtObject::aSetNunDeadzone, "SetNunDeadzone", 0);

	//Nunchuk conditions
	ADDCND("Nunchuk Connected", "Nunchuk", "%o Nunchuk connected", &ExtObject::cNunConnected, "NunchukConnected", 0);

	//Nunchuk expressions
	ADDEXP("Joystick X", "Nunchuk", "NunJoyX", &ExtObject::eNunJoyX, RETURN_FLOAT);
	ADDEXP("Joystick Y", "Nunchuk", "NunJoyY", &ExtObject::eNunJoyY, RETURN_FLOAT);
	ADDEXP("Nunchuk Pitch", "Nunchuk", "NunPitch", &ExtObject::eNunPitch, RETURN_FLOAT);
	ADDEXP("Nunchuk Roll", "Nunchuk", "NunRoll", &ExtObject::eNunRoll, RETURN_FLOAT);
	ADDEXP("Nunchuk Acceleration X", "Nunchuk", "NunAccX", &ExtObject::eNunAccX, RETURN_FLOAT);
	ADDEXP("Nunchuk Acceleration Y", "Nunchuk", "NunAccY", &ExtObject::eNunAccY, RETURN_FLOAT);
	ADDEXP("Nunchuk Acceleration Z", "Nunchuk", "NunAccZ", &ExtObject::eNunAccZ, RETURN_FLOAT);
	ADDEXP("Nunchuk Orientation X", "Nunchuk", "NunOriX", &ExtObject::eNunOriX, RETURN_FLOAT);
	ADDEXP("Nunchuk Orientation Y", "Nunchuk", "NunOriY", &ExtObject::eNunOriY, RETURN_FLOAT);
	ADDEXP("Nunchuk Orientation Z", "Nunchuk", "NunOriZ", &ExtObject::eNunOriZ, RETURN_FLOAT);
	ADDEXP("Nunchuk Update age", "Nunchuk", "NunUpdateAge", &ExtObject::eNunUpdateAge, RETURN_INTEGER);
	ADDEXP("Nunchuk Deadzone X", "Nunchuk", "NunDeadzoneX", &ExtObject::eNunDeadzoneX, RETURN_FLOAT);
	ADDEXP("Nunchuk Deadzone Y", "Nunchuk", "NunDeadzoneY", &ExtObject::eNunDeadzoneY, RETURN_FLOAT);

	//Balance board actions
	//ADDACT("My action", "My category", "Example action (%0)", &ExtObject::aMyAction, "MyAction", 0);
	ADDACT("Reset weight calibration", "Balance board", "Reset weight calibration", &ExtObject::aResetWeightCalibration, "ResetWeightCalibration", 0 );
	//Balance board conditions
	ADDCND("Is balance board", "Balance board", "%o is balance board", &ExtObject::cIsBalanceBoard, "IsBalanceBoard", 0);
	
	//Balance board expressions
	// ADDEXP(List name, Category, Display string, Function address, Flags)
	ADDEXP("Total weight", "Balance board", "TotalWeight", &ExtObject::eTotalWeight, 0);
	ADDEXP("Top left weight", "Balance board", "TopLeftWeight", &ExtObject::eTopLeftWeight, 0);
	ADDEXP("Top right weight", "Balance board", "TopRightWeight", &ExtObject::eTopRightWeight, 0);
	ADDEXP("Bottom left weight", "Balance board", "BottomLeftWeight", &ExtObject::eBottomLeftWeight, 0);
	ADDEXP("Bottom right weight", "Balance board", "BottomRightWeight", &ExtObject::eBottomRightWeight, 0);

	// This line includes your common ACEs as specified in Main.h
#include "..\Common\CommonAceTable.hpp"
}


