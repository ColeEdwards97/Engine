#pragma once
#include "InputConstants.h"

namespace Engine
{
	namespace InputConversion
	{
		const InputConstant RawToInputConstant(const int raw);
		const InputConstant KeyCodeToInputConstant(const KeyCode key);
		const InputConstant MouseButtonToInputConstant(const MouseButton button);
		const InputAxis MouseAxisToInputAxis(const MouseAxis axis);

		const KeyCode RawToKeyCode(const int raw);
		const MouseButton RawToMouseButton(const int raw);

		const int InputConstantToRaw(const InputConstant constant);
		const int KeyCodeToRaw(const KeyCode key);
		const int MouseButtonToRaw(const MouseButton button);
	}
}