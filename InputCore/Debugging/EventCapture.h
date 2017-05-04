#pragma once
/**
@file EventCapture.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swInputLibrary/InputCore/InputDeviceEvent.h"
#include "swInputLibrary/InputCore/EventQueue.h"

#include <vector>


namespace sw {
namespace input
{

/**@brief Event structure for debugging.
This structure holds additionally FrameNumber. This allows user to provide full set of input events
ordered by sending time.

@ingroup DebugInput*/
struct DebugEvent
{
	DeviceEvent			EventContent;
	Size				FrameNumber;
	uint8				DeviceIdx;
	DeviceEventType		DeviceType;
};



/**@brief This class provides functionality of capturing events for debug and test purposes.

@ingroup DebugInput*/
class EventCapture
{
private:

	EventQueue< DebugEvent >		m_events;

protected:
public:
	explicit		EventCapture		() = default;
					~EventCapture		() = default;

	void			QueueEvent			( const DeviceEvent& event, Size frameNum, DeviceEventType deviceType, uint8 deviceIdx = 0 );
	void			QueueEvent			( const DebugEvent& event );

	const DebugEvent&		QueryEvent	( Size frameNum );
	bool					IsNext		( Size frameNum );
};


}	// input
}	// sw


