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
	remote.Connect(wiimote::FIRST_AVAILABLE);
	remote.SetLEDs(1);
	return 0;
}

long ExtObject::aDisconnect(LPVAL params)
{
	remote.Disconnect();
	return 0;
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
