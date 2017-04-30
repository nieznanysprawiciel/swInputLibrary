#pragma once
/**
@file InputDispatcher.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swInputLibrary/InputCore/IInput.h"
#include "swInputLibrary/InputCore/Device.h"


namespace sw {
namespace input
{

/**@brief Provides input events in order of creation.
This class uses timestamp to sort events.*/
class InputDispatcher
{
public:

	struct DispatchedEvent
	{
		DeviceEvent		Event;
		Device*			ProducerDevice;

	// ================================ //
	//
		DispatchedEvent( Device* device, DeviceEvent evt )
			:	Event( evt )
			,	ProducerDevice( device )
		{}
	};

private:

	std::vector< KeyboardDeviceOPtr >&		m_keyboards;
	std::vector< MouseDeviceOPtr >&			m_mouses;
	std::vector< JoystickDeviceOPtr >&		m_joysticks;

	Timestamp			m_nextTimestamp;
	Timestamp			m_minTimestamp;

protected:
public:
	explicit		InputDispatcher		( IInput* input );
					~InputDispatcher	() = default;


	DispatchedEvent			NextEvent		();


	std::vector< KeyboardDeviceOPtr >&		GetKeyboards	() { return m_keyboards; }
	std::vector< MouseDeviceOPtr >&			GetMouses		() { return m_mouses; }
	std::vector< JoystickDeviceOPtr >&		GetJoysticks	() { return m_joysticks; }

private:


};


//====================================================================================//
//			Inline implementation	
//====================================================================================//


inline		InputDispatcher::InputDispatcher		( IInput* input )
	:	m_keyboards( input->GetKeyboardDevice() )
	,	m_mouses( input->GetMouseDevice() )
	,	m_joysticks( input->GetJoystickDevice() )
	,	m_nextTimestamp( 0 )
	,	m_minTimestamp( std::numeric_limits< Timestamp >::max() )
{

}

// ================================ //
//
inline InputDispatcher::DispatchedEvent		InputDispatcher::NextEvent()
{
	for( int i = 0; i < m_keyboards.size(); i++ )
	{
		if( m_keyboards[ i ]->GetEventsQueue().FrontEvent().LogicalTime == m_nextTimestamp )
		{

		}
	}


	assert( !"Implement me" );
	return InputDispatcher::DispatchedEvent( nullptr, KeyEvent() );
}

}	// input
}	// sw

