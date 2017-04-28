/**
@file MouseDevice.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "MouseDevice.h"


namespace sw {
namespace input
{

// ================================ //
//
void			MouseDevice::AddEvent		( const DeviceEvent& event )
{
	m_events.push_back( event );
}

// ================================ //
//
void			MouseDevice::AddEvent		( const ButtonEvent& event )
{
	AddEvent( DeviceEvent( event ) );
}

// ================================ //
//
void			MouseDevice::AddEvent		( const AxisEvent& event )
{
	AddEvent( DeviceEvent( event ) );
}

// ================================ //
//
void			MouseDevice::AddEvent		( const CursorEvent& event )
{
	AddEvent( DeviceEvent( event ) );
}


}	// input
}	// sw
