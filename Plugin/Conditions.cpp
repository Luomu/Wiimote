// Include StdAfx
#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////////////////
// Conditions
//////////////////////////////////////////////////////////////////////////////////

long ExtObject::cMyCondition(LPVAL params)
{
	// Always run
	return true;
}

long ExtObject::cConnected(LPVAL params)
{
	return false;
}

long ExtObject::cConnectionLost(LPVAL params)
{
	if (remote.ConnectionLost())
		return true;
	else
		return false;
}

long ExtObject::cButtonPressed(LPVAL params)
{
	return false;
}