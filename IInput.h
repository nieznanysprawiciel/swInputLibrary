#pragma once
/**
@file IInput.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "KeyboardState.h"
#include "MouseState.h"
#include "JoystickState.h"

#include "swInputLibrary/MouseDevice.h"
#include "swInputLibrary/KeyboardDevice.h"
#include "swInputLibrary/JoystickDevice.h"

#include "InputDeviceInfo.h"

#include <vector>

typedef void*	AppInstanceHandle;
typedef void*	WindowHandle;

namespace sw {
namespace input
{


/**@brief Initialization structure for input objects.

@ingroup Input*/
struct InputInitInfo
{
	AppInstanceHandle		AppInstance;
	WindowHandle			WndHandle;
};



/**@brief Interface for input classes for capturing user input.

@todo Uzupe³niæ interfejs i wydzieliæ modu³y obs³uguj¹ce konkretne implementacje
urz¹dzeñ wejœciowych.*/
class IInput
{
private:
protected:
public:
	virtual				~IInput() = 0 {};

	/**@brief Inicjalizuje ca³y modu³. Po wywo³aniu tej funkcji modu³ musi byæ gotowy do u¿ytku
	w innym przypadku powinien zwróciæ false.*/
	virtual bool										Init				( const InputInitInfo& initInfo ) = 0;

	virtual const std::vector< const KeyboardState* >&	GetKeyboardStates	() const = 0;
	virtual const std::vector< const MouseState* >&		GetMouseStates		() const = 0;
	virtual const std::vector< const JoystickState* >&	GetJoystickStates	() const = 0;

	virtual std::vector< KeyboardDeviceOPtr >&			GetKeyboardDevice	() = 0;
	virtual std::vector< MouseDeviceOPtr >&				GetMouseDevice		() = 0;
	virtual std::vector< JoystickDeviceOPtr >&			GetJoystickDevice	() = 0;

	virtual std::vector< const InputDeviceInfo* >		GetDevicesInfo		() const = 0;

	virtual void										Update				( float timeInterval ) = 0;

	/**@brief Funkcja na nowo sprawdza obecne w systemie urz¹dzenia i aktualizuje wszystkie
	potrzebne dane.*/
	virtual bool										UpdateDevices		() = 0;
};




}	// input
}	// sw

