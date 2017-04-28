#include "WinApiInputProxy.h"
#include <Windowsx.h>


namespace sw {
namespace input
{



/**@brief */
WinApiInputProxy::WinApiInputProxy()
	:	m_lastX( 0 )
	,	m_lastY( 0 )
	,	m_eventNum( 0 )
{}

/**@brief */
WinApiInputProxy::~WinApiInputProxy()
{}

/**@brief */
bool WinApiInputProxy::Init( const InputInitInfo & initInfo )
{
	m_keyboards.push_back( KeyboardDeviceOPtr( new KeyboardDevice() ) );
	m_mouses.push_back( MouseDeviceOPtr( new MouseDevice() ) );
	m_joysticks.push_back( JoystickDeviceOPtr( new JoystickDevice() ) );

	m_keyboardsStates.push_back( &m_keyboards[ 0 ]->GetState() );
	m_mousesStates.push_back( &m_mouses[ 0 ]->GetState() );
	m_joysticksStates.push_back( &m_joysticks[ 0 ]->GetState() );

	return true;
}


/**@copydoc IInput::GetKeyboardStates*/
const std::vector< const KeyboardState* >&	WinApiInputProxy::GetKeyboardStates	() const
{
	return m_keyboardsStates;
}

/**@copydoc IInput::GetMouseStates*/
const std::vector< const MouseState* >&		WinApiInputProxy::GetMouseStates	() const
{
	return m_mousesStates;
}

/**@copydoc IInput::GetJoystickStates*/
const std::vector< const JoystickState* >&	WinApiInputProxy::GetJoystickStates	() const
{
	return m_joysticksStates;
}

/**@copydoc IInput::GetKeyboardDevice*/
std::vector< KeyboardDeviceOPtr >&		WinApiInputProxy::GetKeyboardDevice	()
{
	return m_keyboards;
}

/**@copydoc IInput::GetMouseDevice*/
std::vector< MouseDeviceOPtr >&			WinApiInputProxy::GetMouseDevice	()
{
	return m_mouses;
}

/**@copydoc IInput::GetJoystickDevice*/
std::vector< JoystickDeviceOPtr >&		WinApiInputProxy::GetJoystickDevice	()
{
	return m_joysticks;
}


/**@brief */
std::vector< const InputDeviceInfo* >	WinApiInputProxy::GetDevicesInfo	() const
{
	std::vector< const InputDeviceInfo* > infos;
	for( auto& device : m_keyboards )
		infos.push_back( &device->GetInfo() );
	for( auto& device : m_joysticks )
		infos.push_back( &device->GetInfo() );
	for( auto& device : m_mouses )
		infos.push_back( &device->GetInfo() );

	return infos;
}

/**@copydoc IInput::Update

Funkcja zapisuje pozycjê myszy z ostatniej klatki, ¿eby j¹ przerobiæ na informacjê o zmianach na osiach myszy.
WPF dostarcza tylko informacjê o po³o¿eniu myszy wzglêdem okna podgl¹du renderowania. Z tego przesuniêcie na osiach
trzeba sobie stworzyæ samemu.*/
void		WinApiInputProxy::Update( float timeInterval )
{
	m_eventNum = 0;

	//for( auto& keyboard : m_keyboards )
	//	keyboard->RemoveEvents();

	//for( auto& mouse : m_mouses )
	//	mouse->RemoveEvents();
}

/**@copydoc IInput::UpdateDevices

Urz¹dzenie jest zawsze aktualne.*/
bool		WinApiInputProxy::UpdateDevices()
{
	return true;
}

//====================================================================================//
//			WPF API	
//====================================================================================//

#define NUM_WINAPI_MOUSE_BUTTONS 7

/**@brief Tablica mapowania przycisków myszy WinApi na wartoœci silnikowe.*/
Mouse::PHYSICAL_BUTTONS MOUSE_BUTTONS_MAPPING[ NUM_WINAPI_MOUSE_BUTTONS ] =
{
	Mouse::PHYSICAL_BUTTONS::NONE,
	Mouse::PHYSICAL_BUTTONS::LEFT_BUTTON,
	Mouse::PHYSICAL_BUTTONS::RIGHT_BUTTON,
	Mouse::PHYSICAL_BUTTONS::NONE,
	Mouse::PHYSICAL_BUTTONS::MIDDLE_BUTTON,
	Mouse::PHYSICAL_BUTTONS::BUTTON3,
	Mouse::PHYSICAL_BUTTONS::BUTTON4
};

#define NUM_WINAPI_KEYBOARD_BUTTONS 173

/**@brief Tablica mapowania przycisków klawiatury WinApi na wartoœci silnikowe.*/
Keyboard::PHYSICAL_KEYS KEYBOARD_BUTTONS_MAPPING[ NUM_WINAPI_KEYBOARD_BUTTONS ] ={};	// Inicjujemy zerami, które przypadkowo s¹ równie¿ wartoœci¹ Keyboard::PHYSICAL_KEYS::KEY_NONE

// To jest odrobinê wygodniejsza metoda inicjalizowania, poniewa¿ nie trzeba wype³niaæ wszystkich miejsc od razu.
bool ArrayStaticInitializerFun()
{
	KEYBOARD_BUTTONS_MAPPING[ VK_BACK ]		= Keyboard::PHYSICAL_KEYS::KEY_BACKSPACE;
	KEYBOARD_BUTTONS_MAPPING[ VK_TAB ]		= Keyboard::PHYSICAL_KEYS::KEY_TAB;
	KEYBOARD_BUTTONS_MAPPING[ VK_RETURN ]	= Keyboard::PHYSICAL_KEYS::KEY_RETURN;
	KEYBOARD_BUTTONS_MAPPING[ VK_SHIFT ]	= Keyboard::PHYSICAL_KEYS::KEY_LSHIFT;		// ??
	KEYBOARD_BUTTONS_MAPPING[ VK_CONTROL ]	= Keyboard::PHYSICAL_KEYS::KEY_LCONTROL;	// ?? Left control and right control
	KEYBOARD_BUTTONS_MAPPING[ VK_MENU ]		= Keyboard::PHYSICAL_KEYS::KEY_LALT;		// ??
	KEYBOARD_BUTTONS_MAPPING[ VK_PAUSE ]	= Keyboard::PHYSICAL_KEYS::KEY_PAUSE;
	KEYBOARD_BUTTONS_MAPPING[ VK_CAPITAL ]	= Keyboard::PHYSICAL_KEYS::KEY_CAPSLOCK;
	KEYBOARD_BUTTONS_MAPPING[ VK_ESCAPE ]	= Keyboard::PHYSICAL_KEYS::KEY_ESCAPE;
	KEYBOARD_BUTTONS_MAPPING[ VK_SPACE ]	= Keyboard::PHYSICAL_KEYS::KEY_SPACE;
	KEYBOARD_BUTTONS_MAPPING[ VK_PRIOR ]	= Keyboard::PHYSICAL_KEYS::KEY_PAGEUP;
	KEYBOARD_BUTTONS_MAPPING[ VK_NEXT ]		= Keyboard::PHYSICAL_KEYS::KEY_PAGEDOWN;
	KEYBOARD_BUTTONS_MAPPING[ VK_END ]		= Keyboard::PHYSICAL_KEYS::KEY_END;
	KEYBOARD_BUTTONS_MAPPING[ VK_HOME ]		= Keyboard::PHYSICAL_KEYS::KEY_HOME;
	KEYBOARD_BUTTONS_MAPPING[ VK_LEFT ]		= Keyboard::PHYSICAL_KEYS::KEY_LEFTARROW;
	KEYBOARD_BUTTONS_MAPPING[ VK_UP ]		= Keyboard::PHYSICAL_KEYS::KEY_UP;
	KEYBOARD_BUTTONS_MAPPING[ VK_RIGHT ]	= Keyboard::PHYSICAL_KEYS::KEY_RIGHT;
	KEYBOARD_BUTTONS_MAPPING[ VK_DOWN ]		= Keyboard::PHYSICAL_KEYS::KEY_DOWN;
	KEYBOARD_BUTTONS_MAPPING[ VK_SNAPSHOT ]	= Keyboard::PHYSICAL_KEYS::KEY_PRINTSCREEN;
	KEYBOARD_BUTTONS_MAPPING[ VK_INSERT ]	= Keyboard::PHYSICAL_KEYS::KEY_INSERT;
	KEYBOARD_BUTTONS_MAPPING[ VK_DELETE ]	= Keyboard::PHYSICAL_KEYS::KEY_DELETE;

	KEYBOARD_BUTTONS_MAPPING[ '0' ]	= Keyboard::PHYSICAL_KEYS::KEY_0;
	KEYBOARD_BUTTONS_MAPPING[ '1' ]	= Keyboard::PHYSICAL_KEYS::KEY_1;
	KEYBOARD_BUTTONS_MAPPING[ '2' ]	= Keyboard::PHYSICAL_KEYS::KEY_2;
	KEYBOARD_BUTTONS_MAPPING[ '3' ]	= Keyboard::PHYSICAL_KEYS::KEY_3;
	KEYBOARD_BUTTONS_MAPPING[ '4' ]	= Keyboard::PHYSICAL_KEYS::KEY_4;
	KEYBOARD_BUTTONS_MAPPING[ '5' ]	= Keyboard::PHYSICAL_KEYS::KEY_5;
	KEYBOARD_BUTTONS_MAPPING[ '6' ]	= Keyboard::PHYSICAL_KEYS::KEY_6;
	KEYBOARD_BUTTONS_MAPPING[ '7' ]	= Keyboard::PHYSICAL_KEYS::KEY_7;
	KEYBOARD_BUTTONS_MAPPING[ '8' ]	= Keyboard::PHYSICAL_KEYS::KEY_8;
	KEYBOARD_BUTTONS_MAPPING[ '9' ]	= Keyboard::PHYSICAL_KEYS::KEY_9;

	KEYBOARD_BUTTONS_MAPPING[ 'A' ]	= Keyboard::PHYSICAL_KEYS::KEY_A;
	KEYBOARD_BUTTONS_MAPPING[ 'B' ]	= Keyboard::PHYSICAL_KEYS::KEY_B;
	KEYBOARD_BUTTONS_MAPPING[ 'C' ]	= Keyboard::PHYSICAL_KEYS::KEY_C;
	KEYBOARD_BUTTONS_MAPPING[ 'D' ]	= Keyboard::PHYSICAL_KEYS::KEY_D;
	KEYBOARD_BUTTONS_MAPPING[ 'E' ]	= Keyboard::PHYSICAL_KEYS::KEY_E;
	KEYBOARD_BUTTONS_MAPPING[ 'F' ]	= Keyboard::PHYSICAL_KEYS::KEY_F;
	KEYBOARD_BUTTONS_MAPPING[ 'G' ]	= Keyboard::PHYSICAL_KEYS::KEY_G;
	KEYBOARD_BUTTONS_MAPPING[ 'H' ]	= Keyboard::PHYSICAL_KEYS::KEY_H;
	KEYBOARD_BUTTONS_MAPPING[ 'I' ]	= Keyboard::PHYSICAL_KEYS::KEY_I;
	KEYBOARD_BUTTONS_MAPPING[ 'J' ]	= Keyboard::PHYSICAL_KEYS::KEY_J;
	KEYBOARD_BUTTONS_MAPPING[ 'K' ]	= Keyboard::PHYSICAL_KEYS::KEY_K;
	KEYBOARD_BUTTONS_MAPPING[ 'L' ]	= Keyboard::PHYSICAL_KEYS::KEY_L;
	KEYBOARD_BUTTONS_MAPPING[ 'M' ]	= Keyboard::PHYSICAL_KEYS::KEY_M;
	KEYBOARD_BUTTONS_MAPPING[ 'N' ]	= Keyboard::PHYSICAL_KEYS::KEY_N;
	KEYBOARD_BUTTONS_MAPPING[ 'O' ]	= Keyboard::PHYSICAL_KEYS::KEY_O;
	KEYBOARD_BUTTONS_MAPPING[ 'P' ]	= Keyboard::PHYSICAL_KEYS::KEY_P;
	KEYBOARD_BUTTONS_MAPPING[ 'Q' ]	= Keyboard::PHYSICAL_KEYS::KEY_Q;
	KEYBOARD_BUTTONS_MAPPING[ 'R' ]	= Keyboard::PHYSICAL_KEYS::KEY_R;
	KEYBOARD_BUTTONS_MAPPING[ 'S' ]	= Keyboard::PHYSICAL_KEYS::KEY_S;
	KEYBOARD_BUTTONS_MAPPING[ 'T' ]	= Keyboard::PHYSICAL_KEYS::KEY_T;
	KEYBOARD_BUTTONS_MAPPING[ 'U' ]	= Keyboard::PHYSICAL_KEYS::KEY_U;
	KEYBOARD_BUTTONS_MAPPING[ 'W' ]	= Keyboard::PHYSICAL_KEYS::KEY_W;
	KEYBOARD_BUTTONS_MAPPING[ 'X' ]	= Keyboard::PHYSICAL_KEYS::KEY_X;
	KEYBOARD_BUTTONS_MAPPING[ 'Y' ]	= Keyboard::PHYSICAL_KEYS::KEY_Y;
	KEYBOARD_BUTTONS_MAPPING[ 'Z' ]	= Keyboard::PHYSICAL_KEYS::KEY_Z;

	KEYBOARD_BUTTONS_MAPPING[ VK_LWIN ]		= Keyboard::PHYSICAL_KEYS::KEY_LWIN;
	KEYBOARD_BUTTONS_MAPPING[ VK_RWIN ]		= Keyboard::PHYSICAL_KEYS::KEY_RWIN;
	KEYBOARD_BUTTONS_MAPPING[ VK_APPS ]		= Keyboard::PHYSICAL_KEYS::KEY_APPS;
	KEYBOARD_BUTTONS_MAPPING[ VK_SLEEP ]	= Keyboard::PHYSICAL_KEYS::KEY_SLEEP;

	KEYBOARD_BUTTONS_MAPPING[ VK_NUMPAD0 ]	= Keyboard::PHYSICAL_KEYS::KEY_NUMPAD0;
	KEYBOARD_BUTTONS_MAPPING[ VK_NUMPAD1 ]	= Keyboard::PHYSICAL_KEYS::KEY_NUMPAD1;
	KEYBOARD_BUTTONS_MAPPING[ VK_NUMPAD2 ]	= Keyboard::PHYSICAL_KEYS::KEY_NUMPAD2;
	KEYBOARD_BUTTONS_MAPPING[ VK_NUMPAD3 ]	= Keyboard::PHYSICAL_KEYS::KEY_NUMPAD3;
	KEYBOARD_BUTTONS_MAPPING[ VK_NUMPAD4 ]	= Keyboard::PHYSICAL_KEYS::KEY_NUMPAD4;
	KEYBOARD_BUTTONS_MAPPING[ VK_NUMPAD5 ]	= Keyboard::PHYSICAL_KEYS::KEY_NUMPAD5;
	KEYBOARD_BUTTONS_MAPPING[ VK_NUMPAD6 ]	= Keyboard::PHYSICAL_KEYS::KEY_NUMPAD6;
	KEYBOARD_BUTTONS_MAPPING[ VK_NUMPAD7 ]	= Keyboard::PHYSICAL_KEYS::KEY_NUMPAD7;
	KEYBOARD_BUTTONS_MAPPING[ VK_NUMPAD8 ]	= Keyboard::PHYSICAL_KEYS::KEY_NUMPAD8;
	KEYBOARD_BUTTONS_MAPPING[ VK_NUMPAD9 ]	= Keyboard::PHYSICAL_KEYS::KEY_NUMPAD9;

	KEYBOARD_BUTTONS_MAPPING[ VK_MULTIPLY ]	= Keyboard::PHYSICAL_KEYS::KEY_MULTIPLY;
	KEYBOARD_BUTTONS_MAPPING[ VK_ADD ]		= Keyboard::PHYSICAL_KEYS::KEY_ADD;
	KEYBOARD_BUTTONS_MAPPING[ VK_SUBTRACT ]	= Keyboard::PHYSICAL_KEYS::KEY_SUBTRACT;
	KEYBOARD_BUTTONS_MAPPING[ VK_DECIMAL ]	= Keyboard::PHYSICAL_KEYS::KEY_DECIMAL;
	KEYBOARD_BUTTONS_MAPPING[ VK_DIVIDE ]	= Keyboard::PHYSICAL_KEYS::KEY_DIVIDE;

	KEYBOARD_BUTTONS_MAPPING[ VK_F1 ]		= Keyboard::PHYSICAL_KEYS::KEY_F1;
	KEYBOARD_BUTTONS_MAPPING[ VK_F2 ]		= Keyboard::PHYSICAL_KEYS::KEY_F2;
	KEYBOARD_BUTTONS_MAPPING[ VK_F3 ]		= Keyboard::PHYSICAL_KEYS::KEY_F3;
	KEYBOARD_BUTTONS_MAPPING[ VK_F4 ]		= Keyboard::PHYSICAL_KEYS::KEY_F4;
	KEYBOARD_BUTTONS_MAPPING[ VK_F5 ]		= Keyboard::PHYSICAL_KEYS::KEY_F5;
	KEYBOARD_BUTTONS_MAPPING[ VK_F6 ]		= Keyboard::PHYSICAL_KEYS::KEY_F6;
	KEYBOARD_BUTTONS_MAPPING[ VK_F7 ]		= Keyboard::PHYSICAL_KEYS::KEY_F7;
	KEYBOARD_BUTTONS_MAPPING[ VK_F8 ]		= Keyboard::PHYSICAL_KEYS::KEY_F8;
	KEYBOARD_BUTTONS_MAPPING[ VK_F9 ]		= Keyboard::PHYSICAL_KEYS::KEY_F9;
	KEYBOARD_BUTTONS_MAPPING[ VK_F10 ]		= Keyboard::PHYSICAL_KEYS::KEY_F10;
	KEYBOARD_BUTTONS_MAPPING[ VK_F11 ]		= Keyboard::PHYSICAL_KEYS::KEY_F11;
	KEYBOARD_BUTTONS_MAPPING[ VK_F12 ]		= Keyboard::PHYSICAL_KEYS::KEY_F12;
	KEYBOARD_BUTTONS_MAPPING[ VK_F13 ]		= Keyboard::PHYSICAL_KEYS::KEY_F13;
	KEYBOARD_BUTTONS_MAPPING[ VK_F14 ]		= Keyboard::PHYSICAL_KEYS::KEY_F14;
	KEYBOARD_BUTTONS_MAPPING[ VK_F15 ]		= Keyboard::PHYSICAL_KEYS::KEY_F15;

	KEYBOARD_BUTTONS_MAPPING[ VK_NUMLOCK ]	= Keyboard::PHYSICAL_KEYS::KEY_NUMLOCK;
	KEYBOARD_BUTTONS_MAPPING[ VK_SCROLL ]	= Keyboard::PHYSICAL_KEYS::KEY_SCROLL;
	KEYBOARD_BUTTONS_MAPPING[ VK_LCONTROL ]	= Keyboard::PHYSICAL_KEYS::KEY_LCONTROL;
	KEYBOARD_BUTTONS_MAPPING[ VK_RCONTROL ]	= Keyboard::PHYSICAL_KEYS::KEY_RCONTROL;

	KEYBOARD_BUTTONS_MAPPING[ VK_LMENU ]	= Keyboard::PHYSICAL_KEYS::KEY_LMENU;
	KEYBOARD_BUTTONS_MAPPING[ VK_RMENU ]	= Keyboard::PHYSICAL_KEYS::KEY_RMENU;
	KEYBOARD_BUTTONS_MAPPING[ VK_RSHIFT ]	= Keyboard::PHYSICAL_KEYS::KEY_RSHIFT;
	KEYBOARD_BUTTONS_MAPPING[ VK_LSHIFT ]	= Keyboard::PHYSICAL_KEYS::KEY_LSHIFT;

	KEYBOARD_BUTTONS_MAPPING[ VK_RSHIFT ]	= Keyboard::PHYSICAL_KEYS::KEY_RSHIFT;

	return false;
}
static bool arrayStaticInitializer = ArrayStaticInitializerFun();



/**@brief Ustawia nowy stan przycisku na klawiaturze.

@todo W przysz³oœci mo¿e trzeba bêdzie dodaæ informacjê o zmienie stanu.
Móg³by to byæ np któryæ bit ustawiony na 1 czy coœ.*/
void			WinApiInputProxy::KeyboardChange		( int keyId, bool pressed )
{
	KeyEvent keyEvent;
	keyEvent.Key = KEYBOARD_BUTTONS_MAPPING[ keyId ];
	keyEvent.State = pressed;
	keyEvent.LogicalTime = m_eventNum++;

	m_keyboards[ 0 ]->AddEvent( keyEvent );
}


/**@brief Ustawia nowy stan przycisku myszy.

@todo W przysz³oœci mo¿e trzeba bêdzie dodaæ informacjê o zmienie stanu.
Móg³by to byæ np któryæ bit ustawiony na 1 czy coœ.*/
void			WinApiInputProxy::MouseButtonChange		( int button, bool pressed )
{
	ButtonEvent mouseButtonEvt;
	mouseButtonEvt.Button = MOUSE_BUTTONS_MAPPING[ button ];
	mouseButtonEvt.State = pressed;
	mouseButtonEvt.LogicalTime = m_eventNum++;

	m_mouses[ 0 ]->AddEvent( mouseButtonEvt );
}

/**@brief Ustawia now¹ pozycjê myszy.*/
void			WinApiInputProxy::MousePositionChange	( short X, short Y )
{
	auto& mouse = m_mousesStates[ 0 ];
	
	CursorEvent cursorEvent;
	cursorEvent.OffsetX = X - m_lastX;
	cursorEvent.OffsetY = Y - m_lastY;
	cursorEvent.LogicalTime = m_eventNum++;

	m_mouses[ 0 ]->AddEvent( cursorEvent );

	m_lastX = X;
	m_lastY = Y;

	// Change in mouse position is translated into axis change.
	// Theoretically it's the same event but better give it a new number.
	AxisEvent cursorAxisX;
	cursorAxisX.LogicalTime = m_eventNum++;
	cursorAxisX.Delta = cursorEvent.OffsetX;
	cursorAxisX.Axis = Mouse::PHYSICAL_AXES::X_AXIS;

	m_mouses[ 0 ]->AddEvent( cursorAxisX );

	AxisEvent cursorAxisY;
	cursorAxisY.LogicalTime = m_eventNum++;
	cursorAxisY.Delta = cursorEvent.OffsetY;
	cursorAxisY.Axis = Mouse::PHYSICAL_AXES::Y_AXIS;

	m_mouses[ 0 ]->AddEvent( cursorAxisY );
}

/**@brief Ustawia przesuniêcie kó³ka myszy.*/
void			WinApiInputProxy::MouseWheelChange		( double delta )
{
	AxisEvent wheel;
	wheel.Delta = (float)delta;
	wheel.Axis = Mouse::PHYSICAL_AXES::WHEEL;
	wheel.LogicalTime = m_eventNum++;

	m_mouses[ 0 ]->AddEvent( DeviceEvent( wheel ) );
}

/**@brief Poniewa¿ okno straci³o focus to czyœcimy stan przycisków i myszy.

@todo Dokoñczyæ*/
void			WinApiInputProxy::LostFocus()
{

}

/**@brief Funkcja uzupe³nia stan klasy bezpoœrednio na podstawie komunikatów z WinAPI.

Je¿eli siê u¿ywa tej funkcji nie nale¿y ju¿ wywo³ywaæ pozosta³ych funkcji.*/
void			WinApiInputProxy::HandleEvent			( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if( message == WM_MOUSEMOVE )
	{
		int xPos = GET_X_LPARAM( lParam );
		int yPos = GET_Y_LPARAM( lParam );
		MousePositionChange( xPos, yPos );
	}
	else if( message == WM_KEYDOWN )
	{
		if( wParam <= VK_XBUTTON2 )
			MouseButtonChange( (int)wParam, true );
		KeyboardChange( (int)wParam, true );
	}
	else if( message == WM_KEYUP )
	{
		if( wParam <= VK_XBUTTON2 )
			MouseButtonChange( (int)wParam, false );
		KeyboardChange( (int)wParam, false );
	}
	else if( message == WM_MOUSEWHEEL )
	{
		MouseWheelChange( GET_WHEEL_DELTA_WPARAM( wParam ) );
	}
}



}	// input
}	// sw

