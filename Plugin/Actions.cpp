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
	return 0;
}

long ExtObject::aDisconnect(LPVAL params)
{
	remote.Disconnect();
	return 0;
}

