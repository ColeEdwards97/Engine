#include "engpch.h"

#include "InputConversion.h"

namespace Engine
{
	namespace InputConversion
	{
		const InputConstant RawToInputConstant(const int raw) { return { static_cast<InputConstant>(raw) }; }
		const InputConstant KeyCodeToInputConstant(const KeyCode key) { return InputConstant{ static_cast<InputConstant>(key) }; }
		const InputConstant MouseButtonToInputConstant(const MouseButton button) { return InputConstant{ static_cast<InputConstant>(button) }; }
		const InputAxis MouseAxisToInputAxis(const MouseAxis axis) { return InputAxis{ static_cast<InputAxis>(axis) }; }

		const KeyCode RawToKeyCode(const int raw) { return KeyCode{ static_cast<KeyCode>(raw) }; }
		const MouseButton RawToMouseButton(const int raw) { return MouseButton{ static_cast<MouseButton>(raw) }; }

		const int InputConstantToRaw(const InputConstant constant) { return int{ static_cast<int>(constant) }; }
		const int KeyCodeToRaw(const KeyCode key) { return int{ static_cast<int>(key) }; }
		const int MouseButtonToRaw(const MouseButton button) { return int{ static_cast<int>(button) }; }
	}
}