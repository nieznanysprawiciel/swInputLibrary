#pragma once
/**
@file MouseDevice.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "MouseState.h"
#include "InputDeviceInfo.h"
#include "InputDeviceEvent.h"

#include <vector>


namespace sw {
namespace input
{


/**@brief Mouse state and events.*/
class MouseDevice
{
private:

	InputDeviceInfo		m_info;
	MouseState			m_state;

	std::vector< DeviceEvent >		m_events;

protected:
public:
	explicit		MouseDevice		() = default;
					~MouseDevice	() = default;


	const InputDeviceInfo&		GetInfo			() const { return m_info; }
};


}	// input
}	// sw


