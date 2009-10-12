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

	ADDPARAMCOMBO("Button", "Remote button", "A|B|1|2|Home|Up|Down|Left|Right");
	ADDCND("Button down", "Buttons", "%o %0 is down", &ExtObject::cButtonDown, "ButtonDown", 0);

	/////////////////////////////
	// Actions
	// Format:
	// ADDCND(List name, Category, Display string, Function address, Script name, Flags)
	ADDPARAM(PARAM_VALUE, "Example parameter", "Here is an example parameter.");
	ADDACT("My action", "My category", "Example action (%0)", &ExtObject::aMyAction, "MyAction", 0);

	ADDACT("Connect", "Connection", "Connect remote", &ExtObject::aConnect, "Connect", 0);
	ADDACT("Disconnect", "Connection", "Disconnect remote", &ExtObject::aDisconnect, "Disconnect", 0);

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
	ADDEXP("Battery level", "Status", "BatteryLevel", &ExtObject::eBatteryPercent, RETURN_INTEGER);

	// This line includes your common ACEs as specified in Main.h
#include "..\Common\CommonAceTable.hpp"
}


