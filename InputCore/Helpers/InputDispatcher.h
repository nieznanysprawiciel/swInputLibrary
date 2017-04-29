#pragma once
/**
@file InputDispatcher.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swInputLibrary/InputCore/IInput.h"


namespace sw {
namespace input
{

/**@brief Provides input events in order of creation.
This class uses timestamp to sort events.*/
class InputDispatcher
{
private:

	std::vector< KeyboardDeviceOPtr >&		m_keyboards;
	std::vector< MouseDeviceOPtr >&			m_mouses;
	std::vector< JoystickDeviceOPtr >&		m_joysticks;

protected:
public:
	explicit		InputDispatcher		( IInput* input );
					~InputDispatcher	() = default;


	DeviceEvent			NextEvent		();


	std::vector< KeyboardDeviceOPtr >&		GetKeyboards	() { return m_keyboards; }
	std::vector< MouseDeviceOPtr >&			GetMouses		() { return m_mouses; }
	std::vector< JoystickDeviceOPtr >&		GetJoysticks	() { return m_joysticks; }
};


//====================================================================================//
//			Inline implementation	
//====================================================================================//


inline		InputDispatcher::InputDispatcher		( IInput* input )
	:	m_keyboards( input->GetKeyboardDevice() )
	,	m_mouses( input->GetMouseDevice() )
	,	m_joysticks( input->GetJoystickDevice() )
{

}

// ================================ //
//
inline DeviceEvent		InputDispatcher::NextEvent()
{
	assert( !"Implement me" );
	return DeviceEvent( KeyEvent() );
}

}	// input
}	// sw

