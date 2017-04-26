#pragma once
/**
@file KeyboardDevice.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "KeyboardState.h"
#include "InputDeviceInfo.h"
#include "InputDeviceEvent.h"

#include <vector>


namespace sw {
namespace input
{


/**@brief Keyboard state and events.*/
class KeyboardDevice
{
private:

	InputDeviceInfo		m_info;
	KeyboardState		m_state;

	std::vector< KeyEvent >		m_events;

protected:
public:
	explicit		KeyboardDevice		() = default;
					~KeyboardDevice		() = default;


	const InputDeviceInfo&		GetInfo			() const { return m_info; }
};


}	// input
}	// sw

