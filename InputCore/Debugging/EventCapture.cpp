#include "EventCapture.h"
#include "EventCapture.h"
#include "EventCapture.h"
#include "EventCapture.h"
#include "EventCapture.h"
/**
@file EventCapture.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "EventCapture.h"


namespace sw {
namespace input
{




// ================================ //
//
EventCapture::EventCapture()
	:	m_nextTimeStamp( 0 )
	,	m_frameNumber( 0 )
{}

// ================================ //
//
void			EventCapture::QueueUpKeyEvent	( Keyboard::PhysicalKeys key )
{
	KeyState state;
	state.UnPress();

	QueueKeyEvent( state, key );
}

// ================================ //
//
void			EventCapture::QueueDownKeyEvent	( Keyboard::PhysicalKeys key )
{
	KeyState state;
	state.Press();

	QueueKeyEvent( state, key );
}

// ================================ //
//
void			EventCapture::QueueKeyEvent		( KeyState state, Keyboard::PhysicalKeys key )
{
	KeyEvent keyEvent;
	keyEvent.State = state;
	keyEvent.Key = key;

	DeviceEvent newEvent( keyEvent, m_nextTimeStamp++ );
	QueueEvent( newEvent, m_frameNumber, DeviceEventType::KeyboardEvent, 0 );
}

// ================================ //
//
void			EventCapture::QueueEvent		( const DeviceEvent& event, Size frameNum, DeviceEventType deviceType, uint8 deviceIdx )
{
	DebugEvent evt;
	memcpy( &evt.EventContent, &event, sizeof( event ) );
	evt.FrameNumber = frameNum;
	evt.DeviceType = deviceType;
	evt.DeviceIdx = deviceIdx;

	QueueEvent( evt );
}

// ================================ //
/// @todo Sort events.
void			EventCapture::QueueEvent		( const DebugEvent& event )
{
	m_events.AddEvent( event );
}

// ================================ //
/// @todo Don't ignore frameNum
const DebugEvent&	EventCapture::QueryEvent	( Size frameNum )
{
	if( !m_events.NoMoreEvents() )
	{
		return m_events.PopEvent();
	}

	DebugEvent evt;
	return evt;
}

// ================================ //
//
bool				EventCapture::IsNext		( Size frameNum )
{
	return m_events.FrontEvent().FrameNumber == frameNum;
}

// ================================ //
//
void				EventCapture::GoToNextFrame	()
{
	m_nextTimeStamp = 0;
	m_frameNumber++;
}

}	// input
}	// sw
