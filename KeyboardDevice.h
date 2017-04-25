#pragma once
/**
@file KeyboardDevice.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "KeyboardState.h"
#include "InputDeviceInfo.h"


namespace sw
{

/**@brief */
class KeyboardDevice
{
private:

	InputDeviceInfo		m_info;
	KeyboardState		m_state;

protected:
public:
	explicit		KeyboardDevice		() = default;
					~KeyboardDevice	() = default;


	const InputDeviceInfo&		GetInfo			() const		{ return m_info; }
};



}	// sw

