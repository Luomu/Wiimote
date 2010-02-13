// Include StdAfx
#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////////////////
// Actions
//////////////////////////////////////////////////////////////////////////////////

long ExtObject::aMyAction(LPVAL params)
{
	// Get the example parameter
	int param = params[0].GetInt();

	// Do nothing
	return 0;
}

long ExtObject::aConnect(LPVAL params)
{
	if(remote.Connect(wiimote::FIRST_AVAILABLE)) {
		remote.SetLEDs(1);
		remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR_EXT);
		remote.Nunchuk.Joystick.DeadZone.X = 0.03f;
		remote.Nunchuk.Joystick.DeadZone.Y = 0.03f;
	}
	return 0;
}

long ExtObject::aDisconnect(LPVAL params)
{
	remote.Disconnect();
	return 0;
}

long ExtObject::aSetReportType(LPVAL params)
{
	//Buttons|Accelerometer|Infrared
	int mode = params[0].GetInt();
	if(mode == 0)
		remote.SetReportType(wiimote::IN_BUTTONS, true);
	if(mode == 1)
		remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_EXT);
	if(mode == 2)
		remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR_EXT);
	return 0;
	/*enum input_report
	{
	// combinations if buttons/acceleration/IR/Extension data
	IN_BUTTONS				 = 0x30,
	IN_BUTTONS_ACCEL		 = 0x31,
	IN_BUTTONS_ACCEL_IR		 = 0x33, // reports IR EXTENDED data (dot sizes)
	IN_BUTTONS_ACCEL_EXT	 = 0x35,
	IN_BUTTONS_ACCEL_IR_EXT	 = 0x37, // reports IR BASIC data (no dot sizes)
	IN_BUTTONS_BALANCE_BOARD = 0x32, // must use this for the balance board
	};*/
}

long ExtObject::aSetRumble(LPVAL params)
{
	bool mode = params[0].GetBool();
	if(remote.IsConnected())
		remote.SetRumble(mode);
	return 0;
}

long ExtObject::aSetLeds(LPVAL params)
{
	unsigned leds = 1 * params[0].GetBool() + 2 * params[1].GetBool() + 4 * params[2].GetBool() + 8 * params[3].GetBool();
	if(remote.IsConnected())
		remote.SetLEDs(leds);
	return 0;
}


long ExtObject::aSetNunDeadzone( LPVAL params )
{
	float x = clampf(params[0].GetFloat(), 0.f, 1.f);
	float y = clampf(params[1].GetFloat(), 0.f, 1.f);

	if(remote.IsConnected()) {
		remote.Nunchuk.Joystick.DeadZone.X = x;
		remote.Nunchuk.Joystick.DeadZone.Y = y;
	}

	return 0;
}


long ExtObject::aResetWeightCalibration( LPVAL params )
{
	if(!remote.IsBalanceBoard())
		return 0;

	remote.CalibrateAtRest();
	return 0;
}