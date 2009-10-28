// Main.h
// Definitions and classes for the object workings

// Only include once
#ifndef MAIN_H
#define MAIN_H

#define MINIMUM_VERSION	1

// IDE FLAGS
// Can be a combination of:
//OF_NOSIZE	- Extension cannot be resized at edittime
//OF_NODRAW - Extension does not display anything
//OF_ALLOWANGLES - Can be rotated at edittime
//OF_PRIVATEVARIABLES - Uses private variables
//OF_MOVEMENTPLUGIN - Is a movement plugin
//OF_MOVEMENTS - Allow movement plugins to be added
//OF_EFFECTS - Allow display effects
//OF_NOCOMMONDEBUG - Don't show 'Common' field (X/Y/W/H/Angle/Opacity) in debugger
//OF_NODEBUG - Don't show at all in debugger
//OF_UNDEFINEDEXPRESSIONS - Allow ReturnUndefinedExpression to be called
#define IDE_FLAGS 	OF_NOCOMMONDEBUG | OF_NODRAW

#include "..\Common\ExpReturn.hpp"

#include "..\Wiiyourself\wiimote.h"
#include "Controls.h"

#define OBJECTRECT CRect(editObject->objectX, editObject->objectY, editObject->objectX + editObject->objectWidth, editObject->objectY + editObject->objectHeight)

//////////// RUNTIME OBJECT ////////////
// Add any member functions or data you want to this class.
// Your extension inherits CRunObject.  See the definition
// for the default member values you have access to.
class ExtObject : public CRunObject
{
public:
	wiimote remote;
	// Constructor (called when Construct creates the object)
	ExtObject(initialObject* editObject, VRuntime* pVRuntime);
	// Destructor (called when Construct destroys the object)
	~ExtObject();

	IRenderer* const renderer;

	//////////////////////////
	// OnFrame: called once per frame just before Draw() (after the events list)
	// OnFrame2: called once per frame just after Draw() (before the events list)
	BOOL		OnFrame();
	BOOL		OnFrame2();
	// Draw: called when Construct wants you to render your object.
	void		Draw();
	// WindowProc is called if your extension creates a window and calls RegisterWindow().
	LRESULT		WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	BOOL		PreTranslateMessage(MSG* msg);
	// Return default expression editor value and undefined expressions when enabled.
	long		ReturnDefaultValue(LPVAL params, ExpReturn& ret);
	long		ReturnUndefinedExpression(CString& expName, LPVAL params, ExpReturn& ret);
	// Called just after the constructor when your object has been prepared.
	void		OnCreate();
	// Called when a frame changes and your object is global
	void		OnFrameChange(int oldFrame, int newFrame);
	// Called when your object should save/load itself at runtime
	void		Serialize(bin& ar);
	// Data functions
	long		GetData(int id, void* param);
	long		CallFunction(int id, void* param);
	// Debugging
	void		DebuggerUpdateDisplay(ExpStore*& pPrivateVars);
	void		OnDebuggerValueChanged(const char* name, const char* value);

	BOOL		ButtonDown(const int button);
	void		UpdateButtonState(const int button);
	void		FixIrRotation();
	void		CalculateIrXY();
	float		CalculateDistance();

	////////////////////////////////////////////////////
	// ACTIONS, CONDITIONS AND EXPRESSIONS DEFINITIONS
#include "..\Common\CommonAceDecl.hpp"

	long cConnected(LPVAL params);
	long cConnectionLost(LPVAL params);

	long cButtonPressed(LPVAL params);
	long cButtonDown(LPVAL params);
	long cButtonReleased(LPVAL params);

	long aMyAction(LPVAL params);

	long aConnect(LPVAL params);
	long aDisconnect(LPVAL params);
	long aSetReportType(LPVAL params);
	long aSetRumble(LPVAL params);
	long aSetLeds(LPVAL params);

	long eBatteryPercent(LPVAL params, ExpReturn& ret);
	long eReportLevel(LPVAL params, ExpReturn& ret);
	long eLedStatus(LPVAL params, ExpReturn& ret);

	long eAccX(LPVAL params, ExpReturn& ret);
	long eAccY(LPVAL params, ExpReturn& ret);
	long eAccZ(LPVAL params, ExpReturn& ret);

	long ePitch(LPVAL params, ExpReturn& ret);
	long eRoll(LPVAL params, ExpReturn& ret);
	long eOriX(LPVAL params, ExpReturn& ret);
	long eOriY(LPVAL params, ExpReturn& ret);
	long eOriZ(LPVAL params, ExpReturn& ret);

	long eIrX(LPVAL params, ExpReturn& ret);
	long eIrY(LPVAL params, ExpReturn& ret);
	long eIrZ(LPVAL params, ExpReturn& ret);

	long eRawX(LPVAL params, ExpReturn &ret);
	long eRawY(LPVAL params, ExpReturn &ret);

	long eUpdateAge(LPVAL params, ExpReturn &ret);

	//Nunchuk expressions
	long eNunJoyX(LPVAL params, ExpReturn &ret);
	long eNunJoyY(LPVAL params, ExpReturn &ret);
	long eNunPitch(LPVAL params, ExpReturn &ret);
	long eNunRoll(LPVAL params, ExpReturn &ret);
	long eNunAccX(LPVAL params, ExpReturn &ret);
	long eNunAccY(LPVAL params, ExpReturn &ret);
	long eNunAccZ(LPVAL params, ExpReturn &ret);
	long eNunOriX(LPVAL params, ExpReturn &ret);
	long eNunOriY(LPVAL params, ExpReturn &ret);
	long eNunOriZ(LPVAL params, ExpReturn &ret);
	long eNunUpdateAge(LPVAL params, ExpReturn &ret);

	vector<RunControl> controls;

	//calculated, possibley smoothed IR values 0-1.0
	float calcX;
	float calcY;
	float calcZ;

	//debugging stuff
	string debugLastAction;
	int ButtonStates[BUTTONS];

	////////////////////////////////////////////////////
	// Data members

	// Use when private variables (OF_PRIVATEVARIABLES) are enabled.
	//vector<ExpStore> privateVars;
};

//////////// EDITTIME INFO ////////////
class EditExt
{
public:
	///////////////////////////
	// Class data
	EditExt(class VEditTime* pVEditTime, class editInfo* pEInfo);
	~EditExt();

	void Draw();
	int  GetMenuIcons(int ACEMenu);
	void Initialize();
	void OnPut();
	void OnRemoved();
	int  OnShowACEMenu(TABLE ACEType);
	BOOL OnSizeObject();
	void Serialize(bin& ar);
	void OnPropertiesUpdate();
	void GetAnimationHandle(int& handle);

	class VEditTime* pEditTime;	// Pointer to Virtual Edittime
	class editInfo*  pInfo;		// Pointer to object edittime info

	///////////////////////////
	// Your edittime extension data goes here
	int iTexture;		// DX texture

	//int myValue;
	int remoteNumber;
	Control controls[BUTTONS];
	int controllerCombo;
};

//operators to serialize Controls
bin& operator<<(bin& b, const Control& c);
bin& operator>>(bin& b, Control& c);

// Internal stuff include
#include "..\Common\Internal.hpp"
#include "..\Common\Properties.h"

// Only include once
#endif