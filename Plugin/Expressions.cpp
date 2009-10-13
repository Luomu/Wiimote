// Include StdAfx
#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////////////////
// Built-in expressions
//////////////////////////////////////////////////////////////////////////////////

// Return the Default Value.  This is the value to be returned if your object name
// is used without an expression name, eg. in "Counter + 1".
// Parameters can be passed, eg. MyObject(3,7).  You can check ExpReturn::Type() or GetNumParams() to check for overloads.
long ExtObject::ReturnDefaultValue(LPVAL theParams, ExpReturn& ret)
{
	return ret = 0;
}

// Called for undefined expression names, if your extension allows it.
// Eg: MyObject.UndefinedExpression(3,4,5) calls this routine with
// "UndefinedExpression" as the expression name.  OF_UNDEFINEDEXPRESSIONS must be specified in Main.h.
long ExtObject::ReturnUndefinedExpression(CString& expName, LPVAL theParams, ExpReturn& ret)
{
	return ret = 0;
}

//////////////////////////////////////////////////////////////////////////////////
// Expressions
//////////////////////////////////////////////////////////////////////////////////

long ExtObject::eBatteryPercent(LPVAL params, ExpReturn& ret)
{
	return ret = remote.BatteryPercent;
}

long ExtObject::eIrState(LPVAL params, ExpReturn& ret)
{
	if(remote.IR.Mode == wiimote_state::ir::EXTENDED)
		return ret.ReturnString(pRuntime, "Extended");
	else if(remote.IR.Mode == wiimote_state::ir::BASIC)
		return ret.ReturnString(pRuntime, "Basic");
	else
		return ret.ReturnString(pRuntime, "Off");
}

long ExtObject::ePitch(LPVAL params, ExpReturn &ret)
{
	return ret = remote.Acceleration.Orientation.Pitch;
}

long ExtObject::eRoll(LPVAL params, ExpReturn &ret)
{
	return ret = remote.Acceleration.Orientation.Roll;
}

long ExtObject::eOriX(LPVAL params, ExpReturn &ret)
{
	return ret = remote.Acceleration.Orientation.X;
}

long ExtObject::eOriY(LPVAL params, ExpReturn &ret)
{
	return ret = remote.Acceleration.Orientation.Y;
}

long ExtObject::eOriZ(LPVAL params, ExpReturn &ret)
{
	return ret = remote.Acceleration.Orientation.Z;
}

long ExtObject::eAccX(LPVAL params, ExpReturn &ret)
{
	return ret = remote.Acceleration.X;
}

long ExtObject::eAccY(LPVAL params, ExpReturn &ret)
{
	return ret = remote.Acceleration.Y;
}

long ExtObject::eAccZ(LPVAL params, ExpReturn &ret)
{
	return ret = remote.Acceleration.Z;
}