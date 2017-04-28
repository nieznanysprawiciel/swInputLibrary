/**
@file WPFInputProxy.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include "WPFInputProxy.h"




namespace sw {
namespace input
{




/**@brief */
WPFInputProxy::WPFInputProxy()
	:	m_lastX( 0 )
	,	m_lastY( 0 )
	,	m_eventNum( 0 )
{}

/**@brief */
WPFInputProxy::~WPFInputProxy()
{}

/**@brief */
bool			WPFInputProxy::Init( const InputInitInfo & initInfo )
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
const std::vector< const KeyboardState* >&	WPFInputProxy::GetKeyboardStates	() const
{
	return m_keyboardsStates;
}

/**@copydoc IInput::GetMouseStates*/
const std::vector< const MouseState* >&		WPFInputProxy::GetMouseStates	() const
{
	return m_mousesStates;
}

/**@copydoc IInput::GetJoystickStates*/
const std::vector< const JoystickState* >&	WPFInputProxy::GetJoystickStates	() const
{
	return m_joysticksStates;
}

/**@copydoc IInput::GetKeyboardDevice*/
std::vector< KeyboardDeviceOPtr >&		WPFInputProxy::GetKeyboardDevice()
{
	return m_keyboards;
}

/**@copydoc IInput::GetMouseDevice*/
std::vector< MouseDeviceOPtr >&			WPFInputProxy::GetMouseDevice()
{
	return m_mouses;
}

/**@copydoc IInput::GetJoystickDevice*/
std::vector< JoystickDeviceOPtr >&		WPFInputProxy::GetJoystickDevice()
{
	return m_joysticks;
}


/**@brief */
std::vector< const InputDeviceInfo* >	WPFInputProxy::GetDevicesInfo		() const
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
void WPFInputProxy::Update( float timeInterval )
{
	m_eventNum = 0;

	//auto& mouse = m_mouses[ 0 ];
	//auto axes = mouse->GetAxesState();

	//axes[ Mouse::PHYSICAL_AXES::X_AXIS ] = static_cast<float>( mouse->GetPositionX() - m_lastX );
	//axes[ Mouse::PHYSICAL_AXES::Y_AXIS ] = static_cast<float>( mouse->GetPositionY() - m_lastY );

	//m_lastX = mouse->GetPositionX();
	//m_lastY = mouse->GetPositionY();
}

/**@copydoc IInput::UpdateDevices

Urz¹dzenie jest zawsze aktualne.*/
bool WPFInputProxy::UpdateDevices()
{
	return true;
}

//====================================================================================//
//			WPF API	
//====================================================================================//

#define NUM_WPF_MOUSE_BUTTONS 5

/**@brief Tablica mapowania przycisków myszy WPFa na wartoœci silnikowe.

namespace System.Windows.Input
{
	public enum MouseButton
	{
		Left = 0,
		Middle = 1,
		Right = 2,
		XButton1 = 3,
		XButton2 = 4
	}
}*/
Mouse::PHYSICAL_BUTTONS MOUSE_BUTTONS_MAPPING[ NUM_WPF_MOUSE_BUTTONS ] =
{
	Mouse::PHYSICAL_BUTTONS::LEFT_BUTTON,
	Mouse::PHYSICAL_BUTTONS::MIDDLE_BUTTON,
	Mouse::PHYSICAL_BUTTONS::RIGHT_BUTTON,
	Mouse::PHYSICAL_BUTTONS::BUTTON3,
	Mouse::PHYSICAL_BUTTONS::BUTTON4
};

#define NUM_WPF_KEYBOARD_BUTTONS 173

/**@brief Tablica mapowania przycisków klawiatury WPFa na wartoœci silnikowe.*/
Keyboard::PHYSICAL_KEYS KEYBOARD_BUTTONS_MAPPING[ NUM_WPF_KEYBOARD_BUTTONS ] =
{
	Keyboard::PHYSICAL_KEYS::KEY_NONE,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///Cancel
	Keyboard::PHYSICAL_KEYS::KEY_BACK,
	Keyboard::PHYSICAL_KEYS::KEY_TAB,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///LineFeed
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///Clear
	Keyboard::PHYSICAL_KEYS::KEY_RETURN,
	Keyboard::PHYSICAL_KEYS::KEY_PAUSE,
	Keyboard::PHYSICAL_KEYS::KEY_CAPSLOCK,
	Keyboard::PHYSICAL_KEYS::KEY_KANA,		///KanaMode
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///JunjaMode
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///FinalMode
	Keyboard::PHYSICAL_KEYS::KEY_KANJI,
	Keyboard::PHYSICAL_KEYS::KEY_ESCAPE,
	Keyboard::PHYSICAL_KEYS::KEY_CONVERT,
	Keyboard::PHYSICAL_KEYS::KEY_NOCONVERT,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///ImeAccept
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///ImeModeChange
	Keyboard::PHYSICAL_KEYS::KEY_SPACE,
	Keyboard::PHYSICAL_KEYS::KEY_PGUP,
	Keyboard::PHYSICAL_KEYS::KEY_PGDN,
	Keyboard::PHYSICAL_KEYS::KEY_END,
	Keyboard::PHYSICAL_KEYS::KEY_HOME,
	Keyboard::PHYSICAL_KEYS::KEY_LEFT,
	Keyboard::PHYSICAL_KEYS::KEY_UP,
	Keyboard::PHYSICAL_KEYS::KEY_RIGHT,
	Keyboard::PHYSICAL_KEYS::KEY_DOWN,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///Select
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///Print
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///Execute
	Keyboard::PHYSICAL_KEYS::KEY_SYSRQ,	///PrintScreen
	Keyboard::PHYSICAL_KEYS::KEY_INSERT,
	Keyboard::PHYSICAL_KEYS::KEY_DELETE,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///Help
	Keyboard::PHYSICAL_KEYS::KEY_0,
	Keyboard::PHYSICAL_KEYS::KEY_1,
	Keyboard::PHYSICAL_KEYS::KEY_2,
	Keyboard::PHYSICAL_KEYS::KEY_3,
	Keyboard::PHYSICAL_KEYS::KEY_4,
	Keyboard::PHYSICAL_KEYS::KEY_5,
	Keyboard::PHYSICAL_KEYS::KEY_6,
	Keyboard::PHYSICAL_KEYS::KEY_7,
	Keyboard::PHYSICAL_KEYS::KEY_8,
	Keyboard::PHYSICAL_KEYS::KEY_9,
	Keyboard::PHYSICAL_KEYS::KEY_A,
	Keyboard::PHYSICAL_KEYS::KEY_B,
	Keyboard::PHYSICAL_KEYS::KEY_C,
	Keyboard::PHYSICAL_KEYS::KEY_D,
	Keyboard::PHYSICAL_KEYS::KEY_E,
	Keyboard::PHYSICAL_KEYS::KEY_F,
	Keyboard::PHYSICAL_KEYS::KEY_G,
	Keyboard::PHYSICAL_KEYS::KEY_H,
	Keyboard::PHYSICAL_KEYS::KEY_I,
	Keyboard::PHYSICAL_KEYS::KEY_J,
	Keyboard::PHYSICAL_KEYS::KEY_K,
	Keyboard::PHYSICAL_KEYS::KEY_L,
	Keyboard::PHYSICAL_KEYS::KEY_M,
	Keyboard::PHYSICAL_KEYS::KEY_N,
	Keyboard::PHYSICAL_KEYS::KEY_O,
	Keyboard::PHYSICAL_KEYS::KEY_P,
	Keyboard::PHYSICAL_KEYS::KEY_Q,
	Keyboard::PHYSICAL_KEYS::KEY_R,
	Keyboard::PHYSICAL_KEYS::KEY_S,
	Keyboard::PHYSICAL_KEYS::KEY_T,
	Keyboard::PHYSICAL_KEYS::KEY_U,
	Keyboard::PHYSICAL_KEYS::KEY_V,
	Keyboard::PHYSICAL_KEYS::KEY_W,
	Keyboard::PHYSICAL_KEYS::KEY_X,
	Keyboard::PHYSICAL_KEYS::KEY_Y,
	Keyboard::PHYSICAL_KEYS::KEY_Z,
	Keyboard::PHYSICAL_KEYS::KEY_LWIN,
	Keyboard::PHYSICAL_KEYS::KEY_RWIN,
	Keyboard::PHYSICAL_KEYS::KEY_APPS,
	Keyboard::PHYSICAL_KEYS::KEY_SLEEP,
	Keyboard::PHYSICAL_KEYS::KEY_NUMPAD0,
	Keyboard::PHYSICAL_KEYS::KEY_NUMPAD1,
	Keyboard::PHYSICAL_KEYS::KEY_NUMPAD2,
	Keyboard::PHYSICAL_KEYS::KEY_NUMPAD3,
	Keyboard::PHYSICAL_KEYS::KEY_NUMPAD4,
	Keyboard::PHYSICAL_KEYS::KEY_NUMPAD5,
	Keyboard::PHYSICAL_KEYS::KEY_NUMPAD6,
	Keyboard::PHYSICAL_KEYS::KEY_NUMPAD7,
	Keyboard::PHYSICAL_KEYS::KEY_NUMPAD8,
	Keyboard::PHYSICAL_KEYS::KEY_NUMPAD9,
	Keyboard::PHYSICAL_KEYS::KEY_MULTIPLY,
	Keyboard::PHYSICAL_KEYS::KEY_ADD,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///Separator
	Keyboard::PHYSICAL_KEYS::KEY_SUBTRACT,
	Keyboard::PHYSICAL_KEYS::KEY_DECIMAL,
	Keyboard::PHYSICAL_KEYS::KEY_DIVIDE,
	Keyboard::PHYSICAL_KEYS::KEY_F1,
	Keyboard::PHYSICAL_KEYS::KEY_F2,
	Keyboard::PHYSICAL_KEYS::KEY_F3,
	Keyboard::PHYSICAL_KEYS::KEY_F4,
	Keyboard::PHYSICAL_KEYS::KEY_F5,
	Keyboard::PHYSICAL_KEYS::KEY_F6,
	Keyboard::PHYSICAL_KEYS::KEY_F7,
	Keyboard::PHYSICAL_KEYS::KEY_F8,
	Keyboard::PHYSICAL_KEYS::KEY_F9,
	Keyboard::PHYSICAL_KEYS::KEY_F10,
	Keyboard::PHYSICAL_KEYS::KEY_F11,
	Keyboard::PHYSICAL_KEYS::KEY_F12,
	Keyboard::PHYSICAL_KEYS::KEY_F13,
	Keyboard::PHYSICAL_KEYS::KEY_F14,
	Keyboard::PHYSICAL_KEYS::KEY_F15,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///F16
	Keyboard::PHYSICAL_KEYS::KEY_NONE,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///F24
	Keyboard::PHYSICAL_KEYS::KEY_NUMLOCK,
	Keyboard::PHYSICAL_KEYS::KEY_SCROLL,
	Keyboard::PHYSICAL_KEYS::KEY_LSHIFT,
	Keyboard::PHYSICAL_KEYS::KEY_RSHIFT,
	Keyboard::PHYSICAL_KEYS::KEY_LCONTROL,
	Keyboard::PHYSICAL_KEYS::KEY_RCONTROL,
	Keyboard::PHYSICAL_KEYS::KEY_LALT,
	Keyboard::PHYSICAL_KEYS::KEY_RALT,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///BrowserBack
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///BrowserForward
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///BrowserRefresh
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///BrowserStop
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///BrowserSearch
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///BrowserFavorites
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///BrowserHome
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///VolumeMute
	Keyboard::PHYSICAL_KEYS::KEY_VOLUMEDOWN,
	Keyboard::PHYSICAL_KEYS::KEY_VOLUMEUP,
	Keyboard::PHYSICAL_KEYS::KEY_NEXTTRACK,
	Keyboard::PHYSICAL_KEYS::KEY_PREVTRACK,
	Keyboard::PHYSICAL_KEYS::KEY_MEDIASTOP,
	Keyboard::PHYSICAL_KEYS::KEY_PLAYPAUSE,
	Keyboard::PHYSICAL_KEYS::KEY_MAIL,
	Keyboard::PHYSICAL_KEYS::KEY_MEDIASELECT,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///LaunchApplication1
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///LaunchApplication2
	Keyboard::PHYSICAL_KEYS::KEY_SEMICOLON,
	Keyboard::PHYSICAL_KEYS::KEY_ADD,		///OEM Plus
	Keyboard::PHYSICAL_KEYS::KEY_COMMA,
	Keyboard::PHYSICAL_KEYS::KEY_SUBTRACT,
	Keyboard::PHYSICAL_KEYS::KEY_PERIOD,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///OEM Question
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///OEM tilde
	Keyboard::PHYSICAL_KEYS::KEY_ABNT_C1,
	Keyboard::PHYSICAL_KEYS::KEY_ABNT_C2,
	Keyboard::PHYSICAL_KEYS::KEY_LBRACKET,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///OEM pipe
	Keyboard::PHYSICAL_KEYS::KEY_RBRACKET,
	Keyboard::PHYSICAL_KEYS::KEY_APOSTROPHE,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///OEM8
	Keyboard::PHYSICAL_KEYS::KEY_BACKSLASH,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///Ime Processed
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///System
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///OEM Attn
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///OEM finish
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///OEM Copy
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///OEM Auto
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///OEM Enlv
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///OEM back tab
	Keyboard::PHYSICAL_KEYS::KEY_NONE,		///OEM attn
	Keyboard::PHYSICAL_KEYS::KEY_NONE,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,
	Keyboard::PHYSICAL_KEYS::KEY_NONE,
	Keyboard::PHYSICAL_KEYS::KEY_NONE
};


/**@brief Ustawia nowy stan przycisku na klawiaturze.

Wpf mo¿e wygenerowaæ eventy o kolejnych wciœniêciach kiedy u¿ytkownik wciœn¹³
i przytrzyma³ przez jakiœ czas klawisz. W takiej sytuacji te eventy s¹ równie¿
dostêpne.*/
void			WPFInputProxy::KeyboardChange		( int keyId, bool pressed )
{
	//auto& keyboard = m_keyboards[ 0 ];
	//auto state = keyboard->KeysState();

	//// Nie u¿ywamy przeci¹¿onego operatora=, poniewa¿ wtedy nie moglibyœmy wy³apywaæ
	//// wielokrotnych wciœnieæ (keystrokes??)
	//if( pressed )
	//	state[ KEYBOARD_BUTTONS_MAPPING[ keyId ] ].Press();
	//else
	//	state[ KEYBOARD_BUTTONS_MAPPING[ keyId ] ].UnPress();

	KeyEvent keyEvent;
	keyEvent.Key = KEYBOARD_BUTTONS_MAPPING[ keyId ];
	keyEvent.State = pressed;
	keyEvent.LogicalTime = m_eventNum++;

	m_keyboards[ 0 ]->AddEvent( keyEvent );
}

/**@brief Ustawia nowy stan przycisku myszy.

@todo W przysz³oœci mo¿e trzeba bêdzie dodaæ informacjê o zmienie stanu.
Móg³by to byæ np któryæ bit ustawiony na 1 czy coœ.*/
void			WPFInputProxy::MouseButtonChange		( int button, bool pressed )
{
	//auto& mouse = m_mouses[ 0 ];
	//auto buttonsState = mouse->GetButtonsState();
	//if( pressed )
	//	buttonsState[ MOUSE_BUTTONS_MAPPING[ button ] ].Press();
	//else
	//	buttonsState[ MOUSE_BUTTONS_MAPPING[ button ] ].UnPress();

	ButtonEvent mouseButtonEvt;
	mouseButtonEvt.Button = MOUSE_BUTTONS_MAPPING[ button ];
	mouseButtonEvt.State = pressed;
	mouseButtonEvt.LogicalTime = m_eventNum++;

	m_mouses[ 0 ]->AddEvent( mouseButtonEvt );
}

/**@brief Ustawia now¹ pozycjê myszy.*/
void			WPFInputProxy::MousePositionChange		( double X, double Y )
{
	//auto& mouse = m_mouses[ 0 ];
	//mouse->SetPosition( (short)X, (short)Y );

	auto& mouse = m_mousesStates[ 0 ];
	
	CursorEvent cursorEvent;
	cursorEvent.OffsetX = (uint16)X - m_lastX;
	cursorEvent.OffsetY = (uint16)Y - m_lastY;
	cursorEvent.LogicalTime = m_eventNum++;

	m_mouses[ 0 ]->AddEvent( cursorEvent );

	m_lastX = (uint16)X;
	m_lastY = (uint16)Y;

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
void			WPFInputProxy::MouseWheelChange			( double delta )
{
	//auto& mouse = m_mouses[ 0 ];
	//mouse->GetAxesState()[ Mouse::PHYSICAL_AXES::WHEEL ] = (float)delta;

	AxisEvent wheel;
	wheel.Delta = (float)delta;
	wheel.Axis = Mouse::PHYSICAL_AXES::WHEEL;
	wheel.LogicalTime = m_eventNum++;

	m_mouses[ 0 ]->AddEvent( DeviceEvent( wheel ) );
}

/**@brief Poniewa¿ okno straci³o focus to czyœcimy stan przycisków i myszy.

@todo Dokoñczyæ*/
void			WPFInputProxy::LostFocus()
{

}

/**@brief Funkcja powinna zostaæ wywo³ana po zakoñczeniu przetwarzania inputu przez aplikacjê.*/
void			WPFInputProxy::PostUpdate()
{
	//MouseWheelChange( 0.0 );

	auto& mouse = m_mouses[ 0 ];
	
	// Zero wheel.
	AxisEvent wheel;
	wheel.Delta = (float)-mouse->GetState().GetAxesState()[ Mouse::PHYSICAL_AXES::WHEEL ];
	wheel.Axis = Mouse::PHYSICAL_AXES::WHEEL;
	wheel.LogicalTime = m_eventNum++;

	m_mouses[ 0 ]->AddEvent( DeviceEvent( wheel ) );

	//for( auto& keyboard : m_keyboards )
	//	keyboard->RemoveEvents();

	//for( auto& mouse : m_mouses )
	//	mouse->RemoveEvents();
}



}	// input
}	// sw
