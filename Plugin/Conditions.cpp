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

	return ButtonState(params[0].GetInt());
}

BOOL ExtObject::ButtonState(int button)
{
	//"A|B|1|2|Home|Up|Down|Left|Right"
	switch(button) {
		case 0:
			return remote.Button.A();
		case 1:
			return remote.Button.B();
		case 2:
			return remote.Button.One();
		case 3:
			return remote.Button.Two();
		case 4:
			return remote.Button.Home();
		case 5:
			return remote.Button.Up();
		case 6:
			return remote.Button.Down();
		case 7:
			return remote.Button.Left();
		case 8:
			return remote.Button.Right();
		default:
			return 0;
	}
}