#pragma once

#include "InputDeviceInfo.h"
#include "KeyState.h"


#define MOUSE_STATE_BUTTONS_NUMBER 8

class MouseState
{
public:
	typedef uint16 Timestamp;

	/**@brief Physical buttons.
	
	Enums form BUTTON0 to BUTTON2 are buttons right, left and modle.
	There'ra aliases for them: LEFT_BUTTON, RIGHT_BUTTON, MIDDLE_BUTTON.

	Next numbers means rest of buttons which can exist on mouse device.*/
	enum PHYSICAL_BUTTONS : int8
	{
		BUTTON0 = 0,
		BUTTON1 = 1,
		BUTTON2 = 2,
		BUTTON3 = 3,
		BUTTON4 = 4,
		BUTTON5 = 5,
		BUTTON6 = 6,
		BUTTON7 = 7,
		LEFT_BUTTON = BUTTON0,
		RIGHT_BUTTON = BUTTON1,
		MIDDLE_BUTTON = BUTTON2,

		NONE = 8,
	};

	/**@brief Physical axes of mouse.*/
	enum PHYSICAL_AXES : int8
	{
		X_AXIS = 0,
		Y_AXIS = 1,
		Z_AXIS = 2,
		W_AXIS = 3,
		WHEEL = Z_AXIS
	};


	struct KeyEvent
	{
		KeyState			State;			///< Only up or down state.
		PHYSICAL_BUTTONS	Button;
	};

	struct AxisEvent
	{
		float				Delta;			///< Axis delta.
		PHYSICAL_AXES		Axis;
	};


	struct CursorEvent
	{
		short				OffsetX;
		short				OffsetY;
	};

	/**@brief Key states changed events.*/
	struct Event
	{
		union
		{
			KeyEvent		Key;
			AxisEvent		Axis;
			CursorEvent		Cursor;
		}				InputData;
		Timestamp		LogicalTime;	///< You can compare this counter with counters in other devices, to compare events order.
										///< This doesn't work between frames.
		
	};


private:

	InputDeviceInfo		m_info;

	float				m_axes[ 4 ];
	short				m_position[ 2 ];	///< Wspó³rzêdne X i Y.
	KeyState			m_buttons[ MOUSE_STATE_BUTTONS_NUMBER ];

public:
	MouseState();
	~MouseState();

	float*						GetAxesState()		{ return m_axes; }
	KeyState*					GetButtonsState()	{ return m_buttons; }

	short						GetPositionX()		{ return m_position[ 0 ]; }
	short						GetPositionY()		{ return m_position[ 1 ]; }

	void						SetPosition			( short X, short Y );

	const InputDeviceInfo&		GetInfo()			{ return m_info; }

	///@name Funkcje do ustawiania stanu (tylko dla dzieci IInput)
	///@{
	void						RemoveEvents	();
	///@}



};

/**@brief */
inline MouseState::MouseState()
{
	for( auto& val : m_axes )
		val = 0.0f;
	for( auto& val : m_buttons )
		val = 0;
}

/**@brief */
inline MouseState::~MouseState()
{ }

/**@brief Ustawia pozycjê myszy.

Powinno byæ u¿ywane jedynie przez modu³ wejœcia (@ref IInput).*/
inline void			MouseState::SetPosition			( short X, short Y )
{
	m_position[ 0 ] = X;
	m_position[ 1 ] = Y;
}

/**@brief Czyœci tablicê z eventów o wciœniêciu klawiszy, ale podtrzymuje stan przycisków.*/
inline void			MouseState::RemoveEvents	()
{
	for( int i = 0; i < MOUSE_STATE_BUTTONS_NUMBER; ++i )
		m_buttons[ i ].HoldState();
}

