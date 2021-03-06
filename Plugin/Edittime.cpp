// Edittime.cpp - Edittime implementation of object
//

// Include StdAfx and Properties.h
#include "StdAfx.h"

#ifndef RUN_ONLY

//////////////////////////////////////////////////////////////////////////////////
// Property table
//////////////////////////////////////////////////////////////////////////////////

// The property table defines the list of properties that appear in the property
// grid when your object is selected in the layout editor.
//
// See the SDK docs for full documentation, but to get you started:-
//
// PROPERTY_EDIT  (myVariable, "Label", "Description");		// A text field property.
// PROPERTY_VALUE (myVariable, "Label 2", "Description");	// An integer property.
// PROPERTY_FLOAT (myVariable, "Label 3", "Description");	// A double/float property
//
// The labels must be unique!

BEGIN_PROPERTY_TABLE();

	PROPERTY_VALUE(remoteNumber, "Remote number", "Remote number (1-4)");
	if(editObject) {
		int count = editObject->pEditTime->GetControlCount();
		string Controls = "-";
		//construct supports 10 players (we only use 1 per plugin instance,
		//selected by remoteNumber
		map<string, int> controlStringToCombo[10];
		vector<Control> comboToControlString;

		controlStringToCombo[0][""] = 0;
		comboToControlString.push_back(Control(0, "",0));

		//build a list of controls
		for(int c = 0; c < count; c++) {
			int controlPlayer = editObject->pEditTime->GetControlPlayer(c);
			string controlName = editObject->pEditTime->GetControlName(c);
			int controlPlayerDisplay = controlPlayer + 1;

			Controls += "|" + controlName + " (" + controlPlayerDisplay + ")";

			//pair control name to a combo index
			controlStringToCombo[controlPlayer][controlName] = c + 1;
			//pair combo index to a control name
			comboToControlString.push_back(Control(controlPlayer, controlName, c + 1));
		}

		if(iMode == MODE_WRITE) {
			for(int i = 0; i < BUTTONS; i++) {
				Control& control = editObject->objectPtr->controls[i];
				if(control.player == -1)
					control.c = 0;
				else
					control.c = controlStringToCombo[control.player][control.control];
			}
		}

		int i = editObject->objectPtr->remoteNumber;

		//"A|B|1|2|Home|Up|Down|Left|Right|Plus|Minus"
		PROPERTY_COMBO(controls[0].c, "A", "", Controls.c_str());
		PROPERTY_COMBO(controls[1].c, "B", "", Controls.c_str());
		PROPERTY_COMBO(controls[2].c, "1", "", Controls.c_str());
		PROPERTY_COMBO(controls[3].c, "2", "", Controls.c_str());
		PROPERTY_COMBO(controls[4].c, "Home", "", Controls.c_str());
		PROPERTY_COMBO(controls[5].c, "Up", "", Controls.c_str());
		PROPERTY_COMBO(controls[6].c, "Down", "", Controls.c_str());
		PROPERTY_COMBO(controls[7].c, "Left", "", Controls.c_str());
		PROPERTY_COMBO(controls[8].c, "Right", "", Controls.c_str());
		PROPERTY_COMBO(controls[9].c, "Plus", "", Controls.c_str());
		PROPERTY_COMBO(controls[10].c, "Minus", "", Controls.c_str());
		PROPERTY_COMBO(controls[11].c, "Nunchuk C", "", Controls.c_str());
		PROPERTY_COMBO(controls[12].c, "Nunchuk Z", "", Controls.c_str());

		if(iMode == MODE_READ) {
			for(int i = 0; i < BUTTONS; i++) {
				Control& control = editObject->objectPtr->controls[i];
				control = comboToControlString[control.c];
			}
		}
	}
	

END_PROPERTY_TABLE  ();


/////////////////////////////////////////////////////////////////////////////////
// Edittime functions
//////////////////////////////////////////////////////////////////////////////////

// Constructor
EditExt::EditExt(VEditTime* pVEditTime, editInfo* pEInfo)
{
	// Store the edittime and einfo pointers
	pEditTime = pVEditTime;
	pInfo = pEInfo;
}

// Destructor: when your object is deleted or the application closed:
// close any allocated resources here
EditExt::~EditExt()
{

}

// Initialization:  when the frame editor is opened.  Create textures, fonts,
// and any other DirectX volatile data here.
void EditExt::Initialize()
{

}

// Called when any property has been changed.
void EditExt::OnPropertiesUpdate()
{
}

// When the object is inserted to the layout editor by the user.
void EditExt::OnPut()
{
	// Default value for the property
	remoteNumber = 1;

	//fill the Control section with defaults
	controls[Wii::A] = Control(0, "Jump",1);
	controls[Wii::Left] = Control(0, "Move Left",2);
	controls[Wii::Right] = Control(0, "Move Right",3);

	controllerCombo = 0;

	// Default object size
	pInfo->objectWidth = 64;
	pInfo->objectHeight = 64;
}


// When the object is removed from the layout editor by the user.
void EditExt::OnRemoved()
{

}

// On object resized
BOOL EditExt::OnSizeObject()
{
	return TRUE;
}

void EditExt::GetAnimationHandle(int& handle)
{
	
}

#else //ifndef RUN_ONLY

BOOL WINAPI ETCreateObject(editInfo* editObject) {return FALSE;}
BOOL WINAPI ETInitializeObject(editInfo* editObject, VEditTime* pVEditTime) {return FALSE;}
BOOL WINAPI ETDestroyObject(editInfo* editObject) {return FALSE;}
int WINAPI ETDrawObject(editInfo *editObject) {return 0;}
void ETOnPropertyChanged(editInfo* editObject) {}
long LinkPropTable() {return 0;}
void WINAPI ETSerialize(editInfo* editObject, bin& ar) {}
void WINAPI ETPutObject(editInfo* editObject) {}
void WINAPI ETRemoveObject(editInfo* editObject) {}
void WINAPI GetInfo(LPOINFO objectInfo) {}
int WINAPI ETGetMenuIcons(editInfo* editObject, int ACEMenu) {return 0;}
int WINAPI ETShowACEMenu(editInfo* editObject, TABLE ACEType)  {return 0;}
BOOL WINAPI ETSizeObject(editInfo* editObject)  {return FALSE;}

#endif // RUN_ONLY