#pragma once
/**
@file MouseDevice.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Device.h"

#include "MouseState.h"
#include "InputDeviceInfo.h"
#include "InputDeviceEvent.h"

#include <vector>


namespace sw {
namespace input
{


/**@brief Mouse state and events.

@ingroup Input*/
class MouseDevice : public Device
{
private:

	InputDeviceInfo		m_info;
	MouseState			m_state;

	std::vector< DeviceEvent >		m_events;

protected:
public:
	explicit		MouseDevice		() = default;
					~MouseDevice	() = default;


	const InputDeviceInfo&		GetInfo			() const	{ return m_info; }
	const MouseState&			GetState		() const	{ return m_state;  }


public:
	///@name Functions for setting state (only for IInput)
	///@{

	/**@brief Add event to event queue.
	This function doesn't change KeyboardState.*/
	void			AddEvent		( const DeviceEvent& event );
	void			AddEvent		( const ButtonEvent& event );
	void			AddEvent		( const AxisEvent& event );
	void			AddEvent		( const CursorEvent& event );

	///@}
};


DEFINE_OPTR_TYPE( MouseDevice );

}	// input
}	// sw


