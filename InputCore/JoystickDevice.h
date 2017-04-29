#pragma once
/**
@file JoystickDevice.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Device.h"

#include "JoystickState.h"
#include "InputDeviceInfo.h"
#include "InputDeviceEvent.h"

#include "EventQueue.h"

#include <vector>


namespace sw {
namespace input
{


/**@brief Joystick or other controller state and events.

@ingroup Input*/
class JoystickDevice : public Device
{
private:

	InputDeviceInfo		m_info;
	JoystickState		m_state;

	EventQueue< DeviceEvent >		m_events;

protected:
public:
	explicit		JoystickDevice		() = default;
					~JoystickDevice		() = default;


	const InputDeviceInfo&		GetInfo			() const { return m_info; }
	const JoystickState&		GetState		() const { return m_state; }

	void						ApplyAllEvents	();

	EventQueue< DeviceEvent >&		GetEventsQueue		()			{ return m_events; }
};

DEFINE_OPTR_TYPE( JoystickDevice );


//====================================================================================//
//			Inline implementation	
//====================================================================================//


// ================================ //
//
inline void			JoystickDevice::ApplyAllEvents	()
{
	while( !m_events.NoMoreEvents() )
	{
		auto& event = m_events.PopEvent();
		//m_state.ApplyEvent( event );
	}
}



}	// input
}	// sw


