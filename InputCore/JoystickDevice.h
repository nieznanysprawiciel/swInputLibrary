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

	std::vector< DeviceEvent >		m_events;

protected:
public:
	explicit		JoystickDevice		() = default;
					~JoystickDevice		() = default;


	const InputDeviceInfo&		GetInfo			() const { return m_info; }
	const JoystickState&		GetState		() const { return m_state; }
};

DEFINE_OPTR_TYPE( JoystickDevice );


}	// input
}	// sw


