// Controls.h -- helper classes for Construct controls (Jump, brake...)
#ifndef CONTROLS_H
#define CONTROLS_H

#define BUTTONS 13
#define IRDOTS 2
#define WIIBUTTONSTRING "A|B|1|2|Home|Up|Down|Left|Right|Plus|Minus|Nunchuk C|Nunchuk Z"
#define WIIMOTE_PI 3.14159265f
#define RAD_TO_DEGREE(r)	((r * 180.0f) / WIIMOTE_PI)
#define DEGREE_TO_RAD(d)	(d * (WIIMOTE_PI / 180.0f))

namespace Wii {
enum Buttons {
	A,
	B,
	ONE,
	TWO,
	Home,
	Up,
	Down,
	Left,
	Right,
	Plus,
	Minus,
	C,
	Z
};
};

namespace WiiButtonState {
	enum States {
		UP,
		JUST_PRESSED,
		DOWN,
		JUST_RELEASED
	};
};

class Control {
public:
	Control() :
	  control(""),
	  player(0),
	  c(0)
	{}

	Control(int _player, std::string _control, int comboc) :
	  control(_control),
	  player(_player),
      c(comboc)
	{}

	Control(const Control& other) :
	  control(other.control),
	  player(other.player),
	  c(other.c)
	{}

	std::string control;
	int player;
	int c; //combo value
};

class RunControl {
	public:
		RunControl() : control(""), player(0), controller(0), button(Wii::A)  {}

		RunControl(Control& ed, int initController, Wii::Buttons initButton) {
			control = ed.control;
			player = ed.player;
			controller = initController;
			button = initButton;
		}

		RunControl(const RunControl& other) :
			control(other.control),
			player(other.player),
			controller(other.controller),
			button(other.button)
		{}

		std::string control;
		int player;
		int controller;
		Wii::Buttons button;

};

inline int clamp(int x, int a, int b)
{
	return x < a ? a : (x > b ? b : x);
}

inline float clampf(float x, float a, float b)
{
	return x < a ? a : (x > b ? b : x);
}

#endif