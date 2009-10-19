// Runtime.cpp - Runtime implementation of object
//

// Include StdAfx
#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////////////////
// Runtime functions
//////////////////////////////////////////////////////////////////////////////////
#ifdef RUN_ONLY

// ExtObject constructor:
// Only use for class initializer list.  Object initialisation must be done in OnCreate.
// It is not safe to make runtime calls here: do so in OnCreate.
ExtObject::ExtObject(initialObject* editObject, VRuntime* pVRuntime)
: renderer(pVRuntime->pRenderer)
{
	pRuntime = pVRuntime;
	info.editObject = editObject;
}

// This is called just after the constructor when your object has been created.  Construct has set
// up your object here so it is safe to make runtime calls.
void ExtObject::OnCreate()
{
	//int myValue;
	int remoteNumber;
	calcX = 1.f;
	calcY = 1.f;

	// Load the edittime data that was serialized.
	bin ar;
	ar.attach(info.editObject->eData, info.editObject->eSize);

	// Read the data.  Same format as you exported in EditExt::Serialize.
	// Your runtime loader must be able to load all versions!
	int Version = 0;
	ar >> Version;
	//ar >> myValue;
	ar >> remoteNumber;

	//controls
	Control editControl;
	for(int i = 0; i < BUTTONS; i++) {
		ar >> editControl;
		if(editControl.control != "")
			controls.push_back(RunControl(editControl, 0, (Wii::Buttons)i));
		ButtonStates[i] = WiiButtonState::UP;
	}

	// Finished reading data
	ar.detach();

	// Set default dimensions
	info.x = info.editObject->eX;
	info.y = info.editObject->eY;
	info.w = info.editObject->eWidth;
	info.h = info.editObject->eHeight;
	info.angle = 0.0f;

	// Update bounding box
	pRuntime->UpdateBoundingBox(this);
}

// Destructor: called when an instance of your object is destroyed.
ExtObject::~ExtObject()
{
}

// Called every frame, before the events and after drawing, for you to update your object if necessary
// Return 1 (do not call again) or 0 (continue calling)
BOOL ExtObject::OnFrame()
{
	if(!remote.IsConnected())
		return 0;

	/*if(remote.RefreshState() == NO_CHANGE)
		return 0;*/
	remote.RefreshState();

	CalculateIrXY();

	//iterate through controls, set states
	vector<RunControl>::iterator i = controls.begin();
	for(; i!= controls.end(); i++)
	{
		float state = pRuntime->GetControlState(i->control.c_str(), i->player);
		state = max(state, ButtonDown(i->button));
		pRuntime->SetControlState(i->control.c_str(), 0, state);
		debugLastAction = i->control;
	}

	for(int i = 0; i < BUTTONS; i++)
		UpdateButtonState(i);
	return 0;
}

// Called every frame, after the events and before drawing, for you to update your object if necessary
// Return 1 (do not call again) or 0 (continue calling)
// It is not safe to destroy objects in OnFrame2().  If you have to do this, use OnFrame().
// If you are storing any pointers to CRunObjects, check the info.destroying flag here.  If it is true,
// you must reset the pointer to NULL as it is no longer valid.
BOOL ExtObject::OnFrame2()
{
	return 1;	// Do not call again
}

// WindowProc:  called when a window message, or WM_COMMAND specifying your window,
// is sent to Construct.  You must call RegisterWindow() before Construct will send
// you messages for the given window.
LRESULT ExtObject::WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, uMessage, wParam, lParam);
}

BOOL ExtObject::PreTranslateMessage(MSG* msg)
{
	return 0;
}

// For global objects
void ExtObject::OnFrameChange(int oldFrame, int newFrame)
{
	// Do anything your global object needs when the frame changes
	// oldFrame is -1 on start of app, newFrame is -1 on end of app
}

// User defined functions
long ExtObject::GetData(int id, void* param)
{
	return 0;
}

long ExtObject::CallFunction(int id, void* param)
{
	return 0;
}

void ExtObject::UpdateButtonState(const int button) {
	if(ButtonDown(button)) {
		if(ButtonStates[button] == WiiButtonState::UP) {
			ButtonStates[button] = WiiButtonState::JUST_PRESSED;
			return;
		}
		if(ButtonStates[button] == WiiButtonState::JUST_PRESSED) {
			ButtonStates[button] = WiiButtonState::DOWN;
			return;
		}
	} else {
		if(ButtonStates[button] == WiiButtonState::DOWN) {
			ButtonStates[button] = WiiButtonState::JUST_RELEASED;
			return;
		}
		if(ButtonStates[button] == WiiButtonState::JUST_RELEASED) {
			ButtonStates[button] = WiiButtonState::UP;
			return;
		}
	}
}

//Attempt to correct raw x/y values for rotation
void ExtObject::FixIrRotation()
{
	float angle = remote.Acceleration.Orientation.Roll;
	float s, c;
	int x, y;

	if(!angle)
		return;
	
	if(angle != 0) {
		s = sin(DEGREE_TO_RAD(angle));
		c = cos(DEGREE_TO_RAD(angle));

		for(int i = 0; i < 4; i++) {
			wiimote_state::ir::dot* dot = &remote.IR.Dot[i];
			_ASSERT(dot);
			if(!dot->bVisible)
				continue;
			x = dot->RawX - (remote.IR.MAX_RAW_X/2);
			y = dot->RawY - (remote.IR.MAX_RAW_Y/2);

			dot->X = (c * x) + (-s * y);
			dot->Y = (s * x) + (c * y);

			dot->X += (remote.IR.MAX_RAW_X/2);
			dot->Y += (remote.IR.MAX_RAW_Y/2);
		}
	}
}

/*
	Things to keep in mind:
	Number of visible leds
	Remote orientation
	Sensor bar position (above/below)
	Aspect ratio
	Maybe use rawX/Y
*/
void ExtObject::CalculateIrXY()
{
	//FixIrRotation();
	calcX = 0.f;
	calcY = 0.f;
	calcZ = 0.f;

	//average values	
	float xtotal = 0.f;
	float ytotal = 0.f;
	int dotcount = 0;

	for(int i=0; i < 4; ++i) {
		if(remote.IR.Dot[i].bVisible) {
			calcX += remote.IR.Dot[i].X;
			calcY += remote.IR.Dot[i].Y;
			calcZ += remote.IR.Dot[i].Size;
			++dotcount;
		}
	}

	if(dotcount) {
		calcX /= dotcount;
		calcY /= dotcount;
		calcZ /= dotcount;
	}
}

#else //ifdef RUN_ONLY

CRunObject* WINAPI RTCreateObject(bin& ar, VRuntime* pRuntime) 
{
	return NULL;
}

void WINAPI RTDestroyObject(ExtObject* object)
{
}

#endif