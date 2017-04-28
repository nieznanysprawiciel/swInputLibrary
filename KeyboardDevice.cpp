/**
@file KeyboardDevice.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "KeyboardDevice.h"



namespace sw {
namespace input
{

// ================================ //
//
void			KeyboardDevice::AddEvent		( const KeyEvent& event )
{
	m_events.push_back( event );
}

// ================================ //
//
void			KeyboardDevice::AddEvent		( const CharacterEvent& event )
{
	m_characters.push_back( event );
}


}	// input
}	// sw
