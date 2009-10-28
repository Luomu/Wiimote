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

long ExtObject::cButtonPressed(LPVAL params)
{
	if(!remote.IsConnected())
		return false;

	if(ButtonStates[params[0].GetInt()] == WiiButtonState::JUST_PRESSED)
		return true;

	return false;
}

long ExtObject::cButtonDown(LPVAL params)
{
	if(!remote.IsConnected())
		return false;

	//if button is reported down by hardware and
	//state is not just pressed, report down
	return ButtonDown(params[0].GetInt());
}

long ExtObject::cButtonReleased(LPVAL params)
{
	if(!remote.IsConnected())
		return false;
	
	//if button is not down, but its state is recorded as down
	//it has been released
	if(ButtonStates[params[0].GetInt()] == WiiButtonState::JUST_RELEASED)
		return true;

	return false;
}

//report button down or not
BOOL ExtObject::ButtonDown(const int button)
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
		case 9:
			return remote.Button.Plus();
		case 10:
			return remote.Button.Minus();
		case 11:
			return remote.Nunchuk.C;
		case 12:
			return remote.Nunchuk.Z;
		default:
			return 0;
	}
}

long ExtObject::cNunConnected(LPVAL params, ExpReturn &ret)
{
	return ret = remote.NunchukConnected();
}