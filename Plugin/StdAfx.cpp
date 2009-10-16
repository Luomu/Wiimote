// Include StdAfx.h
#include "StdAfx.h"

void EndProperties(int iMode, CVirtualPropItem* item, MicroEdittime* pm)
{
	if (iMode == MODE_INIT) {
		ASSIGN_CSTRING(item->Description, "");
		ASSIGN_CSTRING(item->Label, "");
		ASSIGN_CSTRING(item->Text, "");
		item->Type = -1;	// end
		pm->Proc(item);		// post end to property vector
	}
}

//need this to concat strings
string operator+ (string& s, int& i)
{
	std::stringstream out;
	out << i;
	s.append(out.str());
	return s;
}

//need these to serialize Controls
bin& operator<< (bin& b, const Control& c)
{
	CString controlstring = c.control.c_str();
	b << c.c;
	b << controlstring;
	b << c.player;
	return b;
}

bin& operator>> (bin& b, Control& c)
{
	CString controlstring;
	b >> c.c;
	b >> controlstring;
	b >> c.player;

	c.control = controlstring;
	return b;
}
