// Include StdAfx
#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////////////////
// Conditions
//////////////////////////////////////////////////////////////////////////////////

long ExtObject::cConnected(LPVAL params)
{
	return remote.IsConnected();
}

long ExtObject::cConnectionLost(LPVAL params)
{
	if (remote.ConnectionLost())
		return true;
	else
		return false;
}

long ExtObject::cButtonDown(LPVAL params)
{
	if(!remote.IsConnected())
		return false;

	if(params[0].GetInt() == 0 && remote.Button.A())
		return true;

	if(params[0].GetInt() == 1 && remote.Button.B())
		return true;
	return false;
}