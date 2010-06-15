// Include StdAfx.h
#include "StdAfx.h"

#ifdef RUN_ONLY

/////////////////////////////
// RUNTIME serialization
void ExtObject::Serialize(bin& ar)
{
	if (ar.loading) {

		//

	}
	else {

		//

	}
}

#else // RUN_ONLY

/////////////////////////////
// EDITTIME serialization
// Save and load all your object's edittime data here.
// If you change the serialization format after plugin release, change 'Version' and check it while loading.
// You can then use the old serialization routine if 'Version' is still 1, and set new features to their defaults.
// You never need to check 'Version' while saving.
void EditExt::Serialize(bin& ar)
{
	int Version = 3;
	SerializeVersion(ar, Version);

	if(Version < 3)
		return;

	if (ar.loading) {
		ar >> remoteNumber;
		for(int i=0; i < BUTTONS; i++) {
			ar >> controls[i];
		}
		ar >> controllerCombo;

	}
	else {
		ar << remoteNumber;
		for(int i=0; i < BUTTONS; i++) {
			ar << controls[i];
		}
		ar << controllerCombo;

	}
}

#endif // RUN_ONLY